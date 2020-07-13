/**
 * $Id: s3_vdtmr.h,v 1.6 2011/04/21 06:08:35 jcao Exp $
 *
 * Copyright  2004-2006 Irdeto Access B.V.
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
 * This file is part of the 'Timer virtual driver'.
 * It contains all definitions for the Timer virtual driver.
 **/

#ifndef S3_VDTMR_H
#define S3_VDTMR_H

#include "s3_portable_types.h"
#include "s3_vd.h"

/* Notify function used by timer driver to notify of a timer event. */
typedef void (* vd_timer_notify_fn )(
	vd_ref_id            wRefId,				/* Reference Id of caller. */
	ia_word32            wSoftCellVal );	/* Used internally by SoftCell, obtained via VD_Open(). */

/* Structure to hold parameters of VD_Open() call. */
typedef struct
{
	vd_timer_notify_fn   pfnTimeoutNotify;  /* Pointer to call-back function. */
	ia_word32            wSoftCellVal;	/* Softcell internal value. */
	ia_bool              fRepetitive;	/* Timer repetitive (IA_TRUE) or not (IA_FALSE). */
	ia_word32            wTimeout;	/* Timer value. */
} vd_timer_open_st;

/* Supported timer opcodes for VD_IO() call. */
enum
{
	/* Starts an existing timer. */
	VD_TIMER_START = ( VD_DRIVER_TIMER * 10 ),
	/* Stops an existing timer without cancelling. */
	VD_TIMER_STOP
};

#endif /* S3_VDTMR_H */
