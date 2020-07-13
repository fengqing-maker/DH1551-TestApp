/**
 * $Id: s3_event_if_msg.h,v 1.2 2008/06/06 06:26:32 ehietbrink Exp $
 *
 * Copyright 2004-2008 Irdeto Access B.V.
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

#ifndef S3_EVENT_IF_MSG_H
#define S3_EVENT_IF_MSG_H


/* Structure for MSG_IPPV_EVENT_LIST_QUERY. */
typedef struct
{
	vd_rsc_id  wResourceId;	/* Smartcard. */
	ia_byte    bSector;
	ia_byte    bPeriod;
} msg_ippv_event_list_query_st;


/* Structure for MSG_IPPV_EVENT_LIST_REPLY. */
typedef struct
{
	vd_rsc_id  wResourceId;	/* Smartcard. */
	ia_byte    bSector;
	ia_byte    bEventCount;
} msg_ippv_event_list_reply_st;
/* msg_ippv_event_list_reply_event_st astEvents[ bEventCount ] */


typedef struct
{
	ia_word16  wEventId;
	ia_bool    fEventReported;
	ia_word16  wEventCost;
	ia_word16  wDateCode;
} msg_ippv_event_list_reply_event_st;


/* Structure for MSG_IPPV_EVENT_CHECK_QUERY. */
typedef struct
{
	vd_rsc_id  wResourceId;	/* Smartcard. */
	ia_byte    bGracePeriod;
	ia_byte    bEventCount;
} msg_ippv_event_check_query_st;
/* msg_ippv_event_check_item_query_st astEvents[ bEventCount ] */


typedef struct
{
	ia_byte    bSector;
	ia_word16  wEventId;
} msg_ippv_event_check_query_event_st;


/* Structure for MSG_IPPV_EVENT_CHECK_REPLY. */
typedef struct
{
	vd_rsc_id  wResourceId;	/* Smartcard. */
	ia_byte    bEventCount;
} msg_ippv_event_check_reply_st;
/* msg_ippv_event_check_reply_event_st astEvents[ bEventCount ] */


typedef struct
{
	ia_byte    bSector;
	ia_bool    fSectorValid;
	ia_bool    fEventValid;
	ia_word16  wEventId;
	ia_word16  wDateCode;		/* Valid if fEventValid == IA_TRUE. */
	ia_bool    fReported;
	ia_word16  wCost;		/* Valid if fEventValid == IA_TRUE. */
} msg_ippv_event_check_reply_event_st;


#endif /* S3_EVENT_IF_MSG_H. */
