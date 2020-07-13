
#ifndef _CRC_H_
#define _CRC_H_

#include "LoaderCore_Types.h" /* Liu Xin [2002.08.02] */

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************
* The following switch controls whether the CRC32 for MPEG tables  *
* is the NTL code or akr's generated look up table code.           *
* The later is 33.4% to 50% faster                                 *
*******************************************************************/
#undef USE_NTL_MPEG_CRC32

/*******************************************************************
* The following switch controls whether the CRC checking is done   *
* from static or dynamically generated lookup tables.              *
* The later saves +/- 2kBytes of code space, but the table could   *
* be trashed be someone, ideal for the loader.                     *
*******************************************************************/
#undef  USE_STATIC_LOOKUP_TABLES
#define   USE_DYNAMIC_LOOKUP_TABLES


/*******************************************************************
* The use of the GLOBAL swiches DECODER_CODE and LOADER_CODE       *
* control the two switches above, as well as the inclusion of      *
* CRC_CCITT16. (DECODER_CODE only)                                 *
*******************************************************************/
#ifdef   USE_STATIC_LOOKUP_TABLES
#  ifdef    USE_DYNAMIC_LOOKUP_TABLES
#     error : ONLY STATIC or DYMANIC can be used, EXCLUSIVE of the other
#  endif
#else
#  ifndef   USE_DYNAMIC_LOOKUP_TABLES
#     error : neither STATIC or DYMANIC lookup tables specified
#  endif
#endif

#ifdef   USE_STATIC_LOOKUP_TABLES
#  define   LOOKUP_TABLE_TYPE 'S'
#else
#  define   LOOKUP_TABLE_TYPE 'D'
#endif
/*PAGE*/
/*****************************************************************************
*                                                                            *
*     ROUTINE : CRC_MPEG32                                                   *
*                                                                            *
* DESCRIPTION : Calculates the MPEG 32 bit CRC from a start address for the  *
*               size specified.                                              *
*                                                                            *
*                                                                            *
*        NOTE : This the algorithm was derived from NTL code.                *
*                                                                            *
*                                                                            *
*       INPUT : pvStartAddress  - start address of data for crc'ing          *
*               ulSize          - block size to be crc'ed                    *
*                                                                            *
*      OUTPUT : none                                                         *
*                                                                            *
*     RETURNS : 32 bit CRC code                                              *
*                                                                            *
*      Author :  W Keyser                                                    *
*                                                                            *
* Last Changed:                                                              *
*                                                                            *
*****************************************************************************/
lc_uint32 CRC_MPEG32(void *  pvStartAddress, lc_uint32 ulSize);



/*****************************************************************************
*                                                                            *
*     ROUTINE : CRC_16                                                       *
*                                                                            *
* DESCRIPTION : Calculates the "standard" PC 16 bit CRC from a start address *
*               for the size specified.  This the algorithm gives the same   *
*               result as used by PC archiving programs that use 16 bit CRCs.*
*               e.g. PKARC, LHA, LHARC, LZH etc.                             *
*                                                                            *
*       INPUT : pvStartAddress  - start address of data for crc'ing          *
*               ulSize          - block size to be crc'ed                    *
*                                                                            *
*      OUTPUT : none                                                         *
*                                                                            *
*     RETURNS : 16 bit CRC code                                              *
*                                                                            *
*      Author :  A.K.Rossouw                                                 *
*                                                                            *
* Last Changed:                                                              *
*                                                                            *
*****************************************************************************/
lc_uint16 CRC_16(void *  pvStartAddress, lc_uint32 ulSize);

/* Liu Xin [2002.03.06] */
lc_uint16 CRC_16_Seq(void *  pvStartAddress, lc_uint32 ulSize_in_bytes, lc_uint16 wInitValue);

/*****************************************************************************
*                                                                            *
*     ROUTINE : CRC_CCITT16                                                  *
*                                                                            *
* DESCRIPTION : Calculates the "standard" CCITT 16 bit CRC from a start      *
*               address for the size specified.  This the algorithm gives    *
*               the same result as required by XMODEM etc.                   *
*                                                                            *
*       INPUT : pvStartAddress  - start address of data for crc'ing          *
*               ulSize          - block size to be crc'ed                    *
*                                                                            *
*      OUTPUT : none                                                         *
*                                                                            *
*     RETURNS : 16 bit CRC code                                              *
*                                                                            *
*      Author :  A.K.Rossouw                                                 *
*                                                                            *
* Last Changed:                                                              *
*                                                                            *
*****************************************************************************/
lc_uint16 CRC_CCITT16(void *  pvStartAddress, lc_uint32 ulSize);


/*PAGE*/
/*****************************************************************************
*                                                                            *
*     ROUTINE : CRC_Code32                                                   *
*                                                                            *
* DESCRIPTION : Calculates the "standard" Computer 32 bit CRC from a start   *
*               address for the size specified.  This the algorithm gives    *
*               the same result as PKZIP, Ethernet and FDDI.                 *
*                                                                            *
*       INPUT : pvStartAddress  - start address of data for crc'ing          *
*               ulSize          - block size to be crc'ed                    *
*                                                                            *
*      OUTPUT : none                                                         *
*                                                                            *
*     RETURNS : 32 bit CRC code                                              *
*                                                                            *
*      Author :  A.K.Rossouw                                                 *
*                                                                            *
* Last Changed:                                                              *
*                                                                            *
*****************************************************************************/
lc_uint32 CRC_Code32(void *  pvStartAddress, lc_uint32 ulSize_in_bytes);

lc_uint32 CRC_Code32_Seq(void *  pvStartAddress, lc_uint32 ulSize_in_bytes, lc_uint32 wInitValue);



#ifdef  USE_DYNAMIC_LOOKUP_TABLES
/*****************************************************************************
*                                                                            *
*     ROUTINE : CRC_CreateTables                                             *
*                                                                            *
* DESCRIPTION : Creates the lookup tables dynamically. This can be called    *
*               many times, it will only recreated the tables.               *
*                                                                            *
*                                                                            *
*        NOTE : MUST be call at least once before any CRC routines are used, *
*               if this is not done, all CRCs tend to be zero.               *
*                                                                            *
*                                                                            *
*       INPUT : none                                                         *
*                                                                            *
*      OUTPUT : none                                                         *
*                                                                            *
*     RETURNS : none                                                         *
*                                                                            *
*      Author :  A.K.Rossouw                                                 *
*                                                                            *
* Last Changed:                                                              *
*                                                                            *
*****************************************************************************/
void CRC_CreateTables(void);
#endif

#ifdef __cplusplus
}
#endif

#endif   /* _CRC_H */
