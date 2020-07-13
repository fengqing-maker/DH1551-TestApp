/**
 * @file LoaderCoreSPI_OS.h
 * Header for operating system SPIs. This file contains the prototypes for all operating system functions 
 * that are used by the Loader Core.
 *
 * \note It is the integrator's responsibility to implement these interfaces for a particular platform.
 */

#include "LoaderCoreSPI.h"

#include <string.h>
#include <stdarg.h>
#include <errno.h>
//#include <termios.h>
//#include <semaphore.h>
#include <aui_os.h>


//#define LOADERCORESPI_HIGH_MEMORY_SUPPORT

//#define LC_SPI_OS_DEBUG LoaderCoreSPI_Stdlib_printf
#define LC_SPI_OS_DEBUG(...)
#define MAX_SEMA_NUM            (128)

#ifdef LOADERCORESPI_HIGH_MEMORY_SUPPORT
    #define MEMORY_START_ADDR       (__MM_HIGHEST_ADDR & 0xdfffffff)
    #define MEMORY_LEN              ((LC_HIGHEST_MEM_ADDR | 0x80000000) - MEMORY_START_ADDR)
    #define MEMORY_DEV_NAME         "spipoll"
    static aui_hdl g_mem_pool_handle = 0;
    static aui_attr_mempool *g_spi_memory_pool = LC_NULL;
#endif
static int  nb_semaphores   =   0;


#ifdef LOADERCORESPI_HIGH_MEMORY_SUPPORT
static lc_result loadercorespi_os_init()
{
    lc_result lc_ret = LC_SUCCESS;
    AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;
    if(LC_NULL == g_spi_memory_pool)
    {
        g_spi_memory_pool = (aui_attr_mempool *)MALLOC(sizeof(aui_attr_mempool));
        if(LC_NULL != g_spi_memory_pool)
        {
            LC_SPI_OS_DEBUG("%s() Line(%d) MALLOC SUCCESS!\n",__FUNCTION__, __LINE__);
            
            memset(g_spi_memory_pool->sz_name,0,AUI_DEV_NAME_LEN+1);
            g_spi_memory_pool->base = MEMORY_START_ADDR;
            g_spi_memory_pool->len = MEMORY_LEN;
            memcpy(g_spi_memory_pool->sz_name,MEMORY_DEV_NAME,sizeof(MEMORY_DEV_NAME));
            
            aui_ret = aui_os_mempool_create(g_spi_memory_pool, &g_mem_pool_handle);
            if(AUI_RTN_SUCCESS == aui_ret)
            {
                LC_SPI_OS_DEBUG("%s() Line(%d) aui_os_mempool_create SUCCESS!\n",__FUNCTION__, __LINE__);
            }
            else
            {
                LC_SPI_OS_DEBUG("%s() Line(%d) aui_os_mempool_create FAILED!\n",__FUNCTION__, __LINE__);
                FREE(g_spi_memory_pool);
                g_spi_memory_pool= LC_NULL;
                lc_ret = LC_FAILURE;
            }
        }
        else
        {
            LC_SPI_OS_DEBUG("%s() Line(%d) MALLOC FAIL!\n",__FUNCTION__, __LINE__);
            lc_ret = LC_FAILURE;
        }        
    }
    else
    {
        lc_ret = LC_SUCCESS;
    }
    return lc_ret;
}
#endif
/** @defgroup loadercorespis Loader Core SPIs
 *  Loader Core SPIs
 *
 *  
 *  @{
 */


/** @defgroup memoryspi Loader Core Memory SPIs
 *  Loader Core Memory SPIs
 *
 *  These SPIs implement basic memory management functionality required for most operations.  
 * 
 * \note It is the integrator's responsibility to implement these methods for a particular platform.
 *
 *  @{
 */
/**
 * Allocates a block of uninitialized memory. 
 *
 * This function is called to allocate a block of memory and return a pointer to the beginning
 * of the block. If the system is out of memory, or another failure occurs, it must return NULL.
 * When the memory is no longer needed, ::LoaderCoreSPI_Memory_Free will be called to free it.
 *
 * @param[in] bufferSize Number of bytes to allocate. If this is 0, the implementation MUST return an empty block
 *     of allocated memory.
 */
