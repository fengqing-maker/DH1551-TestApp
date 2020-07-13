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

/* SHA1 code by Tom St Denis */
#include "LoaderCorePrivate.h"


#define F0(x,y,z)  (z ^ (x & (y ^ z)))
#define F1(x,y,z)  (x ^ y ^ z)
#define F2(x,y,z)  ((x & y) | (z & (x | y)))
#define F3(x,y,z)  (x ^ y ^ z)

/*
#define STORE64H(x, y)                                                                     \
   { (y)[0] = (lc_uchar)(((x)>>56)&255); (y)[1] = (lc_uchar)(((x)>>48)&255);     \
     (y)[2] = (lc_uchar)(((x)>>40)&255); (y)[3] = (lc_uchar)(((x)>>32)&255);     \
     (y)[4] = (lc_uchar)(((x)>>24)&255); (y)[5] = (lc_uchar)(((x)>>16)&255);     \
     (y)[6] = (lc_uchar)(((x)>>8)&255); (y)[7] = (lc_uchar)((x)&255); }
*/

static void sha1_compress(sha1_state *md, lc_uchar *buf)
{
    lc_uint32 a,b,c,d,e,W[80],i;
    
    /* copy the state into 512-bits into W[0..15] */
    for (i = 0; i < 16; i++) {
        LOAD32H(W[i], buf + (4*i));
    }

    /* copy state */
    a = md->state[0];
    b = md->state[1];
    c = md->state[2];
    d = md->state[3];
    e = md->state[4];

    /* expand it */
    for (i = 16; i < 80; i++) {
        W[i] = ROL(W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16], 1); 
    }

    /* compress */
    /* round one */
    #define FF0(a,b,c,d,e,i) e = (ROL(a, 5) + F0(b,c,d) + e + W[i] + 0x5a827999); b = ROL(b, 30);
    #define FF1(a,b,c,d,e,i) e = (ROL(a, 5) + F1(b,c,d) + e + W[i] + 0x6ed9eba1); b = ROL(b, 30);
    #define FF2(a,b,c,d,e,i) e = (ROL(a, 5) + F2(b,c,d) + e + W[i] + 0x8f1bbcdc); b = ROL(b, 30);
    #define FF3(a,b,c,d,e,i) e = (ROL(a, 5) + F3(b,c,d) + e + W[i] + 0xca62c1d6); b = ROL(b, 30);
 
    for (i = 0; i < 20; ) {
       FF0(a,b,c,d,e,i++);
       FF0(e,a,b,c,d,i++);
       FF0(d,e,a,b,c,i++);
       FF0(c,d,e,a,b,i++);
       FF0(b,c,d,e,a,i++);
    }

    /* round two */
    for (; i < 40; )  { 
       FF1(a,b,c,d,e,i++);
       FF1(e,a,b,c,d,i++);
       FF1(d,e,a,b,c,i++);
       FF1(c,d,e,a,b,i++);
       FF1(b,c,d,e,a,i++);
    }

    /* round three */
    for (; i < 60; )  { 
       FF2(a,b,c,d,e,i++);
       FF2(e,a,b,c,d,i++);
       FF2(d,e,a,b,c,i++);
       FF2(c,d,e,a,b,i++);
       FF2(b,c,d,e,a,i++);
    }

    /* round four */
    for (; i < 80; )  { 
       FF3(a,b,c,d,e,i++);
       FF3(e,a,b,c,d,i++);
       FF3(d,e,a,b,c,i++);
       FF3(c,d,e,a,b,i++);
       FF3(b,c,d,e,a,i++);
    }

    #undef FF0
    #undef FF1
    #undef FF2
    #undef FF3

    /* store */
    md->state[0] = md->state[0] + a;
    md->state[1] = md->state[1] + b;
    md->state[2] = md->state[2] + c;
    md->state[3] = md->state[3] + d;
    md->state[4] = md->state[4] + e;
}

void sha1_init(sha1_state * md)
{
   md->state[0] = 0x67452301;
   md->state[1] = 0xefcdab89;
   md->state[2] = 0x98badcfe;
   md->state[3] = 0x10325476;
   md->state[4] = 0xc3d2e1f0;
   md->curlen = 0;
   md->length[0] = 0;
   md->length[1] = 0;
}

lc_sint32 sha1_process (sha1_state * md, const lc_uchar *buf, lc_uint32 len)
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
           sha1_compress (md, (lc_uchar *)buf);
           
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
           LC_memcpy(md->buf + md->curlen, buf, n);
           md->curlen += n;
           buf += n;
           len -= n;
           if (md->curlen == block_size)
           {
              sha1_compress (md, md->buf);

              md->length[0] += 8*block_size;

              if( 0xffffffff - block_size * 8 < md->length[0] && md->length[0] <=  0xffffffff )
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

lc_sint32 sha1_done(sha1_state * md, lc_uchar *hash)
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
        sha1_compress(md, md->buf);
        md->curlen = 0;
    }

    /* pad upto 56 bytes of zeroes */
    while (md->curlen < 56) {
        md->buf[md->curlen++] = (lc_uchar)0;
    }

    /* store length */
    /*STORE64H(md->length, md->buf+56);*/
    STORE64H_T(md->length,md->buf+56);
    sha1_compress(md, md->buf);




    /* copy output */
    for (i = 0; i < 5; i++) {
        STORE32H(md->state[i], hash+(4*i));
    }
    return CRYPT_OK;
}



