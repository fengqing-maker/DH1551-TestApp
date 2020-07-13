/**
 * $Id: s3_vddd.h,v 1.24 2011/11/24 06:26:46 wangtao Exp $
 *
 * Copyright Irdeto Access B.V.
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
 * This file is part of the 'DVB Descrambler driver'.
 * It contains all definitions for the smartcard virtual driver.
 **/

#ifndef S3_VDDD_H
#define S3_VDDD_H

#include "s3_portable_types.h"
#include "s3_vd.h"

/* VD_IO opcodes. */
enum
{
	VD_DD_SET_PID = ( VD_DRIVER_DVB_DESCRAMBLER * 10 ),
	VD_DD_SET_KEY,
	VD_DD_SET_ARIB_DATA,
	VD_DD_SET_SKEY,

	/* Modified for SCR #17920 */
	VD_DD_ADD_PID,
	VD_DD_REMOVE_PID,

	/*User story #77061: Clean up SCP3 program code in softcell 3.11*/
	VD_DD_SET_SESSION_KEY ,
	/*Added for the secure chipset phase3, load the key to the key ladder*/ 
	VD_DD_SET_ENCRYPTED_KEY,

	/*SoftCell shall support new descramble VD for SMP feature.*/
	VD_DD_KEY_COMMAND
};

/* Odd or even key. */
typedef enum
{
	VD_DD_KEY_ODD,
	VD_DD_KEY_EVEN
} vd_dd_key_type_e;

/* Used scrambling algorithm. */
typedef enum
{
	VD_DD_FAST_I          = 0,
	VD_DD_DVB             = 1,
	VD_DD_AES64           = 4,
	VD_DD_AES128_RCBC_CTS = 5,
	VD_DD_AES128_CBC_IA   = 6
} vd_dd_algorithm_e;

/* Structure used with VD_DD_SET_PID. */
typedef struct
{
	ia_word16          wPid;
} vd_dd_pid_st;

/* Structure used with VD_DD_SET_KEY. */
typedef struct
{
	vd_dd_key_type_e   eKeyType;
	vd_dd_algorithm_e  eAlgorithm;
	ia_word16          wKeyLength;
} vd_dd_key_st;

/* Structure used with VD_DD_SET_ARIB_DATA. */
typedef struct
{
	ia_word16          wKeyLength;
	ia_word16          wConfigLength;
} vd_dd_arib_data_st;

/*User story #77061: Clean up SCP3 program code in softcell 3.11*/


/* Used scrambling algorithm. */
typedef enum
{
	VD_DD_2TDES           = 0,
	/*User story #77061: Clean up SCP3 program code in softcell 3.11*/
	/*SoftCell shall support new synchronization IPI command.*/
	VD_DD_AES			  = 1
} vd_dd_scp3_algorithm_e;


typedef struct
{
	vd_dd_scp3_algorithm_e  eAlgorithm;
	ia_word16          		wKeyLength;
} vd_dd_scp3_skey_st;

#ifndef INCLUDE_GMSS
typedef enum
{
	VD_APP_DATA_OK,
	VD_APP_INVALID_CURS,
	VD_APP_AUTH_FAIL,
	VD_APP_UNKNOWN_HASH_ALGORITHM,
	VD_APP_UNKNOWN_RESPONSE
}vd_app_result_e;   

typedef struct 
{
   ia_byte    			bAKLCCount;
   ia_bool  			fAppDataExist;
   vd_dd_key_type_e   	eKeyType;
   vd_dd_algorithm_e  	eAlgorithm;
}vd_dd_key_input_st;


typedef struct 
{
    ia_byte 			bHeader[3];  
	ia_byte 			bEDCtrl;  /*now is 0*/
    ia_byte 			bExtraDataLength;  /*now is 0*/
    ia_byte 			bPayloadLength;
}vd_aklc_st;

typedef struct
{
    ia_byte  			bHeader[12];
    ia_byte  			bPayloadLength;
}vd_app_data_st;

typedef struct 
{
	vd_app_result_e  eResult;
}vd_app_result_st; 

typedef struct 
{
   ia_bool                 fAppDataExist;
   vd_dd_algorithm_e       eDescramblingKeyAlg;
   vd_dd_scp3_algorithm_e  eKeyLadderAlg;   
   ia_byte 				   bKeyVersion;
   ia_byte                 bEvenKeyLength;
   ia_byte                 bOddKeyLength;
   ia_byte                 bSessionKeyLen;   
   ia_byte				   bAppDataLen;
    				   
}vd_dd_testing_key_input_st;  

#endif

#endif /* S3_VDDD_H */
