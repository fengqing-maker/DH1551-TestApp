/**
 * $Id: s3_pd_msg.h,v 1.0 2014/03/14 06:46:55 wtao Exp $
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

#ifndef S3_PD_MSG_H
#define S3_PD_MSG_H

/* Structure for MSG_PD_START_REQUEST. */
typedef struct 
{
	ia_word32  wPeerID;
}msg_pd_start_request_st;

typedef enum
{
	/** (0x00000000) The operation was successful. */
	PD_REQUEST_RESULT_SUCCESS                                            = 0x00000000,

	/** (0x00000001) One or more required parameters were NULL. */
	PD_REQUEST_RESULT_NULL_PARAM                                         = 0x00000001,

	/** (0x00000002) Memory could not be allocated. */
	PD_REQUEST_RESULT_OUT_OF_MEMORY                                      = 0x00000002,

	/** (0x00000003) The resource  is invalid. */
	PD_REQUEST_RESULT_RESOURCE_NOT_FOUND                                 = 0x00000003,

	/** (0x00000004) The buffer passed in is too small. */
	PD_REQUEST_RESULT_INSUFFICIENT_BUFFER                                = 0x00000004,

	/** (0x00000005) The specified length was not valid. */
	PD_REQUEST_RESULT_INVALID_LENGTH                                     = 0x00000005,

	/** (0x00000006) Some required internal data is missing. */
	PD_REQUEST_RESULT_MISSING_DATA                                       = 0x00000006,

	/** (0x00000007) Authentication checking failed. */
	PD_REQUEST_RESULT_AUTHENTICATION_CHECK_FAILED                        = 0x00000007,

	/** (0x00010000) The proximity session is expired - a new session is required. */
	PD_REQUEST_RESULT_PROXIMITY_SESSION_EXPIERD                          = 0x00010000,

	/** (0x00010001) The peer ID does not represent a valid peer or session. */
	PD_REQUEST_RESULT_PROXIMITY_PEER_UNKNOWN                             = 0x00010001,

	/** (0x00010002) The data being provided to be encrypted/decrypted is invalid. */
	PD_REQUEST_RESULT_PROXIMITY_INVALID_DATA                             = 0x00010002,

	/** (0x00010003) The key being used to encrypt/decrypt data is not ready. */
	PD_REQUEST_RESULT_PROXIMITY_KEY_NOT_READY                            = 0x00010003,

	/** (0x00010004) The response message is not returned within allowed time. */
	PD_REQUEST_RESULT_PROXIMITY_RESPONSE_TIMEOUT                         = 0x00010004,

	/** (0x00010005) The session is terminated by user. */
	PD_REQUEST_RESULT_PROXIMITY_SESSION_TERMINATE                        = 0x00010005,

	/** (0x00011000) The schema mismatch. */
	PD_REQUEST_RESULT_PROXIMITY_SCHEMA_MISMATCH                          = 0x00011000,

	/** (0x00011001) The RTT check is failed. */
	PD_REQUEST_RESULT_PROXIMITY_RTT_CHECK_FAILED                         = 0x00011001,

	/** (0x00011002) The key version is mismatched. */
	PD_REQUEST_RESULT_PROXIMITY_KEY_VERSION_MISMATCH                     = 0x00011002,

	/** (0x00011003) The check type is not supported. */
	PD_REQUEST_RESULT_PROXIMITY_UNSUPPORTED_CHECK_TYPE                   = 0x00011003,

	/** (0x00011004) The message is invalid. */
	PD_REQUEST_RESULT_PROXIMITY_INVALID_MESSAGE                          = 0x00011004,

	/** (0x00011005) The challenge is failed. */
	PD_REQUEST_RESULT_PROXIMITY_CHALLENGE_FAILED                         = 0x00011005,

	/** (0x00012000) A generic error is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_FAILURE                           = 0x00012000,

	/** (0x00012001) The PD_REQUEST_RESULT_NULL_PARAM is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_NULL_PARAM                        = 0x00012001,

	/** (0x00012002) The PD_REQUEST_RESULT_OUT_OF_MEMORY is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_OUT_OF_MEMORY                     = 0x00012002,

	/** (0x00012003) The PD_REQUEST_RESULT_RESOURCE_NOT_FOUND is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_RESOURCE_NOT_FOUND                = 0x00012003,

	/** (0x00012004) The PD_REQUEST_RESULT_INSUFFICIENT_BUFFER is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_INSUFFICIENT_BUFFER               = 0x00012004,

	/** (0x00012005) The PD_REQUEST_RESULT_INVALID_LENGTH is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_INVALID_LENGTH                    = 0x00012005,

	/** (0x00012006) The PD_REQUEST_RESULT_MISSING_DATA is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_MISSING_DATA                      = 0x00012006,

	/** (0x00012007) The PD_REQUEST_RESULT_AUTHENTICATION_CHECK_FAILED is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_AUTHENTICATION_CHECK_FAILED       = 0x00012007,

	/** (0x00013000) The PD_REQUEST_RESULT_PROXIMITY_SCHEMA_MISMATCH is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_SCHEMA_MISMATCH                   = 0x00013000,

	/** (0x00013001) The PD_REQUEST_RESULT_PROXIMITY_RTT_CHECK_FAILED is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_RTT_CHECK_FAILED                  = 0x00013001,

	/** (0x00013002) The PD_REQUEST_RESULT_PROXIMITY_KEY_VERSION_MISMATCH is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_KEY_VERSION_MISMATCH              = 0x00013002,

	/** (0x00013003) The PD_REQUEST_RESULT_PROXIMITY_UNSUPPORTED_CHECK_TYPE is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_UNSUPPORTED_CHECK_TYPE            = 0x00013003,

	/** (0x00013004) The PD_REQUEST_RESULT_PROXIMITY_INVALID_MESSAGE is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_INVALID_MESSAGE                   = 0x00013004,

	/** (0x00013005) The PD_REQUEST_RESULT_PROXIMITY_CHALLENGE_FAILED is occured on remote. */
	PD_REQUEST_RESULT_PROXIMITY_REMOTE_CHALLENGE_FAILED                  = 0x00013005,

	/**(0x10000000)Proximity Dectection is not enabled.*/
	PD_REQUEST_RESULT_PROXIMITY_DETECTION_DISABLED					   = 0x10000000,

	/**(0x10000001)Proximity Dectection library initialize fail.*/
	PD_REQUEST_RESULT_PD_LIB_INIT_FAIL					   					   = 0x10000001
	
}pd_request_result_e;

