/* 
 * LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * gurantee it works.
 *
 * Tom St Denis, tomstdenis@iahu.ca, http://libtomcrypt.org
 */

/* SHA256 code by Tom St Denis */
#include "LoaderCorePrivate.h"


#define F0(x,y,z)  (z ^ (x & (y ^ z)))
#define F1(x,y,z)  (x ^ y ^ z)
#define F2(x,y,z)  ((x & y) | (z & (x | y)))
#define F3(x,y,z)  (x ^ y ^ z)

#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

#define Ch(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#define Maj(x, y, z) (((x) & ((y) | (z))) | ((y) & (z)))


#define SIGMA0(x) (ROTR((x), 2) ^ ROTR((x), 13) ^ ROTR((x), 22))
#define SIGMA1(x) (ROTR((x), 6) ^ ROTR((x), 11) ^ ROTR((x), 25))
#define sigma0(x) (ROTR((x), 7) ^ ROTR((x), 18) ^ ((x) >> 3))
#define sigma1(x) (ROTR((x), 17) ^ ROTR((x), 19) ^ ((x) >> 10))

#define DO_ROUND() { \
  t1 = h + SIGMA1(e) + Ch(e, f, g) + *(Kp++) + *(W++); \
  t2 = SIGMA0(a) + Maj(a, b, c); \
  h = g; \
  g = f; \
  f = e; \
  e = d + t1; \
  d = c; \
  c = b; \
  b = a; \
  a = t1 + t2; \
}

static const lc_uint32 K[64] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
  0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
  0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
  0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
  0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
  0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
  0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
  0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


static void sha256_compress(sha256_state *md, lc_uchar *cbuf)
{
    lc_uint32 a,b,c,d,e,i,f,g,h;
    lc_uint32 *W, *W2, *W7, *W15, *W16;
    lc_uint32 t1, t2;
    const lc_uint32 *Kp;
    lc_uint32 buf[64];

    W = buf;

    /* copy the state into 512-bits into W[0..15] */
    for (i = 0; i < 16; i++) {
        LOAD32H(*(W++), cbuf + (4*i));
    }

    /* expand it */
    W16 = &buf[0];
    W15 = &buf[1];
    W7 = &buf[9];  
    W2 = &buf[14];

    for (i = 0; i < 48; i++) 
    {    
        *(W++) = sigma1(*W2) + *(W7++) + sigma0(*W15) + *(W16++);    
        W2++;    
        W15++;
    }

    /* copy state */
    a = md->state[0];
    b = md->state[1];
    c = md->state[2];
    d = md->state[3];
    e = md->state[4];
    f = md->state[5];
    g = md->state[6];
    h = md->state[7];

    Kp = K;
    W = buf;

    /* compress */
    for (i = 0; i < 64; i++) 
    {
        DO_ROUND();
    }

    /* store */
    md->state[0] = md->state[0] + a;
    md->state[1] = md->state[1] + b;
    md->state[2] = md->state[2] + c;
    md->state[3] = md->state[3] + d;
    md->state[4] = md->state[4] + e;
    md->state[5] = md->state[5] + f;
    md->state[6] = md->state[6] + g;
    md->state[7] = md->state[7] + h;
}

void sha256_init(sha256_state * md)
{
   md->state[0] = 0x6a09e667;
   md->state[1] = 0xbb67ae85;
   md->state[2] = 0x3c6ef372;
   md->state[3] = 0xa54ff53a;
   md->state[4] = 0x510e527f;
   md->state[5] = 0x9b05688c;
   md->state[6] = 0x1f83d9ab;
   md->state[7] = 0x5be0cd19;
   md->curlen = 0;
   md->length[0] = 0;
   md->length[1] = 0;
}

lc_sint32 sha256_process (sha256_state * md, const lc_uchar *buf, lc_uint32 len)
{                                                                              
    lc_uint32 n;
    lc_uint32 block_size = 64;
    lc_uchar bTrafer_Flag = 0;

    if (md->curlen > sizeof(md->buf))
    {
       return CRYPT_INVALID_ARG;
    }
    while (len > 0)
    {
        if (md->curlen == 0 && len >= block_size)
        {
           sha256_compress (md, (lc_uchar *)buf);
           
           md->length[0] += block_size * 8;

           if( (0xffffffff - block_size * 8) < md->length[0] &&  md->length[0] <=  0xffffffff )
           {
                bTrafer_Flag = 1;
           }

           if((1 == bTrafer_Flag) && md->length[0] < block_size * 8)
           {
                md->length[1] += 1;
                bTrafer_Flag = 0;
           }
           
           buf += block_size;
           len -= block_size;
        }
        else
        {
           n = LC_MIN(len, (block_size - md->curlen));
           LC_memcpy(md->buf + md->curlen, buf, (unsigned int)n);
           md->curlen += n;
           buf += n;
           len -= n;
           if (md->curlen == block_size)
           {
              sha256_compress (md, md->buf);
              md->length[0] += block_size * 8;

              if( (0xffffffff - block_size * 8) < md->length[0] &&  md->length[0] <=  0xffffffff )
              {
                  bTrafer_Flag = 1;
              }

              if((1 == bTrafer_Flag) && md->length[0] < block_size * 8)
              {
                  md->length[1] += 1;
                  bTrafer_Flag = 0;
              }
           
              md->curlen = 0;
           }
       }
    }
    return CRYPT_OK;
}

lc_sint32 sha256_done(sha256_state * md, lc_uchar *hash)
{
    lc_sint32 i;

    if (md->curlen >= sizeof(md->buf)) {
       return CRYPT_INVALID_ARG;
    }

    /* increase the length of the message */
    if( (0xffffffff - md->curlen * 8) < md->length[0] && md->length[0] <=  0xffffffff && md->length[0] != 0 )
    {
       md->length[0] += md->curlen * 8;
       md->length[1] += 1;
    }
    else
    {
       md->length[0] += md->curlen * 8;
    }

    /* append the '1' bit */
    md->buf[md->curlen++] = (lc_uchar)0x80;

    /* if the length is currently above 56 bytes we append zeros
     * then compress.  Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (md->curlen > 56) {
        while (md->curlen < 64) {
            md->buf[md->curlen++] = (lc_uchar)0;
        }
        sha256_compress(md, md->buf);
        md->curlen = 0;
    }

    /* pad upto 56 bytes of zeroes */
    while (md->curlen < 56) {
        md->buf[md->curlen++] = (lc_uchar)0;
    }

    /* store length */
    STORE64H_T(md->length, md->buf+56);
    sha256_compress(md, md->buf);

    /* copy output */
    for (i = 0; i < SHA256_HASH_WORDS; i++) {
        STORE32H(md->state[i], hash+(4*i));
    }
    return CRYPT_OK;
}

 lc_sint32  sha256_hash(const lc_buffer_st *pMessage, lc_uchar *hash)
{
	lc_sint32 result = CRYPT_OK;
	sha256_state md;
	sha256_init(&md);

	result = sha256_process(&md, pMessage->bytes ,pMessage->length);
	
	if (CRYPT_OK == result)
	{
		result = sha256_done(&md, hash);
	}	

	return result;
}

