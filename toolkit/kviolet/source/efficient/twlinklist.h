#ifndef __KVIOLET__EFFICIENT__TWLINKLIST__H__
#define __KVIOLET__EFFICIENT__TWLINKLIST__H__

namespace kviolet {
namespace efficent {

typedef struct TWLinkList {
  TWLinkList* _next{nullptr};
  TWLinkList* _prev{nullptr};
} TWLinkList;

TWLinkList* InitializeHead(TWLinkList* node);

void DestroyNode(TWLinkList* entry);

void InsertBack(TWLinkList* head, TWLinkList* nnew);

void InsertFront(TWLinkList* head, TWLinkList* nnew);

void InsertTWLinkList(TWLinkList* nnew, TWLinkList* prev, TWLinkList* next);

}  // namespace efficent
}  // namespace kviolet

#endif  ///__KVIOLET__EFFICIENT__TWLINKLIST__H__
