#ifndef __KVIOLET__EFFICIENT__QUEUE__H__
#define __KVIOLET__EFFICIENT__QUEUE__H__

#include <iostream>

namespace kviolet {
namespace efficent {

template <class _Tp>
class Queue {
 public:
  struct ListNode {
    ListNode *next;
    ListNode *prev;
  };

  struct QueueNode {
    _Tp data;
    ListNode list;
  };

 public:
  Queue() {
    _head = new ListNode();
    _head->next = _head->prev = _head;
  }

  ~Queue() {
    while (Pop()) {
    }

    delete _head;
  }

  void Push(const _Tp &data) {
    auto ins = new QueueNode();
    ins->data = data;

    {
      auto temp = _head->next;
      _head->next = &ins->list;
      ins->list.prev = _head;

      temp->prev = &ins->list;
      ins->list.next = temp;
    }
  }

  bool Pop(_Tp &data) {
    auto iter = _head->prev;
    if (iter == _head) {
      return false;
    }

    auto ins = (QueueNode *)((char *)iter - ((size_t)(&((QueueNode *)0)->list)));
    data = std::move(ins->data);
    {
      auto temp = iter->prev;
      temp->next = _head;
      _head->prev = temp;
    }

    delete ins;

    return true;
  }

  bool Pop() {
    auto iter = _head->prev;
    if (iter == _head) {
      return false;
    }

    auto ins = (QueueNode *)((char *)iter - ((size_t)(&((QueueNode *)0)->list)));
    {
      auto temp = iter->prev;
      temp->next = _head;
      _head->prev = temp;
    }

    delete ins;

    return true;
  }

 private:
  ListNode *_head;
};

}  // namespace efficent
}  // namespace kviolet

#endif  ///__KVIOLET__EFFICIENT__QUEUE__H__
