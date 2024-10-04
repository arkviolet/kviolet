#include "twlinklist.h"

namespace kviolet {
namespace efficent {

void InsertTWLinkList(TWLinkList* nnew, TWLinkList* prev, TWLinkList* next) {
  next->_prev = nnew;
  nnew->_next = next;

  prev->_next = nnew;
  nnew->_prev = prev;
}

void InitHeadTWLinkList(TWLinkList* head) {
  head->_next = head->_prev = head;
}

bool IsTWLinkList(TWLinkList* head) {
  return (head == head->_next);
}

void AddTWLinkListHead(TWLinkList* head, TWLinkList* nnew) {
  InsertTWLinkList(nnew, head, head->_next);
}

void AddTWLinkListTail(TWLinkList* head, TWLinkList* nnew) {
  InsertTWLinkList(nnew, head->_prev, head);
}

void DelTWLinkListNode(TWLinkList* entry) {
  entry->_prev->_next = entry->_next;
  entry->_next->_prev = entry->_prev;
}

}  // namespace efficent
}  // namespace kviolet
