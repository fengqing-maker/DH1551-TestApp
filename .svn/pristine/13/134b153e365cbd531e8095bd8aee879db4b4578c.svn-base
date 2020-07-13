/**
 * $Id: s3_vd_loader.h,v 1.6 2012/11/05 10:53:23 wangtao Exp $
 *
 * Copyright 2004-2006 Irdeto Access B.V.
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

/**
 * This file is part of the 'loader virtual driver'.
 **/

#ifndef S3_VD_LOADER_H
#define S3_VD_LOADER_H

#include "s3_portable_types.h"
#include "s3_vd.h"

/* VD_IO opcodes. */
enum
{
	VD_LOADER_GET_SYSTEM_ID = ( VD_DRIVER_LOADER * 10 ),
	VD_LOADER_GET_KEY_VERSION,
	VD_LOADER_GET_SIGNATURE_VERSION,
	VD_LOADER_GET_VARIANT,
	VD_LOADER_GET_MANUFACTURER_ID,
	VD_LOADER_GET_HARDWARE_VERSION,
	VD_LOADER_GET_LOAD_VERSION,
	VD_LOADER_GET_SECURE_CHIP_CSSN,
	VD_LOADER_GET_LOADER_VERSION,	/* Fixed SCR#152574: [3.14]SoftCell3 need to support Enforce Firmware Upgrade */
	/*SCR#192479: [Global Pairing]SoftCell3 shall read private data before synchronizing with smart card.*/
	VD_LOADER_GET_PRIVATE_DATA,	
	/*Support CCA private data feature*/	
	VD_LOADER_GET_EXTERNAL_PRIVATE_DATA,
	/*To support CCC for TSC1.1*/
	VD_LOADER_GET_CHIP_CONFIGURATION_CHECK_MAC,
	/*SCR#389959: [STB Firmware Enforcement] Softcell shall calculate encrypted STB attributes (S').*/
	VD_LOADER_GET_IMAGE_VERSION

};

/* Structure used with VD_LOADER_GET_SYSTEM_ID. */
typedef struct
{
	ia_word16	wSystemId;
} vd_loader_system_id_st;

/* Structure used with VD_LOADER_GET_KEY_VERSION. */
typedef struct
{
	ia_word16	wKeyVersion;
} vd_loader_key_version_st;

/* Structure used with VD_LOADER_GET_SIGNATURE_VERSION. */
typedef struct
{
	ia_word16	wSignatureVersion;
} vd_loader_signature_version_st;

/* Structure used with VD_LOADER_GET_VARIANT. */
typedef struct
{
	ia_word16	wVariant;
} vd_loader_variant_st;

/* Structure used with VD_LOADER_GET_MANUFACTURER_ID. */
typedef struct
{
	ia_word16	wManufacturerId;
} vd_loader_manufacturer_id_st;

/* Structure used with VD_LOADER_GET_HARDWARE_VERSION. */
typedef struct
{
	ia_word16	wHardwareVersion;
} vd_loader_hardware_version_st;

/* Structure used with VD_LOADER_GET_LOAD_VERSION. */
typedef struct
{
	ia_word16	wLoadVersion;
} vd_loader_load_version_st;

/* Structure used with VD_LOADER_GET_SECURE_CHIP_CSSN. */
typedef struct
{
	ia_word32	wCSSN;
	ia_byte		bCrypto;
	ia_word32	wRsaBoot;
	ia_word32	wJtag;
	ia_word32	wCwMode;
} vd_loader_secure_chip_st;

/* Structure for loader version, used with VD_LOADER_GET_LOADER_VERSION. */
/* Fixed SCR#152574: [3.14]SoftCell3 need to support Enforce Firmware Upgrade */
typedef struct
{
	ia_byte bMajor;
	ia_byte bMinor;
} vd_loader_loader_version_st;

/*support chip configuration check*/
#define CCC_MAC_SIZE 16
typedef enum
{
    /*CCCK*/
    CCC_ENCRYPTION_KEY_ID_CCCK   = 6
}ccc_encryption_key_id_e;

/**Encryption algorithm**/
typedef enum
{
    /*TDES algorithm */
    CCC_ENCRYPTION_ALGORITHM_TDES   = 1,
    /*AES algorithm*/
    CCC_ENCRYPTION_ALGORITHM_AES    = 2
}ccc_encryption_algorithm_e;

typedef struct 
{
    /* Identifier of encryption key*/     
    ccc_encryption_key_id_e eKeyId; 
    /* Encryption algorithm*/     
    ccc_encryption_algorithm_e eAlgorithm; 
    /* The mask used for the Chip Configuration Check.*/     
    ia_byte abMask[CCC_MAC_SIZE];
}chip_configuration_check_query_st ;

typedef struct 
{
    /* 128-bit CBC-MAC */
    ia_byte abChipConfigurationMac[CCC_MAC_SIZE];
}chip_configuration_check_reply_st ;

/*SCR#389959: [STB Firmware Enforcement] Softcell shall calculate encrypted STB attributes (S').*/
#define MAX_IMAGE_VERSION_SIZE (32)

#endif /* S3_VD_LOADER_H */
