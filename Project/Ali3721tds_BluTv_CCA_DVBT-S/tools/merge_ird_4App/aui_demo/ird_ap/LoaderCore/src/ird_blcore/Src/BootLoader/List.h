/**
 * @file List.h
 * A simple implementation of list. 
 */


#ifndef LIST_H__INCLUDED__
#define LIST_H__INCLUDED__


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _ListNode
{
    lc_uchar *pData;
    lc_uint32 dataLength;
    struct _ListNode *pNext;
}ListNode;

typedef struct _List
{
    lc_uint32 count;
    ListNode *pFirstNode;
    ListNode *pLastNode;
}List;



List *ListCreate(void);
ListNode *ListGetFirst(List *pList);
ListNode *ListGetNext(ListNode *pCurrent);
lc_result ListAppend(List *pList, lc_uchar *pData, lc_uint32 dataLength);
ListNode *ListFind(List *pList, lc_uchar *pData);
lc_result ListDestroy(List *pList, lc_bool flagFreeData);
lc_result ListDeleteNode(List *pList, ListNode *pNode, lc_bool flagFreeData);
lc_uint32 ListGetCount(List *pList);

#ifdef __cplusplus
}
#endif

#endif
