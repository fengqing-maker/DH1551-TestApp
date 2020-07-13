/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\softcell\buildroot\output\build\ird_vd-1.0.0-20160728\virtual_driver\s3_osdrv.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/28/2016 17:20:15
 *  @revision           none
 *
 *  @author              <>
 */

#include <stdlib.h>
//#include <pthread.h>
//#include <mqueue.h>
#include <time.h>
//#include <sys/times.h>
//#include <unistd.h>
//#include <semaphore.h>
#include <aui_common.h>
#include <aui_os.h>
#include <s3_osdrv.h>
#include <s3_vd.h>
#include "ali_vd_drv.h"

#define IRD_PRIO_MIN 0
#define IRD_PRIO_MAX 15

#define DEFAULT_MSG_PRIO 5
/*thread priory map: ird task prio --> Linux thread prio*/
static int thread_prio_tlb[IRD_PRIO_MAX + 1] = {1, 3, 6, 9 ,12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 99};
#define MAX_SEMA_NUM            (128)
static int  nb_semaphores=0;

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define	DEFAULT_MAX_MSG_SIZE	(1024)
typedef struct task_mq{
	unsigned int tid;
	char *mq_path;
	//mqd_t	mqd;
	//struct mq_attr	attr;
	aui_hdl mqd;
	aui_attr_msgq attr;
	struct aui_list_head node;
}task_mq;

AUI_LIST_HEAD(thread_msg_q_head);
static int create_task_msg_q(os_drv_task_h tid, ia_word16 wQueueDepth);
static aui_hdl get_task_msg_q(os_drv_task_h tid);
static int del_task_msg_q(os_drv_task_h tid);

/**
 *  Function Name:      
 *  @brief              
 *		Memory management.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/28/2016, Created
 *
 *  @note
 */
