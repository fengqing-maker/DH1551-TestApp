
#ifndef _ADI_OS_H_
#define _ADI_OS_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ADIOS_TIMEOUT_IMMEDIATE  		(0)		// 超时参数之立即超时选项

#define ADIOS_TIMEOUT_INFINITY   		(~0)	// 超时参数之永不超时选项

#define ADIOS_EVENT_AUTO_RESET		(1 << 0)	// ADIOSEventWait之后事件自动无效选项

#define ADIOS_EVENT_INITIAL_STATUS	(1 << 1)	// 初始化事件后立即有效选项

#define ADIOS_MUTEX_DEFAULT			(0)			// 创建互斥量时，使用默认选项

#define	ADIOS_MUTEX_OBTAIN			(1 << 0)	// 创建互斥量后立即获取到锁选项

#define ADIOS_THREAD_NAME_MAX_LEN    32

enum
{
	ADIOS_ERROR_BAD_PARAMETER = ADI_OS_ERROR_BASE,
	ADIOS_ERROR_FEATURE_NOT_SUPPORTED,
	ADIOS_ERROR_UNKNOWN_ERROR,
	ADIOS_ERROR_NO_MEMORY,
	ADIOS_ERROR_THREAD_BUSY

};

typedef struct
{
	unsigned int uThreadId;
	unsigned int uPriority;
	char szThreadName[ADIOS_THREAD_NAME_MAX_LEN];
}ADIOSThreadInfo_S;

typedef struct 
{
	int  m_nSecond;	
	int  m_nMiliSecond;
	long m_lUSecond;
}ADIOSTimeVal_S;


typedef struct
{
	unsigned int m_unYear_13         :13;
	unsigned int m_unMonth_8         :8;
	unsigned int m_unDay_8           :8;
	unsigned int m_unWeek_3          :3;
}ADIOSDate_S;

typedef struct
{
	unsigned int m_unHour_8         :8;
	unsigned int m_unMinute_8       :8;
	unsigned int m_unSecond_8       :8;
	unsigned int m_unMilSecond_8    :8;
}ADIOSTime_S;

typedef struct
{
	ADIOSDate_S m_sDate;
	ADIOSTime_S m_sTime;
}ADIOSSysTime_S;


/*日光节约时间的状态*/ 
typedef enum
{
	E_ADI_DST_NONE,     /*不使用*/ 
	E_ADI_DST_USA,      /*美国*/    
	E_ADI_DST_AUST,     /*澳洲*/    
	E_ADI_DST_WET,      /*西欧*/    
	E_ADI_DST_MET,      /*中欧*/    
	E_ADI_DST_EET,      /*东欧*/    
	E_ADI_DST_CAN,      /*加拿大*/    
	E_ADI_DST_GB,       /*大不列颠*/    
	E_ADI_DST_RUM,      /*罗马尼亚*/    
	E_ADI_DST_TUR,      /*土耳其*/     
	E_ADI_DST_AUSTALT   /*澳洲（1986年以后）*/ 
}ADIOSDSTTime_E;  

typedef struct
{	
	int            m_tzMinWest;     /* 和Greenwich时间差了多少分钟 */ 	
	ADIOSDSTTime_E m_tzDstTime;     
}ADIOSTimezone_S;



typedef void (*ADIOSThreadEntry_F)(void * pvParam);

ADI_Error_Code ADIOSGetMemPoolId(int *pnCachedPoolId, int *pnNonCachedPoolId);

ADI_Error_Code ADIOSThreadCreate(const char * pcName,int nPriority,int nStackSize, ADIOSThreadEntry_F fnThreadEntry,void * pvArg,ADI_HANDLE * phThread);

ADI_Error_Code ADIOSThreadDestroy (ADI_HANDLE hThread);

ADI_Error_Code  ADIOSThreadSelf(ADI_HANDLE * phThread);

void ADIOSThreadSleep(unsigned int uMilliSeconds);