/* Structure for MSG_PD_START_REPLY. */
typedef struct
{
	ia_word32  wPeerID;
	pd_request_result_e eResult;
}msg_pd_start_reply_st;

/* Structure for MSG_PD_STOP_REQUEST. */
typedef struct
{
	ia_word32  wPeerID;
}msg_pd_stop_request_st;

/* Structure for MSG_PD_STOP_REPLY. */
typedef struct
{
	ia_word32  wPeerID;
	pd_request_result_e eResult;
}msg_pd_stop_reply_st;

typedef enum
{
    /** (0x00000000) Proximity session is active and valid. */
    PD_STATUS_ACTIVE              = 0x00000000,

    /** (0x00000001) Proximity session is now invalid. */
    PD_STATUS_INVALID             = 0x00000001,

    /** (0x00000002) Proximity session is in the middle of being negotiated. */
    PD_STATUS_NEGOTIATING         = 0x00000002,

    /** (0x00000003) A communication error prevented the proximity session from being established. */
    PD_STATUS_COMM_ERROR          = 0x00000003,

    /** (0x00000004) A RTT timeout error prevented the proximity session from being established. */
    PD_STATUS_RTT_TIMEOUT         = 0x00000004,

    /** (0x00000005) The maximum message timeout was reached when waiting for a response. */
    PD_STATUS_MESSAGE_TIMEOUT     = 0x00000005,

    /** (0x00000006) The client was providing invalid challenge responses. */
    PD_STATUS_INVALID_RESPONSE    = 0x00000006,

    /** (0x00000007) The root key version isn't compatible (different version numbers). */
    PD_STATUS_NOT_COMPATIBLE_ROOT = 0x00000007,

    /** (0x00000008) Proximity session is expired. */
    PD_STATUS_EXPIRED             = 0x00000008,

    /** (0x10000000) Proximity Detection is Enabled, need to do PD check.**/
    PD_STATUS_ENABLED			= 0x10000000,

    /** (0x10000001) Proximity Detection is Disabled, no need to do PD check.**/
    PD_STATUS_DISABLED			= 0x10000001,

    /** (0x10000002) All the PD sessions are closed.**/
    PD_STATUS_ALL_SESSIONS_CLOSED		= 0x10000002,

    /*SCR#285376 - [3.18.0.11] [IT] When calling MSG_PD_GET_SOURCE_PROPERTY_QUERY, The eStatus is  0xcdcdcdcd= unknown! if eResult returns PD_REQUEST_RESULT_PROXIMITY_PEER_UNKNOWN*/
    /** (0x10000003) PD status is unknown.**/
    PD_STATUS_UNKNOWN		= 0x10000003
    
}pd_status_e;

/* Structure for MSG_PD_STATUS_NOTIFY. */
typedef struct
{
	ia_word32		wPeerID;
	pd_status_e 	eStatus;
}msg_pd_status_st;


typedef enum
{
	PD_CRYPTO_MODE_ENCRYPT,
	PD_CRYPTO_MODE_DECRYPT
}pd_crypto_mode_e;


/* Structure for MSG_PD_CRYPTO_QUERY. */
typedef struct
{
	ia_word32  wPeerID;
	pd_crypto_mode_e   eMode;
	ia_word32  wDataLength;
     /* Structure is followed by ia_byte abData[ wDataLength ]. */
}msg_pd_crypto_query_st;


/* Structure for MSG_PD_CRYPTO_REPLY. */
typedef struct
{
	ia_word32  wPeerID;
	pd_request_result_e	eResult;
	ia_word32  wDataLength;
     /* Structure is followed by ia_byte abData[ wDataLength ]. */
}msg_pd_crypto_reply_st;


/* Structure for MSG_PD_GET_SOURCE_PROPERTY_QUERY. */
typedef struct
{
	ia_word32  wPeerID;
}msg_pd_get_source_property_query_st;

/* Structure for MSG_PD_GET_SOURCE_PROPERTY_REPLY*/
typedef struct
{
	pd_request_result_e eResult;
	msg_pd_status_st	 stStatus;
}msg_pd_get_source_property_reply_st;

#endif /* S3_PD_MSG_H. */
