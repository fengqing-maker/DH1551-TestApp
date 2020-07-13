#ifndef APMessageQueue_H
#define APMessageQueue_H

#include "adi_typedef.h"

#include <list>
using std::list;

class APMessageQueue
{

public:

    APMessageQueue ( const char* pstrName, int nMaxMsgs, int nMaxMsgLen, unsigned int unOptions );
    ~APMessageQueue ( );

public:

    unsigned int APReceiveMsgQueue ( void * pvMsg, int nMaxMsgBytes, unsigned int unTimeout );
    unsigned int APSendMsgQueue ( const void * pvMsg, int nMsgBytes, unsigned int unTimeout );
    unsigned int APGetNumMsgsMsgQueue ( );

private:

    char m_acMSGQName [ 256 ];

    int m_nMaxMsgs;
    int m_nMaxMsgLen;
    unsigned int m_unOptions;

    list< void * > m_MsgFreeList;
    list< void * > m_MsgDBList;

    ADI_HANDLE m_hSafeMutex;

    ADI_HANDLE m_hDBSemaphore;
    ADI_HANDLE m_hFreeSemaphore;

    unsigned char * m_pbDataBuf;

private:

    unsigned int AddTailMsg ( void * pvMsg, list< void * > & msgList );
    unsigned int RemoveHeadMsg ( void *& pvMsg, list < void * > & msgList );

};

#endif /* APMessageQueue_H */
