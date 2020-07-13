/**
 * @file LoaderCoreSPI_OS.h
 * Header for operating system SPIs. This file contains the prototypes for all operating system functions 
 * that are used by the Loader Core.
 *
 * \note It is the integrator's responsibility to implement these interfaces for a particular platform.
 */

#ifndef LOADERCORESPI_OS_H__INCLUDED__
#define LOADERCORESPI_OS_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
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
extern void* LoaderCoreSPI_Memory_Malloc(lc_uint32 bufferSize);

/**
 * Frees a block of memory.
 *
 * This function is called to free a block of memory previously allocated using ::LoaderCoreSPI_Memory_Malloc.
 *
 * @param[in] pVoid Pointer to a block of previously allocated memory. If this is NULL, the implementation
 *     MUST handle it gracefully and ignore it. If this points to an area of memory that was not previously
 *     allocated by ::LoaderCoreSPI_Memory_Malloc, OR it has already been freed, the result is undefined.
 */
extern void LoaderCoreSPI_Memory_Free(void * pVoid);

extern void* LoaderCoreSPI_Memory_AlignedMalloc(lc_uint32 required_bytes, lc_uint32 alignment);

extern void LoaderCoreSPI_Memory_AlignedFree(void *p);


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
                                             lc_handle * pSemaphoreHandle);
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
extern lc_result LoaderCoreSPI_Semaphore_Post(lc_handle semaphoreHandle);
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
extern lc_result LoaderCoreSPI_Semaphore_WaitTimeout(lc_handle semaphoreHandle, lc_uint32 millisecondTimeout);

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
extern lc_result LoaderCoreSPI_Semaphore_Close(lc_handle * pSemaphoreHandle);
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
extern lc_result LoaderCoreSPI_Thread_Sleep(lc_sint32 millisecond);

/** @} */

/** @defgroup datetimespi Loader Core Date Time SPIs
 *  Loader Core Date Time SPIs
 *
 *  Loader Core will retrieve date time info via these SPIs.
 *  
 *  @{
 */


/** @} */

/** @} */ /* End of Loader Core SPIs */


#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_OS_H__INCLUDED__ */

