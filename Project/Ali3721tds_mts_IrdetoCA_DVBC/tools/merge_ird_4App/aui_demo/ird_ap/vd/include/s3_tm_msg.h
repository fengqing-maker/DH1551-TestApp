/**
 * $Id: s3_tm_msg.h,v 1.3 2009/04/15 00:45:05 dfu Exp $
 *
 * Copyright 2004-2007 Irdeto Access B.V.
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

#ifndef S3_TM_MSG_H
#define S3_TM_MSG_H

/* Message structures for MSG_SERVICE_INFO_REPLY. */
typedef struct
{
	ia_byte    bServiceCount;
} msg_service_info_data_st;

typedef struct
{
	ia_word16  wNetworkId;
	ia_word16  wTransportId;
	ia_word16  wServiceId;
} msg_service_info_st;

/* Message structures for MSG_TRANSPORT_INFO_REPLY. */
typedef struct
{
	ia_byte    bTransportCount;
} msg_transport_info_data_st;

typedef struct
{
	ia_word16  wNetworkId;
	ia_word16  wTransportId;
} msg_transport_info_st;

/* Message structures for MSG_NETWORK_INFO_REPLY. */
typedef struct
{
	ia_byte    bNetworkCount;
} msg_network_info_data_st;

typedef struct
{
	ia_word16  wNetworkId;
} msg_network_info_st;

typedef struct
{
	vd_rsc_id	wResourceId;
}msg_smartcard_tms_query_data_st;

#define TMS_DATA_LENGTH	32

typedef struct
{
	vd_rsc_id	wResourceId;
	ia_byte		abTMSUserData [ TMS_DATA_LENGTH ];
}msg_smartcard_tms_reply_data_st;
#endif /* S3_TM_MSG_H. */
