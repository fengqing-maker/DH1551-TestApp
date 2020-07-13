/****************************************************************************
*                                                                           *
* windef.h -- Basic Windows Type Definitions                                *
*                                                                           *
* Copyright (c) CastPal Corporation. All rights reserved.                 *
*                                                                           *
****************************************************************************/


#ifndef _MSWINDEF_
#define _MSWINDEF_


#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif /* NO_STRICT */

// Win32 defines _WIN32 automatically,
// but Macintosh doesn't, so if we are using
// Win32 Functions, we must do it here

#ifndef _WIN32
#define _WIN32
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WINVER
#define WINVER 0x0500
#endif /* WINVER */

/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */

#define MAX_PATH          260


#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifndef QS_QUIT
#define QS_QUIT				0x0800
#endif

#ifndef ZERO
#define ZERO 0
#endif

#ifndef BS_TYPEMASK
#define BS_TYPEMASK			0x0f
#endif


#undef far
#undef near
#undef pascal

#define far
#define near
#if (!defined(_MAC)) && ((_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED))
#define pascal __stdcall
#else
#define pascal
#endif

#if defined(DOSWIN32) || defined(_MAC)
#define cdecl _cdecl
#ifndef CDECL
#define CDECL _cdecl
#endif
#else
#define cdecl
#ifndef CDECL
#define CDECL
#endif
#endif

#ifdef _MAC
#define CALLBACK    PASCAL
#define WINAPI      CDECL
#define WINAPIV     CDECL
#define APIENTRY    WINAPI
#define APIPRIVATE  CDECL
#ifdef _68K_
#define PASCAL      __pascal
#else
#define PASCAL
#endif
#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#else
#define CALLBACK
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
#define PASCAL      pascal
#endif

#undef FAR
#undef  NEAR
#define FAR                 
#define NEAR                

#undef CONST
#define CONST               const

#ifndef WIN32
typedef  unsigned short		WCHAR;
typedef  WCHAR				*PWSTR;
typedef  WCHAR				*LPWSTR;
typedef  CONST WCHAR		*LPCWSTR;  
typedef  CONST CHAR			*LPCSTR, *PCSTR;
typedef  LPCSTR 			PCTSTR, LPCTSTR;

typedef CHAR *LPCH, *PCH;

typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;

typedef  char				TCHAR;
typedef  TCHAR 				*LPTSTR;

typedef  LONG				INT_PTR;
typedef  DWORD				UINT_PTR;
typedef  DWORD 				LONG_PTR;
typedef  DWORD 				ULONG_PTR;    

typedef ULONG_PTR DWORD_PTR,*PDWORD_PTR;
typedef ULONG_PTR SIZE_T,	*PSIZE_T;
typedef LONG_PTR SSIZE_T,	*PSSIZE_T;

typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;


typedef WORD				LANGID;      
typedef LONG				SCODE;
typedef DWORD				ACCESS_MASK;
typedef ACCESS_MASK			*PACCESS_MASK;
#endif

typedef struct _tagMSLUID {
	DWORD LowPart;
	LONG HighPart;
} MSLUID, *PMSLUID;
#ifndef _MSSYSTEMTIME_
#define _MSSYSTEMTIME_
typedef struct _MSSYSTEMTIME
    {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
    } 	MSSYSTEMTIME;

typedef struct _MSSYSTEMTIME  *PMSSYSTEMTIME;

typedef struct _MSSYSTEMTIME *LPMSSYSTEMTIME;

#endif // !_SYSTEMTIME
#ifndef _MSSECURITY_ATTRIBUTES_
#define _MSSECURITY_ATTRIBUTES_
typedef struct _CSSECURITY_ATTRIBUTES
    {
    DWORD nLength;
    /* [size_is] */ LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
    } 	MSSECURITY_ATTRIBUTES;

typedef struct _MSSECURITY_ATTRIBUTES *PMSSECURITY_ATTRIBUTES;

typedef struct _MSSECURITY_ATTRIBUTES *LPMSSECURITY_ATTRIBUTES;

#endif // !_SECURITY_ATTRIBUTES_

