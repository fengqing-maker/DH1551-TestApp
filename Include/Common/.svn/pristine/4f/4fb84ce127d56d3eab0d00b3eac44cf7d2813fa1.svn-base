/*
 * APSafeThread.h
 *
 *  Created on: 2012-11-10
 *      Author: hxc
 */

#ifndef APSAGETHREAD_H_
#define APSAGETHREAD_H_

#include "adi_typedef.h"
#include "APSemaphore.h"

class APSafeThread
{

public:

    APSafeThread ( unsigned int unPriority, unsigned int unStackSize, char acName[ ], unsigned int unNameLen );
    virtual ~APSafeThread ( );

public:

    static void ThreadFun ( void * pAPSafeThread );
    void GetThreadSatus ( char acName [ ], unsigned int unNameLen );

protected:

    void StartRun ( );
    unsigned int GetStackSize ( );

    void Exit ( );

    virtual void OnceProcess ( ) = 0;

private:

    int ThreadMain ( );
    void CreateThread ( APSafeThread * pAPSafeThread, ADI_HANDLE & hADIHandle );
    void DestroyThread ( ADI_HANDLE hADIHandle );

private:

    ADI_HANDLE m_hADIHandle;

    char m_acThreadName [ 256 ];

    APSemaphore m_APSemaphore;

    unsigned int m_unPriority;
    unsigned int m_unStackSize;

    unsigned int m_unExit;
    unsigned int m_unLastProcessTickCount;
	unsigned int m_unRun;

};

#endif /* APSAGETHREAD_H_ */
