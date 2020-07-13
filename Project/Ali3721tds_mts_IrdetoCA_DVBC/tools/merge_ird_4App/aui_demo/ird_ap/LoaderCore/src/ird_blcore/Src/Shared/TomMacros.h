
#if !defined(_TOMMACROS_H_)
#define _TOMMACROS_H_

#include "LoaderCore_Types.h"
#include "LoaderCorePrivate.h"

/* Enum for return value. */
enum {
    CRYPT_OK=0,             /* Result OK */
    CRYPT_ERROR,            /* Generic Error */
    CRYPT_NOP,              /* Not a failure but no operation was performed */
    
    CRYPT_INVALID_KEYSIZE,  /* Invalid key size given */
    CRYPT_INVALID_ROUNDS,   /* Invalid number of rounds */
    CRYPT_FALC_TESTVECTOR,  /* Algorithm failed test vectors */
    
    CRYPT_BUFFER_OVERFLOW,  /* Not enough space for output */
    CRYPT_INVALID_PACKET,   /* Invalid input packet given */
    
    CRYPT_INVALID_PRNGSIZE, /* Invalid number of bits for a PRNG */
    CRYPT_ERROR_READPRNG,   /* Could not read enough from PRNG */
    
    CRYPT_INVALID_CIPHER,   /* Invalid cipher specified */
    CRYPT_INVALID_HASH,     /* Invalid hash specified */
    CRYPT_INVALID_PRNG,     /* Invalid PRNG specified */
    
    CRYPT_MEM,              /* Out of memory */
    
    CRYPT_PK_TYPE_MISMATCH, /* Not equivalent types of PK keys */
    CRYPT_PK_NOT_PRIVATE,   /* Requires a private PK key */
    
    CRYPT_INVALID_ARG,      /* Generic invalid argument */
    CRYPT_FILE_NOTFOUND,    /* File Not Found */
    
    CRYPT_PK_INVALID_TYPE,  /* Invalid type of PK key */
    CRYPT_PK_INVALID_SYSTEM,/* Invalid PK system specified */
    CRYPT_PK_DUP,           /* Duplicate key already in key ring */
    CRYPT_PK_NOT_FOUND,     /* Key not found in keyring */
    CRYPT_PK_INVALID_SIZE,  /* Invalid size input for PK parameters */
    
    CRYPT_INVALID_PRIME_SIZE /* Invalid size of prime requested */
};


/* Configuration change this to suport your needs */
#ifndef ENDIAN_BIG
#define ENDIAN_LITTLE
#endif

#define ENDIAN_32BITWORD

#define STORE64H_T(x, y)                                                                     \
   { (y)[0] = (lc_uchar)(((x[1])>>24)&255); (y)[1] = (lc_uchar)(((x[1])>>16)&255);     \
     (y)[2] = (lc_uchar)(((x[1])>>8)&255); (y)[3] = (lc_uchar)(((x[1]))&255);     \
     (y)[4] = (lc_uchar)(((x[0])>>24)&255); (y)[5] = (lc_uchar)(((x[0])>>16)&255);     \
     (y)[6] = (lc_uchar)(((x[0])>>8)&255); (y)[7] = (lc_uchar)((x[0])&255); }

/* ---- HELPER MACROS ---- */

#ifdef ENDIAN_LITTLE

#define STORE32H(x, y)                                                                     \
     { (y)[0] = (lc_uchar)(((x)>>24)&255); (y)[1] = (lc_uchar)(((x)>>16)&255);   \
       (y)[2] = (lc_uchar)(((x)>>8)&255); (y)[3] = (lc_uchar)((x)&255); }

#define LOAD32H(x, y)                            \
     { x = ((lc_uint32)((y)[0] & 255)<<24) | \
           ((lc_uint32)((y)[1] & 255)<<16) | \
           ((lc_uint32)((y)[2] & 255)<<8)  | \
           ((lc_uint32)((y)[3] & 255)); }