extern void* LoaderCoreSPI_Memory_Malloc(lc_uint32 bufferSize)
{

    if (0 == bufferSize)
	{
		LC_SPI_OS_DEBUG("LoaderCoreSPI_Memory_Malloc size = 0\n");
		return LC_NULL;
	}
#ifdef LOADERCORESPI_HIGH_MEMORY_SUPPORT
    if(LC_SUCCESS == loadercorespi_os_init())
    {
        return aui_os_mempool_malloc(g_mem_pool_handle,bufferSize);
    }
    else
    {
		LC_SPI_OS_DEBUG("loadercorespi_os_init fail\n");
		return LC_NULL;
    }
#else
    return MALLOC(bufferSize);
#endif
}


/**
 * Frees a block of memory.
 *
 * This function is called to free a block of memory previously allocated using ::LoaderCoreSPI_Memory_Malloc.
 *
 * @param[in] pVoid Pointer to a block of previously allocated memory. If this is NULL, the implementation
 *     MUST handle it gracefully and ignore it. If this points to an area of memory that was not previously
 *     allocated by ::LoaderCoreSPI_Memory_Malloc, OR it has already been freed, the result is undefined.
 */
extern void LoaderCoreSPI_Memory_Free(void * pVoid)
{
#ifdef LOADERCORESPI_HIGH_MEMORY_SUPPORT
    AUI_RTN_CODE ret = AUI_RTN_SUCCESS;
    if(LC_SUCCESS == loadercorespi_os_init())
    {
        if(LC_NULL != pVoid)
        {
            ret =  aui_os_mempool_free(g_mem_pool_handle,pVoid);
            if(AUI_RTN_SUCCESS != ret)
            {
                LC_SPI_OS_DEBUG("aui_os_mempool_free Fail\n");
            }
            else
            {
                pVoid = LC_NULL;
            }
        }
        else
        {
    		LC_SPI_OS_DEBUG("LoaderCoreSPI_Memory_Free pVoid = NULL\n");
        }
    }
    else
    {
		LC_SPI_OS_DEBUG("loadercorespi_os_init fail\n");
    }
#else
    if(LC_NULL != pVoid)
    {
        FREE (pVoid);
        pVoid = LC_NULL;
    }
    else
    {
		LC_SPI_OS_DEBUG("LoaderCoreSPI_Memory_Free pVoid = NULL\n");
    }
#endif    
}

/**
 * Allocates a aligned block of uninitialized memory. 
 *
 * This function is called to allocate a aligned block of memory and return a pointer to the beginning
 * of the block. If the system is out of memory, or another failure occurs, it must return NULL.
 * When the memory is no longer needed, ::LoaderCoreSPI_Memory_AlignedFree will be called to free it.
 *
 * @param[in] required_bytes Number of bytes to allocate. If this is 0, the implementation MUST return an empty block
 *     of allocated memory.
 *
 * @param[in] alignment Number of bytes to align.
 */
