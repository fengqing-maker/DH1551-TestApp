/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : VbCipher.c                                            
*                                                                            *
*   Description : This is used for encrypting or decrypting any data block   *
*                 of even size under a key of any size.                      *
*                                                                            *
*****************************************************************************/

#include "LoaderCorePrivate.h"


/*****************************************************************************
*                                                                            *
*     Routine : VBCIPHER_VariBlockCipher                                     *
*                                                                            *
* Description : VariBlockCipher - a single routine for encrypting and        *
*               decrypting any even block size under any size of key         *
*               securely, efficiently and simply. (A small modification would*
*               be required to allow for odd block sizes.)                   *
*                                                                            *
*               The decryption operation is identical, except the byte order *
*               in the provided key must be reversed.  The same routine can  *
*               be used for both operations only if bBlockSize is even.      *
*               The cipher is self-inverse for symmetric keys.               *
*                                                                            *
*               The operation may be done in place (both pointers equal), or *
*               may be done from one location to another non-overlapping     *
*               location.                                                    *
*                                                                            *
*               Although not shown to be necessary, it is preferred that the *
*               GCD of keysize and blocksize be 1.                           *
*                                                                            *
*               The blocksize and keysize may be made larger than bytes,     *
*               provided the internal variable set to the product of these is*
*               made long enough to accommodate this product.                *
*                                                                            *
*       Input : pabInBlock     : A pointer to the input block, ie the data   *
*                                block to be encrypted or decrypted.         *
*               bBlockSize     : The block size of the input block; must be  *
*                                an even number.                             *
*               pabKey         : A pointer to the key that should be used    *
*                                for encryption/decryption.                  *
*               bKeySize       : The key size in bytes.                      *
*                                                                            *
*      Output : pabOutBlock    : A pointer to the encrypted or decrypted     *
*                                block.                                      *
*                                                                           *
*     Returns : None.                                                        *
*                                                                            *
*      Author : Manfred von Willich                                          *
*                                                                            *
* Last Changed: 1995-05-25                                                   *
*                                                                            *
*****************************************************************************/
void VBCIPHER_VariBlockCipher (lc_uchar pabOutBlock [], 
                         const lc_uchar pabInBlock [],
                         const lc_uint16 wBlockSize,
                         const lc_uchar pabKey [], 
                         const lc_uchar bKeySize)
{

   static const lc_uchar abSbox [256] =
   {
      0x10, 0xDA, 0xA9, 0xA8, 0xC6, 0x6A, 0x7A, 0x4D,
      0x52, 0xF2, 0x02, 0xB2, 0xAA, 0x55, 0xB7, 0x45,
      0xA6, 0x9C, 0xFE, 0x90, 0xE8, 0xF1, 0x9E, 0x6F,
      0x98, 0x78, 0x7B, 0x88, 0xFC, 0xA3, 0x58, 0x9A,
      0x1A, 0xB5, 0xED, 0x97, 0x9F, 0x3E, 0xB4, 0x95,
      0x5E, 0xE0, 0x0C, 0x15, 0xBB, 0x1E, 0xD4, 0x13,
      0x17, 0xA4, 0x0A, 0x23, 0xA0, 0x28, 0x38, 0xA5,
      0x79, 0x65, 0xFD, 0xE3, 0x11, 0xEE, 0x9B, 0x87,
      0x18, 0x44, 0x60, 0x34, 0xD3, 0xC2, 0x92, 0xBD,
      0xE6, 0x83, 0xF6, 0x53, 0x7D, 0x99, 0x66, 0x6C,
      0x5C, 0x89, 0x74, 0x6E, 0x40, 0x68, 0xBC, 0xAB,
      0x57, 0x2D, 0xE2, 0x09, 0x85, 0xD8, 0xAC, 0xBA,
      0x77, 0xD9, 0xF7, 0xB8, 0x71, 0x47, 0xC7, 0x2B,
      0xE5, 0x31, 0x82, 0xCC, 0x64, 0x9D, 0x76, 0x8E,
      0x8A, 0xDC, 0x16, 0x7C, 0xFB, 0x33, 0x54, 0xA7,
      0xBF, 0x37, 0x63, 0x0B, 0x35, 0x6D, 0x5B, 0x32,
      0xCF, 0x51, 0xEF, 0xD5, 0x0F, 0x46, 0xB1, 0xC9,
      0x43, 0x00, 0x1C, 0x7E, 0x70, 0x8F, 0x29, 0x3F,
      0x0E, 0x4A, 0x5F, 0x41, 0xAF, 0xF8, 0xCB, 0xCD,
      0xE9, 0x75, 0x1B, 0xDD, 0x8B, 0xE7, 0x27, 0x59,
      0x73, 0x0D, 0xB9, 0x8C, 0x62, 0x20, 0xD6, 0xAD,
      0x7F, 0xA2, 0x1F, 0x49, 0x93, 0xCA, 0x2E, 0x07,
      0xDE, 0xDB, 0x94, 0x69, 0xEA, 0x14, 0x3C, 0x4F,
      0xD0, 0xC1, 0xEC, 0x8D, 0x39, 0xB6, 0xEB, 0xE4,
      0xBE, 0x30, 0xFF, 0x21, 0x42, 0x3A, 0xE1, 0x25,
      0x06, 0xF4, 0x03, 0xC4, 0x3D, 0x6B, 0xDF, 0x1D,
      0x2C, 0x81, 0x2F, 0x4B, 0xD2, 0x84, 0x4C, 0x56,
      0x86, 0x22, 0x01, 0xF3, 0x72, 0x24, 0x08, 0x05,
      0x67, 0x12, 0xFA, 0xD1, 0x80, 0xB3, 0x04, 0xC3,
      0xF5, 0x5A, 0x26, 0xC8, 0x36, 0xF0, 0x19, 0x48,
      0x4E, 0xC5, 0x91, 0x5D, 0x2A, 0xAE, 0x96, 0x50,
      0xF9, 0xB0, 0xA1, 0xD7, 0x61, 0xC0, 0x3B, 0xCE
   };
   lc_uint16 wStep;
   lc_uchar bTmp;
   lc_uint16 wI, wJ, wT0, wT1, wT2;

   /* reverse and copy data into the destination, which may be the source */
   for (wI=(wBlockSize+1)/2, wJ=wBlockSize-wI-1; wI < wBlockSize; wI++, wJ--)
   {
      bTmp = pabInBlock[wI];
      pabOutBlock[wI] = pabInBlock[wJ];
      pabOutBlock[wJ] = bTmp;
   }

   /* perform the ciphering loop */
   wI = 0;
   wJ = 0;
   wT0 = wBlockSize - 1;
   wT1 = 1;
   wT2 = (wBlockSize+1)/2;
   for (wStep = wBlockSize * bKeySize; wStep != 0; wStep--)
   {
      bTmp = abSbox[pabOutBlock[wI] ^ pabKey[wJ]];
      pabOutBlock[wT0] ^= bTmp;
      pabOutBlock[wT1] ^= bTmp;
      pabOutBlock[wT2] ^= bTmp;
      wT0 = wI;
      wI = wT1;
      wT1 += 1; 
      if (wT1 == wBlockSize) 
      {
         wT1 = 0;
      }
      wT2 += 1; 
      if (wT2 == wBlockSize) 
      {
         wT2 = 0;
      }
      wJ += 1; 
      if (wJ == bKeySize) 
      {
         wJ = 0;
      }
   }

   /* erase internal data for cleanliness */
   bTmp = 0x00;
}