typedef unsigned int HMSHANDLE ;
typedef unsigned int HWNDCLASS;
typedef unsigned int HMSSURFACE;
typedef unsigned int HGDIOBJECT;
typedef	void * SEC_THREAD_START;
typedef unsigned int HDCPALETTE;
typedef unsigned int HMSZORDER;
typedef unsigned int HCLIPMSRECT;
typedef unsigned int HBUTTON;
typedef unsigned int HSTATIC;
typedef unsigned int HDIALOG;
typedef unsigned int HMSPALETTEENTRY;
typedef unsigned int HPALETTEORDER;
typedef unsigned int HPROGRESS;
typedef unsigned int HSCROLLBAR;
typedef unsigned int HEDIT;
typedef unsigned int HLINE;
typedef unsigned int HBUF;
typedef unsigned int HPATHLIST;
typedef unsigned int HPATHPAR;
typedef unsigned int HPATHOBJ;
typedef unsigned int HCLIPOBJ;
typedef unsigned int HMSRECTTYPE;
typedef unsigned int HCLIPLIST;
typedef unsigned int HMSICONIMAGEDATA;
typedef unsigned int HONESTACKMEMORY;
typedef unsigned int DHSURF;
typedef unsigned int DHPDEV;
typedef unsigned int HMSWND;
typedef unsigned int HMSHOOK;
typedef unsigned int HMSGDIOBJ;
typedef unsigned int HMSOBJECT;
typedef unsigned int HMSACCEL;
typedef unsigned int HMSBITMAP;
typedef unsigned int HMSBRUSH;
typedef unsigned int HMSCOLORSPACE;
typedef unsigned int HMSDC;
typedef unsigned int HMSGLRC;
typedef unsigned int HMSDESK;
typedef unsigned int HMSENHMETAFILE;
typedef unsigned int HMSFONT;
typedef unsigned int HMSICON;
typedef unsigned int HMSMENU;
typedef unsigned int HMSMETAFILE;
typedef unsigned int HMSINSTANCE;
typedef unsigned int HMSMODULE;
typedef unsigned int HMSPALETTE;
typedef unsigned int HMSPEN;
typedef unsigned int HMSRGN;
typedef unsigned int HMSRSRC;
typedef unsigned int HMSSTR;
typedef unsigned int HMSTASK;
typedef unsigned int HMSWINSTA;
typedef unsigned int HMSKL;
typedef unsigned int HMSMONITOR;
typedef unsigned int HMSWINEVENTHOOK;
typedef unsigned int HMSUMPD;
typedef unsigned int HMSCURSOR;
typedef unsigned int HMSKEY;
typedef unsigned int HMSRAWINPUT;

/* Types use for passing & returning polymorphic values */

#ifndef NOMINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  /* NOMINMAX */

#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))

typedef WORD                ATOM;

#ifndef _MAC
#ifdef _WIN64
typedef INT_PTR (FAR WINAPI *FARPROC)();
typedef INT_PTR (NEAR WINAPI *NEARPROC)();
typedef INT_PTR (WINAPI *PROC)();
#else
typedef int (FAR WINAPI *FARPROC)(void);
typedef int (NEAR WINAPI *NEARPROC)(void);
typedef int (WINAPI *PROC)(void);
#endif  // _WIN64
#else
typedef int (CALLBACK *FARPROC)();
typedef int (CALLBACK *NEARPROC)();
typedef int (CALLBACK *PROC)();
#endif

typedef DWORD   COLORREF;
typedef DWORD   *LPCOLORREF;

typedef struct tagMSRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} MSRECT, *PMSRECT, NEAR *NPMSRECT, FAR *LPMSRECT;

typedef const MSRECT FAR* LPCMSRECT;

typedef struct _MSRECTL       /* rcl */
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} MSRECTL, *PMSRECTL, *LPMSRECTL;

typedef const MSRECTL FAR* LPCMSRECTL;

typedef struct tagMSPOINT
{
    LONG  x;
    LONG  y;
} MSPOINT, *PMSPOINT, NEAR *NPMSPOINT, FAR *LPMSPOINT;

typedef struct _MSPOINTL      /* ptl  */
{
    LONG  x;
    LONG  y;
} MSPOINTL, *PMSPOINTL;

typedef struct tagMSSIZE
{
    LONG        cx;
    LONG        cy;
} MSSIZE, *PMSSIZE, *LPMSSIZE;

typedef MSSIZE               MSSIZEL;
typedef MSSIZE               *PMSSIZEL, *LPMSSIZEL;

typedef struct tagMSPOINTS
{
#ifndef _MAC
    SHORT   x;
    SHORT   y;
#else
    SHORT   y;
    SHORT   x;
#endif
} MSPOINTS, *PMSPOINTS, *LPMSPOINTS;

/* mode selections for the device mode function */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8

#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* device capabilities indices */
#define DC_FIELDS           1
#define DC_PAPERS           2
#define DC_PAPERMSSIZE        3
#define DC_MINEXTENT        4
#define DC_MAXEXTENT        5
#define DC_BINS             6
#define DC_DUPLEX           7
#define DC_MSSIZE             8
#define DC_EXTRA            9
#define DC_VERSION          10
#define DC_DRIVER           11
#define DC_BINNAMES         12
#define DC_ENUMRESOLUTIONS  13
#define DC_FILEDEPENDENCIES 14
#define DC_TRUETYPE         15
#define DC_PAPERNAMES       16
#define DC_ORIENTATION      17
#define DC_COPIES           18

#ifdef __cplusplus
}
#endif

#endif /* _MSWINDEF_ */
