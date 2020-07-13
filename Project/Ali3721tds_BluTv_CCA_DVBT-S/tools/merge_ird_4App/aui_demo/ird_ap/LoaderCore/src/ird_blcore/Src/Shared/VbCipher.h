
/*****************************************************************************
******************************************************************************
**                                                                          **
**   (c) 1997 IRDETO Consultants  B.V.  All Rights Reserved.                **
**   This Software Code is provided "AS IS" without a warranty of any kind. **
**   All express or implied representations and warranties, including any   **
**   implied warranty of merchantability, fitness for a particular purpose, **
**   non-infringement are hereby excluded. All liabilities are disclaimed,  **
**   including express or implied liabilities, direct or indirect, and      **
**   consequential damages.                                                 **
**                                                                          **
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*          File : VbCipher.h                                                 *
*                                                                            *
*   Description : This is used for encrypting or decrypting any data block   *
*                 of even size under a key of any size.                      *
*                                                                            *
*        Status : Tested                                                     *
*                                                                            *
*        Author : Manfred von Willich                                        *
*                                                                            *
* Last modified : 1995-02-28                                                 *
*                                                                            *
*****************************************************************************/

#ifndef _VBCIPHER_H_
#define _VBCIPHER_H_

#ifdef __cplusplus
extern "C" {
#endif


/**** DEFINITIONS ***********************************************************/


/**** DECLARATIONS **********************************************************/

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
                         const lc_uchar bKeySize);


#ifdef __cplusplus
}
#endif

#endif
