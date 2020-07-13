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

/* AES implementation by Tom St Denis
 *
 * Derived from the Public Domain source code by
 
---  
  * rijndael-alg-fst.c
  *
  * @version 3.0 (December 2000)
  *
  * Optimised ANSI C code for the Rijndael cipher (now AES)
  *
  * @author Vincent Rijmen <vincent.rijmen@esat.kuleuven.ac.be>
  * @author Antoon Bosselaers <antoon.bosselaers@esat.kuleuven.ac.be>
  * @author Paulo Barreto <paulo.barreto@terra.com.br>
---
 */

#include "Aes.h"
#include "AesTable.c"
#include "../Shared/TomMacros.h"


lc_sint32 aes_setup(const lc_uchar *key, lc_sint32 keylen, lc_sint32 rounds, aes_key *skey)
{
    lc_sint32 i, j;
    lc_uint32 temp, *rk, *rrk;
        
    if (keylen != 16 && keylen != 24 && keylen != 32) {
       return CRYPT_INVALID_KEYSIZE;
    }
    
    if (rounds != 0 && rounds != (10 + ((keylen/8)-2)*2)) {
       return CRYPT_INVALID_ROUNDS;
    }
    
    skey->Nr = 10 + ((keylen/8)-2)*2;
        
    /* setup the forward key */
    i                 = 0;
    rk                = skey->eK;
    LOAD32H(rk[0], key     );
    LOAD32H(rk[1], key +  4);
    LOAD32H(rk[2], key +  8);
    LOAD32H(rk[3], key + 12);
    if (keylen == 16) {
        j = 44;
        for (;;) {
            temp  = rk[3];
            rk[4] = rk[0] ^
                (Te4_3[byte(temp, 2)]) ^
                (Te4_2[byte(temp, 1)]) ^
                (Te4_1[byte(temp, 0)]) ^
                (Te4_0[byte(temp, 3)]) ^
                rcon[i];
            rk[5] = rk[1] ^ rk[4];
            rk[6] = rk[2] ^ rk[5];
            rk[7] = rk[3] ^ rk[6];
            if (++i == 10) {
               break;
            }
            rk += 4;
        }
    } else if (keylen == 24) {
        j = 52;   
        LOAD32H(rk[4], key + 16);
        LOAD32H(rk[5], key + 20);
        for (;;) {
        #ifdef _MSC_VER
            temp = skey->eK[rk - skey->eK + 5]; 
        #else
            temp = rk[5];
        #endif
            rk[ 6] = rk[ 0] ^
                (Te4_3[byte(temp, 2)]) ^
                (Te4_2[byte(temp, 1)]) ^
                (Te4_1[byte(temp, 0)]) ^
                (Te4_0[byte(temp, 3)]) ^
                rcon[i];
            rk[ 7] = rk[ 1] ^ rk[ 6];
            rk[ 8] = rk[ 2] ^ rk[ 7];
            rk[ 9] = rk[ 3] ^ rk[ 8];
            if (++i == 8) {
                break;
            }
            rk[10] = rk[ 4] ^ rk[ 9];
            rk[11] = rk[ 5] ^ rk[10];
            rk += 6;
        }
    } else if (keylen == 32) {
        j = 60;
        LOAD32H(rk[4], key + 16);
        LOAD32H(rk[5], key + 20);
        LOAD32H(rk[6], key + 24);
        LOAD32H(rk[7], key + 28);
        for (;;) {
        #ifdef _MSC_VER
            temp = skey->eK[rk - skey->eK + 7]; 
        #else
            temp = rk[7];
        #endif
            rk[ 8] = rk[ 0] ^
                (Te4_3[byte(temp, 2)]) ^
                (Te4_2[byte(temp, 1)]) ^
                (Te4_1[byte(temp, 0)]) ^
                (Te4_0[byte(temp, 3)]) ^
                rcon[i];
            rk[ 9] = rk[ 1] ^ rk[ 8];
            rk[10] = rk[ 2] ^ rk[ 9];
            rk[11] = rk[ 3] ^ rk[10];
            if (++i == 7) {
                break;
            }
            temp = rk[11];
            rk[12] = rk[ 4] ^
                (Te4_3[byte(temp, 3)]) ^
                (Te4_2[byte(temp, 2)]) ^
                (Te4_1[byte(temp, 1)]) ^
                (Te4_0[byte(temp, 0)]);
            rk[13] = rk[ 5] ^ rk[12];
            rk[14] = rk[ 6] ^ rk[13];
            rk[15] = rk[ 7] ^ rk[14];
            rk += 8;
        }
    } else {
       /* this can't happen */
       j = 4;
    }
    
    /* setup the inverse key now */
    rk   = skey->dK;
    rrk  = skey->eK + j - 4; 
    
    /* apply the inverse MixColumn transform to all round keys but the first and the last: */
    /* copy first */
    *rk++ = *rrk++;
    *rk++ = *rrk++;
    *rk++ = *rrk++;
    *rk   = *rrk;
    rk -= 3; rrk -= 3;
    
    for (i = 1; i < skey->Nr; i++) {
        rrk -= 4;
        rk  += 4;
    #ifdef SMALL_CODE        
        temp = rrk[0];
        rk[0] =
            Td0[255 & Te4[byte(temp, 3)]] ^
            Td1[255 & Te4[byte(temp, 2)]] ^
            Td2[255 & Te4[byte(temp, 1)]] ^
            Td3[255 & Te4[byte(temp, 0)]];
        temp = rrk[1];
        rk[1] =
            Td0[255 & Te4[byte(temp, 3)]] ^
            Td1[255 & Te4[byte(temp, 2)]] ^
            Td2[255 & Te4[byte(temp, 1)]] ^
            Td3[255 & Te4[byte(temp, 0)]];
        temp = rrk[2];
        rk[2] =
            Td0[255 & Te4[byte(temp, 3)]] ^
            Td1[255 & Te4[byte(temp, 2)]] ^
            Td2[255 & Te4[byte(temp, 1)]] ^
            Td3[255 & Te4[byte(temp, 0)]];
        temp = rrk[3];
        rk[3] =
            Td0[255 & Te4[byte(temp, 3)]] ^
            Td1[255 & Te4[byte(temp, 2)]] ^
            Td2[255 & Te4[byte(temp, 1)]] ^
            Td3[255 & Te4[byte(temp, 0)]];
     #else
        temp = rrk[0];
        rk[0] =
            Tks0[byte(temp, 3)] ^
            Tks1[byte(temp, 2)] ^
            Tks2[byte(temp, 1)] ^
            Tks3[byte(temp, 0)];
        temp = rrk[1];
        rk[1] =
            Tks0[byte(temp, 3)] ^
            Tks1[byte(temp, 2)] ^
            Tks2[byte(temp, 1)] ^
            Tks3[byte(temp, 0)];
        temp = rrk[2];
        rk[2] =
            Tks0[byte(temp, 3)] ^
            Tks1[byte(temp, 2)] ^
            Tks2[byte(temp, 1)] ^
            Tks3[byte(temp, 0)];
        temp = rrk[3];
        rk[3] =
            Tks0[byte(temp, 3)] ^
            Tks1[byte(temp, 2)] ^
            Tks2[byte(temp, 1)] ^
            Tks3[byte(temp, 0)];
      #endif            
     
    }

    /* copy last */
    rrk -= 4;
    rk  += 4;
    *rk++ = *rrk++;
    *rk++ = *rrk++;
    *rk++ = *rrk++;
    *rk   = *rrk;

    return CRYPT_OK;   
}

