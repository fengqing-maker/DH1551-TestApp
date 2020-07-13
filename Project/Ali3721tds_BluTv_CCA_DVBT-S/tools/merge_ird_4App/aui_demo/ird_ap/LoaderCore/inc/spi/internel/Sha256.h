
#ifndef _SHA256_LOADER_H_
#define _SHA256_LOADER_H_

#include "../LoaderCore_Types.h"
#include "TomMacros.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SHA256_HASH_SIZE 32
/* Hash size in 32-bit words */
#define SHA256_HASH_WORDS 8

typedef struct _sha256_state {
    lc_uint32 length[2];
    lc_uint32 state[8], curlen;
    lc_uchar buf[64];
} sha256_state;

void sha256_init(sha256_state * md);

lc_sint32 sha256_process(sha256_state * md, 
                        const lc_uchar *buf, 
                        lc_uint32 len);

lc_sint32 sha256_done(sha256_state * md, 
                     lc_uchar *hash);

 lc_sint32 sha256_hash(
	 const lc_buffer_st *pMessage, 
	 lc_uchar *hash);

#ifdef __cplusplus
}
#endif

#endif /* _SHA256_LOADER_H_ */


