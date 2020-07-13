/*
 * $Id: s3_vd_stream_crypto.h,v 1.14 2012/05/16 10:46:26 wangtao Exp $
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
 */

/*
 * This file contains all the definitions for the 'Stream Crypto virtual driver'.
 */

#ifndef S3_VD_STREAM_CRYPTO_H
#define S3_VD_STREAM_CRYPTO_H

#include "s3_portable_types.h"
#include "s3_vd.h"

/* VD_IO() opcodes. */
enum
{
	VD_STREAM_CRYPTO_SET_KEY = ( VD_DRIVER_STREAM_CRYPTO * 10 ),
	VD_STREAM_CRYPTO_SET_KEY_BY_TYPE,
	/* Set secure chipset session key CSSK. */
	VD_STREAM_CRYPTO_SET_SKEY,
	/*Clean up SCP3 program code in softcell 3.11*/
	VD_STREAM_CRYPTO_SET_ENCRYPTED_KEY,
	/*SMP*/
	VD_STREAM_CRYPTO_KEY_COMMAND
};

/* Definitions of the algorithms. */
typedef enum
{
	VD_CRYPTO_ALGORITHM_AES,
	VD_CRYPTO_ALGORITHM_3DES
} vd_crypto_algorithm_e;

/* Definitions of the operations. */
typedef enum
{
	VD_CRYPTO_OPERATION_ENCRYPT,
	VD_CRYPTO_OPERATION_DECRYPT
} vd_crypto_operation_e;

/* Structure given in VD_Open() for this driver type. */
typedef struct
{
	vd_crypto_algorithm_e  eAlgorithm;
	vd_crypto_operation_e  eOperation;
} vd_stream_crypto_open_st;


typedef struct
{
	ia_word16  wKeyLength;
} vd_stream_crypto_key_st;


typedef enum
{
	VD_STREAM_CRYPTO_KEY_ODD,
	VD_STREAM_CRYPTO_KEY_EVEN,
	VD_STREAM_CRYPTO_KEY_SINGLE /*the DRM-fallback single key for VD_STREAM_CRYPTO_SET_ENCRYPTED_KEY*/
} vd_stream_crypto_key_type_e;

typedef struct
{
	vd_stream_crypto_key_type_e  eKeyType;
	vd_crypto_algorithm_e        eAlgorithm;
	ia_word16                    wKeyLength;
} vd_stream_crypto_key_by_type_st;


#ifndef INCLUDE_GMSS
typedef struct 
{
  	ia_byte    bAKLCCount;
  	ia_bool     fAppDataExist;
  	vd_stream_crypto_key_type_e  eKeyType;
  	vd_crypto_algorithm_e        eAlgorithm;
}vd_crypto_key_input_st;

#endif
#endif /* S3_VD_STREAM_CRYPTO_H */

