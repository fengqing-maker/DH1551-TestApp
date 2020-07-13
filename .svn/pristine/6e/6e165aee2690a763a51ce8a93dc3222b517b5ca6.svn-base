
/*****************************************************************************
******************************************************************************
*
*        file : Decompression.h
*
* Description : Decompresses data compressed with the partner module.
*               The compressed file has a four byte marker that indicates
*               the data is in fact compressed data.
*
*
*      NOTE 1. : This method of compression is based on the program LZARI.C 
*                a LZSS arithmetic compression program by Haruhiko Okumura.
*                "LZARI.C 4/7/1989 Haruhiko Okumura"
*                The file LZARI.C was posted on BBS'es together with two other
*                programs by Haruhiko Okumura as part of a Dr Dobbs 
*                compression contest.
*
*
*      NOTE 2. : Some minor changes have been made including expansion
*                in the same buffer. The variables types have been changed
*                to meet the IRDETO coding standard otherwise the code and
*                comment changes have been kept to a minimum to avoid 
*                changing the behaviour of the program.
*
*      NOTE 3. : No CRC checking done here, should be done by the "user",
*                this should be for both the compressed and decompressed
*                data.
*
*      NOTE 4. : The buffer size and compressed size checks will be changed.
*                Possibly these check will be removed in the decoder version
*                of the decompression, as long as "head-end" tests are done
*                on the data with a similar routine.
*
*
*      Author : A Rossouw
*
*      Status : Draft
*
*     History :
*
*        $LOG : Decompression.h
*
*    Copyright: IRDETO 1994 (c)
*
******************************************************************************
*****************************************************************************/
#ifndef _DECOMPRESSION_H_
#define _DECOMPRESSION_H_

#include "LoaderCore_Types.h" 

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
*                                                                            *
*     ROUTINE : DECOMP_Decompress                                            *
*                                                                            *
* DESCRIPTION : Decompresses compressed data in the same buffer as the       *
*               compressed data.                                             *
*                                                                            *
*       INPUT : ulOriginalSize - the original uncompressed size of the data  *
*               ulPackedSize   - the compressed size of the data             *
*               pBufferIn      - pointer to buffer containing the compressed *
*                                data                                        *
*               pBufferOut     - pointer to buffer containing the            *
*                                decompressed data                           *
*                                                                            *
*                                                                            *
*      OUTPUT : pBuffer        - return buffer pointer  (same as input)      *
*                                                                            *
*     RETURNS :  0 = decompression was succesful                             *
*               -1 = buffer too small, should 2x compressed size             *
*               -2 = invalid type marker                                     *
*               -3 = resultant size larger than original                     *
*               -4 = over run, write pointer passed read pointer within the  *
*                    (same) buffer.                                          *
*                                                                            *
*      Author : A Rossouw                                                    *
*                                                                            *
* Last Changed: 16 Dec 94                                                    *
*                                                                            *
*****************************************************************************/
lc_sint32 DECOMP_Decompress(lc_uint32 ulOriginalSize, 
                      lc_uint32 ulCompressedSize, 
                      lc_uchar  *pBufferIn,
                      lc_uchar  *pBufferOut);


#ifdef __cplusplus
}
#endif

#endif /* _DECOMPRESSION_H_ */


