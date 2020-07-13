
/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : Crc.c                                                      *
*                                                                            *
*   Description : Used for calculating CRCs in the system.                   *
*               If possible all CRCs should be calculated using this module. *
*                                                                            *
*****************************************************************************/

#include "Crc.h"

/**** DEFINITIONS ***********************************************************/
#ifndef CRC_DEBUG
   #define TEXTIO_printf(x,y)
#endif

#ifdef  USE_DYNAMIC_LOOKUP_TABLES
/* local protypes */
static lc_uint32 ReturnTableEntry (lc_sint32 iIndex);
static lc_uint32 Reverse (lc_uint32 ulValue, lc_sint32 iBits);

/* The following are used to generate the lookup tabels   */
static lc_sint32  iWidth;    /* Width in bits [8,32].       */
static lc_uint32  ulPoly;    /* The algorithm's polynomial. */
static lc_bool fReverse;  /* Reflect input bytes         */

/* lookup tables */
static lc_uint32 ulTable_MPEG32[256];
static lc_uint32 ulTable_CRC32[256];
static lc_uint16 awTable_CRC16[256];

#endif  /* USE_DYNAMIC_LOOKUP_TABLES */


/*SUBTITLE CRC_MPEG32 */
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
lc_uint32 CRC_MPEG32(void *  pvStartAddress, lc_uint32 ulSize_in_bytes)
{
   lc_uint32 ulCRC;
   lc_uchar* pbData;

   /**********************
   * Lookup Table method *
   **********************/

   /* init the start value */
   ulCRC = 0xFFFFFFFF;

   pbData = pvStartAddress;

   /* calculate CRC */
   while (ulSize_in_bytes--)
   {
      ulCRC = ulTable_MPEG32[((ulCRC>>24) ^ *pbData++) & 0xFF] ^ (ulCRC << 8);
   }
   return ulCRC;


}  /* CRC_MPEG32 */

/*SUBTITLE CRC_16 */
/*PAGE*/

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
lc_uint16 CRC_16(void *  pvStartAddress, lc_uint32 ulSize_in_bytes)
{

   lc_uint16  wCRC;
   lc_uchar* pbData;

   TEXTIO_printf("pvStartAddress: %lx\n", (lc_uint32) pvStartAddress);
   TEXTIO_printf("Size: %lx\n", (lc_uint16) ulSize_in_bytes);
   
   /* init the start value */
   wCRC = 0x0;
   /* calculate CRC */
   pbData = pvStartAddress;

   #ifdef CRC_DEBUG
   if (ulSize_in_bytes < 100)
   {
      while (ulSize_in_bytes--)
      {
         TEXTIO_printf ("%x\n", *pbData);
         wCRC = (((wCRC >> 8) & 0xFF) ^ awTable_CRC16[((wCRC ^ *pbData++) & 0xFF)]);
         TEXTIO_printf ("%x\n", wCRC);
      }
   }
   else
   #endif
   {
      while (ulSize_in_bytes--)
      {
         wCRC = (((wCRC >> 8) & 0xFF) ^ awTable_CRC16[((wCRC ^ *pbData++) & 0xFF)]);
      }
   }
   
   return (wCRC);
}  /* CRC_16 */

/* Liu Xin [2002.03.06]
   Sometimes we need to verify several inconsecutive areas and get the final CRC16. */
lc_uint16 CRC_16_Seq(void *  pvStartAddress, lc_uint32 ulSize_in_bytes, lc_uint16 wInitValue)
{

   lc_uint16  wCRC;
   lc_uchar* pbData;

   TEXTIO_printf("pvStartAddress: %lx\n", (lc_uint32) pvStartAddress);
   TEXTIO_printf("Size: %lx\n", (lc_uint16) ulSize_in_bytes);
   
   /* init the start value */
   wCRC = wInitValue;
   /* calculate CRC */
   pbData = pvStartAddress;

   #ifdef CRC_DEBUG
   if (ulSize_in_bytes < 100)
   {
      while (ulSize_in_bytes--)
      {
         TEXTIO_printf ("%x\n", *pbData);
         wCRC = (((wCRC >> 8) & 0xFF) ^ awTable_CRC16[((wCRC ^ *pbData++) & 0xFF)]);
         TEXTIO_printf ("%x\n", wCRC);
      }
   }
   else
   #endif
   {
      while (ulSize_in_bytes--)
      {
         wCRC = (((wCRC >> 8) & 0xFF) ^ awTable_CRC16[((wCRC ^ *pbData++) & 0xFF)]);
      }
   }
   
   return (wCRC);
}  /* CRC_16 */

/*SUBTITLE CRC_Code32 */
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
lc_uint32 CRC_Code32(void *  pvStartAddress, lc_uint32 ulSize_in_bytes)
{

#define INIT  0xffffffff
#define XOROT 0xffffffff

   lc_uint32      ulCRC;
   lc_uchar   *pbData;          /* %% SRP changed to HuGe 15/02 */

   /* init the start value */
   ulCRC = INIT;
   pbData = pvStartAddress;
   /* calculate CRC */
   while (ulSize_in_bytes--)
   {
      ulCRC = ulTable_CRC32[(ulCRC ^ *pbData++) & 0xFF] ^ (ulCRC >> 8);
   }
   /* XOR the output value */
   return ulCRC ^ XOROT;
}


