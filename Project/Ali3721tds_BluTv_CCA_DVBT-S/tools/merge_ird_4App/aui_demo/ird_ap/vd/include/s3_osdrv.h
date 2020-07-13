/**
 * $Id: s3_osdrv.h,v 1.9 2011/04/21 06:08:14 jcao Exp $
 *
 * Copyright 2001-2006 Irdeto Access B.V.
 *
 * This file and the information contained herein are the subject of copyright
 * and intellectual property rights under international convention. All rights
 * reserved. No part of this file may be reproduced, stored in a retrieval
 * system or transmitted in any form by any means, electronic, mechanical or
 * optical, in whole or in part, without the prior written permission of Irdeto
 * Access B.V.
 *
 * This file is part of the SoftCell 3 Integration library.
 *
 * Please refer at Irdeto Access document 710467, "Operating System Driver API"
 * for a full description of the API presented in this file.
 *
 **/

#ifndef S3_OSDRV_H
#define S3_OSDRV_H

#include "s3_portable_types.h"

/* Handles. */
typedef ia_word32  os_drv_semaphore_h;
typedef ia_word32  os_drv_task_h;

/* User values for ia_result. */
enum
{
	/* The handle given to a task or semaphore is invalid. */
	IA_INVALID_OS_HANDLE = IA_FIRST_USER_RESULT_VALUE
};

/* Returned if no semaphore available. */
#define OS_DRV_SEMAPHORE_ERROR   ((os_drv_semaphore_h)(~0L))
/* Returned if no mailbox available or task cannot be created. */
#define OS_DRV_TASK_ERROR        ((os_drv_task_h)(~0L))

/* Task function prototype */
typedef void (* os_drv_task_fn)( void *pvTaskData );

/* Memory management. */
void *OS_DRV_AllocateMemory( ia_uint32 uiSize );
void OS_DRV_FreeMemory( void *pvMemory );

/* Task management. */
os_drv_task_h OS_DRV_CreateTask( os_drv_task_fn tNewTask, void *pvTaskData,
	ia_byte bPriority, ia_word32 wStackSize, ia_word16 wQueueDepth );
void OS_DRV_DelayTask( ia_word16 wDelay );

/* message management. */
ia_result OS_DRV_SendMessage( os_drv_task_h hTask, ia_word16 wMessageLength, void *pvMsg );
void *OS_DRV_ReceiveMessage( ia_word16 *pwMessageLength );

/* Semaphore management. */
os_drv_semaphore_h OS_DRV_CreateSemaphore( ia_uint32 ulInitialValue );
ia_result OS_DRV_DeleteSemaphore( os_drv_semaphore_h hSemaphore );
ia_result OS_DRV_SignalSemaphore( os_drv_semaphore_h hSemaphore );
ia_result OS_DRV_WaitSemaphore( os_drv_semaphore_h hSemaphore );

/* New time function needed by the UMC library. */
ia_word32 OS_DRV_GetCurrentTime( void );
ia_word32 OS_DRV_GetCurrentMs( void );

#endif /* S3_OSDRV_H. */
