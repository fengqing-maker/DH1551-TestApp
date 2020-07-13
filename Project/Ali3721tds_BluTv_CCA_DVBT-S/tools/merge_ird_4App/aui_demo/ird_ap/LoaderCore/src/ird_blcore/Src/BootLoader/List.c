
/******************************************************************************
 *                    COPYRIGHT (C) 2011 IRDETO B.V.                          *
 ******************************************************************************
 * FILENAME   : List.c                                                        *
 *                                                                            *
 * DESCRIPTION: A simple implementation of List.                              *
 *                                                                            *
 ******************************************************************************/


#include "../Shared/LoaderCorePrivate.h"
#include "List.h"


List *ListCreate(void)
{
    List *pList = (List *)LC_MALLOC(sizeof(List));
    //LC_memset(pList,0,sizeof(List));
    pList->count = 0;
    pList->pFirstNode = LC_NULL;
    pList->pLastNode = LC_NULL;

    return pList;
}

ListNode *ListGetFirst(List *pList)
{
    ListNode *node = LC_NULL;
    if( LC_NULL != pList )
    {
        node = pList->pFirstNode;
    }

    return node;
}

ListNode *ListGetNext(ListNode *pCurrent)
{
    ListNode *node = LC_NULL;

    if( LC_NULL != pCurrent )
    {
        node = pCurrent->pNext;
    }

    return node;
}

/*Create a new pNode and append it to the end.*/
lc_result ListAppend(List *pList, lc_uchar *pData, lc_uint32 dataLength)
{
    ListNode *pNode = LC_NULL;
    lc_result result = LC_SUCCESS;

    if( LC_NULL == pList )
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if( LC_SUCCESS == result )
    {
        pNode = (ListNode *)LC_MALLOC(sizeof(ListNode));
        if( LC_NULL == pNode )
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
        else
        {
            /* init the result */
            result = LC_FAILURE;
            pNode->pNext = LC_NULL;
            pNode->dataLength = dataLength;            
            /*In case of a data node, we will need to allocate a buffer to hold the data.*/
            if(0 != dataLength )
            {
                pNode->pData = (lc_uchar *)LC_MALLOC(dataLength);
                if(LC_NULL != pNode->pData)
                {
                    /*Copy the data.*/
                    LC_memcpy(pNode->pData, pData, dataLength);

                    if(0 == pList->count)
                    {
                        /*No pNode in the pList.*/
                        pList->pFirstNode = pNode;
                        pList->pLastNode = pNode;
                        ++pList->count;
                        result = LC_SUCCESS;
                    }
                    else if( 1 <= pList->count )
                    {
                        /*More than one pNode in the pList.*/
                        if(pList->pLastNode)
                        {
                            pList->pLastNode->pNext = pNode;
                            pList->pLastNode = pNode;
                            ++pList->count;
                            result = LC_SUCCESS;
                        }
                        else
                        {
                            libc_printf("++++fatal error,bug again: pList->count = %u,pList->pFirstNode = 0x%x, pList->pLastNode = 0x%x\n",
                                pList->count,pList->pFirstNode,pList->pLastNode);
                        }
                    }
                }
            }
#if 0
            else
            {
                pNode->pData = pData;
            }
            
            if(0 == pList->count)
            {
                /*No pNode in the pList.*/
                pList->pFirstNode = pNode;
                pList->pLastNode = pNode;
                ++pList->count;
                result = LC_SUCCESS;
            }
            else if( 1 <= pList->count )
            {
                /*More than one pNode in the pList.*/
                if(pList->pLastNode)
                {
                    pList->pLastNode->pNext = pNode;
                    pList->pLastNode = pNode;
                    ++pList->count;
                    result = LC_SUCCESS;
                }
                else
                {
                    libc_printf("++++fatal error,bug again: pList->count = %u,pList->pFirstNode = 0x%x, pList->pLastNode = 0x%x\n",
                        pList->count,pList->pFirstNode,pList->pLastNode);
                }
            }
#endif
        }
    }

    return result;
}

