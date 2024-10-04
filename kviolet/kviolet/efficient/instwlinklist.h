#ifndef __KVIOLET__EFFICIENT__INS__TWLINKLIST__H__
#define __KVIOLET__EFFICIENT__INS__TWLINKLIST__H__

#include "../common/common.h"
#include "twlinklist.h"

namespace kviolet {
namespace efficent {
template <typename T>
class KVIOLET_CLASS_API INSTWLinkList {
 public:
  struct INSTWNode {
    T _data;
    TWLinkList* _linklist;
  };

 public:
  explicit INSTWLinkList() { _insHead = Creat(); }

  explicit INSTWLinkList(uint32_t size) {
    assert(size > 1);  ///???

    _insHead = Creat(size);
  }

  ~INSTWLinkList() {
    for (uint32_t i = 0; i < _size; ++i) {
      /// get current struct point
      auto* ins = KVIOLET_CONTAINER_OF(_insHead->_linklist, INSTWNode, _linklist);

      /// current struct point  -> next
      _insHead = KVIOLET_CONTAINER_OF(_insHead->_linklist->_next, INSTWNode, _linklist);

      delete ins;
    }
  }

 public:
  uint32_t GetInsLinkListSize() { return _size; }

  void AddInsLinkListTailNode(T* value) {
    assert(value);

    auto* temp = Creat();

    memcpy(&temp->_data, value, sizeof(T));

    AddTWLinkListTail(_insHead->_linklist, temp->_linklist);
  }

  void AddInsLinkListHeadNode(T* value) {
    assert(value);

    auto* temp = Creat();

    memcpy(&temp->_data, value, sizeof(T));

    AddInsLinkListHeadNode(_insHead->_linklist, temp->_linklist);
  }

  void ErgodicInsLinkList() {
    auto* head = _insHead;
    for (uint32_t i = 0; i < _size; ++i) {
      auto* ins = KVIOLET_CONTAINER_OF(head->_linklist, INSTWNode, _linklist);
      {
        /**
         * Option T
         * */
        (void)ins->_data;
      }
      head = KVIOLET_CONTAINER_OF(head->_linklist->_next, INSTWNode, _linklist);
    }
  }

 private:
  INSTWNode* Creat() {
    ++_size;

    auto* head = new INSTWNode();

    InitHeadTWLinkList(head->_linklist);

    return head;
  }

  INSTWNode* Creat(uint32_t size) {
    auto* head = Creat();

    for (int i = 0; i < size - 1; ++i) {
      auto* temp = Creat();

      AddTWLinkListTail(head->_linklist, temp->_linklist);
    }

    return head;
  }

 private:
  uint32_t _size{0};
  INSTWNode* _insHead{nullptr};
};

}  // namespace efficent
}  // namespace kviolet

#endif  ///__KVIOLET__EFFICIENT__INS__TWLINKLIST__H__
