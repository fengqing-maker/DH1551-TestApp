
#ifndef SHA1_H_
#define SHA1_H_

#include "LoaderCore_Types.h"
#include "TomMacros.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _sha1_state {
    lc_uint32 length[2];
    lc_uint32 state[5], curlen;
    lc_uchar buf[64];
} sha1_state;

void sha1_init(sha1_state * md);

lc_sint32 sha1_process(sha1_state * md, 
                        const lc_uchar *buf, 
                        lc_uint32 len);

lc_sint32 sha1_done(sha1_state * md, 
                     lc_uchar *hash);

#ifdef __cplusplus
}
#endif


#endif /* SHA1_H_ */

