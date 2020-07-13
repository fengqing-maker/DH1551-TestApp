/**
 * $Id: s3_vdps.h,v 1.9 2011/04/21 06:08:31 jcao Exp $
 *
 * Copyright  2001-2006 Irdeto Access B.V.
 *
 * This file and the information contained herein are the subject of copyright
 * and intellectual property rights under international convention. All rights
 * reserved. No part of this file may be reproduced, stored in a retrieval
 * system or transmitted in any form by any means, electronic, mechanical or
 * optical, in whole or in part, without the prior written permission of Irdeto
 * Access B.V.
 *
 * This file is part of the SoftCell 3 Integration library.
 **/

/**
 * This file is part of the 'persistent storage virtual driver'.
 * It contains all definitions for the smartcard virtual driver.
 **/

#ifndef S3_VDPS_H
#define S3_VDPS_H

#include "s3_portable_types.h"
#include "s3_vd.h"

/* VD_IO opcodes. */
enum
{
	/* Write data to the file. */
	VD_PS_WRITE = ( VD_DRIVER_PERSISTENT_STORAGE * 10 ),
	/* Read data from the file. */
	VD_PS_READ,
	/* Delete the file. */
	VD_PS_DELETE,
	/*SCR#325795:[Whole Home Networking]Support PS Version 2.*/
	/*Write Data for V2*/	
	VD_PS_WRITE_V2,
	/*Read Data for V2*/
	VD_PS_READ_V2,
	/*Delete Data for V2*/
	VD_PS_DELETE_V2
};

/* The error notification function. */
typedef void (* vd_ps_error_notify_fn)( vd_ref_id wRefId, ia_word32 wSoftCellVal,
	ia_result eError );

/* Structure used with VD_Open(). */
typedef struct
{
	vd_ps_error_notify_fn   pfnErrorNotify;
	ia_word32               wSoftCellVal;
} vd_ps_open_st;

/* Structure used with VD_PS_WRITE. */
typedef struct
{
	ia_word32  wStart;
	ia_word32  wLength;
} vd_ps_write_st;

/* Structure used with VD_PS_READ. */
typedef struct
{
	ia_word32  wStart;
	ia_word32  wLength;
} vd_ps_read_st;

/*SCR#325795:[Whole Home Networking]Support PS Version 2.*/
/* Structure used with VD_PS_WRITE_V2. */
typedef struct
{
	ia_word32  wIndex;
	ia_word32  wStart;
	ia_word32  wLength;
} vd_ps_write_v2_st;

/* Structure used with VD_PS_READ_V2. */
typedef struct
{
	ia_word32  wIndex;
	ia_word32  wStart;
	ia_word32  wLength;
} vd_ps_read_v2_st;
/* Structure used with VD_PS_DELETE_V2. */
typedef struct
{
	ia_word32  wIndex;
} vd_ps_delete_v2_st;

#endif /* S3_VDPS_H */
