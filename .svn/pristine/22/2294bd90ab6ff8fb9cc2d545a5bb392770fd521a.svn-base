/**
 * $Id: s3_rsa_crypto.h,v 1.4 2009/02/02 13:02:50 ehietbrink Exp $
 *
 * Copyright 2004-2009 Irdeto Access B.V.
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

#ifndef S3_RSA_CRYPTO_H
#define S3_RSA_CRYPTO_H


#define RSA_SIGNATURE_LENGTH  128


enum
{
	E101_RSA_CRYPTO_OPERATION_FAILED = 101
};


typedef enum
{
	SIGNATURE_GOOD = 1,
	SIGNATURE_WRONG
} check_signature_result_e;


typedef struct
{
	vd_rsc_id                 wResourceId;
	ia_word16                 wDataLength;
} msg_smartcard_rsa_operation_data_st;


typedef struct
{
	vd_rsc_id                 wResourceId;
	ia_byte                   abSignature[ RSA_SIGNATURE_LENGTH ];
	ia_word16                 wDataLength;
} msg_smartcard_rsa_verify_operation_request_data_st;


typedef struct
{
	vd_rsc_id                 wResourceId;
	ia_byte                   abData[ RSA_SIGNATURE_LENGTH ];
} msg_smartcard_rsa_sign_operation_reply_data_st;


typedef struct
{
	vd_rsc_id                 wResourceId;
	check_signature_result_e  eResult;
} msg_smartcard_rsa_verify_operation_reply_data_st;


#endif  /* S3_RSA_CRYPTO_H */
