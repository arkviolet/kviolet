#ifndef __KVIOLET__EFFICIENT__STACK__H__
#define __KVIOLET__EFFICIENT__STACK__H__

#include <iostream>

namespace kviolet {
namespace efficent {

template <class _Tp>
class Stack {
 public:
  struct ListNode {
    ListNode *next;
    ListNode *prev;
  };

  struct StackNode {
    _Tp data;
    ListNode list;
  };

 public:
  Stack() {
    _head = new ListNode();
    _head->next = _head->prev = _head;
  }

  ~Stack() {
    while (Pop()) {
    }

    delete _head;
  }

  void Push(const _Tp &data) {
    auto ins = new StackNode();
    ins->data = data;

    {
      auto temp = _head->next;
      ins->list.next = temp;
      ins->list.prev = _head;

      _head->next = &(ins->list);
      temp->prev = &(ins->list);
    }
  }

  bool Pop(_Tp &data) {
    auto iter = _head->next;
    if (iter == _head) {
      return false;
    }

    auto ins = (StackNode *)((char *)iter - ((size_t)(&((StackNode *)0)->list)));
    data = std::move(ins->data);

    {
      auto temp = iter->next;
      _head->next = temp;
      temp->prev = _head;
    }
    delete ins;

    return true;
  }

  bool Pop() {
    auto iter = _head->next;
    if (iter == _head) {
      return false;
    }

    auto ins = (StackNode *)((char *)iter - ((size_t)(&((StackNode *)0)->list)));
    {
      auto temp = iter->next;
      _head->next = temp;
      temp->prev = _head;
    }
    delete ins;

    return true;
  }

 private:
  ListNode *_head;
};

}  // namespace efficent
}  // namespace kviolet

#endif  ///__KVIOLET__EFFICIENT__STACK__H__
