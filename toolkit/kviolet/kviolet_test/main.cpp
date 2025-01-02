#include "../source/kviolet.h"

using namespace kviolet::kpoll;
using namespace kviolet::timer;
using namespace kviolet::efficent;
using namespace kviolet::utilities;
using namespace kviolet::container;
using namespace kviolet::message_queue;
using namespace kviolet::module;
using namespace kviolet::system;

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
    list.Remove([&](const int& value) { return value == a; });

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
    lock_map.ForEach([](int key, int value) { std::cout << "key:" << key << ",value:" << value << std::endl; });

    lock_map.Remove(1);
    lock_map.RemoveIf([](const auto& item) { return item.first == 4; });

    std::cout << std::endl;
    lock_map.ForEach([](int key, int value) { std::cout << "key:" << key << ",value:" << value << std::endl; });
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
  Dispatcher::RegisterHandler([&](const std::shared_ptr<Message>& msg) {
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

void test_efficent() {
  /// ringbuffer
  {}

  /// queue
  {
    Queue<std::string> queue_test;

    std::cout << " Queue Push " << std::endl;
    queue_test.Push("this");
    queue_test.Push("is");
    queue_test.Push("just");
    queue_test.Push("test");
    queue_test.Push("data");

    std::cout << " Queue Pop " << std::endl;
    std::string value;
    while (queue_test.Pop(value)) {
      std::cout << value << std::endl;
    }
  }

  /// stack
  {
    Stack<std::string> stack_test;

    std::cout << " Stack Push " << std::endl;
    stack_test.Push("this");
    stack_test.Push("is");
    stack_test.Push("just");
    stack_test.Push("test");
    stack_test.Push("data");

    std::cout << " Stack Pop " << std::endl;
    std::string value;
    while (stack_test.Pop(value)) {
      std::cout << value << std::endl;
    }
  }

  /// list
  {
    INSTWLinkList<int> list_test;

    int a[] = {1, 1, 2, 6, 6, 3, 4, 5};
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
      list_test.PushBack(a[i]);
    }

    std::cout << "Ergodic" << std::endl;
    list_test.Ergodic([](const int& value) { std::cout << value << " "; });
    std::cout << std::endl;

    std::cout << "Remove 1" << std::endl;
    list_test.Remove(1);
    list_test.Ergodic([](const int& value) { std::cout << value << " "; });
    std::cout << std::endl;

    std::cout << "Remove pr" << std::endl;
    list_test.Remove([](const int& value) { return 6 == value; });
    list_test.Ergodic([](const int& value) { std::cout << value << " "; });
    std::cout << std::endl;

    std::cout << "size:" << list_test.Size() << std::endl;
  }
}

class SingletonTest {
 public:
  SingletonTest() { std::cout << "SingletonTest()" << std::endl; }
  ~SingletonTest() { std::cout << "~SingletonTest()" << std::endl; }

 public:
  void Test() { std::cout << "Test()" << std::endl; }
};

class SingletonInterfaceTest : public SingletonInterface {
 public:
  virtual void Handle(void* in, void* out) override { std::cout << "SingletonInterfaceTest" << std::endl; }
};

class SingletonTestHandle final : public Singleton<SingletonTest> {};

void test_module() {
  { SingletonTestHandle::Instance().Test(); }

  {
    SingletonInterfaceTest InterfaceTest;
    SingletonInterface::Instance()->Handle(nullptr, nullptr);
  }
}

void test_system() {
  {
    std::cout << std::this_thread::get_id() << std::endl;
    std::cout << Process::ThreadID() << std::endl;
  }

  {
    std::cout << "<--thread name:" << Process::ThreadName() << std::endl;

    Process::ThreadName("test");

    std::cout << "--> thread name:" << Process::ThreadName() << std::endl;

    std::cout << "max priority:" << Process::MaxThreadPriority() << std::endl;
  }

  {
    const char* argv[] = {"/usr/bin/sleep", "10", nullptr};
    auto pid = Process::Fork(argv);

    std::cout << Process::WaitPid(pid, true) << std::endl;

    pid = Process::Fork(argv);
    for (int i = 0; i < 12; ++i) {
      std::cout << Process::WaitPid(pid, false) << std::endl;
      sleep(1);
    }
  }
}

void test_plug() {
  auto handle = kviolet::module::LoadDriver(
      "/home/i/workspace/kviolet/kviolet/build_x86_64/kviolet_test/"
      "libtest_generic_plug.so",
      "PlugInstance");

  if (handle) {
    handle->Initialize(kviolet::module::PlugBaseInfo());
    handle->Start();
    handle->Stop();
    handle->Destroy();

    handle = nullptr;
  }
}

void test_serialize() {
  std::string str;
  {
    Serialize serialize(128);
#if defined(__GNUC__) && (__GNUC__ >= 6)
    serialize.SerializePack(1, 2, 3, 4, 5, "hello word", 6, 7, 8, 9, 10);
#else
    serialize << 1 << 2 << 3 << 4 << 5 << "hello word" << 6 << 7 << 8 << 9 << 10;
#endif
    str = std::move(std::string(serialize.Str(), serialize.Size()));
  }

  {
    Deserialize deserialize(str.c_str());
    int i1, i2, i3, i4;
    std::string str1;
    int i5, i6, i7, i8, i9, i10;
#if defined(__GNUC__) && (__GNUC__ >= 6)
    deserialize.DeserializePack(i1, i2, i3, i4, i5, str1, i6, i7, i8, i9, i10);
#else
    deserialize >> i1 >> i2 >> i3 >> i4 >> i5 >> str1 >> i6 >> i7 >> i8 >> i9 >> i10;
#endif
    if (str.size() != deserialize.Offset()) {
      std::cout << "deserialize error" << std::endl;
    }

    std::cout << i1 << " " << i2 << " " << i3 << " " << i4 << " " << str1 << " " << i5 << " " << i6 << " " << i7 << " " << i8
              << " " << i9 << " " << i10 << std::endl;
  }

  {
    Serialize message(128);
#if defined(__GNUC__) && (__GNUC__ >= 6)
    message.SerializePack(1, 2, 3, 4, 5, "hello word", 6, 7, 8, 9, 10);
#endif
    message << 1 << 2 << 3 << 4 << 5 << "hello word" << 6 << 7 << 8 << 9 << 10;
  }
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  test_serialize();

  test_plug();

  test_system();

  test_module();

  test_efficent();

  test_message_queue();

  test_container();

  test_timer();

  test_pool();

  return 0;
}
