#include "message_queue.h"

#include "../utilities/timestamp.h"

namespace kviolet {

std::shared_ptr<Message> MessageQueue::Next() {
  int64_t nextPollTimeoutMillis = 0;
  for (;;) {
    auto now = timestamp::Timestamp::MonotonicMilliseconds();

    {
      std::lock_guard<std::recursive_mutex> lk(*list_.get_mutex());
      if (quit_) {
        Clean();
        return nullptr;
      }

      if (list_.empty()) {
        nextPollTimeoutMillis = 1000;
      } else {
        std::shared_ptr<Message> message = list_.front();
        if (now < message->When()) {
          nextPollTimeoutMillis = (message->When() - now);
        } else {
          list_.pop_front();
          return message;
        }
      }
    }

    if (nextPollTimeoutMillis == 0) {
      nextPollTimeoutMillis = 1;
    }

    event_.Join(nextPollTimeoutMillis);
  }

  return nullptr;
}

bool MessageQueue::EnqueueMessage(const std::shared_ptr<Message> &message,
                                  uint64_t when) {
  if (when != 0) {
    when += timestamp::Timestamp::MonotonicMilliseconds();
  }

  message->SetWhen(when);

  {
    std::lock_guard<std::recursive_mutex> lk(*list_.get_mutex());
    if (quit_) {
      return false;
    }

    if (list_.empty()) {
      list_.push_back(message);
    } else if ((when == 0) && (list_.front()->When() == 0)) {
      decltype(list_)::iterator it;
      for (it = list_.begin(); it != list_.end(); ++it) {
        if (it->get()->When() != 0) {
          break;
        }
      }

      list_.insert(it, message);
    } else {
      decltype(list_)::iterator it;
      for (it = list_.begin(); it != list_.end(); ++it) {
        if (it->get()->When() > when) {
          break;
        }
      }

      list_.insert(it, message);
    }
  }

  event_.Notify();

  return true;
}

void MessageQueue::Clean() { list_.clear(); }

void MessageQueue::Quit() {
  quit_ = true;
  event_.Notify();
}

void MessageQueue::Dump() {
  std::cout << "Dump:" << std::endl;
  list_.for_each([](const std::shared_ptr<Message> &message) {
    std::cout << "message: " << message->When() << std::endl;
  });

  std::cout << std::endl;
}
}  // namespace kviolet