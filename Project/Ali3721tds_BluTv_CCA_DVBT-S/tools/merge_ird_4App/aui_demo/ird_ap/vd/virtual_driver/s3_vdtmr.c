/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vdtmr.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 15:18:09
 *  @revision           none
 *
 *  @author              <>
 */


/**
 * This file is part of the 'Timer virtual driver'.
 * It contains all definitions for the Timer virtual driver.
 **/


#include <s3_portable_types.h>
#include <s3_vd.h>
#include <s3_vdtmr.h>

#include <signal.h>
#include <time.h>
//#include <sys/time.h>
#include <stdlib.h>
#include <aui_os.h>
#include "ali_vd_drv.h"


#ifndef __timer_t_defined
#define __timer_t_defined
typedef int timer_t;



struct timespec {            
    time_t tv_sec;    /* Seconds */            
    long   tv_nsec;  /* Nanoseconds */      
  };         

struct itimerspec {            
   struct timespec it_interval;  /* Timer interval */            
   struct timespec it_value;     /* Initial expiration */        
 }; 
#endif

 
typedef struct _lc_timer_               
{                                       
    timer_t timer_id;                   
    vd_timer_notify_fn   pfn_timeout_notify;  /* Pointer to call-back function. */
    ia_word32            w_soft_cell_val;    /* Softcell internal value. */
    ia_bool              f_repetitive;    /* Timer repetitive (IA_TRUE) or not (IA_FALSE). */
    ia_word32            w_timeout;    /* Timer value. */
}lc_timer; 



static ia_word32 open_cnt = 0;
                         
static ia_word16 vd_tmr_get_drv_version();
static vd_ref_id vd_tmr_open (vd_rsc_id wResourceID, void *pvData);
static ia_result vd_tmr_close (vd_ref_id wRefId);
static ia_result vd_tmr_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead);

static int set_timer(timer_t timerId, ia_word32 timeMSec);

static vd_drv vdtmr_res0 = {
		.drv_typ 			= VD_DRIVER_TIMER,
		.priv				= NULL,
		.get_drv_version 	= vd_tmr_get_drv_version,
		.get_resources		= NULL,
		.drv_open			= vd_tmr_open,
		.drv_close			= vd_tmr_close,
		.drv_ioctl			= vd_tmr_ioctl,
		.destroy			= NULL,
};


static void lc_time_out_cb (unsigned int priv)// (vd_ref_id wRefId, ia_word32 wSoftCellVal) 
{
	lc_timer* my_timer = (lc_timer*)priv;

	if(NULL!= my_timer)
	{
		if(NULL != my_timer->pfn_timeout_notify)
		{
			my_timer->pfn_timeout_notify((vd_ref_id)my_timer,my_timer->w_soft_cell_val);
		}
		else
		{
			DEBUG_S3_VD_PRINTF("no callback function!\n");
		}

		if(IA_TRUE == my_timer->f_repetitive)
		{
			vd_tmr_ioctl((vd_ref_id)my_timer, VD_TIMER_START, 0, NULL, NULL, NULL);
		}
		else
		{
			
		}
	}
	else
	{
		DEBUG_S3_VD_PRINTF("unknow lc callback!\n");
	}
	
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_word16 vd_tmr_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = 1;

	return ver;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static vd_ref_id vd_tmr_open (vd_rsc_id wResourceID, void *pvData)
{
	//struct sigevent sev;
	//timer_t timer_id;
    aui_attr_timer aui_timer;
	aui_hdl aui_timer_id = NULL;
    
	vd_timer_open_st *pTimerInfo = (vd_timer_open_st *)pvData;

	lc_timer *my_timer = (lc_timer *)malloc(sizeof(lc_timer));
	
	my_timer->pfn_timeout_notify = pTimerInfo->pfnTimeoutNotify;
    my_timer->w_soft_cell_val = pTimerInfo->wSoftCellVal;
    my_timer->f_repetitive = pTimerInfo->fRepetitive;
    my_timer->w_timeout= pTimerInfo->wTimeout;

	//sev.sigev_notify = SIGEV_THREAD;
	//sev.sigev_signo = SIGRTMIN;
	//sev.sigev_value.sival_ptr = my_timer;
	//sev.sigev_notify_function = lc_time_out_cb;
	//sev.sigev_notify_attributes = NULL;

    memset(&aui_timer,0,sizeof(aui_attr_timer));
    if (pTimerInfo->fRepetitive)
		aui_timer.ul_type=TIMER_CYCLIC;
	else
		aui_timer.ul_type=TIMER_ALARM;
	aui_timer.ul_time_out = pTimerInfo->wTimeout;
    aui_timer.ul_para1 = (unsigned long)my_timer;
    aui_timer.timer_call_back = lc_time_out_cb;
    
	/* create timer */
	//if (timer_create(CLOCK_REALTIME, &sev, &timer_id))
    if (AUI_RTN_FAIL == aui_os_timer_create (&aui_timer, (aui_hdl *)&aui_timer_id))
	{
		free(my_timer);
		return -1;
	}

	if ( NULL == aui_timer_id)
	{
		free(my_timer);
		return -1;
	}
	
	my_timer->timer_id = aui_timer_id;

	//if( -1 == set_timer(my_timer->timer_id,my_timer->w_timeout))
	//{
		//free (my_timer);
		//return -1;
	//}

	open_cnt++;
	return (vd_ref_id)my_timer;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_result vd_tmr_close (vd_ref_id wRefId)
{
	ia_result ret = IA_SUCCESS;
	lc_timer* my_timer = (lc_timer *)wRefId;

	if(NULL == my_timer)
	{
		return IA_FAIL;
	}

	if (0 == open_cnt)
		return IA_FAIL;

	if( -1 == timer_delete(my_timer->timer_id))
	{
		ret = IA_FAIL;
	}
	else
	{
		free(my_timer);
	}

	open_cnt--;
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_result vd_tmr_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead)
{
	ia_result ret = IA_SUCCESS;
	lc_timer* my_timer = (lc_timer *)wRefId;
	
	if(NULL == my_timer)
	{
		return IA_FAIL;
	}
	switch (wOpCode)
	{
		case VD_TIMER_START:
		{
			if( -1 == set_timer(my_timer->timer_id,my_timer->w_timeout))
			{
			    ret = IA_FAIL;
			    DEBUG_S3_VD_PRINTF("timer stop fail!\n");
			}
			break;
		}

		case VD_TIMER_STOP:
		{
			if( -1 == set_timer(my_timer->timer_id, 0))
			{
			    ret = IA_FAIL;
			    DEBUG_S3_VD_PRINTF("timer stop fail!\n");
			}
			break;
		}
	}

	return ret;

}
/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/26/2016, Created
 *
 *  @note
 */
static int set_timer(timer_t timerId, ia_word32 timeMSec)
 {
     struct itimerspec its;

     ansi_memset(&its,0,sizeof(struct itimerspec));
     /* Start the timer */
     its.it_value.tv_sec = timeMSec / 1000;
     its.it_value.tv_nsec = (timeMSec % 1000) * 1000000;
     its.it_interval.tv_sec = 0;
     its.it_interval.tv_nsec = 0;
 
     if (-1 == timer_settime(timerId, 0, &its, NULL))
     {
         DEBUG_S3_VD_PRINTF("set_timer error \n");
         return -1;
     }
     DEBUG_S3_VD_PRINTF("call set_timer reset timer done.\n");    
     return 0;
 }

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
ia_result init_s3_vdtmr()
{
	ia_result ret = IA_SUCCESS;

	/*here implement your own module init code*/
	
	ret = register_vd_drv(&vdtmr_res0);
	
	return ret;
}