void aes_ecb_encrypt(const lc_uchar *pt, lc_uchar *ct, aes_key *skey)
{
    lc_uint32 s0, s1, s2, s3, t0, t1, t2, t3, *rk;
    lc_sint32 Nr, r;
       
    Nr = skey->Nr;
    rk = skey->eK;
    
    /*
     * map byte array block to cipher state
     * and add initial round key:
     */
    LOAD32H(s0, pt      ); s0 ^= rk[0];
    LOAD32H(s1, pt  +  4); s1 ^= rk[1];
    LOAD32H(s2, pt  +  8); s2 ^= rk[2];
    LOAD32H(s3, pt  + 12); s3 ^= rk[3];

    /*
     * Nr - 1 full rounds:
     */
    r = Nr >> 1;
    for (;;) {
        t0 =
            Te0[byte(s0, 3)] ^
            Te1[byte(s1, 2)] ^
            Te2[byte(s2, 1)] ^
            Te3[byte(s3, 0)] ^
            rk[4];
        t1 =
            Te0[byte(s1, 3)] ^
            Te1[byte(s2, 2)] ^
            Te2[byte(s3, 1)] ^
            Te3[byte(s0, 0)] ^
            rk[5];
        t2 =
            Te0[byte(s2, 3)] ^
            Te1[byte(s3, 2)] ^
            Te2[byte(s0, 1)] ^
            Te3[byte(s1, 0)] ^
            rk[6];
        t3 =
            Te0[byte(s3, 3)] ^
            Te1[byte(s0, 2)] ^
            Te2[byte(s1, 1)] ^
            Te3[byte(s2, 0)] ^
            rk[7];

        rk += 8;
        if (--r == 0) {
            break;
        }

        s0 =
            Te0[byte(t0, 3)] ^
            Te1[byte(t1, 2)] ^
            Te2[byte(t2, 1)] ^
            Te3[byte(t3, 0)] ^
            rk[0];
        s1 =
            Te0[byte(t1, 3)] ^
            Te1[byte(t2, 2)] ^
            Te2[byte(t3, 1)] ^
            Te3[byte(t0, 0)] ^
            rk[1];
        s2 =
            Te0[byte(t2, 3)] ^
            Te1[byte(t3, 2)] ^
            Te2[byte(t0, 1)] ^
            Te3[byte(t1, 0)] ^
            rk[2];
        s3 =
            Te0[byte(t3, 3)] ^
            Te1[byte(t0, 2)] ^
            Te2[byte(t1, 1)] ^
            Te3[byte(t2, 0)] ^
            rk[3];
    }
    /*
     * apply last round and
     * map cipher state to byte array block:
     */
    s0 =
        (Te4_3[(t0 >> 24)       ]) ^
        (Te4_2[(t1 >> 16) & 0xff]) ^
        (Te4_1[(t2 >>  8) & 0xff]) ^
        (Te4_0[(t3      ) & 0xff]) ^
        rk[0];
    STORE32H(s0, ct);
    s1 =
        (Te4_3[(t1 >> 24)       ]) ^
        (Te4_2[(t2 >> 16) & 0xff]) ^
        (Te4_1[(t3 >>  8) & 0xff]) ^
        (Te4_0[(t0      ) & 0xff]) ^
        rk[1];
    STORE32H(s1, ct+4);
    s2 =
        (Te4_3[(t2 >> 24)       ]) ^
        (Te4_2[(t3 >> 16) & 0xff]) ^
        (Te4_1[(t0 >>  8) & 0xff]) ^
        (Te4_0[(t1      ) & 0xff]) ^
        rk[2];
    STORE32H(s2, ct+8);
    s3 =
        (Te4_3[(t3 >> 24)       ]) ^
        (Te4_2[(t0 >> 16) & 0xff]) ^
        (Te4_1[(t1 >>  8) & 0xff]) ^
        (Te4_0[(t2      ) & 0xff]) ^ 
        rk[3];
    STORE32H(s3, ct+12);
}

