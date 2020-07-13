
#ifndef _AURATYPEDEF_H_
#define _AURATYPEDEF_H_

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef WIN32
    typedef char			 CHAR;
    typedef CHAR			 *PCHAR;
    typedef CHAR			 *LPCHAR;

    typedef unsigned char    UCHAR;
    typedef UCHAR			 *PUCHAR;
    typedef UCHAR			 *LPUCHAR;

    typedef short			 SHORT;
    typedef SHORT			 *PSHORT;
    typedef SHORT			 *LPSHORT;

    typedef unsigned short   USHORT;
    typedef USHORT			 *PUSHORT;
    typedef USHORT			 *LPUSHORT;

    typedef long			 LONG;
    typedef LONG			 *PLONG;
    typedef LONG			 *LPLONG;

    typedef unsigned long	 ULONG;
    typedef ULONG			 *PULONG;
    typedef ULONG			 *LPULONG;

    typedef int              INT;
    typedef int              *PINT;
    typedef int              *LPINT;

    typedef unsigned int     UINT;
    typedef unsigned int     *PUINT;
    typedef unsigned int     *LPUINT;

    typedef float            FLOAT;
    typedef FLOAT            *PFLOAT;
    typedef FLOAT            *LPFLOAT;

    typedef void			 VOID;
    typedef void			 *PVOID;
    typedef void             *LPVOID;
    typedef const void       *LPCVOID;

    typedef char		 INT8;
    typedef short		 INT16;
    typedef int 		 INT32;
    typedef unsigned char	     UINT8;
    typedef unsigned short 	 UINT16;
    typedef unsigned int 	 UINT32;

#ifndef DEFINED_BOOL
    typedef unsigned int       BOOL;
#define  DEFINED_BOOL
#endif

    typedef BOOL             *PBOOL;
    typedef BOOL             *LPBOOL;

    typedef unsigned char 	 BYTE;
    typedef BYTE             *PBYTE;
    typedef BYTE             *LPBYTE;

    typedef  unsigned short	 WORD;
    typedef WORD             *PWORD;
    typedef WORD             *LPWORD;

    typedef unsigned int     DWORD;
    typedef DWORD            *PDWORD;
    typedef DWORD            *LPDWORD;
#else
#include <windows.h>
#endif

    /*Standard constants*/
#undef FALSE
#undef TRUE
#undef NULL

#define FALSE   		 ( ADI_FALSE)
#define TRUE    		 (ADI_TRUE)
#define NULL    		 (0)


#ifndef SUCCESS
#define SUCCESS			 (CSUDI_SUCCESS)
#endif

#ifndef FAILURE
#define FAILURE			 (CSUDI_FAILURE) 
#endif

#ifdef	__cplusplus
}
#endif
/** @} */

#endif

