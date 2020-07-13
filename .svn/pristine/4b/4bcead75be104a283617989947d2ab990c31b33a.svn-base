/**
 * @file LoaderCoreSPI_TIMER.h
 * Header for timer methods. This file contains the prototypes for all timer functions 
 * that are used by the Loader Core.
 *
 */
#include "LoaderCoreSPI.h"

//#include <signal.h>
//#include <time.h>
//#include <sys/time.h>
#include <aui_os.h>
#include <osal/osal.h>

#define UC_SPI_TIMER_DEBUG(...)

typedef struct _lc_timer_
{
    void * timer_id;
    void * timer_context;
    lc_bool is_repetitive;
    lc_uint32 timeout;
    lc_timer_callback on_time_callback;
}lc_timer;


static void lc_time_out_cb(unsigned int priv)
{
	lc_timer* my_timer = NULL;

	UC_SPI_TIMER_DEBUG("lc_time_out_cb\n");
	my_timer = (lc_timer*)priv;
	if(NULL!= my_timer)
	{
		if(NULL != my_timer->on_time_callback)
		{
			my_timer->on_time_callback((lc_uint32)my_timer,my_timer->timer_context);
		}

		//if(0 == my_timer->is_repetitive)
		//{
		//    if(LC_SUCCESS != LoaderCoreSPI_Timer_Stop((lc_uint32)my_timer))
		//    {
		//       UC_SPI_TIMER_DEBUG("stop no repete timer fail\n ");
		//    }
		//}
		//else
		//{
		//   if(LC_SUCCESS != LoaderCoreSPI_Timer_Start((lc_uint32)my_timer))
		//   {
		//       UC_SPI_TIMER_DEBUG("stop repete timer fail\n ");
		//   }
		//}
	}
}

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
lc_result LoaderCoreSPI_Timer_Open(lc_uint32* pTimerId,lc_timer_info* pTimerInfo)
{
    lc_result lc_ret = LC_SUCCESS;
    aui_attr_timer aui_timer;
	aui_hdl aui_timer_id = NULL;
    
    if((NULL == pTimerId) ||(NULL == pTimerInfo))
    {
        lc_ret = LC_ERROR_NULL_PARAM;
        UC_SPI_TIMER_DEBUG("invalid input parametors!\n");
        return lc_ret;
    }
    
    lc_timer *my_timer = (lc_timer *)LoaderCoreSPI_Memory_Malloc(sizeof(lc_timer));
    LoaderCoreSPI_Stdlib_memset(my_timer,0,sizeof(lc_timer));
    LoaderCoreSPI_Stdlib_memset(&aui_timer,0,sizeof(aui_attr_timer));

    my_timer->is_repetitive = pTimerInfo->isRepetitive;
    my_timer->on_time_callback = pTimerInfo->onTimeCallback;
    my_timer->timer_context = pTimerInfo->timerContext;
    my_timer->timeout= pTimerInfo->timeout;

	if (pTimerInfo->isRepetitive)
		aui_timer.ul_type=TIMER_CYCLIC;
	else
		aui_timer.ul_type=TIMER_ALARM;
	aui_timer.ul_time_out = pTimerInfo->timeout;
    aui_timer.ul_para1 = (unsigned long)my_timer;
    aui_timer.timer_call_back = lc_time_out_cb;

    /* create timer */
    if (AUI_RTN_FAIL == aui_os_timer_create (&aui_timer, (aui_hdl *)&aui_timer_id))
    {
        UC_SPI_TIMER_DEBUG("timer_create, error");
        LoaderCoreSPI_Memory_Free(my_timer);
        lc_ret = LC_FAILURE;
        return lc_ret;
    }
    
    if ( NULL == aui_timer_id)
    {
        UC_SPI_TIMER_DEBUG("timer_create error, id is -1");
        LoaderCoreSPI_Memory_Free(my_timer);
        lc_ret = LC_FAILURE;
        return lc_ret;
    }

    my_timer->timer_id = aui_timer_id;
	*pTimerId = (lc_uint32)my_timer;
	
    return lc_ret;
}



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
lc_result LoaderCoreSPI_Timer_Close(lc_uint32 timerId)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_timer* my_timer = NULL;

    if(0 == timerId)
    {
        UC_SPI_TIMER_DEBUG("invalid input parametors!\n");
        lc_ret = LC_ERROR_NULL_PARAM;
        return lc_ret;
    }
	
	my_timer = (lc_timer *)timerId;
	
    if(AUI_RTN_FAIL == aui_os_timer_delete((aui_hdl *)&(my_timer->timer_id)))
    {
        UC_SPI_TIMER_DEBUG("timer delete fail!\n");
        lc_ret = LC_FAILURE;
    }
    else
    {
        LoaderCoreSPI_Memory_Free(my_timer);
        lc_ret = LC_SUCCESS;
    }
    
    return lc_ret;
}



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
lc_result LoaderCoreSPI_Timer_Start(lc_uint32 timerId)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_timer* my_timer = NULL;

    if(0 == timerId)
    {
        lc_ret = LC_ERROR_NULL_PARAM;
        UC_SPI_TIMER_DEBUG("invalid input parametors!\n");
        return lc_ret;
    }

	my_timer = (lc_timer *)timerId;

    if( AUI_RTN_FAIL == aui_os_timer_run((aui_hdl)my_timer->timer_id, 1))
    {
        lc_ret = LC_FAILURE;
        UC_SPI_TIMER_DEBUG("timer stop fail!\n");
    }
    else
    {
        lc_ret = LC_SUCCESS;
    }
    return lc_ret;
}



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
lc_result LoaderCoreSPI_Timer_Stop(lc_uint32 timerId)
{
	lc_result lc_ret = LC_SUCCESS;
	lc_timer* my_timer = NULL;

	if(0 == timerId)
	{
		UC_SPI_TIMER_DEBUG("invalid input parametors!\n");
		lc_ret = LC_ERROR_NULL_PARAM;
		return lc_ret;
	}

	my_timer = (lc_timer *)timerId;

    if( AUI_RTN_FAIL == aui_os_timer_run((aui_hdl)my_timer->timer_id, 0))
    {
        lc_ret = LC_FAILURE;
        UC_SPI_TIMER_DEBUG("timer stop fail!\n");
    }
    else
    {
        lc_ret = LC_SUCCESS;
    }
    
    return lc_ret;
}



