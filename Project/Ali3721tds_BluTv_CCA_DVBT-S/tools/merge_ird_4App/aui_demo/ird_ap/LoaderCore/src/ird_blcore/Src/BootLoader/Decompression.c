
/*TITLE Decompression Routine*/
/*****************************************************************************
******************************************************************************
*
*        file : Decompression.c
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
*      Status : Final
*
*     History : Fix for multiple calls.
*
*        $LOG : Decompression.c
*
*    Copyright: IRDETO 1994 (c)
*
******************************************************************************
*****************************************************************************/
#include "Decompression.h"


/********** global variables of passed parameters ***********/
static lc_uchar  *pBufferRead;

/********** Bit I/O **********/

#define SAFETY_ZONE      16               

static lc_uchar bMask = 0;
static lc_uint32 GetBit(void)     /* Get one bit (0 or 1) */
{
   static lc_uchar bByteBuffer;

   if ((bMask >>= 1) == 0) 
   {
      bByteBuffer = *pBufferRead++; 
      bMask = 128;
   }
   return ((bByteBuffer & bMask) != 0);
}


/********** LZSS with multiple binary trees **********/

#define N       4096 /* size of ring buffer */
#define F         60 /* upper limit for match_length */
#define THRESHOLD 2   /* encode string into position and length
                     if match_length is greater than this */

/******************************************************************************
* ring buffer of size N, with extra F-1 bytes to facilitate string comparison *
* of longest match.  These are set by the InsertNode() procedure.             *
* left & right children & parents -- These constitute binary search trees.    *
******************************************************************************/
static lc_uint32 text_buf[N + F - 1];             

/********** Arithmetic Compression **********/

/*  If you are not familiar with arithmetic compression, you should read
      I. E. Witten, R. M. Neal, and J. G. Cleary,
         Communications of the ACM, Vol. 30, pp. 520-540 (1987),
   from which much have been borrowed.  */

#define M   15

/* Q1 (= 2 to the M) must be sufficiently large, but not so
   large as the unsigned long 4 * Q1 * (Q1 - 1) overflows.  */

#define Q1  (1 << M)
#define Q2  (2 * Q1)
#define Q3  (3 * Q1)
#define Q4  (4 * Q1)
#define MAX_CUM (Q1 - 1)

#define N_CHAR  (256 - THRESHOLD + F)
/* character code = 0, 1, ..., N_CHAR - 1 */

static lc_uint32 low = 0, high = Q4, value = 0;
static lc_uint32   sym_to_char[N_CHAR + 1];
static lc_uint32  sym_freq[N_CHAR + 1];  /* frequency for symbols */
static lc_uint32  sym_cum[N_CHAR + 1];   /* cumulative freq for symbols */
static lc_uint32  position_cum[N + 1];   /* cumulative freq for positions */

static void StartModel(void)  /* Initialize model */
{
   lc_uint32 ch, sym, i;

   sym_cum[N_CHAR] = 0;
   for (sym = N_CHAR; sym >= 1; sym--) 
   {
      ch = sym - 1;
      sym_to_char[sym] = ch;
      sym_freq[sym] = 1;
      sym_cum[sym - 1] = sym_cum[sym] + sym_freq[sym];
   }
   sym_freq[0] = 0;  /* sentinel (!= sym_freq[1]) */
   position_cum[N] = 0;
   for (i = N; i >= 1; i--)
   {
      position_cum[i - 1] = position_cum[i] + 10000 / (i + 200);
      /* empirical distribution function (quite tentative) */
      /* Please devise a better mechanism! */
   }
}

static void UpdateModel(lc_uint32 sym)
{
   lc_sint32 i;
   lc_uint32 c, ch_i, ch_sym;

   if (sym_cum[0] >= MAX_CUM) 
   {
      c = 0;
      for (i = N_CHAR; i > 0; i--) 
      {
         sym_cum[i] = c;
         c += (sym_freq[i] = (sym_freq[i] + 1) >> 1);
      }
      sym_cum[0] = c;
   }
   for (i = sym; sym_freq[i] == sym_freq[i - 1]; i--) 
   {
   }
   if (i < sym) 
   {
      ch_i = sym_to_char[i];    
      ch_sym = sym_to_char[sym];
      sym_to_char[i] = ch_sym;  
      sym_to_char[sym] = ch_i;
   }
   sym_freq[i]++;
   while (--i >= 0)
   {
      sym_cum[i]++;
   }
}

