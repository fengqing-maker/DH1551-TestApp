
#if !defined(_AES_H_)
#define _AES_H_

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _aes_key {
   lc_uint32 eK[64], dK[64];
   lc_sint32 Nr;
} aes_key;

lc_sint32 aes_setup(const lc_uchar *key, 
                     lc_sint32 keylen, 
                     lc_sint32 rounds, 
                     aes_key *skey);

void aes_ecb_encrypt(const lc_uchar *pt, 
                            lc_uchar *ct, 
                            aes_key *key);

void aes_ecb_decrypt(const lc_uchar *ct, 
                            lc_uchar *pt, 
                            aes_key *key);


#ifdef __cplusplus
}
#endif

#endif


