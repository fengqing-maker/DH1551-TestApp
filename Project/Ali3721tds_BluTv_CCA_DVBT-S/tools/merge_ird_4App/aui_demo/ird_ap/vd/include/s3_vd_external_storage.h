/*
 * $Id: s3_vd_external_storage.h,v 1.4 2011/04/21 09:02:55 jcao Exp $
 *
 * Copyright 2004-2006 Irdeto Access B.V.
 *
 * This file and the information contained herein are the subject of copyright
 * and intellectual property rights under international convention. All rights
 * reserved. No part of this file may be reproduced, stored in a retrieval
 * system or transmitted in any form by any means, electronic, mechanical or
 * optical, in whole or in part, without the prior written permission of Irdeto
 * Access B.V.
 *
 * This file is part of the SoftCell 3 Integration library.
 */

/**
 * This file contains all the definitions for the 'External Storage virtual driver'.
 **/

#ifndef S3_VD_EXTERNAL_STORAGE_H
#define S3_VD_EXTERNAL_STORAGE_H

#include "s3_portable_types.h"
#include "s3_vd.h"

/* VD_IO opcodes. */
enum
{
	VD_ES_WRITE = ( VD_DRIVER_EXTERNAL_STORAGE * 10 ),
	VD_ES_READ
};

/* Definitions of the mode in wiche records are accessed. */
typedef enum
{
	VD_ES_ACCESS_MODE_READONLY,
	VD_ES_ACCESS_MODE_WRITEONLY,
	VD_ES_ACCESS_MODE_READWRITE
} vd_es_access_mode_e;

/* The notify function to report asynchronous write errors. */
typedef void (*vd_es_error_notify_fn)( vd_ref_id wRefId, ia_word32 wSoftCellVal,
	ia_result eError );

/* Structure given in VD_Open() for this driver type. */
typedef struct
{
	ia_word32               wRecordId;
	vd_es_access_mode_e     eAccessMode;
	vd_es_error_notify_fn   pfnErrorNotify;
	ia_word32               wSoftCellVal;
} vd_es_open_st;

/* Structure used on input for VD_ES_WRITE opcode in VD_IO(). */
typedef struct
{
	ia_word32  wStart;
	ia_word32  wLength;
} vd_es_write_st;
/* Structure is followed by ia_byte abDataToWrite[ wLength ]. */

/* Structure used on input for VD_ES_READ opcode in VD_IO(). */
typedef struct
{
	ia_word32  wStart;
	ia_word32  wLength;
} vd_es_read_st;

#endif /* S3_VD_EXTERNAL_STORAGE_H */