static lc_uint32 BinarySearchSym(lc_uint32 x)
/* 1      if x >= sym_cum[1],
   N_CHAR if sym_cum[N_CHAR] > x,
   i such that sym_cum[i - 1] > x >= sym_cum[i] otherwise */
{
   lc_uint32 i, j, k;

   i = 1;  j = N_CHAR;
   while (i < j) 
   {
      k = (i + j) / 2;
      if (sym_cum[k] > x) 
      {
         i = k + 1;
      }
      else
      {
         j = k;
      }
   }
   return i;
}

static lc_uint32 BinarySearchPos(lc_uint32 x)
/* 0 if x >= position_cum[1],
   N - 1 if position_cum[N] > x,
   i such that position_cum[i] > x >= position_cum[i + 1] otherwise */
{
   lc_uint32 i, j, k;

   i = 1;  j = N;
   while (i < j) 
   {
      k = (i + j) / 2;
      if (position_cum[k] > x) 
      {
         i = k + 1;
      }
      else
      {
         j = k;
      }
   }
   return i - 1;
}

static void StartDecode(void)
{
   lc_uint32 i;

   for (i = 0; i < M + 2; i++)
   {
      value = 2 * value + GetBit();
   }
}

static lc_uint32 DecodeChar(void)
{
   lc_uint32    sym, ch;
   lc_uint32  range;

   range = high - low;
   sym = BinarySearchSym((((value - low + 1) * sym_cum[0] - 1) / range));
   high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
   low +=       (range * sym_cum[sym    ]) / sym_cum[0];
   for ( ; ; ) 
   {
      if (low >= Q2) 
      {
         value -= Q2;  
         low -= Q2;  
         high -= Q2;
      } 
      else if (low >= Q1 && high <= Q3) 
      {
         value -= Q1;  
         low -= Q1;  
         high -= Q1;
      } 
      else if (high > Q2) 
      {
         break;
      }
      low += low;  
      high += high;
      value = 2 * value + GetBit();
   }
   ch = sym_to_char[sym];
   UpdateModel(sym);
   return ch;
}

static lc_uint32 DecodePosition(void)
{
   lc_uint32   position;
   lc_uint32 range;

   range = high - low;
   position = BinarySearchPos((unsigned int) (((value - low + 1) * position_cum[0] - 1) / range));
   high = low + (range * position_cum[position    ]) / position_cum[0];
   low +=       (range * position_cum[position + 1]) / position_cum[0];
   for ( ; ; ) 
   {
      if (low >= Q2) 
      {
         value -= Q2;  
         low -= Q2;
         high -= Q2;
      } 
      else if (low >= Q1 && high <= Q3) 
      {
         value -= Q1;  
         low -= Q1;  
         high -= Q1;
      } 
      else if (high > Q2)
      {
         break;
      }
      low += low;  
      high += high;
      value = 2 * value + GetBit();
   }
   return position;
}


/*SUBTITLE DECOMP_Decompress */
/*PAGE*/
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
*               pBufferOut     - pointer to buffer containing the           *
*                                 decompressed data                          *
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
                      lc_uchar  *pBufferOut) /*First part is buffer-in, the next part is buffer-out.*/
{
   lc_uint32  i, j, k, r, c;
   lc_uint32 lCount;
   lc_uint32 ulActual = 0;
   lc_uchar  *pbBufferWrite;


   if ((ulCompressedSize == 0) ||
      (ulCompressedSize > ulOriginalSize))
   {
      return -1;
   }

   pBufferRead = pBufferIn;

   if (!((*pBufferRead++ == 0x61) && 
      (*pBufferRead++ == 0x6b) &&
      (*pBufferRead++ == 0x72) && 
      (*pBufferRead++ == 0x2e)))
   {
      return -2;
   }

   pbBufferWrite = pBufferOut;

   /* init for multiple running */
   low   = 0;
   high  = Q4;
   value = 0;
   bMask = 0;
   
   StartDecode();
   StartModel();
   for (i = 0; i < N - F; i++)
   {
      text_buf[i] = ' ';
   }
   r = N - F;

   for (lCount = 0; lCount < ulOriginalSize; )
   {
      c = DecodeChar();
      if (c < 256)
      {
         *pbBufferWrite++ = (lc_uchar) c;
         if (++ulActual > ulOriginalSize)
         {
            return -3;
         }
         text_buf[r++] = c;
         r &= (N - 1);
         lCount++;
      }
      else
      {
         i = (r - DecodePosition() - 1) & (N - 1);
         j = c - 255 + THRESHOLD;
         for (k = 0; k < j; k++)
         {
            c = text_buf[(i + k) & (N - 1)];
            *pbBufferWrite++ = (lc_uchar) c;
            if (++ulActual > ulOriginalSize)
            {
               return -3;
            }
            text_buf[r++] = c;
            r &= (N - 1);
            lCount++;
         }
      }
   }
   return 0;
}
/*lint -restore */