void *OS_DRV_AllocateMemory( ia_uint32 uiSize )
{
	char *mem = NULL;

	if (0 == uiSize)
	{
		DEBUG_S3_VD_PRINTF("OS_DRV_AllocateMemory size = 0\n");
		return NULL;
	}

	mem = malloc(uiSize);
	return mem;
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
void OS_DRV_FreeMemory( void *pvMemory )
{
	 if(NULL != pvMemory)
    {
        free(pvMemory);
    }
     return ;

}

/* Task management. */

/**
 *  Function Name:      
 *  @brief              
 *		Task management.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/28/2016, Created
 *
 *  @note
 */
os_drv_task_h OS_DRV_CreateTask( os_drv_task_fn tNewTask, void *pvTaskData,
	ia_byte bPriority, ia_word32 wStackSize, ia_word16 wQueueDepth)
{
	int err =0;
	aui_hdl* mqd = NULL;
    unsigned int tid;
    //pthread_attr_t	attr;
    char *mq_path = NULL;

	if((bPriority < IRD_PRIO_MIN) || (bPriority > IRD_PRIO_MAX))
	{	
		DEBUG_S3_VD_PRINTF("error param bPriority: %d\n", bPriority);
		return OS_DRV_TASK_ERROR;
	}
    #if 0
	err = pthread_attr_init(&attr);
 	if (err != 0)
 	{
		return OS_DRV_TASK_ERROR;
	}
	err = pthread_attr_setstacksize (&attr, wStackSize);
 	if (err != 0)
 	{
		return OS_DRV_TASK_ERROR;
	}
	err = pthread_attr_setschedpolicy (&attr, SCHED_FIFO);
	if (err != 0)
 	{
		return OS_DRV_TASK_ERROR;
	}
    err = pthread_create(&tid, &attr, tNewTask, pvTaskData);
    if (err != 0)
 	{
		goto fail;
	}
	err = pthread_setschedprio(tid, thread_prio_tlb[bPriority]);
	if (err != 0)
 	{
		goto fail;
	}
    #endif
    aui_hdl entry_task_hdl=NULL;

	aui_attr_task attr_task;
    memset(&attr_task, 0, sizeof(aui_attr_task));
	
	attr_task.ul_priority = bPriority;
	attr_task.p_fun_task_entry = tNewTask;
	attr_task.para1 = (unsigned long)pvTaskData;
	attr_task.ul_quantum = 10;
	attr_task.ul_stack_size = wStackSize;
	if(AUI_RTN_SUCCESS != aui_os_task_create(&attr_task, &entry_task_hdl))
	{
	    goto fail;
	}
 
	err = create_task_msg_q((os_drv_task_h) tid, wQueueDepth);
	if (err != 0)
 	{
		DEBUG_S3_VD_PRINTF("can't bond thread an message queue\n");
		goto fail;
	}

	return (os_drv_task_h)(tid);
fail: 
	//pthread_attr_destroy (&attr);
	//pthread_cancel(tid);
	return OS_DRV_TASK_ERROR;
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
void OS_DRV_DelayTask( ia_word16 wDelay )
{
	ia_result ret = IA_SUCCESS;
	
	osal_delay(wDelay*1000);
   	return ret;

}

/**
 *  Function Name:      
 *  @brief              
 *		 message management.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_result OS_DRV_SendMessage( os_drv_task_h hTask, ia_word16 wMessageLength, void *pvMsg)
{
	ia_result ret = IA_SUCCESS;
	int err = 0;
	aui_hdl	mqd = NULL;
    os_drv_task_h tid = hTask;

    if((NULL == pvMsg) || (wMessageLength < 0))
    {
		ret = IA_FAIL;
		return ret;
    }
    mqd = get_task_msg_q(tid);
    if(mqd < 0)
    {
		ret = IA_FAIL;
		return ret;
    }
    //err = mq_send(mqd, pvMsg, wMessageLength, DEFAULT_MSG_PRIO);
    err = aui_os_msgq_snd(mqd, pvMsg, wMessageLength, DEFAULT_MSG_PRIO);
    if (err != 0)
 	{
		DEBUG_S3_VD_PRINTF("can't bond thread an message queue\n");
		ret = IA_FAIL;
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
void *OS_DRV_ReceiveMessage( ia_word16 *pwMessageLength)
{
	char *mem = NULL;
	int len = 0;
	int err = 0;
	aui_attr_msgq attr;
	aui_hdl	mqd = NULL;
    unsigned int tid;
    AUI_RTN_CODE ret = AUI_RTN_FAIL;
    //aui_hdl *x_task_id = NULL;

   	//tid = pthread_self();
    if(AUI_RTN_SUCCESS!= aui_os_task_id_get(NULL, &tid))
        return NULL;

    mqd = get_task_msg_q(tid);
    if(mqd == NULL)
    {
		return NULL;
    }
    
    //err = mq_getattr(mqd, &attr);
    if(AUI_RTN_SUCCESS!=aui_os_msgq_attr_get(mqd, &attr))
    //if (err != 0)
 	{
		DEBUG_S3_VD_PRINTF("can't get msg queue attr!\n");
		return NULL;
	}
	mem = OS_DRV_AllocateMemory(attr.ul_msg_size_max);
	if(NULL == mem)
	{
		DEBUG_S3_VD_PRINTF("can't alloc msg mem!\n");
		return NULL;
	}
    //len = mq_receive(mqd, mem, attr.mq_msgsize, DEFAULT_MSG_PRIO);
    if(AUI_RTN_SUCCESS!=aui_os_msgq_rcv(mqd, mem, attr.ul_msg_size_max, &len, DEFAULT_MSG_PRIO))
    //if(len <= 0)
    {
    	OS_DRV_FreeMemory(mem);
		return NULL;
    }
    if (NULL != pwMessageLength)
 	{
		*pwMessageLength = len;
	}
	return mem;
}


/**
 *  Function Name:      
 *  @brief              
 *		Semaphore management.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/28/2016, Created
 *
 *  @note
 */
os_drv_semaphore_h OS_DRV_CreateSemaphore( ia_uint32 ulInitialValue )
{
	//int err = 0;
    //sem_t *sem = NULL;
	os_drv_semaphore_h hd_adr = NULL;
	
	if (nb_semaphores >= MAX_SEMA_NUM)
	{
        DEBUG_S3_VD_PRINTF("Semaphore reach max num!\n");
		return OS_DRV_SEMAPHORE_ERROR;
	}
    #if 0
	sem = OS_DRV_AllocateMemory(sizeof(sem_t));
	if (NULL == sem)
	{
        DEBUG_S3_VD_PRINTF("Not enought memory!\n");
		return OS_DRV_SEMAPHORE_ERROR;
	}
	ansi_memset(sem, 0, sizeof(sem_t));
	err = sem_init(sem, 0, ulInitialValue);
	if(err != 0)
	{
		OS_DRV_FreeMemory(sem);
		sem = NULL;
		return OS_DRV_SEMAPHORE_ERROR;
	}
	nb_semaphores ++;
	hd_adr = (os_drv_semaphore_h) sem;
    #endif

    aui_attr_sem attr_sem;
	int aui_rtn = AUI_RTN_SUCCESS;
    
    memset(&attr_sem, 0, sizeof(aui_attr_sem));
    attr_sem.ul_max_val = ulInitialValue;//set to 1 means create a mutex. set to 0 means create a signal.
	attr_sem.ul_cnt = 0;
	aui_rtn = aui_os_sem_create(&attr_sem, (aui_hdl *)&hd_adr);
	if(AUI_RTN_SUCCESS != aui_rtn)
	{
		return OS_DRV_SEMAPHORE_ERROR;
	}

	return hd_adr ;
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_result OS_DRV_DeleteSemaphore(os_drv_semaphore_h hSemaphore)
{
	ia_result ret = IA_SUCCESS;
    AUI_RTN_CODE err = 0;
	aui_hdl *sem = NULL;

	sem = (aui_hdl *) hSemaphore;
	if(NULL == sem)
	{
		return IA_INVALID_OS_HANDLE;

	}
    err = aui_os_sem_delete(sem);
    if(err!=AUI_RTN_SUCCESS)
        return IA_FAIL;
    #if 0
	err = sem_destroy(sem);
 	if(0 != err)
 	{
		DEBUG_S3_VD_PRINTF("[s3_vd] : Semaphore close fail!\n");
		return IA_FAIL;
 	}
	free(sem);
	sem = NULL;
	nb_semaphores --;
    #endif
 	ret = IA_SUCCESS;
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_result OS_DRV_SignalSemaphore( os_drv_semaphore_h hSemaphore )
{
	ia_result ret = IA_SUCCESS;
    AUI_RTN_CODE err =0;
	aui_hdl *sem = NULL;

	sem = (aui_hdl *) hSemaphore;
	if(NULL != sem)
	{
		err = aui_os_sem_release(sem);
        if(AUI_RTN_SUCCESS == err)
        {
            ret = IA_SUCCESS; 
        }
        else
        {
           	ret = IA_FAIL;
        }
     }
     else
     {
         return IA_INVALID_OS_HANDLE;
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_result OS_DRV_WaitSemaphore( os_drv_semaphore_h hSemaphore )
{
	ia_result ret = IA_SUCCESS;
    AUI_RTN_CODE err =0;
	aui_hdl *sem = NULL;
	
	sem = (aui_hdl *) hSemaphore; 
	if(NULL != sem)
    {
        err = aui_os_sem_wait(sem, -1);
        if(AUI_RTN_SUCCESS == err)
        {
            ret = IA_SUCCESS; 
        }
        else
        {
            ret = IA_FAIL;
        }
     }
     else
     {
         return IA_INVALID_OS_HANDLE;
     }
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *		New time function needed by the UMC library.
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/28/2016, Created
 *
 *  @note
 */
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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_word32 OS_DRV_GetCurrentTime( void )
{
	time_t t_val;

	t_val = time(NULL);
	return (ia_word32) t_val;

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
 *  @date               7/28/2016, Created
 *
 *  @note
 */
ia_word32 OS_DRV_GetCurrentMs( void )
{
	ia_word32 val = 0;
	//clock_t t_cnt = 0;
	//struct tms buf;
	//ia_word32 tick_per_ms = (ia_word32) sysconf(_SC_CLK_TCK);
	
	//t_cnt = times(&buf);
	//val = (t_cnt / tick_per_ms);

    aui_os_timer_get(NULL, AUI_TIMER_TICK_GET, &val);
	return val;

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
 *  @date               8/17/2016, Created
 *
 *  @note
 */
static int create_task_msg_q(os_drv_task_h tid, ia_word16 wQueueDepth)
{
	aui_hdl	mqd = NULL;
	struct task_mq *pmq = NULL;
	
	pmq = OS_DRV_AllocateMemory(sizeof(struct task_mq));
	if((NULL == pmq) || (wQueueDepth < 0))
	{
		return -1;
	}
	ansi_memset(pmq, 0, sizeof(struct task_mq));
	pmq->tid = tid;
	sprintf(pmq->mq_path, "%ul", tid);
	pmq->attr.ul_buf_size = wQueueDepth*DEFAULT_MAX_MSG_SIZE;
	pmq->attr.ul_msg_size_max= DEFAULT_MAX_MSG_SIZE;
	if(AUI_RTN_SUCCESS!= aui_os_msgq_create(&pmq->attr, &mqd))
        return -1;
    
    pmq->mqd = mqd;
	
	AUI_INIT_LIST_HEAD(&pmq->node);
	aui_list_add_tail(&pmq->node, &thread_msg_q_head);
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
 *  @date               8/17/2016, Created
 *
 *  @note
 */
static aui_hdl get_task_msg_q(os_drv_task_h tid)
{
	aui_hdl	mqd = -1;
	struct task_mq *pmq = NULL;

	aui_list_for_each_entry(pmq, &thread_msg_q_head, node)
	{
		if(pmq->tid == tid)
		{
			mqd = pmq->mqd;
			break;
		}

	}
	return mqd;

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
 *  @date               8/17/2016, Created
 *
 *  @note
 */
static int del_task_msg_q(os_drv_task_h tid)
{
	int ret = 0;;
	aui_hdl	mqd = -1;
	struct task_mq *pmq = NULL;

	aui_list_for_each_entry(pmq, &thread_msg_q_head, node)
	{
		if(pmq->tid == tid)
		{
			mqd = pmq->mqd;
			if(AUI_RTN_SUCCESS != aui_os_msgq_delete(&mqd))
			//if(ret < 0)
			{
				DEBUG_S3_VD_PRINTF("MSG queue close fail!\n");
			}
			aui_list_del(&pmq->node);
			OS_DRV_FreeMemory(pmq);
			pmq = NULL;
			break;
		}

	}
	return ret;

}
