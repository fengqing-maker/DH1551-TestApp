/**
 * $Id: s3_hn_streaming.h,v 1.0 2014/08/06 06:46:55 axu Exp $
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

#ifndef S3_HN_STREAMING_H
#define S3_HN_STREAMING_H


/*Struct for MSG_HN_STREAMING_PR_LICENSE_REQUEST*/
typedef struct
{
	vd_rsc_id	wResourceId;
	ia_word16	wContentType;
}msg_hn_streaming_pr_license_request_st;


/*Struct for MSG_HN_STREAMING_PR_LICENSE_REPLY*/
typedef enum
{
	PR_LICENSE_REQUEST_SUCCESS = 0,
	PR_LICENSE_REQUEST_NO_ENTITLEMENT,
	PR_LICENSE_REQUEST_RIGHT_NOT_DETERMINED
}pr_license_request_result_e;

typedef struct
{
      pr_license_request_result_e	eResult;
      ia_word16		wContentType;
      ia_word16 	wLicenseLength;
}msg_hn_streaming_pr_license_reply_st;

/*Struct for MSG_HN_STREAMING_RIGHT_QUERY*/
typedef struct
{
	vd_rsc_id	wResourceId;
	ia_bool		fKeepTrack;
}msg_hn_streaming_right_query_st;

/*Struct for MSG_HN_STREAMING_RIGHT_NOTIFY*/
typedef struct
{
      ia_word16 wTypeCount;
}msg_hn_streaming_right_notify_st;

typedef enum
{
	STREAMING_RIGHT_OK = 0,
     STREAMING_RIGHT_NO_ENTITLEMENT
}streaming_right_status_e;

typedef struct 
{
	ia_word16  wContentType;
	streaming_right_status_e eStatus;
}msg_streaming_right_st;


#endif /* S3_HN_STREAMING_H. */
