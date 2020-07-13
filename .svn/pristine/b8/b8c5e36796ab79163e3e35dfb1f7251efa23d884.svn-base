/**
 * $Id: s3_ippv_msg.h,v 1.10 2007/09/14 06:46:55 axu Exp $
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

#ifndef S3_IPPV_MSG_H
#define S3_IPPV_MSG_H

/* Structure for MSG_IPPV_EVENT_NOTIFY. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_byte		bSector;
	ia_word16	wEventId;
	ia_word16	wEventCost;
	ia_byte		bClockValue;
	ia_byte		bPreviewValue;
	ia_word16	wServiceCount;
} msg_ippv_event_notify_st;
/* ia_word16 awServiceId[]. */

/* Structure for MSG_IPPV_BUY_QUERY. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_byte		bSector;
	ia_word16	wEventId;
	ia_byte		abIppvPin[ 2 ];
} msg_ippv_buy_query_st;

typedef enum
{
	IPPV_BUY_SUCCESS = 1,
	IPPV_BUY_EVENT_NOT_AVAILABLE,
	IPPV_BUY_PIN_FAIL = 0x51,
	IPPV_BUY_PIN_BLOCK = 0x54,
	IPPV_BUY_STORE_FULL = 0x9b,
	IPPV_BUY_NO_CREDIT = 0x9c
} msg_ippv_buy_status_e;

/* Structure for MSG_IPPV_BUY_QUERY. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_byte		bSector;
	ia_word16	wEventId;
	msg_ippv_buy_status_e		eResult;
} msg_ippv_buy_reply_st;

/* Structure for MSG_IPPV_SECTOR_INFORMATION_QUERY. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_byte		bSector;
} msg_ippv_sector_query_st;

/* Status for MSG_IPPV_SECTOR_INFORMATION_REPLY. */
typedef enum
{
	IPPV_SECTOR_SUCCESS = 1,
	IPPV_SECTOR_CARD_ERROR,
	IPPV_SECTOR_SECTOR_ERROR,
	IPPV_SECTOR_UNKNOWN_ERROR
} ippv_sector_information_status_e;

/* Structure for MSG_IPPV_SECTOR_INFORMATION_REPLY. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_byte		bSector;
	ia_byte		bMaxNoIppvEvents;
	ia_word16	wOperatorPurse;
	ia_word16	wCustomerPurse;
	ia_word16	wDebitLimit;
	ia_word16	wDebitThreshold;
	ippv_sector_information_status_e	eResult;
} msg_ippv_sector_reply_st;

/* Structure for MSG_IPPV_SET_DEBIT_THRESH. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_byte		bSector;
	ia_word16   wDebitThreshold;
} msg_ippv_set_debit_threshold_query_st;

/* Structure for MSG_IPPV_CALLBACK_REQUEST. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_byte		bSector;
	ia_byte		bPhoneNumberLength;
	ia_byte     bPhoneControl;
	ia_word16	wDelay;
	ia_byte		bDelayMultiplier;
} msg_ippv_callback_request_st;
/* ia_byte abPhoneNumber[ bPhoneNumberLength ]. */

/* Structure for MSG_IPPV_REMOTE_CHANNEL_REQUEST and REPLY. */
typedef struct
{
	vd_rsc_id	wResourceId;	/* Smartcard. */
	ia_word16	wPayloadLength;
} msg_ippv_remote_channel_st;
/* ia_byte abPayload[ wPayloadLength ]. */


typedef struct
{
	vd_rsc_id	wResourceId;
	ia_byte		bSector;
} msg_ippv_phone_number_query_data_st;


typedef struct
{
	vd_rsc_id	wResourceId;
	ia_byte		bSector;
	ia_byte		bPhoneNumberLength;
} msg_ippv_phone_number_data_st;


#endif /* S3_IPPV_MSG_H. */
