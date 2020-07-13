/**
 * $Id: s3_vddf.h,v 1.26 2007/12/12 09:43:59 hqian Exp $
 *
 * Copyright Irdeto Access B.V.
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
 * This file contains all external definitions for versions 1,2 and 3 of the 'Transport DeMUX and
 * Filter driver'. Corresponding vd_driver_type_e is VD_DRIVER_DVB_FILTER.
 * Version 1 was known as the 'DVB DeMUX and Filter driver'.
 **/

#ifndef S3_VDDF_H
#define S3_VDDF_H

#include "s3_portable_types.h"
#include "s3_vd.h"

/* Typedefs. */
typedef ia_word32  vd_df_filter_id;

/* Event types. */
typedef enum
{
	VD_DF_EVENT_JUMP
} vd_df_event_e;


#define VD_DF_ILLEGAL_FILTER_ID  ((vd_df_filter_id)0xFFFFFFFF)

typedef void (* vd_df_receive_notify_fn)( vd_ref_id tChannelId, ia_word32 wSoftCellVal );

typedef void (* vd_df_receive_notify_v2_fn)( vd_ref_id tChannelId, ia_word32 wSoftCellVal,
	ia_word16 wSectionLength, ia_byte *pbSection);

typedef void (* vd_df_event_notify_fn)( vd_ref_id tChannelId, ia_word32 wSoftCellVal, 
	vd_df_event_e eEvent, ia_word16 wInfoLength, void *pvInfo );

/* VD_IO opcodes. */
enum
{
	VD_DF_ALLOCATE_FILTER = ( VD_DRIVER_DVB_FILTER * 10 ),
	VD_DF_FREE_FILTER,
	VD_DF_SET_PID,
	VD_DF_SET_FILTER,
	VD_DF_READ_SECTION,
	VD_DF_START,
	VD_DF_STOP,
	VD_DF_RESET,
	VD_DF_SET_IP_SOCKET,
	VD_DF_SET_IPV6_SOCKET,
	VD_DF_SET_SUBCHID_PA,
	VD_DF_SET_CMMB_CONFIG,
	VD_DF_CONFIG_EVENT_CALLBACK
};


/* Filter types. */
typedef enum
{
	/* Return all matching packets. */
	VD_DF_EQUALITY,
	/* Return all non matching packets. */
	VD_DF_INEQUALITY
} vd_df_filter_type_e;


/* Channel (section) types. */
typedef enum
{
	VD_DF_EMM_CHANNEL,
	VD_DF_ECM_CHANNEL,
	VD_DF_MAPTBL_CHANNEL
} vd_df_channel_type_e;


/* Transport types. */
typedef enum
{
	VD_DF_DVB_MPEG_TS,
	VD_DF_IP_SOCKET,
	VD_DF_CMMB_DATA_UNIT	
} vd_df_transport_type_e;


/* Structure used with VD_Open(). */

typedef struct
{
	vd_df_receive_notify_v2_fn  pfnReceiveNotify;
	ia_word32                   wSoftCellVal;
	ia_word16                   wMaxSectionSize;
	vd_df_channel_type_e        eChannelType;
	vd_df_transport_type_e      eTransportType;
} vd_df_open_v2_st;


typedef struct
{
	vd_df_receive_notify_fn     pfnReceiveNotify;
	ia_word32                   wSoftCellVal;
	ia_word16                   wMaxSectionSize;
	vd_df_channel_type_e        eChannelType;
} vd_df_open_st;


/* Structure used with VD_DF_ALLOCATE_FILTER (output), VD_DF_SET_FILTER and VD_DF_FREE_FILTER. */
typedef struct
{
	vd_df_filter_id             wFilterId;
} vd_df_filter_st;


/* Structure used with VD_DF_SET_PID. */
typedef struct
{
	ia_word16                   wPid;
} vd_df_pid_st;


/* Structure used with VD_DF_SET_SUBCHID_PA. */
typedef struct
{
	ia_byte                     bSubChId;
	ia_word16                   wPA;
} vd_df_subchid_pa_st;


/* Structure used with VD_DF_READ_SECTION. */
typedef struct
{
	vd_df_filter_id             wFilterId;
	ia_word16                   wSectionLength;
} vd_df_read_st;


/* Structure used with VD_DF_ALLOCATE_FILTER (input). */
typedef struct
{
	vd_df_filter_type_e         eFilterType;
	ia_word16                   wFilterLength;
} vd_df_alloc_filter_st;

/* Structure used with VD_DF_CONFIG_EVENT_CALLBACK (input). */
typedef struct
{
	vd_df_event_notify_fn  pfnEventNotify;
} vd_df_config_event_st;

#endif /* S3_VDDF_H */
