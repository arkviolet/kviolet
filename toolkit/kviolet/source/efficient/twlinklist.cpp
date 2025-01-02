#include "twlinklist.h"

namespace kviolet {
namespace efficent {

TWLinkList* InitializeHead(TWLinkList* node) {
  node->_next = node->_prev = node;
  return node;
}

void DestroyNode(TWLinkList* entry) {
  entry->_prev->_next = entry->_next;
  entry->_next->_prev = entry->_prev;
}

void InsertBack(TWLinkList* head, TWLinkList* nnew) { InsertTWLinkList(nnew, head->_prev, head); }

void InsertFront(TWLinkList* head, TWLinkList* nnew) { InsertTWLinkList(nnew, head, head->_next); }

void InsertTWLinkList(TWLinkList* nnew, TWLinkList* prev, TWLinkList* next) {
  next->_prev = nnew;
  nnew->_next = next;

  prev->_next = nnew;
  nnew->_prev = prev;
}

}  // namespace efficent
}  // namespace kviolet