ADI_Error_Code ADIOSMsgQueueCreate(const char * pcName,int nMaxMsgs,int nSizePerMsg,ADI_HANDLE * phMsgQueue);

ADI_Error_Code ADIOSMsgQueueDestroy(ADI_HANDLE hMsgQueue);

ADI_Error_Code ADIOSMsgQueueReceive(ADI_HANDLE hMsgQueue,void * pvMsg,int nMaxMsgBytes,unsigned int uTimeout);

ADI_Error_Code ADIOSMsgQueueSend(ADI_HANDLE hMsgQueue, const void * pvMsg, int nMsgBytes, unsigned int uTimeout);


ADI_Error_Code ADIOSSemCreate(const char * pcName,int nInitialCount,int nMaxCount,ADI_HANDLE * phSemaphore);

ADI_Error_Code ADIOSSemDestroy(ADI_HANDLE hSemaphore);

ADI_Error_Code ADIOSSemWait(ADI_HANDLE hSemaphore,unsigned int uTimeout);

ADI_Error_Code ADIOSSemRelease(ADI_HANDLE hSemaphore);


ADI_Error_Code ADIOSMutexCreate(const char * pcName, unsigned int uOptions,ADI_HANDLE * phMutex);

ADI_Error_Code ADIOSMutexDestroy(ADI_HANDLE hMutex);

ADI_Error_Code ADIOSMutexWait(ADI_HANDLE hMutex,unsigned int uTimeout);

ADI_Error_Code ADIOSMutexRelease(ADI_HANDLE hMutex);



ADI_Error_Code ADIOSEventCreate(const char * pcName,unsigned int  uFlags,ADI_HANDLE * phEvent);

ADI_Error_Code ADIOSEventDestroy(ADI_HANDLE hEvent);

ADI_Error_Code ADIOSEventReset(ADI_HANDLE hEvent);

ADI_Error_Code ADIOSEventSet(ADI_HANDLE hEvent);

ADI_Error_Code ADIOSEventWait(ADI_HANDLE hEvent,unsigned int uTimeout);



void * ADIOSMalloc( unsigned int uSize );

void* ADIOSRealloc( void * pvAddr,unsigned int uSize );

void* ADIOSCalloc(unsigned int uElements, unsigned int uElementSize);

ADI_Error_Code ADIOSFree( void * pvAddr );


void * ADIOSMallocCache( unsigned int uSize );

void* ADIOSReallocCache( void * pvAddr,unsigned int uSize );

void* ADIOSCallocCache(unsigned int uElements, unsigned int uElementSize);

ADI_Error_Code ADIOSFreeCache( void * pvAddr );


ADI_Error_Code ADIOSCreatePhotoMemPool(void);
ADI_Error_Code ADIOSDeletePhotoMemPool(void);

void * ADIOSMallocPhotoMem(  unsigned int uSize );
ADI_Error_Code ADIOSFreePhotoMem( void * pvAddr );




//从1970-1-1 到目前的秒数 
ADI_Error_Code ADIOSSetClock(unsigned int* pnSeconds);
ADI_Error_Code ADIOSGetClock(unsigned int* pnSeconds);

//系统当前日期与时间
ADI_Error_Code ADIOSGetSysTime(ADIOSSysTime_S * psSysTime , ADIOSTimezone_S *psTimezone);
ADI_Error_Code ADIOSSetSysTime(ADIOSSysTime_S  sSysTime , ADIOSTimezone_S *psTimezone);

//系统开机运行时间
ADI_Error_Code ADIOSGetTime(ADIOSTimeVal_S * psTime);
unsigned int ADIOSGetTickCount(void);


void ADIOSGetMemPoolInfo(void);

void ADIOSGetTaskInfo(void);

ADI_Error_Code ADIOSGetFreeMem(unsigned int * puFreeMem);



#ifdef	__cplusplus
}
#endif

#endif