lc_result ListDestroy(List *pList, lc_bool flagFreeData)
{
    ListNode *pNode = LC_NULL;
    ListNode *pCurrentNode = LC_NULL;
    lc_result result = LC_SUCCESS;

    if( LC_NULL == pList )
    {
        result = LC_ERROR_NULL_PARAM;
    }

    if( LC_SUCCESS == result )
    {
        pNode = pList->pFirstNode;
        while( LC_NULL != pNode )
        {
            pCurrentNode = pNode;
            pNode = pNode->pNext;
        
            /*Time to free the memory.*/
            if( flagFreeData)
            {
                LC_Free_Memory((void **)&pCurrentNode->pData);
            }
        
            LC_Free_Memory((void **)&pCurrentNode);
            
            /*Descrement the count.*/
            --pList->count;
        }
        
        /*Free myself now.*/
        LC_Free_Memory((void **)&pList);
    }

    return result;
}

/*Delete the pNode and at the same time keep the link.*/
lc_result ListDeleteNode(List *pList, ListNode *pNode, lc_bool flagFreeData)
{
    ListNode *pCurrentNode = LC_NULL;
    lc_result result = LC_SUCCESS;

    if(( LC_NULL == pList ) || ( LC_NULL == pNode ))
    {
        result = LC_ERROR_NULL_PARAM;
    }
    else
    {
        if( 0 == pList->count )
        {
            result = LC_ERROR_INVALID_PARAMETER;
        }
    }

    if( LC_SUCCESS == result )
    {
        /**
         * Set result to a value not equal to LC_SUCCESS. 
         * LC_SUCCESS means that we have found the node successfully!
         */
        result = LC_ERROR_INVALID_PARAMETER;
        /*Check whether it is the first node.*/
        if( pNode == pList->pFirstNode)
        {
            /*It is the first node.*/

            if( pNode == pList->pLastNode )
            {
                /*It is also the last node.*/
                pList->pLastNode = LC_NULL;
            }

            /*Move to the next node.*/
            pList->pFirstNode = pList->pFirstNode->pNext;

            /*Set the flag to indicate that we have found the node.*/
            result = LC_SUCCESS;
        }
        else
        {
            /*It is NOT the first node, go through the list.*/
            pCurrentNode = pList->pFirstNode;
            
            while(LC_NULL != pCurrentNode)
            {
                if(LC_NULL == pCurrentNode->pNext)
                {
                    /*We have reached the end of this list.*/
                    break;
                }
                else
                {
                    if( pNode == pCurrentNode->pNext )
                    {
                        /*We have found the correct node.*/
                        /*It is the last node.*/
                        if( pNode == pList->pLastNode )
                        {
                            pList->pLastNode = pCurrentNode;
                        }

                        /*Skip it and keep the link.*/
                        pCurrentNode->pNext = pCurrentNode->pNext->pNext;

                        /*Set the flag to indicate that we have found the node.*/
                        result = LC_SUCCESS;

                        break;
                    }
                }

                /*Move to next one.*/
                pCurrentNode = pCurrentNode->pNext;
            }
        }
    }

    if( LC_SUCCESS == result )
    {
        /*Time to free the memory.*/
        if(( LC_NULL != pNode ) && ( flagFreeData))
        {
            LC_Free_Memory((void **)&pNode->pData);
        }
        
        if( LC_NULL != pNode )
        {
            LC_Free_Memory((void **)&pNode);
        }
        
        /*Descrement the count.*/
        --pList->count;
    }

    return LC_SUCCESS;
}

lc_uint32 ListGetCount(List *pList)
{
    lc_uint32 count = 0;
    if( LC_NULL != pList )
    {
        count = pList->count;
    }

    return count;
}

ListNode *ListFind(List *pList, lc_uchar *pData)
{
    ListNode *pNode;
    
    pNode = ListGetFirst(pList);
    while(LC_NULL != pNode)
    {
        if( pData == pNode->pData )
        {
            break;
        }

        /*Get pNext  pNode.*/
        pNode = ListGetNext(pNode); 
    }

    return pNode;
}


