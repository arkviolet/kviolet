#include "manager.h"

#include "../common/define.h"
#include "../utilities/timestamp.h"

namespace kviolet {
namespace timer {

using namespace kviolet::utilities;

class InstanceTimerEvent : public ITimerEvent {
 public:
  explicit InstanceTimerEvent(std::function<void()> function) : _function(std::move(function)) {}

  virtual ~InstanceTimerEvent() override = default;

 public:
  void OnPause() override {}
  void OnResume() override {}
  void OnTrigger() override {
    if (_function) {
      _function();
    }
  }
  void OnStop(bool forced) override { (void)forced; }

 private:
  std::function<void()> _function{};
};

///////////////////////////////////////////////////////

TimerManager::TimerManager() {
  _tickTime = 0;
  _lastTime = Timestamp::MonotonicMilliseconds();
  _thread = std::move(std::thread(&TimerManager::DriverThread, this));
}

TimerManager::~TimerManager() {
  Stop();

  if (_thread.joinable()) {
    _thread.join();
  }

  _nearList->clear();

  for (auto& iter : _wheelList) {
    for (auto& it : iter) {
      ClearSpokes(it);
    }
  }
}

void TimerManager::Stop() {
  _running = false;
}

void TimerManager::Destroy(const std::shared_ptr<ITimerEvent>& event) {
  auto find = _manager.find(event);
  if (find != _manager.end()) {
    find->second->Destroy();
  }
}

bool TimerManager::Pause(const std::shared_ptr<ITimerEvent>& event) {
  auto find = _normal.find(event);
  if (_normal.end() == find) {
    return false;
  }

  find->second->Pause(_tickTime);

  _normal.erase(find);

  _normal.insert(std::make_pair(event, find->second));

  return true;
}

bool TimerManager::Resume(const std::shared_ptr<ITimerEvent>& event) {
  auto find = _pause.find(event);
  if (_pause.end() == find) {
    return false;
  }

  find->second->Resume(_tickTime);

  AddNode(find->second);

  _pause.erase(find);
  _normal.insert(std::make_pair(event, find->second));

  return true;
}

bool TimerManager::Start(const std::shared_ptr<ITimerEvent>& event, int64_t count, std::time_t interval) {
  if (_manager.end() != _manager.find(event)) {
    return false;
  }

  auto node = std::make_shared<TimerNode>(event, count, interval + _tickTime, interval);

  AddNode(node);

  _manager.insert(std::make_pair(event, node));
  _normal.insert(std::make_pair(event, node));

  return true;
}

bool TimerManager::Start(std::function<void()> function, int64_t count, std::time_t interval) {
  auto event = std::make_shared<InstanceTimerEvent>(std::move(function));

  if (_manager.end() == _manager.find(event)) {
    auto node = std::make_shared<TimerNode>(event, count, interval + _tickTime, interval);

    AddNode(node);

    _manager.insert(std::make_pair(event, node));

    _normal.insert(std::make_pair(event, node));

    return true;
  } else {
    return false;
  }
}

/**
 * 提高精度可采用 timefd + select/epool
 */
void TimerManager::DriverThread() {
  while (_running) {
    KVIOLET_THIS_THREAD_SLEEP_MS(2);

    Update();
  }
}

void TimerManager::Update() {
  auto now = Timestamp::MonotonicMilliseconds();

  auto ticks = now - _lastTime;

  _lastTime = now;

  for (uint64_t i = 0; i < ticks; ++i) {
    Executes();
  }
}

void TimerManager::Executes() {
  auto index = _tickTime & ((1 << TIMER_NEAR_BITS) - 1);

  if (index == 0) {
    if (Cascade(0, (std::size_t)(_tickTime >> (TIMER_NEAR_BITS + 0 * TIMER_WHEEL_BITS)) & ((1 << TIMER_WHEEL_BITS) - 1)) &&
        Cascade(1, (std::size_t)(_tickTime >> (TIMER_NEAR_BITS + 1 * TIMER_WHEEL_BITS)) & ((1 << TIMER_WHEEL_BITS) - 1)) &&
        Cascade(2, (std::size_t)(_tickTime >> (TIMER_NEAR_BITS + 2 * TIMER_WHEEL_BITS)) & ((1 << TIMER_WHEEL_BITS) - 1))) {
      Cascade(3, (std::size_t)(_tickTime >> (TIMER_NEAR_BITS + 3 * TIMER_WHEEL_BITS)) & ((1 << TIMER_WHEEL_BITS) - 1));
    }
  }

  ++_tickTime;

  std::vector<std::shared_ptr<TimerNode>> spokesList;

  _nearList[index].swap(spokesList);

  for (auto& node : spokesList) {
    if (node->IsValid()) {
      if (node->IsPause()) {
      } else {
        node->Trigger();

        node->RevisedExpire(_tickTime);

        AddNode(node);
      }
    } else {
      _pause.erase(node->Event());
      _normal.erase(node->Event());
      _manager.erase(node->Event());
    }
  }
}

void TimerManager::AddNode(std::shared_ptr<TimerNode>& node) {
  std::lock_guard<std::mutex> lock(_lock);

  auto expire = node->Expire();

  auto offset = (uint64_t)(expire - _tickTime);

  if (offset < (1 << TIMER_NEAR_BITS))  /// [0, 0x100)
  {
    auto index = expire & ((1 << TIMER_NEAR_BITS) - 1);

    _nearList[index].push_back(node);
  } else if (offset < (1 << (TIMER_NEAR_BITS + TIMER_WHEEL_BITS)))  /// [0x100, 0x4000)
  {
    auto index = (expire >> TIMER_NEAR_BITS) & ((1 << TIMER_WHEEL_BITS) - 1);

    _wheelList[0][index].push_back(node);
  } else if (offset < (1 << (TIMER_NEAR_BITS + 2 * TIMER_WHEEL_BITS)))  /// [0x4000, 0x100000)
  {
    auto index = (expire >> (TIMER_NEAR_BITS + TIMER_WHEEL_BITS)) & ((1 << TIMER_WHEEL_BITS) - 1);

    _wheelList[1][index].push_back(node);
  } else if (offset < (1 << (TIMER_NEAR_BITS + 3 * TIMER_WHEEL_BITS)))  /// [0x100000, 0x4000000)
  {
    auto index = (expire >> (TIMER_NEAR_BITS + 2 * TIMER_WHEEL_BITS)) & ((1 << TIMER_WHEEL_BITS) - 1);

    _wheelList[2][index].push_back(node);
  } else if ((int64_t)offset < 0) {
    auto index = _tickTime & ((1 << TIMER_NEAR_BITS) - 1);

    _nearList[index].push_back(node);
  } else if (offset <= 0xffffffffUL) {
    auto index = (expire >> (TIMER_NEAR_BITS + 3 * TIMER_WHEEL_BITS)) & ((1 << TIMER_WHEEL_BITS) - 1);

    _wheelList[3][index].push_back(node);
  } else {
    throw std::runtime_error("The timing interval exceeds the maximum limit");
  }
}

void TimerManager::ClearSpokes(std::vector<std::shared_ptr<TimerNode>>& spokesList) {
  std::vector<std::shared_ptr<TimerNode>>().swap(spokesList);
}

/// 转动时间轮
bool TimerManager::Cascade(std::size_t wheel, std::size_t index) {
  std::vector<std::shared_ptr<TimerNode>> spokesList{};

  _wheelList[wheel][index].swap(spokesList);

  for (auto& iter : spokesList) {
    AddNode(iter);
  }

  return index == 0;
}

}  // namespace timer
}  // namespace kviolet
