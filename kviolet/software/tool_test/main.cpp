#include "../../kviolet/kviolet.h"

using namespace kviolet::kpoll;
using namespace kviolet::timer;
using namespace kviolet::efficent;
using namespace kviolet::utilities;
using namespace kviolet::container;
using namespace kviolet::message_queue;

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

void test_twlinklist() {
  INSTWLinkList<int> list_test;

  int a[] = {1, 1, 2, 6, 6, 3, 4, 5};
  for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
    list_test.PushBack(a[i]);
  }

  std::cout << "Ergodic" << std::endl;
  list_test.Ergodic([](const int &value) { std::cout << value << " "; });
  std::cout << std::endl;

  std::cout << "Remove 1" << std::endl;
  list_test.Remove(1);
  list_test.Ergodic([](const int &value) { std::cout << value << " "; });
  std::cout << std::endl;

  std::cout << "Remove pr" << std::endl;
  list_test.Remove([](const int &value) { return 6 == value; });
  list_test.Ergodic([](const int &value) { std::cout << value << " "; });
  std::cout << std::endl;

  std::cout << "size:" << list_test.Size() << std::endl;
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  test_twlinklist();

  return 0;

  std::list<int> x;
  x.push_back(1);
  x.push_back(2);
  x.push_back(3);
  x.push_back(4);

  for (auto &iter : x) {
    std::cout << iter << " ";
  }
  std::cout << std::endl;

  return 0;
  test_message_queue();

  test_container();

  test_timer();

  test_pool();

  /// ringbuffer
  {
  }

  return 0;
}
