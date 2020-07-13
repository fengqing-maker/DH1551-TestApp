/**
 * @file LoaderCoreSPI_Stdlib.h
 * Header for C runtime standard library methods. This file contains the prototypes for all standard CRT functions 
 * that are used by the Loader Core.
 */
#ifndef LOADERCORESPI_STDLIB_H__INCLUDED__
#define LOADERCORESPI_STDLIB_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup loadercorespis Loader Core SPIs
 *  Loader Core SPIs
 *
 *  
 *  @{
 */

/** @defgroup stdlib Loader Core Standard Library
 *  Loader Core Standard Library Functions
 *
 * These functions are a direct mapping of the corresponding ANSI C runtime libraries. 
 * In cases where these functions are already available on the platform, they can be used directly.
 * On platforms where full ANSI C runtime support is not provided, they need to be implemented manually.
 *  @{
 */

/**
 * CRT memcpy function
 */
void *
LoaderCoreSPI_Stdlib_memcpy(
    void *pDest,
    const void *pSource,
    lc_uint32 count);

/**
 * CRT memset function
 */
void *
LoaderCoreSPI_Stdlib_memset(
    void *dest,
    lc_uchar c,
    lc_uint32 count);

/**
 * CRT memcmp function
 *
 * @param[in] pBuf1 Pointer to block of memory.
 * @param[in] pBuf2 Pointer to block of memory.
 * @param[in] len Number of bytes to compare.
 * @retval
 *     Returns an integral value indicating the relationship between the content of the memory blocks:
 *     A zero value indicates that the contents of both memory blocks are equal.
 *     A value greater than zero indicates that the first byte that does not match in both memory blocks has a greater value in ptr1 than in ptr2 as if evaluated as unsigned char values;
 *     And a value less than zero indicates the opposite. 
 */
lc_sint32
LoaderCoreSPI_Stdlib_memcmp(
    const lc_uchar *pBuf1,
    const lc_uchar *pBuf2,
    lc_uint32 len);

/**
 * CRT printf function
 *
 * @param[in] pFormat C string that contains the text and format to be written to the buffer.
 * @retval
 *      On success, the total number of characters written is returned.
 *      On failure, a negative number is returned.
 */
lc_sint32
LoaderCoreSPI_Stdlib_printf(
    const lc_char *pFormat,
    ...);

int LC_EXT_memcmp(const void *s1,const void *s2,lc_uint32 count)  ;

/** @} */

/** @} */ /* End of Loader Core SPIs */

#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_STDLIB_H__INCLUDED__ */

