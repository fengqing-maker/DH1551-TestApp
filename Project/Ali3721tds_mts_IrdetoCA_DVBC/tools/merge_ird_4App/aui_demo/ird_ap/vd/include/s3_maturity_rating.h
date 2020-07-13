/**
 * $Id: s3_maturity_rating.h,v 1.4 2007/09/12 08:24:16 ehietbrink Exp $
 *
 * Copyright 2007 Irdeto Access B.V.
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

#ifndef S3_MATURITY_RATING_H
#define S3_MATURITY_RATING_H

typedef enum
{
	IA_MR_USER_PROFILE_READ,
	IA_MR_USER_PROFILE_SET,
	IA_MR_USER_PROFILE_DELETE
} msg_mr_user_profile_action_e;

typedef enum
{
	MR_USER_PROFILE_OK,
	MR_USER_PROFILE_CARD_ERROR,
	MR_USER_PROFILE_CARD_MR_INCAPABLE,
	MR_USER_PROFILE_SUBSCRIBER_PIN_WRONG,
	MR_USER_PROFILE_SUBSCRIBER_PIN_BLOCK,
	MR_USER_PROFILE_ACCESS_NOT_ALLOWED,
	MR_USER_PROFILE_USER_ID_OUT_OF_RANGE,
	MR_USER_PROFILE_USER_NOT_EXIST,
	MR_USER_PROFILE_USER_AGE_OUT_OF_RANGE
} msg_mr_user_profile_status_e;

typedef enum
{
	IA_MR_CONFIG_READ,
	IA_MR_CONFIG_UPDATE
} msg_mr_config_action_e;

typedef enum
{
	MR_CONFIG_OK,
	MR_CONFIG_CARD_ERROR,
	MR_CONFIG_CARD_MR_INCAPABLE,
	MR_CONFIG_PIN_WRONG,
	MR_CONFIG_PIN_BLOCK,
	MR_CONFIG_DISABLE_MR_NOT_ALLOWED
} msg_mr_config_status_e;

typedef struct
{
	ia_byte                       bProfileID;
	ia_byte                       bUserAge;
	ia_byte                       abUserPin[ 2 ];
} msg_mr_user_profile_data_st;

typedef struct
{
	vd_rsc_id                     wResourceId;
	ia_byte                       abSubscriberPin[ 2 ];
	msg_mr_user_profile_action_e  eAction;
	msg_mr_user_profile_data_st   stUserProfile;
}	msg_mr_user_profile_query_st;

typedef struct
{
	vd_rsc_id                     wResourceId;
	msg_mr_user_profile_action_e  eAction;
	msg_mr_user_profile_status_e  eResult;
	msg_mr_user_profile_data_st   stUserProfile;
}	msg_mr_user_profile_reply_st;

typedef struct
{
	vd_rsc_id                     wResourceId;
	msg_mr_config_action_e        eAction;
	msg_mr_config_status_e        eResult;
} msg_mr_config_reply_st;

typedef struct
{
	ia_bool                       fEnable;
} msg_mr_config_data_st;

typedef struct
{
	vd_rsc_id                     wResourceId;
	ia_bool                       fMRcapable;
} msg_mr_capability_reply_st;

typedef struct
{
	vd_rsc_id                     wResourceId;
	ia_byte                       abSubscriberPin[ 2 ];
	msg_mr_config_action_e        eAction;
} msg_mr_config_query_st;


typedef struct
{
	ia_byte                       abMRPin[ 2 ];
} msg_mr_define_st;

#endif

