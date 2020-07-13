/**
 * $Id: s3_hn_skelp.h,v 1.0 2014/12/13 06:46:55 axu Exp $
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

#ifndef S3_HN_SKELP_H
#define S3_HN_SKELP_H


/*Struct for MSG_SKELP_DATA_REQUEST*/
typedef struct
{
	vd_rsc_id	wResourceId;
}msg_skelp_data_request_st ;


/*ske-lp data request result definitions*/
typedef enum
{
	SKELP_DATA_REQUEST_RESULT_SUCCESS = 0,
	/*-SCR#345890:[3.18.3] Behavior not match design with wrong smartcard resource id.*/
	/*SKELP_DATA_REQUEST_RESULT_ERROR was removed*/
	SKELP_DATA_REQUEST_RESULT_NOT_APPLICABLE
}skelp_data_request_result_e ;

/*Struct for MSG_SKELP_DATA_REPLY*/
typedef struct
{
      skelp_data_request_result_e	eResult;
      ia_word16		wLength;
	/* Structure is followed by ia_byte abData[ wLength ]. */
}msg_skelp_data_reply_st ;



#endif /* S3_HN_SKELP_H. */
