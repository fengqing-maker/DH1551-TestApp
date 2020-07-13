/**
 *
 * Copyright 2007-2014 Irdeto Access B.V.
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

#ifndef S3_VDPD_H
#define S3_VDPD_H

#include "s3_portable_types.h"


typedef void (* vd_pd_receive_notify_fn)( vd_ref_id wRefId, ia_word32 wSoftCellVal, ia_word32 wPeerId, ia_word32 wDataLength, ia_byte *pbData );

/* VD_IO opcodes. */
enum
{
	VD_PD_SEND_MSG = ( VD_DRIVER_PROXIMITY_DETECTION* 10 )
};

typedef struct
{
	vd_pd_receive_notify_fn		pfnReceiveNotify;
	ia_word32		wSoftCellVal;
}vd_pd_open_st;

typedef struct
{
   ia_word32 wPeerId;
   ia_word32  wDataLen;
}vd_pd_send_msg_st;


#endif /* S3_VDPD_H */
