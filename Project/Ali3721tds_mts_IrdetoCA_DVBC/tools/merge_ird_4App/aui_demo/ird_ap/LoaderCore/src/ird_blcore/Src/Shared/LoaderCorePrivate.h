
#ifndef LOADERCORE_PRIVATE_H
#define LOADERCORE_PRIVATE_H


#include "LoaderCoreSPI.h"

/* helpers */
#include "ErrorReport.h"
#include "TraceLog.h"
#include "LcAssert.h"
#include "Bit.h"

/* algorithms */
#include "Crc.h"
#include "Pkcs.h"
#include "Sha1.h"
#include "Sha256.h"
#include "VbCipher.h"

/* modules */
#include "Bbcb.h"
#include "KeyUpdate.h"
#include "ModuleManager.h"
#include "LoaderPartition.h"

#include "UartInterface.h"
#include "LedDisplay.h"



#define LC_memcpy  LoaderCoreSPI_Stdlib_memcpy
#define LC_memset  LoaderCoreSPI_Stdlib_memset
#define LC_memcmp  LoaderCoreSPI_Stdlib_memcmp
#define LC_printf  LoaderCoreSPI_Stdlib_printf

/*Helper function to check lc_buffer_st pointer zero.*/
lc_result LC_CheckType_Bytes( const lc_buffer_st *pBytes );
/*Helper function to free pointer buffer and also set it to null.*/
void LC_Free_Memory( void **ppMem );
/*Helper function to allocate buffer and also memset it to zero.*/
void* LC_MALLOC(lc_uint32 bufferSize);

#define LC_UNUSED( x )    ( x )

#define LC_MIN(x,y) ((x)<(y)?(x):(y))

#define LC_MAX(x,y) ((x)>(y)?(x):(y))


#endif
