#ifndef __KVIOLET__EFFICIENT__INS__TWLINKLIST__H__
#define __KVIOLET__EFFICIENT__INS__TWLINKLIST__H__

#include "../common/common.h"
#include "twlinklist.h"

namespace kviolet {
namespace efficent {

template <class _Tp>
class INSTWLinkList {
 public:
  struct INSTWNode {
    _Tp _data;
    TWLinkList _linklist;  /// TODO TWLinkList _linklist; --> TWLinkList* _linklist;
    INSTWNode(int data) : _data(data) {}
  };

 public:
  explicit INSTWLinkList() {
    _head = new TWLinkList();
    _head = InitializeHead(_head);
  }

  ~INSTWLinkList() {
    auto iter = _head->_next;
    while (_head != iter) {
      auto* node = KVIOLET_CONTAINER_OF(iter, INSTWNode, _linklist);
      DestroyNode(iter);
      iter = iter->_next;
      delete node;
    }
    delete _head;
  }

 public:
  void PushBack(const int& value) {
    auto node = new INSTWNode(value);
    InsertBack(_head, &node->_linklist);
  }

  void PushFront(const int& value) {
    auto node = new INSTWNode(value);
    InsertFront(_head, &node->_linklist);
  }

  bool Empty() { return _head == _head->_next; }

  uint32_t Size() {
    uint32_t size = 0;
    auto iter = _head->_next;
    while (iter != _head) {
      iter = iter->_next;
      ++size;
    }

    return size;
  }

  void Remove(const _Tp& value) {
    auto iter = _head->_next;
    while (_head != iter) {
      auto* node = KVIOLET_CONTAINER_OF(iter, INSTWNode, _linklist);
      if (node->_data == value) {
        DestroyNode(iter);
        delete node;
        return;
      }
      iter = iter->_next;
    }
  }

  template <typename _Pre>
  void Remove(const _Pre& pr) {
    auto iter = _head->_next;
    while (_head != iter) {
      auto* node = KVIOLET_CONTAINER_OF(iter, INSTWNode, _linklist);
      if (pr(node->_data)) {
        DestroyNode(iter);
        iter = iter->_next;
        delete node;
      } else {
        iter = iter->_next;
      }
    }
  }

  template <typename _Pre>
  void Ergodic(const _Pre& pr) {
    auto iter = _head->_next;
    while (_head != iter) {
      auto* node = KVIOLET_CONTAINER_OF(iter, INSTWNode, _linklist);
      pr(node->_data);
      iter = iter->_next;
    }
  }

 private:
  TWLinkList* _head{nullptr};
};

}  // namespace efficent
}  // namespace kviolet

#endif  ///__KVIOLET__EFFICIENT__INS__TWLINKLIST__H__