void aes_ecb_decrypt(const lc_uchar *ct, lc_uchar *pt, aes_key *skey)
{
    lc_uint32 s0, s1, s2, s3, t0, t1, t2, t3, *rk;
    lc_sint32 Nr, r;
    
    Nr = skey->Nr;
    rk = skey->dK;

    /*
     * map byte array block to cipher state
     * and add initial round key:
     */
    LOAD32H(s0, ct      ); s0 ^= rk[0];
    LOAD32H(s1, ct  +  4); s1 ^= rk[1];
    LOAD32H(s2, ct  +  8); s2 ^= rk[2];
    LOAD32H(s3, ct  + 12); s3 ^= rk[3];

    /*
     * Nr - 1 full rounds:
     */
    r = Nr >> 1;
    for (;;) {

        t0 =
            Td0[byte(s0, 3)] ^
            Td1[byte(s3, 2)] ^
            Td2[byte(s2, 1)] ^
            Td3[byte(s1, 0)] ^
            rk[4];
        t1 =
            Td0[byte(s1, 3)] ^
            Td1[byte(s0, 2)] ^
            Td2[byte(s3, 1)] ^
            Td3[byte(s2, 0)] ^
            rk[5];
        t2 =
            Td0[byte(s2, 3)] ^
            Td1[byte(s1, 2)] ^
            Td2[byte(s0, 1)] ^
            Td3[byte(s3, 0)] ^
            rk[6];
        t3 =
            Td0[byte(s3, 3)] ^
            Td1[byte(s2, 2)] ^
            Td2[byte(s1, 1)] ^
            Td3[byte(s0, 0)] ^
            rk[7];

        rk += 8;
        if (--r == 0) {
            break;
        }


        s0 =
            Td0[byte(t0, 3)] ^
            Td1[byte(t3, 2)] ^
            Td2[byte(t2, 1)] ^
            Td3[byte(t1, 0)] ^
            rk[0];
        s1 =
            Td0[byte(t1, 3)] ^
            Td1[byte(t0, 2)] ^
            Td2[byte(t3, 1)] ^
            Td3[byte(t2, 0)] ^
            rk[1];
        s2 =
            Td0[byte(t2, 3)] ^
            Td1[byte(t1, 2)] ^
            Td2[byte(t0, 1)] ^
            Td3[byte(t3, 0)] ^
            rk[2];
        s3 =
            Td0[byte(t3, 3)] ^
            Td1[byte(t2, 2)] ^
            Td2[byte(t1, 1)] ^
            Td3[byte(t0, 0)] ^
            rk[3];
    }

    /*
     * apply last round and
     * map cipher state to byte array block:
     */
    s0 =
        (Td4[(t0 >> 24)       ] & 0xff000000) ^
        (Td4[(t3 >> 16) & 0xff] & 0x00ff0000) ^
        (Td4[(t2 >>  8) & 0xff] & 0x0000ff00) ^
        (Td4[(t1      ) & 0xff] & 0x000000ff) ^
        rk[0];
    STORE32H(s0, pt);
    s1 =
        (Td4[(t1 >> 24)       ] & 0xff000000) ^
        (Td4[(t0 >> 16) & 0xff] & 0x00ff0000) ^
        (Td4[(t3 >>  8) & 0xff] & 0x0000ff00) ^
        (Td4[(t2      ) & 0xff] & 0x000000ff) ^
        rk[1];
    STORE32H(s1, pt+4);
    s2 =
        (Td4[(t2 >> 24)       ] & 0xff000000) ^
        (Td4[(t1 >> 16) & 0xff] & 0x00ff0000) ^
        (Td4[(t0 >>  8) & 0xff] & 0x0000ff00) ^
        (Td4[(t3      ) & 0xff] & 0x000000ff) ^
        rk[2];
    STORE32H(s2, pt+8);
    s3 =
        (Td4[(t3 >> 24)       ] & 0xff000000) ^
        (Td4[(t2 >> 16) & 0xff] & 0x00ff0000) ^
        (Td4[(t1 >>  8) & 0xff] & 0x0000ff00) ^
        (Td4[(t0      ) & 0xff] & 0x000000ff) ^
        rk[3];
    STORE32H(s3, pt+12);
}