lc_uint32 CRC_Code32_Seq(void *  pvStartAddress, lc_uint32 ulSize_in_bytes, lc_uint32 wInitValue)
{

#define XOROT 0xffffffff

   lc_uint32      ulCRC;
   lc_uchar   *pbData;          /* %% SRP changed to HuGe 15/02 */

   /* init the start value */
   ulCRC = wInitValue;
   pbData = pvStartAddress;
   /* calculate CRC */
   while (ulSize_in_bytes--)
   {
      ulCRC = ulTable_CRC32[(ulCRC ^ *pbData++) & 0xFF] ^ (ulCRC >> 8);
   }
   /* XOR the output value */
   return ulCRC ^ XOROT;
}


#ifdef  USE_DYNAMIC_LOOKUP_TABLES
/*SUBTITLE CRC_CreateTables */
/*PAGE*/
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
void CRC_CreateTables(void)
{
   lc_sint32 i;

   /* do PC crc16 first */
   iWidth   = 16;
   ulPoly   = 0x8005;
   fReverse = LC_TRUE;

   for (i=0; i<256; i++)
   {
      awTable_CRC16[i] = (lc_uint16) ReturnTableEntry(i);
   }

   /* next, do PC type CRC-32 */
   iWidth   = 32;
   ulPoly   = 0x04C11DB7;
   fReverse = LC_TRUE;

   for (i=0; i<256; i++)
   {
      ulTable_CRC32[i] = (lc_uint32) ReturnTableEntry(i);
   }

   /* next, do MPEG type CRC-32 */
   iWidth   = 32;
   ulPoly   = 0x04C11DB7;
   fReverse = LC_FALSE;

   for (i=0; i<256; i++)
   {
      ulTable_MPEG32[i] = (lc_uint32) ReturnTableEntry(i);
   }

}


/*PAGE*/
/*****************************************************************************
*                                                                            *
*     ROUTINE : ReturnTableEntry                                             *
*                                                                            *
* DESCRIPTION : This routine returns a specific entry for a lookup table.    *
*               This routine uses some globally defined variables to         *
*               generate the value for the requested entry.                  *
*                                                                            *
*                                                                            *
*        NOTE : Nested routine for CRC_CreateTables ONLY.                    *
*                                                                            *
*                                                                            *
*       INPUT : iIndex - number of entry whose value is wanted.              *
*                                                                            *
*      OUTPUT : none                                                         *
*                                                                            *
*     RETURNS : the value.                                                   *
*                                                                            *
*      Author :  A.K.Rossouw                                                 *
*                                                                            *
* Last Changed:                                                              *
*                                                                            *
*****************************************************************************/
static lc_uint32 ReturnTableEntry (lc_sint32 iIndex)
{
   lc_sint32   i;
   lc_uint32 ulRetValue;
   lc_uint32 ulTopBit = (1 << (iWidth-1));
   lc_uint32 ulIndexedByte = (lc_uint32) iIndex;

   if (fReverse)
   {
      ulIndexedByte = Reverse(ulIndexedByte,8);
   }
   ulRetValue = ulIndexedByte << (iWidth-8);
   for (i=0; i<8; i++)
   {
      if (ulRetValue & ulTopBit)
      {
         ulRetValue = (ulRetValue << 1) ^ ulPoly;
      }
      else
      {
         ulRetValue<<=1;
      }
   }
   if (fReverse)
   {
      ulRetValue = Reverse(ulRetValue, iWidth);
   }
   return ulRetValue;
}


/*****************************************************************************
*                                                                            *
*     ROUTINE : Reverse                                                      *
*                                                                            *
* DESCRIPTION : This routine adjusts the data to the reversed or reflected   *
*               mode, the value returned has the bottom n bits reflected.    *
*                                                                            *
*                                                                            *
*        NOTE : Nested routine for ReturnTableEntry ONLY.                    *
*                                                                            *
*                                                                            *
*       INPUT : ulValue - input value                                        *
*               iBits   - number of bits to reflect (reverse)                *
*                                                                            *
*      OUTPUT : none                                                         *
*                                                                            *
*     RETURNS : the reversed value                                           *
*                                                                            *
*      Author :  A.K.Rossouw                                                 *
*                                                                            *
* Last Changed:                                                              *
*                                                                            *
*****************************************************************************/
static lc_uint32 Reverse (lc_uint32 ulValue, lc_sint32 iBits)
{
   lc_sint32   i;
   lc_uint32 ulTemp = ulValue;

   for (i=0; i<iBits; i++)
   {
      if (ulTemp & 1)
      {
         ulValue|=  (1 << ((iBits-1)-i));
      }
      else
      {
         ulValue&= ~(1 << ((iBits-1)-i));
      }
      ulTemp>>=1;
   }
   return ulValue;
}

#endif  /* USE_DYNAMIC_LOOKUP_TABLES */


