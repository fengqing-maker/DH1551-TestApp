/*-
 * Copyright (c) 2001-2003 Allan Saddi <allan@saddi.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY ALLAN SADDI AND HIS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL ALLAN SADDI OR HIS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _PKCS_H
#define _PKCS_H

#include "../LoaderCore_Types.h"
#include "TomMacros.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Number of bits in a single element of a pkcs_long_num
 */
#define LC_RSA_ELEM_LEN_BITS (32)


#define LC_SHA1_HASH_LEN    (20)
#define LC_SHA256_HASH_LEN    (32)

/** 
 
* Length of signed CCP CAM signature
 
*/

#define SIGNATURE_LENGTH    256


/*!
 * \def LC_RSA_KEY_LEN_BITS
 * \brief Maximum length in bits of the key
 */
#define LC_RSA_KEY_LEN_BITS  (2048)

/*
 
* Length in bits of a pkcs_long_num type
 
*/

#define LC_RSA_MAX_LEN_BITS  ((LC_RSA_KEY_LEN_BITS*2)+LC_RSA_ELEM_LEN_BITS)

extern const lc_uchar loaderEnhancedSecureKey[];

typedef enum
{
    PKCS_SHA1_MODE = 0,
    PKCS_SHA256_MODE = 1,
    PKCS_UNSUPPORT_MODE = 2
} pkcs_hash_mode;

typedef struct
{
  /* 
   * Array which contains the pkcs_long_num, index 0 is the most significant 
   * element
   */
   lc_uint32 num[LC_RSA_MAX_LEN_BITS/LC_RSA_ELEM_LEN_BITS]; 
} pkcs_long_num;

typedef enum {

    /** (0x00000000) The operation was successful. */
    PKCS_ERROR_SUCCESS                        = 0x00000000,	
    
    /** (0x00000001) One or more required parameters were NULL. */
    PKCS_ERROR_NULL_PARAM                     = 0x00000001,  
    
    /** (0x00000002) The specified length was not valid. */
    PKCS_ERROR_INVALID_LENGTH                 = 0x00000002,
    
    /** (0x00000003) Signature verification failed. */
    PKCS_ERROR_SIGNATURE_VERIFICATION         = 0x00000003,
    
    /** (0x0000004) Some required internal data is missing. */
    PKCS_ERROR_MISSING_DATA                   = 0x00000004,    
    
    /** (0x0000005) Some required internal data is missing. */
    PKCS_ERROR_NONE_SHA1ORSHA256              = 0x00000005

} pkcs_result;


/**
 * Byte buffer structure
 *
 * This structure is used for passing arbitrary blocks of memory to the Universal Client API.
 * 
 * The caller sets the \a bytes member to point to a 
 * buffer, and sets the \a length member to be the length of the buffer.
 * 
 * When used as an output parameter, the function being called will copy data up to
 * the length of the buffer into the memory specified by \a bytes. When used as an
 * input parameter, the function leaves the contents of the buffer alone. 
 */
typedef struct _lc_buffer_st pkcs_buffer_st;


pkcs_result Rsa_CheckHashMode(pkcs_hash_mode *pPkcsHashMode);

pkcs_result Rsa_VerifyPkcs(lc_uchar* pRsaKey, const lc_uchar signature[SIGNATURE_LENGTH], pkcs_buffer_st *pHash);

#ifdef __cplusplus
}
#endif

#endif /* _PKCS_H */


