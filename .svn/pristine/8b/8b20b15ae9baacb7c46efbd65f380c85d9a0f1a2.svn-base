/**
 * @file LoaderCoreSPI_Stdlib.h
 * Header for C runtime standard library methods. This file contains the prototypes for all standard CRT functions 
 * that are used by the Loader Core.
 */

#include "LoaderCoreSPI.h"
#include <string.h>
#include <stdio.h>

/**
 * CRT memcpy function
 */
void *
LoaderCoreSPI_Stdlib_memcpy(
    void *pDest,
    const void *pSource,
    lc_uint32 count)
{
    return MEMCPY(pDest,pSource,count);
}


/**
 * CRT memset function
 */
void *
LoaderCoreSPI_Stdlib_memset(
    void *dest,
    lc_uchar c,
    lc_uint32 count)
{
    return MEMSET(dest,c, count);
}


/**
 * CRT memcmp function
 *
 * @param[in] pBuf1 Pointer to block of memory.
 * @param[in] pBuf2 Pointer to block of memory.
 * @param[in] len Number of bytes to compare.
 * @retval
 *     Returns an integral value indicating the relationship between the content of the memory blocks:
 *     A zero value indicates that the contents of both memory blocks are equal.
 *     A value greater than zero indicates that the first byte that does not match in both memory blocks has a greater value in ptr1 than in ptr2 as if evaluated as unsigned char values
{
	return LC_SUCCESS;
}

 *     And a value less than zero indicates the opposite. 
 */
lc_sint32
LoaderCoreSPI_Stdlib_memcmp(
    const lc_uchar *pBuf1,
    const lc_uchar *pBuf2,
    lc_uint32 len)
{
    return MEMCMP(pBuf1,pBuf2,len);
}


int LC_EXT_memcmp(const void *s1,const void *s2,lc_uint32 count)  
{  
    if(LC_NULL == s1 || LC_NULL == s2 || 0 == count)
    {
        LoaderCoreSPI_Stdlib_printf("%s ERROR:INVAILD parameter!!!\n", __FUNCTION__);
    }
    int res = 0;  
    const unsigned char *p1 =(const unsigned char *)s1;
    const unsigned char *p2 =(const unsigned char *)s2;   
    for(p1 ,p2;count > 0;p1++,p2++,count--)  
        if((res =*p1 - *p2) != 0)   
            break;  
    return res;  
}


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
    ...)
{
	libc_printf(pFormat);
    return 0;
}




