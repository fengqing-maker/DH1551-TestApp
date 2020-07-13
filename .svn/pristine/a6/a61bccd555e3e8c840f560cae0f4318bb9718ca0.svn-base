/**
 * $Id: s3_lppv_msg.h,v 1.3 2007/12/05 14:31:31 ehietbrink Exp $
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

#ifndef S3_LPPV_MSG_H
#define S3_LPPV_MSG_H

typedef enum
{
	LPPV_QUERY_SUCCESS = 1,
	LPPV_STB_NOT_SUPPORT,
	LPPV_CARD_NOT_SUPPORT,
	LPPV_CARD_ERROR,
	LPPV_MODE_ERROR,
	LPPV_QUERY_MODE_ERROR,
	LPPV_SECTOR_ERROR,
	LPPV_SECTOR_NOT_ACTIVE_ERROR,
	LPPV_PIN_FAIL_ERROR,
	LPPV_PIN_BLOCK_ERROR,
	LPPV_ORDER_EXIST_ERROR,
	LPPV_STORE_FULL_ERROR,
	LPPV_NO_TICKET_ID_ERROR,
	LPPV_DATE_CODE_ERROR,
	LPPV_DELETE_IPPV_ERROR,
	LPPV_RECHARGE_CODE_INVALID,
	LPPV_UNKNOWN_ERROR = 255
} lppv_query_status_e;
 
 enum
{
	LPPV_ALL_TICKET_RECORD = 1,
	LPPV_EXPIRIED_TICKET_RECORD,
	LPPV_ACTIVE_TICKET_RECORD
};


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSTBPPVMode;
} msg_lppv_aware_query_st;


typedef struct
{
	ia_byte              bSector;
	ia_byte              bSCPPVMode;
} msg_lppv_ppv_mode_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSCPPVMode;
	ia_byte              bSTBPPVMode;
	ia_byte              bSectorCount;
	lppv_query_status_e  eResult;
} msg_lppv_aware_reply_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_byte              bPreviewWindow;
	ia_byte              bBuyWindow;
	ia_byte              bTicketCount;
} msg_lppv_event_notify_st;


typedef struct
{
	ia_word16            wTicketId;
	ia_word16            wCost;
	ia_word16            wExpiryDataCode;
	ia_byte              bPurchaseStatus;
} msg_lppv_event_ticket_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_byte              bTicketMode;
} msg_lppv_read_ticket_query_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_byte              bTicketCount;
	lppv_query_status_e  eResult;
} msg_lppv_read_ticket_reply_st;


typedef struct
{
	ia_word16            wTicketId;
	ia_word16            wCost;
	ia_word16            wDateCode;
	ia_word16            wExpiryDataCode;
} msg_lppv_read_ticket_reply_ticket_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_word16            wTicketId;
	ia_byte              abPIN[ 2 ];
} msg_lppv_delete_ticket_query_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_word16            wTicketId;
	lppv_query_status_e  eResult;
} msg_lppv_delete_ticket_reply_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
} msg_lppv_read_credit_query_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_word16            wCredit;
	ia_word16            wCurrentDC;
	ia_word16            wExpiryDC;
	ia_bool              fClearOnExpiry;
	ia_word16            wLastIncreaseCredits;
	ia_word16            wLastIncreaseDC;
	lppv_query_status_e  eResult;
} msg_lppv_read_credit_reply_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
} msg_lppv_read_order_query_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_byte              bOrderCount;
	lppv_query_status_e  eResult;
} msg_lppv_read_order_reply_st;


typedef struct
{
	ia_word16            wTicketId;
	ia_bool              fIgnoreBuyWindow;
	ia_word16            wMaxCost;
	ia_word16            wExpiryDataCode;
} msg_lppv_read_order_reply_order_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_word16            wTicketId;
	ia_bool              fIgnoreBuyWindow;
	ia_word16            wMaxCost;
	ia_word16            wExpiryDataCode;
	ia_byte              abPIN[ 2 ];
} msg_lppv_place_order_query_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_word16            wTicketId;
	lppv_query_status_e  eResult;
} msg_lppv_place_order_reply_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_word16            wTicketId;
	ia_byte              abPIN[ 2 ];
} msg_lppv_cancel_order_query_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bSector;
	ia_word16            wTicketId;
	lppv_query_status_e  eResult;
} msg_lppv_cancel_order_reply_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              bTicketCount;
} msg_lppv_purchase_data_notify_st;


typedef struct
{
	ia_byte              bSector;
	ia_word16            wTicketId;
	ia_byte              bTextCount;
	ia_byte              bCostCount;
} msg_lppv_purchase_data_ticket_st;


typedef struct
{
	ia_char              abLanguage[ 3 ];
	ia_byte              bTicketTextCount;
} msg_lppv_purchase_data_text_st;


typedef struct
{
	ia_char              abCountry[ 3 ];
	ia_byte              bTicketCostCount;
} msg_lppv_purchase_data_cost_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	ia_byte              abRechargeCode[ 10 ];	/* Must contain 20 digits in BCD format. */
} msg_lppv_offline_recharge_code_query_st;


typedef struct
{
	vd_rsc_id            wResourceId;
	lppv_query_status_e  eResult;
} msg_lppv_offline_recharge_code_reply_st;


#endif /* S3_LPPV_MSG_H. */
