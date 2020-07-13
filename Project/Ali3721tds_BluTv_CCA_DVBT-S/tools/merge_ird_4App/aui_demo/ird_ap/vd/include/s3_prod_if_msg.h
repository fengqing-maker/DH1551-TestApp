/**
 * $Id: s3_prod_if_msg.h,v 1.7 2008/06/06 06:26:32 ehietbrink Exp $
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

#ifndef S3_PROD_IF_MSG_H
#define S3_PROD_IF_MSG_H


/* Message structures for MSG_PRODUCT_CHECK_QUERY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_byte    bGracePeriod;
	ia_bool    fKeepTrack;
	ia_byte    bProductCount;
} msg_product_check_query_st;


typedef struct
{
	ia_byte    bSector;
	ia_bool    fAnySector;
	ia_word16  wProduct;
} msg_product_check_query_product_st;


/* Message structures for MSG_PRODUCT_CHECK_REPLY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_byte    bProductCount;
} msg_product_check_reply_st;


typedef struct
{
	ia_byte    bSector;
	ia_bool    fSectorValid;
	ia_bool    fProductValid;
	ia_word16  wProduct;
} msg_product_check_reply_product_st;


/* Message structures for MSG_ANY_PRODUCT_QUERY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_byte    bGracePeriod;
	ia_bool    fKeepTrack;
	ia_bool    fAnySector;
	ia_byte    bSectorCount;
} msg_any_product_query_st;


/* Message structures for MSG_ANY_PRODUCT_REPLY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_byte    bSectorCount;
} msg_any_product_reply_st;


typedef struct
{
	ia_byte    bSector;
	ia_bool    fSectorValid;
	ia_bool    fProductValid;
	ia_word16  wProduct;
} msg_any_product_reply_sector_st;


/* Message structures for MSG_PRODUCT_LIST_QUERY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_byte    bGracePeriod;
	ia_bool    fKeepTrack;
	ia_bool    fAnySector;
	ia_byte    bSectorCount;
} msg_product_list_query_st;


/* Message structures for MSG_PRODUCT_LIST_REPLY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_byte    bSectorCount;
} msg_product_list_reply_st;


typedef struct
{	ia_byte    bSector;
	ia_bool    fSectorValid;
	ia_byte    bProductCount;
} msg_product_list_sector_st;


/* Message structures for MSG_EXTENDED_PRODUCT_LIST_QUERY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_bool    fAnySector;
	ia_byte    bSectorCount;
} msg_extended_product_list_query_st;


/* Message structures for MSG_EXTENDED_PRODUCT_LIST_REPLY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_byte    bSectorCount;
} msg_extended_product_list_reply_st;


typedef struct
{
	ia_byte    bSector;
	ia_bool    fSectorValid;
	ia_word16  wSectorDateCode;	
	ia_byte    bProductCount;
} msg_extended_product_list_sector_st;


typedef struct
{
	ia_word16  wProductId;
	ia_word16  wStartDate;
	ia_byte    bDuration;
} msg_extended_product_list_product_st;


/* Message structures for MSG_EXPIRED_PRODUCT_QUERY. */
typedef struct
{
	vd_rsc_id  wResourceId;
} msg_expired_product_query_st;


/* Message structures for MSG_EXPIRED_PRODUCT_REPLY. */
typedef struct
{
	vd_rsc_id  wResourceId;
	ia_bool    fExpiredProductsExist;
} msg_expired_product_reply_st;


typedef struct
{
	ia_byte    bSector;
	ia_bool    fIsActive;
} msg_no_of_sectors_info_st;


#endif /* S3_PROD_IF_MSG_H. */
