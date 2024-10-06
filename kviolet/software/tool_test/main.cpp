#include "../../kviolet/kviolet.h"
#include "../../kviolet_enckit/kviolet_enckit.h"

using namespace kviolet::enckit;
using namespace kviolet::kpoll;
using namespace kviolet::timer;
using namespace kviolet::utilities;
using namespace kviolet::container;
using namespace kviolet::message_queue;

void test_fmt() {
  fmt::print("Hello, world!\n");
  auto str = fmt::format("The answer is {}.", 42);
  std::cout << "str:" << str << std::endl;

  fmt::print("Date and time: {}\n", std::chrono::system_clock::now());
  fmt::print("Time: {:%H:%M}\n", std::chrono::system_clock::now());

  std::vector<int> v = {1, 2, 3};
  fmt::print("{}\n", v);
}

void test_container() {
  /// event
  {
    LockEvent lock_event;

    std::thread([&]() {
      sleep(3);
      std::cout << " notify " << std::endl;
      lock_event.Notify(true);
    }).detach();

    std::thread([&]() {
      lock_event.Join();
      std::cout << " Join1 " << std::endl;
    }).detach();

    std::thread([&]() {
      lock_event.Join();
      std::cout << " Join2 " << std::endl;
    }).detach();

    std::cout << lock_event.Join(6000) << std::endl;
  }

  /// list
  {
    LockList<int> list;

    int a = 10;

    list.PushBack(1);
    list.PushBack(2);
    list.EmplaceBack(3);
    list.EmplaceBack(a);
    list.EmplaceBack(10);
    list.EmplaceBack(3);
    list.EmplaceBack(a);
    list.EmplaceBack(4);

    std::cout << std::endl;
    std::cout << list.Size() << std::endl;
    std::cout << list.Front() << std::endl;
    std::cout << list.Empty() << std::endl;

    list.PopFront();

    list.ForEach([](int i) { std::cout << i << std::endl; });

    list.Remove(1);
    list.Remove([&](const int &value) { return value == a; });

    list.ForEach([](int i) { std::cout << i << std::endl; });

    std::cout << std::endl;
  }

  /// LockMap
  {
    LockMap<int, int> lock_map;
    lock_map.Insert(std::make_pair(1, 1));
    lock_map.Insert(std::make_pair(2, 3));
    lock_map.Insert(std::make_pair(3, 3));
    lock_map.Insert(std::make_pair(4, 4));

    std::cout << std::endl;
    lock_map.ForEach(
        [](int key, int value) { std::cout << "key:" << key << ",value:" << value << std::endl; });

    lock_map.Remove(1);
    lock_map.RemoveIf([](const auto &item) { return item.first == 4; });

    std::cout << std::endl;
    lock_map.ForEach(
        [](int key, int value) { std::cout << "key:" << key << ",value:" << value << std::endl; });
  }
}

void test_audio() {
  /// pulseaudio
  {
    int volume = 50;
    std::string audio_path = "./test.wav";
    auto taskid = std::to_string(Timestamp::MonotonicMilliseconds());
    auto pulseaudio = std::make_shared<PulseAudioManager>();
    pulseaudio->Play(taskid, audio_path, volume);
    pulseaudio->Pause(taskid);
    pulseaudio->Resume(taskid);
    pulseaudio->Cancel();
    pulseaudio = nullptr;
  }

  /// gst audio
  {
    int volume = 50;
    std::string audio_path = "./test.wav";  ///*.wav *.mp3
    auto taskid = std::to_string(Timestamp::MonotonicMilliseconds());
    auto gst = std::make_shared<GstAudioManager>();
    gst->Play(taskid, audio_path, volume);
    gst->Pause(taskid);
    gst->Resume(taskid);
    gst->Cancel();
    gst = nullptr;
  }
}

void test_timer() {
  TimerManager timer_manager;
  timer_manager.Start(
      []() {
        auto current = Timestamp::MonotonicMilliseconds();
        std::cout << "current time:" << current << std::endl;
      },
      -1, 1 * 1000);
}

void test_pool() {
  /// thread poll
  {
    ThreadPool thread_poll;
    thread_poll.Commit([]() { std::cout << "task1" << std::endl; });
    thread_poll.Commit([]() { std::cout << "task2" << std::endl; });
    thread_poll.Commit([]() { std::cout << "task3" << std::endl; });
  }
}

class TestMessage : public Message {
 public:
  int i;
  int j;
};

void test_message_queue() {
  Dispatcher::RegisterHandler([&](const std::shared_ptr<Message> &msg) {
    auto m = std::dynamic_pointer_cast<TestMessage>(msg);
    std::cout << m->i << std::endl;
    std::cout << m->j << std::endl;
  });

  for (int i = 0; i < 100; ++i) {
    auto msg = std::make_shared<TestMessage>();
    msg->i = msg->j = i;
    Dispatcher::Send(msg);
    sleep(1);
  }
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  test_message_queue();

  test_fmt();

  test_container();

  test_audio();

  test_timer();

  test_pool();

  /// ringbuffer
  {
  }

  /// message queue
  {
  }

  /// grpc
  {
  }

  /// dbus
  {
  }

  return 0;
}
