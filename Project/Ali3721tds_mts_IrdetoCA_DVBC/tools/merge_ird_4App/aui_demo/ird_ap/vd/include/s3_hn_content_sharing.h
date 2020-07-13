/**
 * $Id: s3_hn_content_sharing.h,v 1.0 2014/12/1 06:46:55 axu Exp $
 *
 * Copyright 2014 Irdeto Access B.V.
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

#ifndef S3_HN_CONTENT_SHARING_H
#define S3_HN_CONTENT_SHARING_H

/*struct of MSG_WHN_GET_SHAREABLE_RECORD_QUERY*/
typedef struct
{
   ia_word32	wRecordId;
   ia_word32	wRightsRecordId;
   ia_word32	wSequenceRecordId;
}msg_whn_get_shareable_record_query_st;



/*Struct for MSG_WHN_GET_SHAREABLE_RECORD_REPLY*/
typedef enum
{
	GET_SHAREABLE_RECORD_SUCCESS = 0,
	GET_SHAREABLE_RECORD_ALREADY_BE_SHAREABLE,
	GET_SHAREABLE_RECORD_NOMSK,
	GET_SHAREABLE_RECORD_CAN_NOT_SHARE,
	GET_SHAREABLE_RECORD_ERROR
}get_shareable_record_result_e;

typedef struct
{
	ia_word32	wRecordId;
	get_shareable_record_result_e eResult;
}msg_whn_get_shareable_record_reply_st;



#endif /* S3_HN_CONTENT_SHARING_H. */
