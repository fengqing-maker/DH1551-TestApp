/**
 * @file LoaderCoreSPI_TIMER.h
 * Header for timer methods. This file contains the prototypes for all timer functions 
 * that are used by the Loader Core.
 *
 */

#ifndef LOADERCORESPI_TIMER_H__INCLUDED__
#define LOADERCORESPI_TIMER_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup loadercorespis Loader Core SPIs
 *  Loader Core SPIs
 *
 *  @{ 
 */

/** @defgroup timerspi Loader Core Timer SPIs
 *  Loader Core Timer SPIs
 *
 *  Methods to Timer .
 *  
 *  @{
 */

/**
 * structure pointer type used to notify the client with a timeout event.
 *
 * A function pointer of this type is passed to the implementation of a timer via the ::LoaderCoreSPI_Timer_Open
 * method. The timer implementation is expected to notify a timeout event.
 *
 *
 */
typedef void (*lc_timer_callback)(
    lc_uint32 timerId,
    void * timerContext);

/**
 * Data structure of notification function for the timer interfaces. 
 */           
typedef struct _lc_timer_info
{
    /**
     * Timer context, this should be sent back to loader core via the notification function onTimerCallBack.
     */
    void * timerContext;

    /**
     * Specify the timeout value, in milliseconds.
     */
    lc_uint32 timeout;

    /**
     * Indicate if the timer is repetitive.
     * If the timer is repetitive, once the timeout event happens, the implementation should notify loader core 
     * and reclock to wait the next timeout. 
     * The process will go on until ::LoaderCoreSPI_Timer_Close or ::LoaderCoreSPI_Timer_Stop is called.
     */
    lc_bool isRepetitive;

    /**
     * Notification function, this function shall be called to notify the timeout event 
     * to loader core.
     */
    lc_timer_callback onTimeCallback;
}lc_timer_info;

/**
 * Function pointer type used to notify Loader Core when timeout.
 *
 * A function pointer of this type is passed to ::LoaderCoreSPI_Timer_Open method. 
 *
 * note The SPI driver must call the onTimeCallback when timeout.
 *
 */

typedef lc_result (*lc_timer_notify_callback)(lc_uint32 timerId,void * timerContext);


/** 
 * Open a timer.
 * 
 * Loader Core will request to open one timer.
 *
 * @param[out] pTimerId The id of the timer which has triggered a timeout event. 
 * @param[in] pTimerInfo The point to data structure of notification function for the timer interfaces.
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Timer_Open(lc_uint32* pTimerId,lc_timer_info* pTimerInfo);

/**
 * Method close a timer.
 *
 * This method is called when the channel is being closed by Loader Core and is 
 * intended to give the SPI driver a chance to clean up any leftover resources set 
 * up during a call to open.
 *
 * @param[in] timerId The id of the timer which has triggered a timeout event. 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Timer_Close(lc_uint32 timerId);

/**
 * Method starts this timer.
 *
 * This function is called to Start one timer with timerId
 * 
 *
 * @param[in] timerId The id of the timer which has triggered a timeout event. 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_ERROR_NULL_PARAM
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Timer_Start(lc_uint32 timerId);

/**
 * Method stops this timer.
 *
 * This function is called to stop one timer with timerId
 *
 * @param[in] timerId The id of the timer which has triggered a timeout event.  
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Timer_Stop(lc_uint32 timerId);


/** @} */ /* End of Loader Core TIMER SPIs */

/** @} */ /* End of Loader Core SPIs */



#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_TIMER_H__INCLUDED__ */

