#ifndef __KVIOLET__EFFICIENT__TWLINKLIST__H__
#define __KVIOLET__EFFICIENT__TWLINKLIST__H__

namespace kviolet {
namespace efficent {

/**
 * 双向循环链表
 * */
typedef struct TWLinkList {
  TWLinkList* _next{nullptr};
  TWLinkList* _prev{nullptr};
} TWLinkList;

/**
 *  Init Head Node
 * */
void InitHeadTWLinkList(TWLinkList* head);

/**
 * Insert [head,head->next]
 * */
void AddTWLinkListHead(TWLinkList* head, TWLinkList* nnew);

/**
 * Insert [head->prev,head]
 * */
void AddTWLinkListTail(TWLinkList* head, TWLinkList* nnew);

/**
 * Is Empty
 * */
bool IsTWLinkList(TWLinkList* head);

/**
 * Delete LinkList Node
 * */
void DelTWLinkListNode(TWLinkList* entry);

}  // namespace efficent
}  // namespace kviolet

#endif  ///__KVIOLET__EFFICIENT__TWLINKLIST__H__