#define STORE64H(x, y)                                                                     \
   { (y)[0] = (lc_uchar)(((x)>>56)&255); (y)[1] = (lc_uchar)(((x)>>48)&255);     \
     (y)[2] = (lc_uchar)(((x)>>40)&255); (y)[3] = (lc_uchar)(((x)>>32)&255);     \
     (y)[4] = (lc_uchar)(((x)>>24)&255); (y)[5] = (lc_uchar)(((x)>>16)&255);     \
     (y)[6] = (lc_uchar)(((x)>>8)&255); (y)[7] = (lc_uchar)((x)&255); }

#endif /* ENDIAN_LITTLE */

#ifdef ENDIAN_BIG
#define STORE32L(x, y)                                                                     \
     { (y)[0] = (lc_uchar)(((x)>>24)&255); (y)[1] = (lc_uchar)(((x)>>16)&255);   \
       (y)[2] = (lc_uchar)(((x)>>8)&255); (y)[3] = (lc_uchar)((x)&255); }

#define LOAD32L(x, y)                            \
     { x = ((lc_uint32)((y)[0] & 255)<<24) | \
           ((lc_uint32)((y)[1] & 255)<<16) | \
           ((lc_uint32)((y)[2] & 255)<<8)  | \
           ((lc_uint32)((y)[3] & 255)); }

#define STORE64L(x, y)                                                                     \
   { (y)[0] = (lc_uchar)(((x)>>56)&255); (y)[1] = (lc_uchar)(((x)>>48)&255);     \
     (y)[2] = (lc_uchar)(((x)>>40)&255); (y)[3] = (lc_uchar)(((x)>>32)&255);     \
     (y)[4] = (lc_uchar)(((x)>>24)&255); (y)[5] = (lc_uchar)(((x)>>16)&255);     \
     (y)[6] = (lc_uchar)(((x)>>8)&255); (y)[7] = (lc_uchar)((x)&255); }


#ifdef ENDIAN_32BITWORD 

#define STORE32H(x, y)        \
     { lc_uint32 __t = (x); LC_memcpy(y, &__t, 4); }

#define LOAD32H(x, y)         \
     LC_memcpy(&(x), y, 4);

#define STORE64H(x, y)                                                                     \
     { (y)[7] = (lc_uchar)(((x)>>56)&255); (y)[6] = (lc_uchar)(((x)>>48)&255);   \
       (y)[5] = (lc_uchar)(((x)>>40)&255); (y)[4] = (lc_uchar)(((x)>>32)&255);   \
       (y)[3] = (lc_uchar)(((x)>>24)&255); (y)[2] = (lc_uchar)(((x)>>16)&255);   \
       (y)[1] = (lc_uchar)(((x)>>8)&255); (y)[0] = (lc_uchar)((x)&255); }


#else /* 64-bit words then  */

#endif /* ENDIAN_64BITWORD */
#endif /* ENDIAN_BIG */

#define BSWAP(x)  ( ((x>>24)&0x000000FF) | ((x<<24)&0xFF000000)  | \
                    ((x>>8)&0x0000FF00)  | ((x<<8)&0x00FF0000) )


/* rotates the hard way */
#define ROL(x, y) ( (((lc_uint32)(x)<<(lc_uint32)((y)&31)) | (((lc_uint32)(x)&0xFFFFFFFF)>>(lc_uint32)(32-((y)&31)))) & 0xFFFFFFFF)
#define ROR(x, y) ( ((((lc_uint32)(x)&0xFFFFFFFF)>>(lc_uint32)((y)&31)) | ((lc_uint32)(x)<<(lc_uint32)(32-((y)&31)))) & 0xFFFFFFFF)


/* extract a byte portably */
#ifdef _MSC_VER
#  define byte(x, n) ((lc_uchar)((x) >> (8 * (n))))
#else
#  define byte(x, n) (((x) >> (8 * (n))) & 255)
#endif   

#endif
