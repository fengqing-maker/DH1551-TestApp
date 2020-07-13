/**
 * $Id: s3_vdhgb.h,v 1.2 2008/04/17 12:18:46 ehietbrink Exp $
 *
 * Copyright 2007-2008 Irdeto Access B.V.
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

#ifndef S3_VDHGB_H
#define S3_VDHGB_H

#include "s3_portable_types.h"
#include <s3_vd.h>


typedef void (* vd_hgb_receive_notify_fn)( vd_ref_id wRefId, ia_word32 wSoftCellVal, 
	ia_word32 wDataLen, const ia_byte *pbData );

/* VD_IO opcodes. */
enum
{
	VD_HG_BROADCAST_SEND = ( VD_DRIVER_HOMEGATEWAY_BROADCAST * 10 )
};


typedef enum
{
	VD_HGB_COMM_MODE_SEND_ONLY,
	VD_HGB_COMM_MODE_RECEIVE_ONLY
}vd_hgb_comm_mode_e;


typedef struct
{
	vd_hgb_receive_notify_fn  pfnReceiveNotify;
	ia_word32                 wSoftCellVal;
	vd_hgb_comm_mode_e        eCommMode;
} vd_hgb_open_st;


#endif /* S3_VDHGB_H */