extern void* LoaderCoreSPI_Memory_AlignedMalloc(lc_uint32 required_bytes, lc_uint32 alignment)
{
    void* p1;   // original block
    void** p2;  // aligned block
    lc_uint32 offset = alignment - 1 + sizeof(void*);
    if ((p1 = (void*)LoaderCoreSPI_Memory_Malloc(required_bytes + offset)) == LC_NULL)
    {
       return LC_NULL;
    }
    p2 = (void**)(((lc_uint32)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    
    return p2;
}

/**
 * Frees a aligned block of memory.
 *
 * This function is called to free a aligned block of memory previously allocated using ::LoaderCoreSPI_Memory_AlignedMalloc.
 *
 * @param[in] p Pointer to a block of previously allocated memory. If this is NULL, the implementation
 *     MUST handle it gracefully and ignore it. If this points to an area of memory that was not previously
 *     allocated by ::LoaderCoreSPI_Memory_Malloc, OR it has already been freed, the result is undefined.
 */
extern void LoaderCoreSPI_Memory_AlignedFree(void *p)
{
    LoaderCoreSPI_Memory_Free(((void**)p)[-1]);
}


/** @} */

/** @defgroup semaphorespi Loader Core Semaphore SPIs
 *  Loader Core Semaphore SPIs
 *
 * These SPIs implement basic thread synchronization, semaphores.
 *
 * \note It is the integrator's responsibility to implement these methods for a particular platform.
 *
 *  @{
 */
/**
 * Create a semaphore
 *
 * This function is called to create a semaphore.
 *
 * A 'semaphore' is a basic synchronization object with the following properties:
 * - It maintains a value, which is used internally to determine when to unblock waiters.
 * - Calling ::LoaderCoreSPI_Semaphore_Post atomically increments the value.
 * - Calling ::LoaderCoreSPI_Semaphore_WaitTimeout waits until the value > 0, then atomically decrements the value. 
 *
 * Semaphores are used by the Loader Core to signal when events occur and to protect
 * data structures from simultaneous access.
 *
 * @param[in] initialValue Initial value for the semaphore.
 * @param[out] pSemaphoreHandle Receives a handle to a newly created semaphore. When the semaphore is no longer needed,
 *     it will be closed using ::LoaderCoreSPI_Semaphore_Close. 
 *
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The implementation may select any other suitable results to return from the \ref result "Result Code List". 
 */
extern lc_result LoaderCoreSPI_Semaphore_Open(lc_uint32 initialValue, 
                                             lc_handle * pSemaphoreHandle)
{
	lc_result uc_ret = LC_SUCCESS;
	aui_attr_sem attr_sem;
	int aui_rtn = AUI_RTN_SUCCESS;
    
	if (NULL == pSemaphoreHandle)
	{
		LC_SPI_OS_DEBUG("Invalid Input\n");
		return LC_ERROR_NULL_PARAM;
	}

	if (nb_semaphores >= MAX_SEMA_NUM)
	{
		LC_SPI_OS_DEBUG("Semaphore reach max num!\n");
		return LC_FAILURE;
	}

	LoaderCoreSPI_Stdlib_memset(&attr_sem, 0, sizeof(aui_attr_sem));

	LC_SPI_OS_DEBUG ("LoaderCoreSPI_Semaphore_Open: initialValue = %d\n", initialValue);
	attr_sem.ul_max_val = initialValue;//set to 1 means create a mutex. set to 0 means create a signal.
	attr_sem.ul_cnt = 0;
	aui_rtn = aui_os_sem_create(&attr_sem, pSemaphoreHandle);
	if(AUI_RTN_SUCCESS != aui_rtn)
	{
		return LC_FAILURE;
	}

	LC_SPI_OS_DEBUG ("Opened a SemaphoreHandle = %p\n", *pSemaphoreHandle);
	nb_semaphores ++;
	return LC_SUCCESS;
}

/**
 * Increment the semaphore value
 *
 * This function is called to atomically increment the value of a semaphore. 
 * If the value goes above 0, this should cause threads waiting in a call to 
 * ::LoaderCoreSPI_Semaphore_WaitTimeout to be unblocked accordingly. 
 *
 * @param[in] semaphoreHandle Handle of semaphore previously created using ::LoaderCoreSPI_Semaphore_Open.
 *
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_NULL_PARAM
 * @retval
 *     ::LC_ERROR_INVALID_HANDLE \note In case of invalid handle, the SPI driver must return LC_ERROR_INVALID_HANDLE.
 * @retval
 *     Other The implementation may select any other suitable results to return from the \ref result "Result Code List". 
 */
extern lc_result LoaderCoreSPI_Semaphore_Post(lc_handle semaphoreHandle)
{
     lc_result lc_ret = LC_SUCCESS;
     int aui_rtn =0;
     
     if(NULL != semaphoreHandle)
     {
        aui_rtn = aui_os_sem_release((aui_hdl)semaphoreHandle);
        if(AUI_RTN_SUCCESS == aui_rtn)
        {
            lc_ret = LC_SUCCESS; 
        }
        else
        {
			LC_SPI_OS_DEBUG("create sem failed\n");
            lc_ret = LC_FAILURE;
        }
     }
     else
     {
         LC_SPI_OS_DEBUG("LoaderCoreSPI_Semaphore_Post Invalid Input\n");
         lc_ret = LC_ERROR_NULL_PARAM;
     }
     return lc_ret;
 }


/**
 * Decrement the semaphore value
 *
 * This function is called to atomically decrement the value of a semaphore.
 * It waits for the semaphore value to be greater than 0, then atomically decrements the value.
 * For example, if there are 3 threads blocked waiting on the semaphore, the value will be 0. 
 * If another thread calls ::LoaderCoreSPI_Semaphore_Post, it will increment the value to 1, and
 * ONE of the threads will be unblocked so that it can decrement the value back to 0. The other two
 * threads remain blocked. 
 * 
 *
 * @param[in] semaphoreHandle Handle of semaphore previously created using ::LoaderCoreSPI_Semaphore_Open.
 * @param[in] millisecondTimeout Timeout period that Loader Core wants to wait until Loader Core gets a signal.
 * \note If millisecondTimeout is zero, it means an infinite wait, i.e. Loader Core wants to wait until it gets a signal.
 *
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_INVALID_HANDLE \note In case of invalid handle, the SPI driver must return LC_ERROR_INVALID_HANDLE.
 * @retval
 *     ::LC_ERROR_TIMEOUT \note In case of timeout, the SPI driver must return LC_ERROR_TIMEOUT.
 * @retval
 *     Other The implementation may select any other suitable results to return from the \ref result "Result Code List". 
 */
extern lc_result LoaderCoreSPI_Semaphore_WaitTimeout(lc_handle semaphoreHandle, lc_uint32 millisecondTimeout)
{
     lc_result lc_ret = LC_SUCCESS;
     int aui_rtn =0;
     
     if((NULL != semaphoreHandle) && (millisecondTimeout >= 0))
     {
	 	aui_rtn = aui_os_sem_wait((aui_hdl)semaphoreHandle,millisecondTimeout);
        if(AUI_RTN_SUCCESS == aui_rtn)
        {
            lc_ret = LC_SUCCESS; 
            LC_SPI_OS_DEBUG("aui_os_sem_wait get the SemaphoreHandle = %p\n", semaphoreHandle);
        }
        else
        {
            lc_ret = LC_ERROR_INVALID_HANDLE;
            LC_SPI_OS_DEBUG("aui_os_sem_wait can not get  the SemaphoreHandle = %p\n", semaphoreHandle);
        }
     }
     else
     {
         lc_ret = LC_ERROR_NULL_PARAM;
         LC_SPI_OS_DEBUG("LoaderCoreSPI_Semaphore_WaitTimeout LC_ERROR_NULL_PARAM\n");
     }
     return lc_ret;
 }



/**
 * Destroy a semaphore object.
 *
 * This function is called to destroy a semaphore previously created using ::LoaderCoreSPI_Semaphore_Open.
 * 
 * @param[in] pSemaphoreHandle Pointer to handle of semaphore to destroy. The implementation
 *     should free any resources associated with the semaphore, and MUST set the value of *pSemaphoreHandle to NULL. 
 *
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_NULL_PARAM
 * @retval
 *     ::LC_ERROR_INVALID_HANDLE \note In case of invalid handle, the SPI driver must return LC_ERROR_INVALID_HANDLE.
 * @retval
 *     Other The implementation may select any other suitable results to return from the \ref result "Result Code List". 
 */
extern lc_result LoaderCoreSPI_Semaphore_Close(lc_handle * pSemaphoreHandle)
{
	lc_result lc_ret = LC_SUCCESS;
	int aui_rtn =0;

     
	if(NULL != pSemaphoreHandle)
	{
		aui_rtn = aui_os_sem_delete((aui_hdl *)pSemaphoreHandle);
		if(AUI_RTN_SUCCESS == aui_rtn)
		{
		    *pSemaphoreHandle =NULL;
		    nb_semaphores--;
		    lc_ret = LC_SUCCESS; 
		}
		else
		{
			lc_ret = LC_ERROR_INVALID_HANDLE;
		}
	}
	else
	{
		lc_ret = LC_ERROR_NULL_PARAM;
	}
	return lc_ret;
 }


/** @} */


/** @defgroup threadspi Loader Core Thread SPIs
 *  Loader Core Thread SPIs
 *
 *  These SPIs implement basic thread management functions. The Loader Core requires
 *  one background thread that is uses for processing commands, ECMs, and EMMs. 
 *
 * \note It is the integrator's responsibility to implement these methods for a particular platform.
 *  @{
 */

/**
 * Suspend the thread for the period specified.
 * 
 * This function is called to suspend the thread for at least the period specified. 
 *
 * @param[in] millisecond is the time in milliseconds to suspend the thread.  
 *
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_INVALID_PARAMETER
 * @retval
 *     Other The implementation may select any other suitable results to return from the \ref result "Result Code List". 
 */
extern lc_result LoaderCoreSPI_Thread_Sleep(lc_sint32 millisecond)
{
    lc_result lc_ret = LC_SUCCESS;
    if(0 <= millisecond)
    {
	   aui_os_task_sleep (millisecond);
    }
    else
    {
        lc_ret = LC_ERROR_NULL_PARAM;
    }
    return lc_ret;
}


/** @} */

/** @defgroup datetimespi Loader Core Date Time SPIs
 *  Loader Core Date Time SPIs
 *
 *  Loader Core will retrieve date time info via these SPIs.
 *  
 *  @{
 */


