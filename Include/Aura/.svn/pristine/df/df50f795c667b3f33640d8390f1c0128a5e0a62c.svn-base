
#ifndef _MSWINUSER_
#define _MSWINUSER_

//
// Define API decoration for direct importing of DLL references.
//


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef WINVER
#define WINVER  0x0500      /* version 5.0 */
#endif /* !WINVER */

#ifndef _WIN32_WINNT
#define _WIN32_WINNT	0x0500		/* version 5.0 */
#endif /* !WINVER */
	//#include <stdarg.h>

#ifndef NOUSER

	typedef HMSHANDLE HMSDWP;
	typedef VOID MENUTEMPLATEA;
	typedef MENUTEMPLATEA MENUTEMPLATE;
	typedef PVOID LPMENUTEMPLATEA;
	typedef LPMENUTEMPLATEA LPMENUTEMPLATE;

	typedef LRESULT( CALLBACK* MSWNDPROC )( HMSWND, UINT, WPARAM, LPARAM );

#ifdef STRICT

	typedef INT_PTR( CALLBACK* MSDLGPROC )( HMSWND, UINT, WPARAM, LPARAM );
	typedef VOID( CALLBACK* MSTIMERPROC )( HMSWND, UINT, UINT_PTR, DWORD );
	typedef BOOL( CALLBACK* MSGRAYSTRINGPROC )( HMSDC, LPARAM, int );
	typedef BOOL( CALLBACK* MSWNDENUMPROC )( HMSWND, LPARAM );
	typedef LRESULT( CALLBACK* MSHOOKPROC )( int code, WPARAM wParam, LPARAM lParam );
	typedef VOID( CALLBACK* MSSENDASYNCPROC )( HMSWND, UINT, ULONG_PTR, LRESULT );

	typedef BOOL( CALLBACK* MSPROPENUMPROCA )( HMSWND, LPCTSTR, HMSHANDLE );
	typedef BOOL( CALLBACK* MSPROPENUMPROCW )( HMSWND, LPCWSTR, HMSHANDLE );

	typedef BOOL( CALLBACK* MSPROPENUMPROCEXA )( HMSWND, LPTSTR, HMSHANDLE, ULONG_PTR );
	typedef BOOL( CALLBACK* MSPROPENUMPROCEXW )( HMSWND, LPWSTR, HMSHANDLE, ULONG_PTR );

	typedef int ( CALLBACK* MSEDITWORDBREAKPROCA )( LPTSTR lpch, int ichCurrent, int cch, int code );
	typedef int ( CALLBACK* MSEDITWORDBREAKPROCW )( LPWSTR lpch, int ichCurrent, int cch, int code );

#if(WINVER >= 0x0400)
	typedef BOOL( CALLBACK* MSDRAWSTATEPROC )( HMSDC hdc, LPARAM lData, WPARAM wData, int cx, int cy );
#endif /* WINVER >= 0x0400 */
#else /* !STRICT */

	typedef FARPROC MSDLGPROC;
	typedef FARPROC MSTIMERPROC;
	typedef FARPROC MSGRAYSTRINGPROC;
	typedef FARPROC MSWNDENUMPROC;
	typedef FARPROC MSHOOKPROC;
	typedef FARPROC MSSENDASYNCPROC;

	typedef FARPROC MSEDITWORDBREAKPROCA;

	typedef FARPROC MSPROPENUMPROCA;

	typedef FARPROC MSPROPENUMPROCEXA;

#if(WINVER >= 0x0400)
	typedef FARPROC MSDRAWSTATEPROC;
#endif /* WINVER >= 0x0400 */
#endif /* !STRICT */

	typedef MSPROPENUMPROCA        MSPROPENUMPROC;
	typedef MSPROPENUMPROCEXA      MSPROPENUMPROCEX;
	typedef MSEDITWORDBREAKPROCA   MSEDITWORDBREAKPROC;

#ifdef STRICT

	typedef BOOL( CALLBACK* MSNAMEENUMPROCA )( LPTSTR, LPARAM );
	typedef BOOL( CALLBACK* MSNAMEENUMPROCW )( LPWSTR, LPARAM );

	typedef MSNAMEENUMPROCA   MSWINSTAENUMPROCA;
	typedef MSNAMEENUMPROCA   MSDESKTOPENUMPROCA;


#else /* !STRICT */

	typedef FARPROC MSNAMEENUMPROCA;
	typedef FARPROC MSWINSTAENUMPROCA;
	typedef FARPROC MSDESKTOPENUMPROCA;


#endif /* !STRICT */

	typedef MSWINSTAENUMPROCA     MSWINSTAENUMPROC;
	typedef MSDESKTOPENUMPROCA    MSDESKTOPENUMPROC;


#define IS_INTRESOURCE(_r) (((ULONG_PTR)(_r) >> 16) == 0)
#undef MAKEINTRESOURCE
#define MAKEINTRESOURCE(i) (LPTSTR)((ULONG_PTR)((WORD)(i)))


#ifndef NORESOURCE

	/*
	 * Predefined Resource Types
	 */
#define RT_CURSOR           MAKEINTRESOURCE(1)
#define RT_BITMAP           MAKEINTRESOURCE(2)
#define RT_ICON             MAKEINTRESOURCE(3)
#define RT_MENU             MAKEINTRESOURCE(4)
#define RT_DIALOG           MAKEINTRESOURCE(5)
#define RT_STRING           MAKEINTRESOURCE(6)
#define RT_FONTDIR          MAKEINTRESOURCE(7)
#define RT_FONT             MAKEINTRESOURCE(8)
#define RT_ACCELERATOR      MAKEINTRESOURCE(9)
#define RT_RCDATA           MAKEINTRESOURCE(10)
#define RT_MESSAGETABLE     MAKEINTRESOURCE(11)

#define DIFFERENCE     11
#define RT_GROUP_CURSOR MAKEINTRESOURCE((ULONG_PTR)RT_CURSOR + DIFFERENCE)
#define RT_GROUP_ICON   MAKEINTRESOURCE((ULONG_PTR)RT_ICON + DIFFERENCE)
#define RT_VERSION      MAKEINTRESOURCE(16)
#define RT_DLGINCLUDE   MAKEINTRESOURCE(17)
#if(WINVER >= 0x0400)
#define RT_PLUGPLAY     MAKEINTRESOURCE(19)
#define RT_VXD          MAKEINTRESOURCE(20)
#define RT_ANICURSOR    MAKEINTRESOURCE(21)
#define RT_ANIICON      MAKEINTRESOURCE(22)
#endif /* WINVER >= 0x0400 */
#define RT_HTML         MAKEINTRESOURCE(23)
#ifdef RC_INVOKED
#define RT_MANIFEST                        24
#define CREATEPROCESS_MANIFEST_RESOURCE_ID  1
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID 2
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID 3
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID 1   /* inclusive */
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID 16  /* inclusive */
#else  /* RC_INVOKED */
#define RT_MANIFEST                        MAKEINTRESOURCE(24)
#define CREATEPROCESS_MANIFEST_RESOURCE_ID MAKEINTRESOURCE( 1)
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(2)
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(3)
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE( 1 /*inclusive*/)
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(16 /*inclusive*/)
#endif /* RC_INVOKED */


#endif /* !NORESOURCE */


		int
		MSwsprintf(
		OUT LPTSTR,
		IN LPCTSTR,
		... );

	 
		int
		MSwcslen(
		const char* pchwStr );

	 
		char*
		MSwcscpy(
		char* pchwDestStr,
		const char* pchwSrcStr );
	 
		int
		MSwcscmp(
		const char *string1,
		const char *string2 );

	 
		char*
		MSwcsncpy(
		char* pchwDestStr,
		const char* pchwSrcStr,
		int nCount );

	 
		char* MSwcscat( char* pchwDestStr,
		const char* pchwSrcStr );

	 
		char* MSwcsncat( char* pchwDestStr, const char* pchwSrcStr, int nCount );

	 
		int
		WINAPI
		MSMultiByteToWideChar(
		IN UINT     CodePage,
		IN DWORD    dwFlags,
		IN LPCSTR   lpMultiByteStr,
		IN int      cbMultiByte,
		OUT LPWSTR  lpWideCharStr,
		IN int      cchWideChar );


	 
		int
		WINAPI
		MSSetDefaultLanguageCode(
		int     nCode );


	 
		double
		WINAPI
		MSwtof(
		const char* string
		);

	 
		int
		WINAPI
		MSwtoi(
		const char* string
		);

	 
		long
		WINAPI
		MSwtol(
		const char* string
		);
	 
		long
		WINAPI
		MSwcstol(
		const char* nptr,
		char** endptr,
		int base );




	/*
	 * SPI_SETDESKWALLPAPER defined constants
	 */
#define SETWALLPAPER_DEFAULT    ((LPWSTR)-1)

#ifndef NOSCROLL

	/*
	 * Scroll Bar Constants
	 */
#define SB_HORZ             0
#define SB_VERT             1
#define SB_CTL              2
#define SB_BOTH             3

	/*
	 * Scroll Bar Commands
	 */
#define SB_LINEUP           0
#define SB_LINELEFT         0
#define SB_LINEDOWN         1
#define SB_LINERIGHT        1
#define SB_PAGEUP           2
#define SB_PAGELEFT         2
#define SB_PAGEDOWN         3
#define SB_PAGERIGHT        3
#define SB_THUMBPOSITION    4
#define SB_THUMBTRACK       5
#define SB_TOP              6
#define SB_LEFT             6
#define SB_BOTTOM           7
#define SB_RIGHT            7
#define SB_ENDSCROLL        8

#endif /* !NOSCROLL */

#ifndef NOSHOWWINDOW


	/*
	 * MSShowWindow() Commands
	 */
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

	/*
	 * Old MSShowWindow() Commands
	 */
#define HIDE_WINDOW         0
#define SHOW_OPENWINDOW     1
#define SHOW_ICONWINDOW     2
#define SHOW_FULLSCREEN     3
#define SHOW_OPENNOACTIVATE 4

	/*
	 * Identifiers for the WM_SHOWWINDOW message
	 */
#define SW_PARENTCLOSING    1
#define SW_OTHERZOOM        2
#define SW_PARENTOPENING    3
#define SW_OTHERUNZOOM      4


#endif /* !NOSHOWWINDOW */

#if(WINVER >= 0x0500)
	/*
	 * AnimateWindow() Commands
	 */
#define AW_HOR_POSITIVE             0x00000001
#define AW_HOR_NEGATIVE             0x00000002
#define AW_VER_POSITIVE             0x00000004
#define AW_VER_NEGATIVE             0x00000008
#define AW_CENTER                   0x00000010
#define AW_HIDE                     0x00010000
#define AW_ACTIVATE                 0x00020000
#define AW_SLIDE                    0x00040000
#define AW_BLEND                    0x00080000

#endif /* WINVER >= 0x0500 */


	/*
	 * WM_KEYUP/DOWN/CHAR HIWORD(lParam) flags
	 */
#define KF_EXTENDED       0x0100
#define KF_DLGMODE        0x0800
#define KF_MENUMODE       0x1000
#define KF_ALTDOWN        0x2000
#define KF_REPEAT         0x4000
#define KF_UP             0x8000

#ifndef NOVIRTUALKEYCODES


	/*
	 * Virtual Keys, Standard MSSet
	 */
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

	/*
	 * 0x07 : unassigned
	 */
#define VK_RECALL		  0x07
#define VK_BACK           0x08
#define VK_TAB            0x09

	/*
	 * 0x0A - 0x0B : reserved
	 */

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D

#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14

#define VK_KANA           0x15
#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19

#define VK_ESCAPE         0x1B

#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F

#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

	/*
	 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	 * 0x40 : unassigned
	 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	 */
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A


#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D
#define	VK_TIMER          0x5E
	/*
	 * 0x5E : reserved
	 */

#define VK_SLEEP          0x5F

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

	/*
	 * 0x88 - 0x8F : unassigned
	 */
#define VK_MUTE       0x88
#define VK_POWER      0x89
#define VK_TV_RADIO   0x8A
#define VK_TELETEXT   0x8B
#define VK_SUBTITLE   0x8C
#define VK_AUDIO      0x8D
#define VK_PAGE_DOWN  0x8E
#define VK_PAGE_UP    0x8F


#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

	/*
	 * NEC PC-9800 kbd definitions
	 */
#define VK_OEM_NEC_EQUAL  0x92   // '=' key on numpad

	/*
	 * Fujitsu/OASYS kbd definitions
	 */
#define VK_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define VK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define VK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define VK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define VK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

	/*
	 * 0x97 - 0x9F : unassigned
	 */
#define VK_CHANNEL_UP      0x97
#define VK_CHANNEL_DOWN	   0x98
#define VK_MAIL_INFO	   0x99
#define VK_FAV			   0x9A
#define VK_GUIDE		   0x9B
#define VK_INFO			   0x9C
#define VK_GAME			   0x9D
#define VK_RECORD		   0x9E
#define VK_STOP			   0x9F

	/*
	 * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
	 * Used only as parameters to MSGetAsyncKeyState() and MSGetKeyState().
	 * No other API or message will distinguish left and right keys in this way.
	 */
#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

#if(_WIN32_WINNT >= 0x0500)
#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC

#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF
#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3
#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

#endif /* _WIN32_WINNT >= 0x0500 */

	/*
	 * 0xB8 - 0xB9 : reserved
	 */
#define VK_RW	0xB8
#define VK_FF	0xB9

#define VK_OEM_1          0xBA   // ';:' for US
#define VK_OEM_PLUS       0xBB   // '+' any country
#define VK_OEM_COMMA      0xBC   // ',' any country
#define VK_OEM_MINUS      0xBD   // '-' any country
#define VK_OEM_PERIOD     0xBE   // '.' any country
#define VK_OEM_2          0xBF   // '/?' for US
#define VK_OEM_3          0xC0   // '`~' for US

	/*
	 * 0xC1 - 0xD7 : reserved
	 */
#define VK_RED			 0xC1
#define VK_GREEN		 0xC2
#define VK_YELLOW	     0xC3
#define VK_BLUE			 0xC4
#define VK_FB			 0xC5
#define VK_FIND			 0xC6
#define VK_MEDIA		 0xC7
#define VK_ONE_TOUCH_PLAY  0xC8
#define VK_EXIT           0xC9
#define VK_ANT		      0xCA
#define VK_STATUS		  0xCB
#define VK_AVOUT          0xCC
#define VK_SETTING        0xCD
#define VK_MOSAIC		  0xCE
#define VK_BQT            0xCF
#define VK_EBOOK          0xD0
#define VK_PVR            0xD1
#define VK_HDDLIST        0xD2
#define VK_JOG			  0xD3
#define VK_RETREAT        0xD4
#define VK_HDMI			  0xD5
#define VK_SN_INFO        0xD6
#define VK_LIST			  0xD7
#define VK_EPG			  0xD8
#define VK_RECORDLIST	  0xD9
#define VK_SEARCH		  0xDA
#define VK_INTERACTIVE	  0xDB
#define VK_MAIL			  0xDC
#define VK_TIMESHIFT	  0xDD
	/*
	 * 0xD8 - 0xDA : unassigned
	 */

#define VK_OEM_4          0xDB  //  '[{' for US
#define VK_OEM_5          0xDC  //  '\|' for US
#define VK_OEM_6          0xDD  //  ']}' for US
#define VK_OEM_7          0xDE  //  ''"' for US
#define VK_OEM_8          0xDF

	/*
	 * 0xE0 : reserved
	 */

	/*
	 * Various extended or enhanced keyboards
	 */
#define VK_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
#define VK_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define VK_ICO_HELP       0xE3  //  Help key on ICO
#define VK_ICO_00         0xE4  //  00 key on ICO

#if(WINVER >= 0x0400)
#define VK_PROCESSKEY     0xE5
#endif /* WINVER >= 0x0400 */

#define VK_ICO_CLEAR      0xE6


#if(_WIN32_WINNT >= 0x0500)
#define VK_PACKET         0xE7
#endif /* _WIN32_WINNT >= 0x0500 */

	/*
	 * 0xE8 : unassigned
	 */

	/*
	 * Nokia/Ericsson definitions
	 */
#define VK_OEM_RESET      0xE9
#define VK_OEM_JUMP       0xEA
#define VK_OEM_PA1        0xEB
#define VK_OEM_PA2        0xEC
#define VK_OEM_PA3        0xED
#define VK_OEM_WSCTRL     0xEE
#define VK_OEM_CUSEL      0xEF
#define VK_OEM_ATTN       0xF0
#define VK_OEM_FINISH     0xF1
#define VK_OEM_COPY       0xF2
#define VK_OEM_AUTO       0xF3
#define VK_OEM_ENLW       0xF4
#define VK_OEM_BACKTAB    0xF5

#define VK_ATTN           0xF6
#define VK_CRSEL          0xF7
#define VK_EXSEL          0xF8
#define VK_EREOF          0xF9
#define VK_PLAY           0xFA
#define VK_ZOOM           0xFB
#define VK_NONAME         0xFC
#define VK_PA1            0xFD
#define VK_OEM_CLEAR      0xFE

	/*
	 * 0xFF : reserved
	 */


#endif /* !NOVIRTUALKEYCODES */

#ifndef NOWH

	/*
	 * MSSetWindowsHook() codes
	 */
#define WH_MIN              (-1)
#define WH_MSGFILTER        (-1)
#define WH_JOURNALRECORD    0
#define WH_JOURNALPLAYBACK  1
#define WH_KEYBOARD         2
#define WH_GETMESSAGE       3
#define WH_CALLWNDPROC      4
#define WH_CBT              5
#define WH_SYSMSGFILTER     6
#define WH_MOUSE            7
#if defined(_WIN32_WINDOWS)
#define WH_HARDWARE         8
#endif
#define WH_DEBUG            9
#define WH_SHELL           10
#define WH_FOREGROUNDIDLE  11
#if(WINVER >= 0x0400)
#define WH_CALLWNDPROCRET  12
#endif /* WINVER >= 0x0400 */

#if (_WIN32_WINNT >= 0x0400)
#define WH_KEYBOARD_LL     13
#define WH_MOUSE_LL        14
#endif // (_WIN32_WINNT >= 0x0400)


#if(WINVER >= 0x0400)
#undef WH_MAX
#if (_WIN32_WINNT >= 0x0400)
#define WH_MAX             14
#else
#define WH_MAX             12
#endif // (_WIN32_WINNT >= 0x0400)
#else
#define WH_MAX             11
#endif

#define WH_MINHOOK         WH_MIN
#define WH_MAXHOOK         WH_MAX

	/*
	 * Hook Codes
	 */
#define HC_ACTION           0
#define HC_GETNEXT          1
#define HC_SKIP             2
#define HC_NOREMOVE         3
#define HC_NOREM            HC_NOREMOVE
#define HC_SYSMODALON       4
#define HC_SYSMODALOFF      5

	/*
	 * CBT Hook Codes
	 */
#define HCBT_MOVESIZE       0
#define HCBT_MINMAX         1
#define HCBT_QS             2
#define HCBT_CREATEWND      3
#define HCBT_DESTROYWND     4
#define HCBT_ACTIVATE       5
#define HCBT_CLICKSKIPPED   6
#define HCBT_KEYSKIPPED     7
#define HCBT_SYSCOMMAND     8
#define HCBT_SETFOCUS       9

	/*
	 * HCBT_CREATEWND parameters pointed to by lParam
	 */
	typedef struct tagMSCBT_CREATEWNDA
	{
		struct tagMSCREATESTRUCTA *lpcs;
		HMSWND           hwndInsertAfter;
	} MSCBT_CREATEWNDA, *LPMSCBT_CREATEWNDA;
	/*
	 * HCBT_CREATEWND parameters pointed to by lParam
	 */
	typedef MSCBT_CREATEWNDA MSCBT_CREATEWND;
	typedef LPMSCBT_CREATEWNDA LPMSCBT_CREATEWND;

	/*
	 * HCBT_ACTIVATE structure pointed to by lParam
	 */
	typedef struct tagMSCBTACTIVATESTRUCT
	{
		BOOL    fMouse;
		HMSWND    hWndActive;
	} MSCBTACTIVATESTRUCT, *LPMSCBTACTIVATESTRUCT;

#if(_WIN32_WINNT >= 0x0501)
	/*
	 * MSWTSSESSION_NOTIFICATION struct pointed by lParam, for WM_WTSSESSION_CHANGE
	 */
	typedef struct tagMSWTSSESSION_NOTIFICATION
	{
		DWORD cbSize;
		DWORD dwSessionId;

	} MSWTSSESSION_NOTIFICATION, *PCSWTSSESSION_NOTIFICATION;

	/*
	 * codes passed in WPARAM for WM_WTSSESSION_CHANGE
	 */

#define WTS_CONSOLE_CONNECT                0x1
#define WTS_CONSOLE_DISCONNECT             0x2
#define WTS_REMOTE_CONNECT                 0x3
#define WTS_REMOTE_DISCONNECT              0x4
#define WTS_SESSION_LOGON                  0x5
#define WTS_SESSION_LOGOFF                 0x6
#define WTS_SESSION_LOCK                   0x7
#define WTS_SESSION_UNLOCK                 0x8

#endif /* _WIN32_WINNT >= 0x0501 */

	/*
	 * WH_MSGFILTER Filter Proc Codes
	 */
#define MSGF_DIALOGBOX      0
#define MSGF_MESSAGEBOX     1
#define MSGF_MENU           2
#define MSGF_SCROLLBAR      5
#define MSGF_NEXTWINDOW     6
#define MSGF_MAX            8                       // unused
#define MSGF_USER           4096

	/*
	 * Shell support
	 */
#define HSHELL_WINDOWCREATED        1
#define HSHELL_WINDOWDESTROYED      2
#define HSHELL_ACTIVATESHELLWINDOW  3

#if(WINVER >= 0x0400)
#define HSHELL_WINDOWACTIVATED      4
#define HSHELL_GETMINRECT           5
#define HSHELL_REDRAW               6
#define HSHELL_TASKMAN              7
#define HSHELL_LANGUAGE             8
#endif /* WINVER >= 0x0400 */
#if(_WIN32_WINNT >= 0x0500)
#define HSHELL_ACCESSIBILITYSTATE   11
#define HSHELL_APPCOMMAND           12
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define HSHELL_WINDOWREPLACED       13
#endif /* _WIN32_WINNT >= 0x0501 */


#if(_WIN32_WINNT >= 0x0500)
	/* wparam for HSHELL_ACCESSIBILITYSTATE */
#define    ACCESS_STICKYKEYS            0x0001
#define    ACCESS_FILTERKEYS            0x0002
#define    ACCESS_MOUSEKEYS             0x0003

	/* cmd for HSHELL_APPCOMMAND and WM_APPCOMMAND */
#define APPCOMMAND_BROWSER_BACKWARD       1
#define APPCOMMAND_BROWSER_FORWARD        2
#define APPCOMMAND_BROWSER_REFRESH        3
#define APPCOMMAND_BROWSER_STOP           4
#define APPCOMMAND_BROWSER_SEARCH         5
#define APPCOMMAND_BROWSER_FAVORITES      6
#define APPCOMMAND_BROWSER_HOME           7
#define APPCOMMAND_VOLUME_MUTE            8
#define APPCOMMAND_VOLUME_DOWN            9
#define APPCOMMAND_VOLUME_UP              10
#define APPCOMMAND_MEDIA_NEXTTRACK        11
#define APPCOMMAND_MEDIA_PREVIOUSTRACK    12
#define APPCOMMAND_MEDIA_STOP             13
#define APPCOMMAND_MEDIA_PLAY_PAUSE       14
#define APPCOMMAND_LAUNCH_MAIL            15
#define APPCOMMAND_LAUNCH_MEDIA_SELECT    16
#define APPCOMMAND_LAUNCH_APP1            17
#define APPCOMMAND_LAUNCH_APP2            18
#define APPCOMMAND_BASS_DOWN              19
#define APPCOMMAND_BASS_BOOST             20
#define APPCOMMAND_BASS_UP                21
#define APPCOMMAND_TREBLE_DOWN            22
#define APPCOMMAND_TREBLE_UP              23
#if(_WIN32_WINNT >= 0x0501)
#define APPCOMMAND_MICROPHONE_VOLUME_MUTE 24
#define APPCOMMAND_MICROPHONE_VOLUME_DOWN 25
#define APPCOMMAND_MICROPHONE_VOLUME_UP   26
#define APPCOMMAND_HELP                   27
#define APPCOMMAND_FIND                   28
#define APPCOMMAND_NEW                    29
#define APPCOMMAND_OPEN                   30
#define APPCOMMAND_CLOSE                  31
#define APPCOMMAND_SAVE                   32
#define APPCOMMAND_PRINT                  33
#define APPCOMMAND_UNDO                   34
#define APPCOMMAND_REDO                   35
#define APPCOMMAND_COPY                   36
#define APPCOMMAND_CUT                    37
#define APPCOMMAND_PASTE                  38
#define APPCOMMAND_REPLY_TO_MAIL          39
#define APPCOMMAND_FORWARD_MAIL           40
#define APPCOMMAND_SEND_MAIL              41
#define APPCOMMAND_SPELL_CHECK            42
#define APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE    43
#define APPCOMMAND_MIC_ON_OFF_TOGGLE      44
#define APPCOMMAND_CORRECTION_LIST        45
#endif /* _WIN32_WINNT >= 0x0501 */

#define FAPPCOMMAND_MOUSE 0x8000
#define FAPPCOMMAND_KEY   0
#define FAPPCOMMAND_OEM   0x1000
#define FAPPCOMMAND_MASK  0xF000

#define GET_APPCOMMAND_LPARAM(lParam) ((short)(HIWORD(lParam) & ~FAPPCOMMAND_MASK))
#define GET_DEVICE_LPARAM(lParam)     ((WORD)(HIWORD(lParam) & FAPPCOMMAND_MASK))
#define GET_MOUSEORKEY_LPARAM         GET_DEVICE_LPARAM
#define GET_FLAGS_LPARAM(lParam)      (LOWORD(lParam))
#define GET_KEYSTATE_LPARAM(lParam)   GET_FLAGS_LPARAM(lParam)
#endif /* _WIN32_WINNT >= 0x0500 */


	/*
	 * Message Structure used in Journaling
	 */
	typedef struct tagMSEVENTMSG {
		UINT    message;
		UINT    paramL;
		UINT    paramH;
		DWORD    time;
		HMSWND     hwnd;
	} MSEVENTMSG, *PMSEVENTMSGMSG, NEAR *NPMSEVENTMSGMSG, FAR *LPMSEVENTMSGMSG;

	typedef struct tagMSEVENTMSG *PMSEVENTMSG, NEAR *NPMSEVENTMSG, FAR *LPMSEVENTMSG;

	/*
	 * Message structure used by WH_CALLWNDPROC
	 */
	typedef struct tagMSCWPSTRUCT {
		LPARAM  lParam;
		WPARAM  wParam;
		UINT    message;
		HMSWND    hwnd;
	} MSCWPSTRUCT, *PMSCWPSTRUCT, NEAR *NPMSCWPSTRUCT, FAR *LPMSCWPSTRUCT;

#if(WINVER >= 0x0400)
	/*
	 * Message structure used by WH_CALLWNDPROCRET
	 */
	typedef struct tagMSCWPRETSTRUCT {
		LRESULT lResult;
		LPARAM  lParam;
		WPARAM  wParam;
		UINT    message;
		HMSWND    hwnd;
	} MSCWPRETSTRUCT, *PMSCWPRETSTRUCT, NEAR *NPMSCWPRETSTRUCT, FAR *LPMSCWPRETSTRUCT;

#endif /* WINVER >= 0x0400 */

#if (_WIN32_WINNT >= 0x0400)

	/*
	 * Low level hook flags
	 */

#define LLKHF_EXTENDED       (KF_EXTENDED >> 8)
#define LLKHF_INJECTED       0x00000010
#define LLKHF_ALTDOWN        (KF_ALTDOWN >> 8)
#define LLKHF_UP             (KF_UP >> 8)

#define LLMHF_INJECTED       0x00000001

	/*
	 * Structure used by WH_KEYBOARD_LL
	 */
	typedef struct tagMSKBDLLHOOKSTRUCT {
		DWORD   vkCode;
		DWORD   scanCode;
		DWORD   flags;
		DWORD   time;
		ULONG_PTR dwExtraInfo;
	} MSKBDLLHOOKSTRUCT, FAR *LPMSKBDLLHOOKSTRUCT, *PMSKBDLLHOOKSTRUCT;

	/*
	 * Structure used by WH_MOUSE_LL
	 */
	/*typedef struct tagMSLLHOOKSTRUCT {
		MSPOINT   pt;
		DWORD   mouseData;
		DWORD   flags;
		DWORD   time;
		ULONG_PTR dwExtraInfo;
	} MSLLHOOKSTRUCT, FAR *LPMSLLHOOKSTRUCT, *PMSLLHOOKSTRUCT;*/

#endif // (_WIN32_WINNT >= 0x0400)

	/*
	 * Structure used by WH_DEBUG
	 */
	typedef struct tagMSDEBUGHOOKINFO
	{
		DWORD   idThread;
		DWORD   idThreadInstaller;
		LPARAM  lParam;
		WPARAM  wParam;
		int     code;
	} MSDEBUGHOOKINFO, *PMSDEBUGHOOKINFO, NEAR *NPMSDEBUGHOOKINFO, FAR* LPMSDEBUGHOOKINFO;

	/*
	 * Structure used by WH_MOUSE
	 */
	typedef struct tagMSMOUSEHOOKSTRUCT {
		MSPOINT   pt;
		HMSWND    hwnd;
		UINT    wHitTestCode;
		ULONG_PTR dwExtraInfo;
	} MSMOUSEHOOKSTRUCT, FAR *LPMSMOUSEHOOKSTRUCT, *PMSMOUSEHOOKSTRUCT;

#if(_WIN32_WINNT >= 0x0500)
#ifdef __cplusplus
	typedef struct tagMSMOUSEHOOKSTRUCTEX : public tagMSMOUSEHOOKSTRUCT
	{
		DWORD   mouseData;
	} MSMOUSEHOOKSTRUCTEX, *LPMSMOUSEHOOKSTRUCTEX, *PMSMOUSEHOOKSTRUCTEX;
#else // ndef __cplusplus
	typedef struct tagMSMOUSEHOOKSTRUCTEX
	{
		MSMOUSEHOOKSTRUCT dummy;
		DWORD   mouseData;
	} MSMOUSEHOOKSTRUCTEX, *LPMSMOUSEHOOKSTRUCTEX, *PMSMOUSEHOOKSTRUCTEX;
#endif
#endif /* _WIN32_WINNT >= 0x0500 */

#if(WINVER >= 0x0400)
	/*
	 * Structure used by WH_HARDWARE
	 */
	typedef struct tagMSHARDWAREHOOKSTRUCT {
		HMSWND    hwnd;
		UINT    message;
		WPARAM  wParam;
		LPARAM  lParam;
	} MSHARDWAREHOOKSTRUCT, FAR *LPMSHARDWAREHOOKSTRUCT, *PMSHARDWAREHOOKSTRUCT;
#endif /* WINVER >= 0x0400 */
#endif /* !NOWH */

	/*
	 * Keyboard Layout API
	 */
#define HKL_PREV            0
#define HKL_NEXT            1


#define KLF_ACTIVATE        0x00000001
#define KLF_SUBSTITUTE_OK   0x00000002
#define KLF_REORDER         0x00000008
#if(WINVER >= 0x0400)
#define KLF_REPLACELANG     0x00000010
#define KLF_NOTELLSHELL     0x00000080
#endif /* WINVER >= 0x0400 */
#define KLF_SETFORPROCESS   0x00000100
#if(_WIN32_WINNT >= 0x0500)
#define KLF_SHIFTLOCK       0x00010000
#define KLF_RESET           0x40000000
#endif /* _WIN32_WINNT >= 0x0500 */


#if(WINVER >= 0x0500)
	/*
	 * Bits in wParam of WM_INPUTLANGCHANGEREQUEST message
	 */
#define INPUTLANGCHANGE_SYSCHARSET 0x0001
#define INPUTLANGCHANGE_FORWARD    0x0002
#define INPUTLANGCHANGE_BACKWARD   0x0004
#endif /* WINVER >= 0x0500 */

	/*
	 * Size of KeyboardLayoutName (number of characters), including nul terminator
	 */
#define KL_NAMELENGTH       9

	 
		HMSKL
		WINAPI
		MSLoadKeyboardLayout(
		IN LPCTSTR pwszKLID,
		IN UINT Flags );


#if(WINVER >= 0x0400)
	 
		HMSKL
		WINAPI
		MSActivateKeyboardLayout(
		IN HMSKL hkl,
		IN UINT Flags );
#else
	 
		BOOL
		WINAPI
		MSActivateKeyboardLayout(
		IN HMSKL hkl,
		IN UINT Flags);
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
	 
		int
		WINAPI
		MSToUnicodeEx(
		IN UINT wVirtKey,
		IN UINT wScanCode,
		IN CONST BYTE *lpKeyState,
		OUT LPWSTR pwszBuff,
		IN int cchBuff,
		IN UINT wFlags,
		IN HMSKL dwhkl );
#endif /* WINVER >= 0x0400 */

	 
		BOOL
		WINAPI
		MSUnloadKeyboardLayout(
		IN HMSKL hkl );

	 
		BOOL
		WINAPI
		MSGetKeyboardLayoutName(
		OUT LPTSTR pwszKLID );


#if(WINVER >= 0x0400)
	 
		int
		WINAPI
		MSGetKeyboardLayoutList(
		IN int nBuff,
		OUT HMSKL FAR *lpList );

	 
		HMSKL
		WINAPI
		MSGetKeyboardLayout(
		IN DWORD idThread
		);
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)

	typedef struct tagMSMOUSEMOVEPOINT {
		int   x;
		int   y;
		DWORD time;
		ULONG_PTR dwExtraInfo;
	} MSMOUSEMOVEPOINT, *PMSMOUSEMOVEPOINT, FAR* LPMSMOUSEMOVEPOINT;

	/*
	 * Values for resolution parameter of MSGetMouseMovePointsEx
	 */
#define GMMP_USE_DISPLAY_POINTS          1
#define GMMP_USE_HIGH_RESOLUTION_POINTS  2

	 
		int
		WINAPI
		MSGetMouseMovePointsEx(
		IN UINT             cbSize,
		IN LPMSMOUSEMOVEPOINT lppt,
		IN LPMSMOUSEMOVEPOINT lpptBuf,
		IN int              nBufPoints,
		IN DWORD            resolution
		);

#endif /* WINVER >= 0x0500 */

#ifndef NODESKTOP
	/*
	 * Desktop-specific access flags
	 */
#define DESKTOP_READOBJECTS         0x0001L
#define DESKTOP_CREATEWINDOW        0x0002L
#define DESKTOP_CREATEMENU          0x0004L
#define DESKTOP_HOOKCONTROL         0x0008L
#define DESKTOP_JOURNALRECORD       0x0010L
#define DESKTOP_JOURNALPLAYBACK     0x0020L
#define DESKTOP_ENUMERATE           0x0040L
#define DESKTOP_WRITEOBJECTS        0x0080L
#define DESKTOP_SWITCHDESKTOP       0x0100L

	/*
	 * Desktop-specific control flags
	 */
#define DF_ALLOWOTHERACCOUNTHOOK    0x0001L

#ifdef _WINGDI_
#ifndef NOGDI

	 
		HMSDESK
		WINAPI
		MSCreateDesktop(
		IN LPCTSTR lpszDesktop,
		IN LPCTSTR lpszDevice,
		IN LPMSDEVMODEA pDevmode,
		IN DWORD dwFlags,
		IN ACCESS_MASK dwDesiredAccess,
		IN LPMSSECURITY_ATTRIBUTES lpsa );

#endif /* NOGDI */
#endif /* _WINGDI_ */

	 
		HMSDESK
		WINAPI
		MSOpenDesktop(
		IN LPCTSTR lpszDesktop,
		IN DWORD dwFlags,
		IN BOOL fInherit,
		IN ACCESS_MASK dwDesiredAccess );

	 
		HMSDESK
		WINAPI
		MSOpenInputDesktop(
		IN DWORD dwFlags,
		IN BOOL fInherit,
		IN ACCESS_MASK dwDesiredAccess );

	 
		BOOL
		WINAPI
		MSEnumDesktops(
		IN HMSWINSTA hwinsta,
		IN MSDESKTOPENUMPROCA lpEnumFunc,
		IN LPARAM lParam );


	 
		BOOL
		WINAPI
		MSEnumDesktopWindows(
		IN HMSDESK hDesktop,
		IN MSWNDENUMPROC lpfn,
		IN LPARAM lParam );

	 
		BOOL
		WINAPI
		MSSwitchDesktop(
		IN HMSDESK hDesktop );

	 
		BOOL
		WINAPI
		MSSetThreadDesktop(
		IN HMSDESK hDesktop );

	 
		BOOL
		WINAPI
		MSCloseDesktop(
		IN HMSDESK hDesktop );

	 
		HMSDESK
		WINAPI
		MSGetThreadDesktop(
		IN DWORD dwThreadId );
#endif  /* !NODESKTOP */

#ifndef NOWINDOWSTATION
	/*
	 * Windowstation-specific access flags
	 */
#define WINSTA_ENUMDESKTOPS         0x0001L
#define WINSTA_READATTRIBUTES       0x0002L
#define WINSTA_ACCESSCLIPBOARD      0x0004L
#define WINSTA_CREATEDESKTOP        0x0008L
#define WINSTA_WRITEATTRIBUTES      0x0010L
#define WINSTA_ACCESSGLOBALATOMS    0x0020L
#define WINSTA_EXITWINDOWS          0x0040L
#define WINSTA_ENUMERATE            0x0100L
#define WINSTA_READSCREEN           0x0200L

	/*
	 * Windowstation-specific attribute flags
	 */
#define WSF_VISIBLE                 0x0001L

	 
		HMSWINSTA
		WINAPI
		MSCreateWindowStation(
		IN LPCTSTR              lpwinsta,
		IN DWORD                 dwReserved,
		IN ACCESS_MASK           dwDesiredAccess,
		IN LPMSSECURITY_ATTRIBUTES lpsa );

	 
		HMSWINSTA
		WINAPI
		MSOpenWindowStation(
		IN LPCTSTR lpszWinSta,
		IN BOOL fInherit,
		IN ACCESS_MASK dwDesiredAccess );

	 
		BOOL
		WINAPI
		MSEnumWindowStations(
		IN MSWINSTAENUMPROCA lpEnumFunc,
		IN LPARAM lParam );



	 
		BOOL
		WINAPI
		MSCloseWindowStation(
		IN HMSWINSTA hWinSta );

	 
		BOOL
		WINAPI
		MSSetProcessWindowStation(
		IN HMSWINSTA hWinSta );

	 
		HMSWINSTA
		WINAPI
		MSGetProcessWindowStation(
		void );
#endif  /* !NOWINDOWSTATION */
	/*
	#ifndef NOSECURITY

	 
	BOOL
	WINAPI
	MSSetUserObjectSecurity(
	IN HMSHANDLE hObj,
	IN PSECURITY_INFORMATION pSIRequested,
	IN PSECURITY_DESCRIPTOR pSID);

	 
	BOOL
	WINAPI
	MSGetUserObjectSecurity(
	IN HMSHANDLE hObj,
	IN PSECURITY_INFORMATION pSIRequested,
	IN OUT PSECURITY_DESCRIPTOR pSID,
	IN DWORD nLength,
	OUT LPDWORD lpnLengthNeeded);

	#define UOI_FLAGS       1
	#define UOI_NAME        2
	#define UOI_TYPE        3
	#define UOI_USER_SID    4

	typedef struct tagMSUSEROBJECTFLAGS {
	BOOL fInherit;
	BOOL fReserved;
	DWORD dwFlags;
	} MSUSEROBJECTFLAGS, *PMSUSEROBJECTFLAGS;

	 
	BOOL
	WINAPI
	MSGetUserObjectInformation(
	IN HMSHANDLE hObj,
	IN int nIndex,
	OUT PVOID pvInfo,
	IN DWORD nLength,
	OUT LPDWORD lpnLengthNeeded);

	 
	BOOL
	WINAPI
	MSSetUserObjectInformation(
	IN HMSHANDLE hObj,
	IN int nIndex,
	IN PVOID pvInfo,
	IN DWORD nLength);

	#endif   //!NOSECURITY
	*/
#if(WINVER >= 0x0400)
	typedef struct tagMSWNDCLASSEXA {
		UINT        cbSize;
		/* Win 3.x */
		UINT        style;
		MSWNDPROC     lpfnWndProc;
		int         cbClsExtra;
		int         cbWndExtra;
		HMSINSTANCE   hInstance;
		HMSICON       hIcon;
		HMSCURSOR     hCursor;
		HMSBRUSH      hbrBackground;
		LPCTSTR      lpszMenuName;
		LPCTSTR      lpszClassName;
		/* Win 4.0 */
		HMSICON       hIconSm;
	} MSWNDCLASSEXA, *PMSWNDCLASSEXA, NEAR *NPMSWNDCLASSEXA, FAR *LPMSWNDCLASSEXA;

	typedef MSWNDCLASSEXA MSWNDCLASSEX;
	typedef PMSWNDCLASSEXA PMSWNDCLASSEX;
	typedef NPMSWNDCLASSEXA NPMSWNDCLASSEX;
	typedef LPMSWNDCLASSEXA LPMSWNDCLASSEX;
#endif /* WINVER >= 0x0400 */

	typedef struct tagMSWNDCLASSA {
		UINT        style;
		MSWNDPROC     lpfnWndProc;
		int         cbClsExtra;
		int         cbWndExtra;
		HMSINSTANCE   hInstance;
		HMSICON       hIcon;
		HMSCURSOR     hCursor;
		HMSBRUSH      hbrBackground;
		LPCTSTR      lpszMenuName;
		LPCTSTR      lpszClassName;
	} MSWNDCLASSA, *PMSWNDCLASSA, NEAR *NPMSWNDCLASSA, FAR *LPMSWNDCLASSA;

	typedef MSWNDCLASSA MSWNDCLASS;
	typedef PMSWNDCLASSA PMSWNDCLASS;
	typedef NPMSWNDCLASSA NPMSWNDCLASS;
	typedef LPMSWNDCLASSA LPMSWNDCLASS;


#ifndef NOMSG

	/*
	 * Message structure
	 */
	typedef struct tagMSMSG {
		HMSWND        hwnd;
		UINT        message;
		WPARAM      wParam;
		LPARAM      lParam;
		DWORD       time;
		MSPOINT       pt;
#ifdef _MAC
		DWORD       lPrivate;
#endif
	} MSMSG, *PMSMSG, NEAR *NPMSMSG, FAR *LPMSMSG;

#define POINTSTOPOINT(pt, pts)                          \
	{ ( pt ).x = ( LONG )( SHORT )LOWORD( *( LONG* )&pts );   \
	( pt ).y = ( LONG )( SHORT )HIWORD( *( LONG* )&pts ); }

#define POINTTOPOINTS(pt)      (MAKELONG((short)((pt).x), (short)((pt).y)))
#define MAKEWPARAM(l, h)      ((WPARAM)(DWORD)MAKELONG(l, h))
#define MAKELPARAM(l, h)      ((LPARAM)(DWORD)MAKELONG(l, h))
#define MAKELRESULT(l, h)     ((LRESULT)(DWORD)MAKELONG(l, h))


#endif /* !NOMSG */

#ifndef NOWINOFFSETS

	/*
	 * Window field offsets for MSGetWindowLong()
	 */
#define GWL_WNDPROC         (-4)
#define GWL_HINSTANCE       (-6)
#define GWL_HWNDPARENT      (-8)
#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)
#define GWL_USERDATA        (-21)
#define GWL_ID              (-12)

#ifdef _WIN64

#undef GWL_WNDPROC
#undef GWL_HINSTANCE
#undef GWL_HWNDPARENT
#undef GWL_USERDATA

#endif /* _WIN64 */

#define GWLP_WNDPROC        (-4)
#define GWLP_HINSTANCE      (-6)
#define GWLP_HWNDPARENT     (-8)
#define GWLP_USERDATA       (-21)
#define GWLP_ID             (-12)

	/*
	 * Class field offsets for MSGetClassLong()
	 */
#define GCL_MENUNAME        (-8)
#define GCL_HBRBACKGROUND   (-10)
#define GCL_HCURSOR         (-12)
#define GCL_HICON           (-14)
#define GCL_HMODULE         (-16)
#define GCL_CBWNDEXTRA      (-18)
#define GCL_CBCLSEXTRA      (-20)
#define GCL_WNDPROC         (-24)
#define GCL_STYLE           (-26)
#define GCW_ATOM            (-32)

#if(WINVER >= 0x0400)
#define GCL_HICONSM         (-34)
#endif /* WINVER >= 0x0400 */

#ifdef _WIN64

#undef GCL_MENUNAME
#undef GCL_HBRBACKGROUND
#undef GCL_HCURSOR
#undef GCL_HICON
#undef GCL_HMODULE
#undef GCL_WNDPROC
#undef GCL_HICONSM

#endif /* _WIN64 */

#define GCLP_MENUNAME       (-8)
#define GCLP_HBRBACKGROUND  (-10)
#define GCLP_HCURSOR        (-12)
#define GCLP_HICON          (-14)
#define GCLP_HMODULE        (-16)
#define GCLP_WNDPROC        (-24)
#define GCLP_HICONSM        (-34)

#endif /* !NOWINOFFSETS */

#ifndef NOWINMESSAGES


	/*
	 * Window Messages
	 */

#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005

#define WM_ACTIVATE                     0x0006
	/*
	 * WM_ACTIVATE state values
	 */
#define     WA_INACTIVE     0
#define     WA_ACTIVE       1
#define     WA_CLICKACTIVE  2

#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_ENABLE                       0x000A
#define WM_SETREDRAW                    0x000B
#define WM_SETTEXT                      0x000C
#define WM_GETTEXT                      0x000D
#define WM_GETTEXTLENGTH                0x000E
#define WM_PAINT                        0x000F
#define WM_CLOSE                        0x0010
#ifndef _WIN32_WCE
#define WM_QUERYENDSESSION              0x0011
#define WM_QUERYOPEN                    0x0013
#define WM_ENDSESSION                   0x0016
#endif
#define WM_QUIT                         0x0012
#define WM_ERASEBKGND                   0x0014
#define WM_SYSCOLORCHANGE               0x0015
#define WM_SHOWWINDOW                   0x0018
#define WM_WININICHANGE                 0x001A
#if(WINVER >= 0x0400)
#define WM_SETTINGCHANGE                WM_WININICHANGE
#endif /* WINVER >= 0x0400 */


#define WM_DEVMODECHANGE                0x001B
#define WM_ACTIVATEAPP                  0x001C
#define WM_FONTCHANGE                   0x001D
#define WM_TIMECHANGE                   0x001E
#define WM_CANCELMODE                   0x001F
#define WM_SETCURSOR                    0x0020
#define WM_MOUSEACTIVATE                0x0021
#define WM_CHILDACTIVATE                0x0022
#define WM_QUEUESYNC                    0x0023

#define WM_GETMINMAXINFO                0x0024
	/*
	 * Struct pointed to by WM_GETMSMINMAXINFO lParam
	 */
	typedef struct tagMSMINMAXINFO {
		MSPOINT ptReserved;
		MSPOINT ptMaxSize;
		MSPOINT ptMaxPosition;
		MSPOINT ptMinTrackSize;
		MSPOINT ptMaxTrackSize;
	} MSMINMAXINFO, *PMSMINMAXINFO, *LPMSMINMAXINFO;

#define WM_PAINTICON                    0x0026
#define WM_ICONERASEBKGND               0x0027
#define WM_NEXTDLGCTL                   0x0028
#define WM_SPOOLERSTATUS                0x002A
#define WM_DRAWITEM                     0x002B
#define WM_MEASUREITEM                  0x002C
#define WM_DELETEITEM                   0x002D
#define WM_VKEYTOITEM                   0x002E
#define WM_CHARTOITEM                   0x002F
#define WM_SETFONT                      0x0030
#define WM_GETFONT                      0x0031
#define WM_SETHOTKEY                    0x0032
#define WM_GETHOTKEY                    0x0033
#define WM_QUERYDRAGICON                0x0037
#define WM_COMPAREITEM                  0x0039
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
#define WM_GETOBJECT                    0x003D
#endif
#endif /* WINVER >= 0x0500 */
#define WM_COMPACTING                   0x0041
#define WM_COMMNOTIFY                   0x0044  /* no longer suported */
#define WM_WINDOWPOSCHANGING            0x0046
#define WM_WINDOWPOSCHANGED             0x0047
	/*******************************************/
	//  WM_DRAWMENUFRAME:
	//  it same as the WM_DRAWMENUITEM,but is only send when the popop menu has ;
	//  first enter,you should paint your menu frame at here;
	/***************************************** */

#define WM_DRAWMENUFRAME				0x34000000  
	/*******************************************/
	//  WM_MEASUREMENUFRAME:
	//  the member CtlID of struc MEASUREITEMSTRUCT means :the x offset;
	//  the member CtlType of struc MEASUREITEMSTRUCT means : the y offset;
	/***************************************** */
#define WM_MEASUREMENUFRAME				0x35000000
	/*******************************************/
	//  WM_MENUREINIT:
	//  when the menu should be redisplay when it has all dispeared,
	//  the gui will send this message to notify the parent window to reinit the menu
	/***************************************** */
#define WM_MENUREINIT					0x36000000
	/*******************************************/
	//  WM_MENUDESTROY:
	//  when the menu will all dispeared(it means destroied)
	//  the gui will send this message to notify the parent window
	/***************************************** */

#define WM_MENUDESTROY					0x37000000
#define WM_POWER                        0x0048
	/*
	 * wParam for WM_POWER window message and DRV_POWER driver notification
	 */
#define PWR_OK              1
#define PWR_FAIL            (-1)
#define PWR_SUSPENDREQUEST  1
#define PWR_SUSPENDRESUME   2
#define PWR_CRITICALRESUME  3

#define WM_COPYDATA                     0x004A
#define WM_CANCELJOURNAL                0x004B


	/*
	 * lParam of WM_COPYDATA message points to...
	 */
	typedef struct tagMSCOPYDATASTRUCT {
		ULONG_PTR dwData;
		DWORD cbData;
		PVOID lpData;
	} MSCOPYDATASTRUCT, *PMSCOPYDATASTRUCT;

#if(WINVER >= 0x0400)
	typedef struct tagMSMDINEXTMENU
	{
		HMSMENU   hmenuIn;
		HMSMENU   hmenuNext;
		HMSWND    hwndNext;
	} MSMDINEXTMENU, *PMSMDINEXTMENU, FAR * LPMSMDINEXTMENU;
#endif /* WINVER >= 0x0400 */


#if(WINVER >= 0x0400)
#define WM_NOTIFY                       0x004E
#define WM_INPUTLANGCHANGEREQUEST       0x0050
#define WM_INPUTLANGCHANGE              0x0051
#define WM_TCARD                        0x0052
#define WM_HELP                         0x0053
#define WM_USERCHANGED                  0x0054
#define WM_NOTIFYFORMAT                 0x0055

#define NFR_ANSI                             1
#define NFR_UNICODE                          2
#define NF_QUERY                             3
#define NF_REQUERY                           4

#define WM_CONTEXTMENU                  0x007B
#define WM_STYLECHANGING                0x007C
#define WM_STYLECHANGED                 0x007D
#define WM_DISPLAYCHANGE                0x007E
#define WM_GETICON                      0x007F
#define WM_SETICON                      0x0080
#endif /* WINVER >= 0x0400 */

#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_GETDLGCODE                   0x0087
#ifndef _WIN32_WCE
#define WM_SYNCPAINT                    0x0088
#endif
#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9



#if(_WIN32_WINNT >= 0x0500)
#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD
#endif /* _WIN32_WINNT >= 0x0500 */


#if(_WIN32_WINNT >= 0x0501)
#define WM_INPUT                        0x00FF
#endif /* _WIN32_WINNT >= 0x0501 */

#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107
#if(_WIN32_WINNT >= 0x0501)
#define WM_UNICHAR                      0x0109
#define WM_KEYLAST                      0x0109
#define UNICODE_NOCHAR                  0xFFFF
#else
#define WM_KEYLAST                      0x0108
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)
#define WM_IME_STARTCOMPOSITION         0x010D
#define WM_IME_ENDCOMPOSITION           0x010E
#define WM_IME_COMPOSITION              0x010F
#define WM_IME_KEYLAST                  0x010F
#endif /* WINVER >= 0x0400 */

#define WM_INITDIALOG                   0x0110
#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112
#define WM_TIMER                        0x0113
#define WM_HSCROLL                      0x0114
#define WM_VSCROLL                      0x0115
#define WM_INITMENU                     0x0116
#define WM_INITMENUPOPUP                0x0117
#define WM_MENUSELECT                   0x011F
#define WM_MENUCHAR                     0x0120
#define WM_ENTERIDLE                    0x0121
#if(WINVER >= 0x0500)
#ifndef _WIN32_WCE
#define WM_MENURBUTTONUP                0x0122
#define WM_MENUDRAG                     0x0123
#define WM_MENUGETOBJECT                0x0124
#define WM_UNINITMENUPOPUP              0x0125
#define WM_MENUCOMMAND                  0x0126

#ifndef _WIN32_WCE
#if(_WIN32_WINNT >= 0x0500)
#define WM_CHANGEUISTATE                0x0127
#define WM_UPDATEUISTATE                0x0128
#define WM_QUERYUISTATE                 0x0129

	/*
	 * LOWORD(wParam) values in WM_*UISTATE*
	 */
#define UIS_SET                         1
#define UIS_CLEAR                       2
#define UIS_INITIALIZE                  3

	/*
	 * HIWORD(wParam) values in WM_*UISTATE*
	 */
#define UISF_HIDEFOCUS                  0x1
#define UISF_HIDEACCEL                  0x2
#if(_WIN32_WINNT >= 0x0501)
#define UISF_ACTIVE                     0x4
#endif /* _WIN32_WINNT >= 0x0501 */
#endif /* _WIN32_WINNT >= 0x0500 */
#endif

#endif
#endif /* WINVER >= 0x0500 */

#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define WM_CTLCOLORMENU					0x0139

#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSEWHEEL                   0x020A
#endif
#if (_WIN32_WINNT >= 0x0500)
#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D
#endif
#undef WM_MOUSELAST
#if (_WIN32_WINNT >= 0x0500)
#define WM_MOUSELAST                    0x020D
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#undef WM_MOUSELAST
#define WM_MOUSELAST                    0x020A
#else
#undef WM_MOUSELAST
#define WM_MOUSELAST                    0x0209
#endif /* (_WIN32_WINNT >= 0x0500) */


#if(_WIN32_WINNT >= 0x0400)
	/* Value for rolling one detent */
#define WHEEL_DELTA                     120
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))

	/* MSSetting to scroll one page for SPI_GET/SETWHEELSCROLLLINES */
#define WHEEL_PAGESCROLL                (UINT_MAX)
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))

	/* XButton values are WORD flags */
#define XBUTTON1      0x0001
#define XBUTTON2      0x0002
	/* Were there to be an XBUTTON3, its value would be 0x0004 */
#endif /* _WIN32_WINNT >= 0x0500 */

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212

#if(WINVER >= 0x0400)
#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)


#define WM_POWERBROADCAST               0x0218

#ifndef _WIN32_WCE
#define PBT_APMQUERYSUSPEND             0x0000
#define PBT_APMQUERYSTANDBY             0x0001

#define PBT_APMQUERYSUSPENDFAILED       0x0002
#define PBT_APMQUERYSTANDBYFAILED       0x0003

#define PBT_APMSUSPEND                  0x0004
#define PBT_APMSTANDBY                  0x0005

#define PBT_APMRESUMECRITICAL           0x0006
#define PBT_APMRESUMESUSPEND            0x0007
#define PBT_APMRESUMESTANDBY            0x0008

#define PBTF_APMRESUMEFROMFAILURE       0x00000001

#define PBT_APMBATTERYLOW               0x0009
#define PBT_APMPOWERSTATUSCHANGE        0x000A

#define PBT_APMOEMEVENT                 0x000B
#define PBT_APMRESUMEAUTOMATIC          0x0012
#endif

#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
#define WM_DEVICECHANGE                 0x0219
#endif /* WINVER >= 0x0400 */

#define WM_MDICREATE                    0x0220
#define WM_MDIDESTROY                   0x0221
#define WM_MDIACTIVATE                  0x0222
#define WM_MDIRESTORE                   0x0223
#define WM_MDINEXT                      0x0224
#define WM_MDIMAXIMIZE                  0x0225
#define WM_MDITILE                      0x0226
#define WM_MDICASCADE                   0x0227
#define WM_MDIICONARRANGE               0x0228
#define WM_MDIGETACTIVE                 0x0229


#define WM_MDISETMENU                   0x0230
#define WM_ENTERSIZEMOVE                0x0231
#define WM_EXITSIZEMOVE                 0x0232
#define WM_DROPFILES                    0x0233
#define WM_MDIREFRESHMSMENU               0x0234


#if(WINVER >= 0x0400)
#define WM_IME_SETCONTEXT               0x0281
#define WM_IME_NOTIFY                   0x0282
#define WM_IME_CONTROL                  0x0283
#define WM_IME_COMPOSITIONFULL          0x0284
#define WM_IME_SELECT                   0x0285
#define WM_IME_CHAR                     0x0286
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
#define WM_IME_REQUEST                  0x0288
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0400)
#define WM_IME_KEYDOWN                  0x0290
#define WM_IME_KEYUP                    0x0291
#endif /* WINVER >= 0x0400 */

#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
#define WM_MOUSEHOVER                   0x02A1
#define WM_MOUSELEAVE                   0x02A3
#endif
#if(WINVER >= 0x0500)
#define WM_NCMOUSEHOVER                 0x02A0
#define WM_NCMOUSELEAVE                 0x02A2
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_WTSSESSION_CHANGE            0x02B1

#define WM_TABLET_FIRST                 0x02c0
#define WM_TABLET_LAST                  0x02df
#endif /* _WIN32_WINNT >= 0x0501 */

#define WM_CUT                          0x0300
#define WM_COPY                         0x0301
#define WM_PASTE                        0x0302
#define WM_CLEAR                        0x0303
#define WM_UNDO                         0x0304
#define WM_RENDERFORMAT                 0x0305
#define WM_RENDERALLFORMATS             0x0306
#define WM_DESTROYCLIPBOARD             0x0307
#define WM_DRAWCLIPBOARD                0x0308
#define WM_PAINTCLIPBOARD               0x0309
#define WM_VSCROLLCLIPBOARD             0x030A
#define WM_SIZECLIPBOARD                0x030B
#define WM_ASKCBFORMATNAME              0x030C
#define WM_CHANGECBCHAIN                0x030D
#define WM_HSCROLLCLIPBOARD             0x030E
#define WM_QUERYNEWPALETTE              0x030F
#define WM_PALETTEISCHANGING            0x0310
#define WM_PALETTECHANGED               0x0311
#define WM_HOTKEY                       0x0312

#if(WINVER >= 0x0400)
#define WM_PRINT                        0x0317
#define WM_PRINTCLIENT                  0x0318
#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define WM_APPCOMMAND                   0x0319
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_THEMECHANGED                 0x031A
#endif /* _WIN32_WINNT >= 0x0501 */


#if(WINVER >= 0x0400)

#define WM_HANDHELDFIRST                0x0358
#define WM_HANDHELDLAST                 0x035F

#define WM_AFXFIRST                     0x0360
#define WM_AFXLAST                      0x037F
#endif /* WINVER >= 0x0400 */

#define WM_PENWINFIRST                  0x0380
#define WM_PENWINLAST                   0x038F


#if(WINVER >= 0x0400)
#define WM_APP                          0x8000
#endif /* WINVER >= 0x0400 */


	/*
	 * NOTE: All Message Numbers below 0x0400 are RESERVED.
	 *
	 * Private Window Messages Start Here:
	 */
#define WM_USER                         0x0400

#if(WINVER >= 0x0400)

	/*  wParam for WM_SIZING message  */
#define WMSZ_LEFT           1
#define WMSZ_RIGHT          2
#define WMSZ_TOP            3
#define WMSZ_TOPLEFT        4
#define WMSZ_TOPRIGHT       5
#define WMSZ_BOTTOM         6
#define WMSZ_BOTTOMLEFT     7
#define WMSZ_BOTTOMRIGHT    8
#endif /* WINVER >= 0x0400 */

#ifndef NONCMESSAGES

	/*
	 * WM_NCHITTEST and MSMOUSEHOOKSTRUCT Mouse Position Codes
	 */
#define HTERROR             (-2)
#define HTTRANSPARENT       (-1)
#define HTNOWHERE           0
#define HTCLIENT            1
#define HTCAPTION           2
#define HTSYSMENU           3
#define HTGROWBOX           4
#define HTSIZE              HTGROWBOX
#define HTMENU              5
#define HTHSCROLL           6
#define HTVSCROLL           7
#define HTMINBUTTON         8
#define HTMAXBUTTON         9
#define HTLEFT              10
#define HTRIGHT             11
#define HTTOP               12
#define HTTOPLEFT           13
#define HTTOPRIGHT          14
#define HTBOTTOM            15
#define HTBOTTOMLEFT        16
#define HTBOTTOMRIGHT       17
#define HTBORDER            18
#define HTREDUCE            HTMINBUTTON
#define HTZOOM              HTMAXBUTTON
#define HTSIZEFIRST         HTLEFT
#define HTSIZELAST          HTBOTTOMRIGHT
#if(WINVER >= 0x0400)
#define HTOBJECT            19
#define HTCLOSE             20
#define HTHELP              21
#endif /* WINVER >= 0x0400 */


	/*
	 * MSSendMessageTimeout values
	 */
#define SMTO_NORMAL         0x0000
#define SMTO_BLOCK          0x0001
#define SMTO_ABORTIFHUNG    0x0002
#if(WINVER >= 0x0500)
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#endif /* WINVER >= 0x0500 */
#endif /* !NONCMESSAGES */

	/*
	 * WM_MOUSEACTIVATE Return Codes
	 */
#define MA_ACTIVATE         1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE       3
#define MA_NOACTIVATEANDEAT 4

	/*
	 * WM_SETICON / WM_GETICON Type Codes
	 */
#define ICON_SMALL          0
#define ICON_BIG            1
#if(_WIN32_WINNT >= 0x0501)
#define ICON_SMALL2         2
#endif /* _WIN32_WINNT >= 0x0501 */


	 
		UINT
		WINAPI
		MSRegisterWindowMessage(
		IN LPCTSTR lpString );



	/*
	 * WM_SIZE message wParam values
	 */
#define SIZE_RESTORED       0
#define SIZE_MINIMIZED      1
#define SIZE_MAXIMIZED      2
#define SIZE_MAXSHOW        3
#define SIZE_MAXHIDE        4

	/*
	 * Obsolete constant names
	 */
#define SIZENORMAL          SIZE_RESTORED
#define SIZEICONIC          SIZE_MINIMIZED
#define SIZEFULLSCREEN      SIZE_MAXIMIZED
#define SIZEZOOMSHOW        SIZE_MAXSHOW
#define SIZEZOOMHIDE        SIZE_MAXHIDE

	/*
	 * WM_WINDOWPOSCHANGING/CHANGED struct pointed to by lParam
	 */
	typedef struct tagMSWINDOWPOS {
		HMSWND    hwnd;
		HMSWND    hwndInsertAfter;
		int     x;
		int     y;
		int     cx;
		int     cy;
		UINT    flags;
	} MSWINDOWPOS, *LPMSWINDOWPOS, *PMSWINDOWPOS;

	/*
	 * WM_NCCALCSIZE parameter structure
	 */
	typedef struct tagMSNCCALCSIZE_PARAMS {
		MSRECT       rgrc[ 3 ];
		PMSWINDOWPOS lppos;
	} MSNCCALCSIZE_PARAMS, *LPMSNCCALCSIZE_PARAMS;

	/*
	 * WM_NCCALCSIZE "window valid rect" return values
	 */
#define WVR_ALIGNTOP        0x0010
#define WVR_ALIGNLEFT       0x0020
#define WVR_ALIGNBOTTOM     0x0040
#define WVR_ALIGNRIGHT      0x0080
#define WVR_HREDRAW         0x0100
#define WVR_VREDRAW         0x0200
#define WVR_REDRAW         (WVR_HREDRAW | \
	WVR_VREDRAW )
#define WVR_VALIDRECTS      0x0400


#ifndef NOKEYSTATES

	/*
	 * Key State Masks for Mouse Messages
	 */
#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010
#if(_WIN32_WINNT >= 0x0500)
#define MK_XBUTTON1         0x0020
#define MK_XBUTTON2         0x0040
#endif /* _WIN32_WINNT >= 0x0500 */

#endif /* !NOKEYSTATES */


#if(_WIN32_WINNT >= 0x0400)
#ifndef NOMSTRACKMOUSEEVENT

#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002
#if(WINVER >= 0x0500)
#define TME_NONCLIENT   0x00000010
#endif /* WINVER >= 0x0500 */
#define TME_QUERY       0x40000000
#define TME_CANCEL      0x80000000


#define HOVER_DEFAULT   0xFFFFFFFF
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0400)
	typedef struct tagMSTRACKMOUSEEVENT {
		DWORD cbSize;
		DWORD dwFlags;
		HMSWND  hwndTrack;
		DWORD dwHoverTime;
	} MSTRACKMOUSEEVENT, *LPMSTRACKMOUSEEVENT;

	 
		BOOL
		WINAPI
		MSTrackMouseEventFun(
		IN OUT LPMSTRACKMOUSEEVENT lpEventTrack );
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0400)

#endif /* !NOMSTRACKMOUSEEVENT */
#endif /* _WIN32_WINNT >= 0x0400 */


#endif /* !NOWINMESSAGES */

#ifndef NOWINSTYLES


	/*
	 * Window Styles
	 */
#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_CAPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L

#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L


#define WS_TILED            WS_OVERLAPPED
#define WS_ICONIC           WS_MINIMIZE
#define WS_SIZEBOX          WS_THICKFRAME
#define WS_TILEDWINDOW      WS_OVERLAPPEDWINDOW

	/*
	 * Common Window Styles
	 */
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
	WS_CAPTION | \
	WS_SYSMENU | \
	WS_THICKFRAME | \
	WS_MINIMIZEBOX | \
	WS_MAXIMIZEBOX )

#define WS_POPUPWINDOW      (WS_POPUP          | \
	WS_BORDER | \
	WS_SYSMENU )

#define WS_CHILDWINDOW      (WS_CHILD)

	/*
	 * Extended Window Styles
	 */
#define WS_EX_DLGMODALFRAME     0x00000001L
#define WS_EX_NOPARENTNOTIFY    0x00000004L
#define WS_EX_TOPMOST           0x00000008L
#define WS_EX_ACCEPTFILES       0x00000010L
#define WS_EX_TRANSPARENT       0x00000020L
#if(WINVER >= 0x0400)
#define WS_EX_MDICHILD          0x00000040L
#define WS_EX_TOOLWINDOW        0x00000080L
#define WS_EX_WINDOWEDGE        0x00000100L
#define WS_EX_CLIENTEDGE        0x00000200L
#define WS_EX_CONTEXTHELP       0x00000400L

#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0400)

#define WS_EX_RIGHT             0x00001000L
#define WS_EX_LEFT              0x00000000L
#define WS_EX_RTLREADING        0x00002000L
#define WS_EX_LTRREADING        0x00000000L
#define WS_EX_LEFTSCROLLBAR     0x00004000L
#define WS_EX_RIGHTSCROLLBAR    0x00000000L

#define WS_EX_CONTROLPARENT     0x00010000L
#define WS_EX_STATICEDGE        0x00020000L
#define WS_EX_APPWINDOW         0x00040000L


#define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW     (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)

#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define WS_EX_LAYERED           0x00080000

#endif /* _WIN32_WINNT >= 0x0500 */


#if(WINVER >= 0x0500)
#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
#define WS_EX_LAYOUTRTL         0x00400000L // Right to left mirroring
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WS_EX_COMPOSITED        0x02000000L
#endif /* _WIN32_WINNT >= 0x0501 */
#if(_WIN32_WINNT >= 0x0500)
#define WS_EX_NOACTIVATE        0x08000000L
#endif /* _WIN32_WINNT >= 0x0500 */


	/*
	 * Class styles
	 */
#define CS_VREDRAW          0x0001
#define CS_HREDRAW          0x0002
#define CS_DBLCLKS          0x0008
#define CS_OWNDC            0x0020
#define CS_CLASSDC          0x0040
#define CS_PARENTDC         0x0080
#define CS_NOCLOSE          0x0200
#define CS_SAVEBITS         0x0800
#define CS_BYTEALIGNCLIENT  0x1000
#define CS_BYTEALIGNWINDOW  0x2000
#define CS_GLOBALCLASS      0x4000

#define CS_IME              0x00010000
#if(_WIN32_WINNT >= 0x0501)
#define CS_DROPSHADOW       0x00020000
#endif /* _WIN32_WINNT >= 0x0501 */



#endif /* !NOWINSTYLES */
#if(WINVER >= 0x0400)
	/* WM_PRINT flags */
#define PRF_CHECKVISIBLE    0x00000001L
#define PRF_NONCLIENT       0x00000002L
#define PRF_CLIENT          0x00000004L
#define PRF_ERASEBKGND      0x00000008L
#define PRF_CHILDREN        0x00000010L
#define PRF_OWNED           0x00000020L

	/* 3D border styles */
#define BDR_RAISEDOUTER 0x0001
#define BDR_SUNKENOUTER 0x0002
#define BDR_RAISEDINNER 0x0004
#define BDR_SUNKENINNER 0x0008

#define BDR_OUTER       (BDR_RAISEDOUTER | BDR_SUNKENOUTER)
#define BDR_INNER       (BDR_RAISEDINNER | BDR_SUNKENINNER)
#define BDR_RAISED      (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define BDR_SUNKEN      (BDR_SUNKENOUTER | BDR_SUNKENINNER)


#define EDGE_RAISED     (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define EDGE_SUNKEN     (BDR_SUNKENOUTER | BDR_SUNKENINNER)
#define EDGE_ETCHED     (BDR_SUNKENOUTER | BDR_RAISEDINNER)
#define EDGE_BUMP       (BDR_RAISEDOUTER | BDR_SUNKENINNER)

	/* Border flags */
#define BF_LEFT         0x0001
#define BF_TOP          0x0002
#define BF_RIGHT        0x0004
#define BF_BOTTOM       0x0008

#define BF_TOPLEFT      (BF_TOP | BF_LEFT)
#define BF_TOPRIGHT     (BF_TOP | BF_RIGHT)
#define BF_BOTTOMLEFT   (BF_BOTTOM | BF_LEFT)
#define BF_BOTTOMRIGHT  (BF_BOTTOM | BF_RIGHT)
#define BF_RECT         (BF_LEFT | BF_TOP | BF_RIGHT | BF_BOTTOM)

#define BF_DIAGONAL     0x0010

	// For diagonal lines, the BF_RECT flags specify the end point of the
	// vector bounded by the rectangle parameter.
#define BF_DIAGONAL_ENDTOPRIGHT     (BF_DIAGONAL | BF_TOP | BF_RIGHT)
#define BF_DIAGONAL_ENDTOPLEFT      (BF_DIAGONAL | BF_TOP | BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMLEFT   (BF_DIAGONAL | BF_BOTTOM | BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMRIGHT  (BF_DIAGONAL | BF_BOTTOM | BF_RIGHT)


#define BF_MIDDLE       0x0800  /* Fill in the middle */
#define BF_SOFT         0x1000  /* For softer buttons */
#define BF_ADJUST       0x2000  /* Calculate the space left over */
#define BF_FLAT         0x4000  /* For flat rather than 3D borders */
#define BF_MONO         0x8000  /* For monochrome borders */


	 
		BOOL
		WINAPI
		MSDrawEdge(
		IN HMSDC hdc,
		IN OUT LPMSRECT qrc,
		IN UINT edge,
		IN UINT grfFlags );

	/* flags for MSDrawFrameControl */

#define DFC_CAPTION             1
#define DFC_MENU                2
#define DFC_SCROLL              3
#define DFC_BUTTON              4
#if(WINVER >= 0x0500)
#define DFC_POPUPMENU           5
#endif /* WINVER >= 0x0500 */

#define DFCS_CAPTIONCLOSE       0x0000
#define DFCS_CAPTIONMIN         0x0001
#define DFCS_CAPTIONMAX         0x0002
#define DFCS_CAPTIONRESTORE     0x0003
#define DFCS_CAPTIONHELP        0x0004

#define DFCS_MENUARROW          0x0000
#define DFCS_MENUCHECK          0x0001
#define DFCS_MENUBULLET         0x0002
#define DFCS_MENUARROWRIGHT     0x0004
#define DFCS_SCROLLUP           0x0000
#define DFCS_SCROLLDOWN         0x0001
#define DFCS_SCROLLLEFT         0x0002
#define DFCS_SCROLLRIGHT        0x0003
#define DFCS_SCROLLCOMBOBOX     0x0005
#define DFCS_SCROLLSIZEGRIP     0x0008
#define DFCS_SCROLLSIZEGRIPRIGHT 0x0010

#define DFCS_BUTTONCHECK        0x0000
#define DFCS_BUTTONRADIOIMAGE   0x0001
#define DFCS_BUTTONRADIOMASK    0x0002
#define DFCS_BUTTONRADIO        0x0004
#define DFCS_BUTTON3STATE       0x0008
#define DFCS_BUTTONPUSH         0x0010

#define DFCS_INACTIVE           0x0100
#define DFCS_PUSHED             0x0200
#define DFCS_CHECKED            0x0400

#if(WINVER >= 0x0500)
#define DFCS_TRANSPARENT        0x0800
#define DFCS_HOT                0x1000
#endif /* WINVER >= 0x0500 */

#define DFCS_ADJUSTRECT         0x2000
#define DFCS_FLAT               0x4000
#define DFCS_MONO               0x8000

	 
		BOOL
		WINAPI
		MSDrawFrameControl(
		IN HMSDC
		IN OUT LPMSRECT,
		IN UINT,
		IN UINT );


	/* flags for MSDrawCaption */
#define DC_ACTIVE           0x0001
#define DC_SMALLCAP         0x0002
#define DC_ICON             0x0004
#define DC_TEXT             0x0008
#define DC_INBUTTON         0x0010
#if(WINVER >= 0x0500)
#define DC_GRADIENT         0x0020
#endif /* WINVER >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
#define DC_BUTTONS          0x1000
#endif /* _WIN32_WINNT >= 0x0501 */

	 
		BOOL
		WINAPI
		MSDrawCaption( IN HMSWND, IN HMSDC, IN CONST MSRECT *, IN UINT );


#define IDANI_OPEN          1
#define IDANI_CAPTION       3

	 
		BOOL
		WINAPI
		MSDrawAnimatedRects(
		IN HMSWND hwnd,
		IN int idAni,
		IN CONST MSRECT * lprcFrom,
		IN CONST MSRECT * lprcTo );

#endif /* WINVER >= 0x0400 */

#ifndef NOCLIPBOARD


	/*
	 * Predefined Clipboard Formats
	 */
#define CF_TEXT             1
#define CF_BITMAP           2
#define CF_METAFILEPICT     3
#define CF_SYLK             4
#define CF_DIF              5
#define CF_TIFF             6
#define CF_OEMTEXT          7
#define CF_DIB              8
#define CF_PALETTE          9
#define CF_PENDATA          10
#define CF_RIFF             11
#define CF_WAVE             12
#define CF_UNICODETEXT      13
#define CF_ENHMETAFILE      14
#if(WINVER >= 0x0400)
#define CF_HDROP            15
#define CF_LOCALE           16
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
#define CF_DIBV5            17
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0500)
#define CF_MAX              18
#elif(WINVER >= 0x0400)
#define CF_MAX              17
#else
#define CF_MAX              15
#endif

#define CF_OWNERDISPLAY     0x0080
#define CF_DSPTEXT          0x0081
#define CF_DSPBITMAP        0x0082
#define CF_DSPMETAFILEPICT  0x0083
#define CF_DSPENHMETAFILE   0x008E

	/*
	 * "Private" formats don't get GlobalFree()'d
	 */
#define CF_PRIVATEFIRST     0x0200
#define CF_PRIVATELAST      0x02FF

	/*
	 * "GDIOBJ" formats do get MSDeleteObject()'d
	 */
#define CF_GDIOBJFIRST      0x0300
#define CF_GDIOBJLAST       0x03FF


#endif /* !NOCLIPBOARD */

	/*
	 * MSDefines for the fVirt field of the Accelerator table structure.
	 */
#define FVIRTKEY  TRUE          /* Assumed to be == TRUE */
#define FNOINVERT 0x02
#define FSHIFT    0x04
#define FCONTROL  0x08
#define FALT      0x10

	typedef struct tagMSACCEL {
#ifndef _MAC
		BYTE   fVirt;               /* Also called the flags field */
		WORD   key;
		WORD   cmd;
#else
		WORD   fVirt;               /* Also called the flags field */
		WORD   key;
		DWORD  cmd;
#endif
	} MSACCEL, *LPMSACCEL;

	typedef struct tagMSPAINTSTRUCT {
		HMSDC         hdc;
		BOOL        fErase;
		MSRECT        rcPaint;
		BOOL        fRestore;
		BOOL        fIncUpdate;
		BYTE        rgbReserved[ 32 ];
	} MSPAINTSTRUCT, *PMSPAINTSTRUCT, *NPMSPAINTSTRUCT, *LPMSPAINTSTRUCT;

	typedef struct tagMSCREATESTRUCTA {
		LPVOID      lpCreateParams;
		HMSINSTANCE   hInstance;
		HMSMENU       hMenu;
		HMSWND        hwndParent;
		int         cy;
		int         cx;
		int         y;
		int         x;
		LONG        style;
		LPCTSTR      lpszName;
		LPCTSTR      lpszClass;
		DWORD       dwExStyle;
	} MSCREATESTRUCTA, *LPMSCREATESTRUCTA;

	typedef MSCREATESTRUCTA MSCREATESTRUCT;
	typedef LPMSCREATESTRUCTA LPMSCREATESTRUCT;

	typedef struct tagMSWINDOWPLACEMENT {
		UINT  length;
		UINT  flags;
		UINT  showCmd;
		MSPOINT ptMinPosition;
		MSPOINT ptMaxPosition;
		MSRECT  rcNormalPosition;
#ifdef _MAC
		MSRECT  rcDevice;
#endif
	} MSWINDOWPLACEMENT;
	typedef MSWINDOWPLACEMENT *PMSWINDOWPLACEMENT, *LPMSWINDOWPLACEMENT;

#define WPF_SETMINPOSITION          0x0001
#define WPF_RESTORETOMAXIMIZED      0x0002
#if(_WIN32_WINNT >= 0x0500)
#define WPF_ASYNCMSWINDOWPLACEMENT    0x0004
#endif /* _WIN32_WINNT >= 0x0500 */

#if(WINVER >= 0x0400)
	typedef struct tagMSNMHDR
	{
		HMSWND      hwndFrom;
		UINT_PTR  idFrom;
		UINT      code;         // NM_ code
	}   MSNMHDR;
	typedef MSNMHDR FAR * LPMSNMHDR;

	typedef struct tagMSSTYLESTRUCT
	{
		DWORD   styleOld;
		DWORD   styleNew;
	} MSSTYLESTRUCT, *LPMSSTYLESTRUCT;
#endif /* WINVER >= 0x0400 */


	/*
	 * Owner draw control types
	 */
#define ODT_MENU        1
#define ODT_LISTBOX     2
#define ODT_COMBOBOX    3
#define ODT_BUTTON      4
#if(WINVER >= 0x0400)
#define ODT_STATIC      5
#endif /* WINVER >= 0x0400 */

	/*
	 * Owner draw actions
	 */
#define ODA_DRAWENTIRE  0x0001
#define ODA_SELECT      0x0002
#define ODA_FOCUS       0x0004

	/*
	 * Owner draw state
	 */
#define ODS_SELECTED    0x0001
#define ODS_GRAYED      0x0002
#define ODS_DISABLED    0x0004
#define ODS_CHECKED     0x0008
#define ODS_FOCUS       0x0010
#if(WINVER >= 0x0400)
#define ODS_DEFAULT         0x0020
#define ODS_COMBOBOXEDIT    0x1000
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
#define ODS_HOTLIGHT        0x0040
#define ODS_INACTIVE        0x0080
#if(_WIN32_WINNT >= 0x0500)
#define ODS_NOACCEL         0x0100
#define ODS_NOFOCUSRECT     0x0200
#endif /* _WIN32_WINNT >= 0x0500 */
#endif /* WINVER >= 0x0500 */

	/*
	 * MSMEASUREITEMSTRUCT for ownerdraw
	 */
	typedef struct tagMSMEASUREITEMSTRUCT {
		UINT       CtlType;
		UINT       CtlID;
		UINT       itemID;
		UINT       itemWidth;
		UINT       itemHeight;
		ULONG_PTR  itemData;
	} MSMEASUREITEMSTRUCT, NEAR *PMSMEASUREITEMSTRUCT, FAR *LPMSMEASUREITEMSTRUCT;


	/*
	 * MSDRAWITEMSTRUCT for ownerdraw
	 */
	typedef struct tagMSDRAWITEMSTRUCT {
		UINT        CtlType;
		UINT        CtlID;
		UINT        itemID;
		UINT        itemAction;
		UINT        itemState;
		HMSWND        hwndItem;
		HMSDC         hDC;
		MSRECT        rcItem;
		ULONG_PTR   itemData;
	} MSDRAWITEMSTRUCT, NEAR *PMSDRAWITEMSTRUCT, FAR *LPMSDRAWITEMSTRUCT;

	/*
	 * MSDELETEITEMSTRUCT for ownerdraw
	 */
	typedef struct tagMSDELETEITEMSTRUCT {
		UINT       CtlType;
		UINT       CtlID;
		UINT       itemID;
		HMSWND       hwndItem;
		ULONG_PTR  itemData;
	} MSDELETEITEMSTRUCT, NEAR *PMSDELETEITEMSTRUCT, FAR *LPMSDELETEITEMSTRUCT;

	/*
	 * COMPAREITEMSTUCT for ownerdraw sorting
	 */
	typedef struct tagMSCOMPAREITEMSTRUCT {
		UINT        CtlType;
		UINT        CtlID;
		HMSWND        hwndItem;
		UINT        itemID1;
		ULONG_PTR   itemData1;
		UINT        itemID2;
		ULONG_PTR   itemData2;
		DWORD       dwLocaleId;
	} MSCOMPAREITEMSTRUCT, NEAR *PMSCOMPAREITEMSTRUCT, FAR *LPMSCOMPAREITEMSTRUCT;

#ifndef NOMSG

	/*
	 * Message Function Templates
	 */

	 
		BOOL
		WINAPI
		MSGetMessage(
		OUT LPMSMSG lpMsg,
		IN HMSWND hWnd,
		IN UINT wMsgFilterMin,
		IN UINT wMsgFilterMax );


	 
		BOOL
		WINAPI
		MSTranslateMessage(
		IN CONST MSMSG *lpMsg );

	 
		LRESULT
		WINAPI
		MSDispatchMessage(
		IN CONST MSMSG *lpMsg );

	 
		BOOL
		WINAPI
		MSSetMessageQueue(
		IN int cMessagesMax );

	 
		BOOL
		WINAPI
		MSPeekMessage(
		OUT LPMSMSG lpMsg,
		IN HMSWND hWnd,
		IN UINT wMsgFilterMin,
		IN UINT wMsgFilterMax,
		IN UINT wRemoveMsg );


	/*
	 * MSPeekMessage() Options
	 */
#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002
#if(WINVER >= 0x0500)
#define PM_QS_INPUT         (QS_INPUT << 16)
#define PM_QS_POSTMESSAGE   ((QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER) << 16)
#define PM_QS_PAINT         (QS_PAINT << 16)
#define PM_QS_SENDMESSAGE   (QS_SENDMESSAGE << 16)
#endif /* WINVER >= 0x0500 */


#endif /* !NOMSG */

	 
		BOOL
		WINAPI
		MSRegisterHotKey(
		IN HMSWND hWnd,
		IN int id,
		IN UINT fsModifiers,
		IN UINT vk );

	 
		BOOL
		WINAPI
		MSUnregisterHotKey(
		IN HMSWND hWnd,
		IN int id );

#define MOD_ALT         0x0001
#define MOD_CONTROL     0x0002
#define MOD_SHIFT       0x0004
#define MOD_WIN         0x0008


#define IDHOT_SNAPWINDOW        (-1)    /* SHIFT-PRINTSCRN  */
#define IDHOT_SNAPDESKTOP       (-2)    /* PRINTSCRN        */

#ifdef WIN_INTERNAL
#ifndef LSTRING
#define NOLSTRING
#endif /* LSTRING */
#ifndef LFILEIO
#define NOLFILEIO
#endif /* LFILEIO */
#endif /* WIN_INTERNAL */

#if(WINVER >= 0x0400)

#define ENDSESSION_LOGOFF    0x80000000
#endif /* WINVER >= 0x0400 */

#define EWX_LOGOFF          0
#define EWX_SHUTDOWN        0x00000001
#define EWX_REBOOT          0x00000002
#define EWX_FORCE           0x00000004
#define EWX_POWEROFF        0x00000008
#if(_WIN32_WINNT >= 0x0500)
#define EWX_FORCEIFHUNG     0x00000010
#endif /* _WIN32_WINNT >= 0x0500 */


#define MSExitWindows(dwReserved, Code) MSExitWindowsEx(EWX_LOGOFF, 0xFFFFFFFF)

	 
		BOOL
		WINAPI
		MSExitWindowsEx(
		IN UINT uFlags,
		IN DWORD dwReserved );

	 
		BOOL
		WINAPI
		MSSwapMouseButton(
		IN BOOL fSwap );

	 
		DWORD
		WINAPI
		MSGetMessagePos(
		void );

	 
		LONG
		WINAPI
		MSGetMessageTime(
		void );

	 
		LPARAM
		WINAPI
		MSGetMessageExtraInfo(
		void );

#if(WINVER >= 0x0400)
	 
		LPARAM
		WINAPI
		MSSetMessageExtraInfo(
		IN LPARAM lParam );
#endif /* WINVER >= 0x0400 */

	 
		LRESULT
		WINAPI
		MSSendMessage(
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );

	 
		LRESULT
		WINAPI
		MSSendMessageTimeout(
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam,
		IN UINT fuFlags,
		IN UINT uTimeout,
		OUT PDWORD_PTR lpdwResult );


	 
		BOOL
		WINAPI
		MSSendNotifyMessage(
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );


	 
		BOOL
		WINAPI
		MSSendMessageCallback(
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam,
		IN MSSENDASYNCPROC lpResultCallBack,
		IN ULONG_PTR dwData );

#if(_WIN32_WINNT >= 0x0501)
	typedef struct {
		UINT  cbSize;
		HMSDESK hdesk;
		HMSWND  hwnd;
		MSLUID  luid;
	} MSBSMINFO, *PMSBSMINFO;

	 
		long
		WINAPI
		MSBroadcastSystemMessageEx(
		IN DWORD,
		IN LPDWORD,
		IN UINT,
		IN WPARAM,
		IN LPARAM,
		OUT PMSBSMINFO );
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)

#if defined(_WIN32_WINNT)
	 
		long
		WINAPI
		MSBroadcastSystemMessage(
		IN DWORD,
		IN LPDWORD,
		IN UINT,
		IN WPARAM,
		IN LPARAM );

#elif defined(_WIN32_WINDOWS)
	// The Win95 version isn't A/W decorated
	 
		long
		WINAPI
		MSBroadcastSystemMessage(
		IN DWORD,
		IN LPDWORD,
		IN UINT,
		IN WPARAM,
		IN LPARAM);

#endif

	//MSBroadcast Special Message Recipient list
#define BSM_ALLCOMPONENTS       0x00000000
#define BSM_VXDS                0x00000001
#define BSM_NETDRIVER           0x00000002
#define BSM_INSTALLABLEDRIVERS  0x00000004
#define BSM_APPLICATIONS        0x00000008
#define BSM_ALLDESKTOPS         0x00000010

	//MSBroadcast Special Message Flags
#define BSF_QUERY               0x00000001
#define BSF_IGNORECURRENTTASK   0x00000002
#define BSF_FLUSHDISK           0x00000004
#define BSF_NOHANG              0x00000008
#define BSF_POSTMESSAGE         0x00000010
#define BSF_FORCEIFHUNG         0x00000020
#define BSF_NOTIMEOUTIFNOTHUNG  0x00000040
#if(_WIN32_WINNT >= 0x0500)
#define BSF_ALLOWSFW            0x00000080
#define BSF_SENDNOTIFYMESSAGE   0x00000100
#endif /* _WIN32_WINNT >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
#define BSF_RETURNHDESK         0x00000200
#define BSF_LUID                0x00000400
#endif /* _WIN32_WINNT >= 0x0501 */

#define BROADCAST_QUERY_DENY         0x424D5144  // Return this value to deny a query.
#endif /* WINVER >= 0x0400 */

	// MSRegisterDeviceNotification

#if(WINVER >= 0x0500)
	typedef  PVOID           HDEVNOTIFY;
	typedef  HDEVNOTIFY     *PHDEVNOTIFY;

#define DEVICE_NOTIFY_WINDOW_HMSHANDLE          0x00000000
#define DEVICE_NOTIFY_SERVICE_HMSHANDLE         0x00000001
#if(_WIN32_WINNT >= 0x0501)
#define DEVICE_NOTIFY_ALL_INTERFACE_CLASSES  0x00000004
#endif /* _WIN32_WINNT >= 0x0501 */

	 
		HDEVNOTIFY
		WINAPI
		MSRegisterDeviceNotification(
		IN HMSHANDLE hRecipient,
		IN LPVOID NotificationFilter,
		IN DWORD Flags
		);

	 
		BOOL
		WINAPI
		MSUnregisterDeviceNotification(
		IN HDEVNOTIFY Handle
		);
#endif /* WINVER >= 0x0500 */


	 
		BOOL
		WINAPI
		MSPostMessage(
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );

	 
		BOOL
		WINAPI
		MSPostThreadMessage(
		IN DWORD idThread,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );

#define MSPostAppMessage(idThread, wMsg, wParam, lParam)\
	MSPostThreadMessage( ( DWORD )idThread, wMsg, wParam, lParam )

	/*
	 * Special HMSWND value for use with MSPostMessage() and MSSendMessage()
	 */
#define HMSWND_BROADCAST  ((HMSWND)0xffff)

#if(WINVER >= 0x0500)
#define HMSWND_MESSAGE     ((HMSWND)-3)
#endif /* WINVER >= 0x0500 */

	 
		BOOL
		WINAPI
		MSAttachThreadInput(
		IN DWORD idAttach,
		IN DWORD idAttachTo,
		IN BOOL fAttach );


	 
		BOOL
		WINAPI
		MSReplyMessage(
		IN LRESULT lResult );

	 
		BOOL
		WINAPI
		MSWaitMessage(
		void );


	 
		DWORD
		WINAPI
		MSWaitForInputIdle(
		IN HMSHANDLE hProcess,
		IN DWORD dwMilliseconds );

	 
#ifndef _MAC
		LRESULT
		WINAPI
#else
		LRESULT
		CALLBACK
#endif
		MSDefWindowProc(
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );


	 
		void
		WINAPI
		MSPostQuitMessage(
		IN int nExitCode );

#ifdef STRICT

	 
		LRESULT
		WINAPI
		MSCallWindowProc(
		IN MSWNDPROC lpPrevWndFunc,
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );

#else /* !STRICT */

	 
		LRESULT
		WINAPI
		MSCallWindowProc(
		IN FARPROC lpPrevWndFunc,
		IN HMSWND hWnd,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam);


#endif /* !STRICT */

	 
		BOOL
		WINAPI
		MSInSendMessage(
		void );

#if(WINVER >= 0x0500)
	 
		DWORD
		WINAPI
		MSInSendMessageEx(
		IN LPVOID lpReserved );

	/*
	 * MSInSendMessageEx return value
	 */
#define ISMEX_NOSEND      0x00000000
#define ISMEX_SEND        0x00000001
#define ISMEX_NOTIFY      0x00000002
#define ISMEX_CALLBACK    0x00000004
#define ISMEX_REPLIED     0x00000008
#endif /* WINVER >= 0x0500 */

	 
		UINT
		WINAPI
		MSGetDoubleClickTime(
		void );

	 
		BOOL
		WINAPI
		MSSetDoubleClickTime(
		IN UINT );

	 
		ATOM
		WINAPI
		MSRegisterClass(
		IN CONST MSWNDCLASSA *lpWndClass );

	 
		BOOL
		WINAPI
		  MSUnregisterClass(
		IN LPCTSTR lpClassName,
		IN HMSINSTANCE hInstance );

	 
		BOOL
		WINAPI
		  MSGetClassInfo(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpClassName,
		OUT LPMSWNDCLASSA lpWndClass );

#if(WINVER >= 0x0400)
	 
		ATOM
		WINAPI
		  MSRegisterClassEx(
		IN CONST MSWNDCLASSEXA * );

	 
		BOOL
		WINAPI
		  MSGetClassInfoEx(
		IN HMSINSTANCE,
		IN LPCTSTR,
		OUT LPMSWNDCLASSEXA );

#endif /* WINVER >= 0x0400 */

#define CW_USEDEFAULT       ((int)0x80000000)

	/*
	 * Special value for MSCreateWindow, et al.
	 */
#define HMSWND_DESKTOP        ((HMSWND)0)

#if(_WIN32_WINNT >= 0x0501)
	typedef BYTE( WINAPI * MSPREGISTERCLASSNAMEW )( LPCWSTR );
#endif /* _WIN32_WINNT >= 0x0501 */

	 
		HMSWND
		WINAPI
		  MSCreateWindowEx(
		IN DWORD dwExStyle,
		IN LPCTSTR lpClassName,
		IN LPCTSTR lpWindowName,
		IN DWORD dwStyle,
		IN int X,
		IN int Y,
		IN int nWidth,
		IN int nHeight,
		IN HMSWND hWndParent,
		IN HMSMENU hMenu,
		IN HMSINSTANCE hInstance,
		IN LPVOID lpParam );


#define MSCreateWindow(lpClassName, lpWindowName, dwStyle, x, y,\
	nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam )\
	  MSCreateWindowEx( 0L, lpClassName, lpWindowName, dwStyle, x, y, \
	nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam )


	 
		BOOL
		WINAPI
		  MSIsWindow(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		 MSIsMenu(
		IN HMSMENU hMenu );

	 
		BOOL
		WINAPI
		 MSIsChild(
		IN HMSWND hWndParent,
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSDestroyWindow(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSShowWindow(
		IN HMSWND hWnd,
		IN int nCmdShow );

#if(WINVER >= 0x0500)
	 
		BOOL
		WINAPI
		 MSAnimateWindow(
		IN HMSWND hWnd,
		IN DWORD dwTime,
		IN DWORD dwFlags );
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0500)
#if defined(_WINGDI_) && !defined (NOGDI)

	 
		BOOL
		WINAPI
		MSUpdateLayeredWindow(
		HMSWND hWnd,
		HMSDC hdcDst,
		MSPOINT *pptDst,
		MSSIZE *psize,
		HMSDC hdcSrc,
		MSPOINT *pptSrc,
		COLORREF crKey,
		BLENDFUNCTION *pblend,
		DWORD dwFlags );
#endif

#if(_WIN32_WINNT >= 0x0501)
	 
		BOOL
		WINAPI
		MSGetLayeredWindowAttributes(
		HMSWND hwnd,
		COLORREF *pcrKey,
		BYTE *pbAlpha,
		DWORD *pdwFlags );

#define PW_CLIENTONLY           0x00000001


	 
		BOOL
		WINAPI
		MSPrintWindow(
		IN HMSWND hwnd,
		IN HMSDC hdcBlt,
		IN UINT nFlags );

#endif /* _WIN32_WINNT >= 0x0501 */

	 
		BOOL
		WINAPI
		MSSetLayeredWindowAttributes(
		HMSWND hwnd,
		COLORREF crKey,
		BYTE bAlpha,
		DWORD dwFlags );

#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002


#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004


#endif /* _WIN32_WINNT >= 0x0500 */

#if(WINVER >= 0x0400)
	 
		BOOL
		WINAPI
		MSShowWindowAsync(
		IN HMSWND hWnd,
		IN int nCmdShow );
#endif /* WINVER >= 0x0400 */

	 
		BOOL
		WINAPI
		MSFlashWindow(
		IN HMSWND hWnd,
		IN BOOL bInvert );

#if(WINVER >= 0x0500)
	typedef struct {
		UINT  cbSize;
		HMSWND  hwnd;
		DWORD dwFlags;
		UINT  uCount;
		DWORD dwTimeout;
	} MSFLASHWINFO, *PMSFLASHWINFO;

	 
		BOOL
		WINAPI
		MSFlashWindowEx(
		PMSFLASHWINFO pfwi );

#define FLASHW_STOP         0
#define FLASHW_CAPTION      0x00000001
#define FLASHW_TRAY         0x00000002
#define FLASHW_ALL          (FLASHW_CAPTION | FLASHW_TRAY)
#define FLASHW_TIMER        0x00000004
#define FLASHW_TIMERNOFG    0x0000000C

#endif /* WINVER >= 0x0500 */

	 
		BOOL
		WINAPI
		MSShowOwnedPopups(
		IN HMSWND hWnd,
		IN BOOL fShow );

	 
		BOOL
		WINAPI
		MSOpenIcon(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSCloseWindow(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSMoveWindow(
		IN HMSWND hWnd,
		IN int X,
		IN int Y,
		IN int nWidth,
		IN int nHeight,
		IN BOOL bRepaint );

	 
		BOOL
		WINAPI
		MSSetWindowPos(
		IN HMSWND hWnd,
		IN HMSWND hWndInsertAfter,
		IN int X,
		IN int Y,
		IN int cx,
		IN int cy,
		IN UINT uFlags );

	 
		BOOL
		WINAPI
		MSGetWindowPlacement(
		IN HMSWND hWnd,
		OUT MSWINDOWPLACEMENT *lpwndpl );

	 
		BOOL
		WINAPI
		MSSetWindowPlacement(
		IN HMSWND hWnd,
		IN CONST MSWINDOWPLACEMENT *lpwndpl );


#ifndef NODEFERWINDOWPOS

	 
		HMSDWP
		WINAPI
		MSBeginDeferWindowPos(
		IN int nNumWindows );

	 
		HMSDWP
		WINAPI
		MSDeferWindowPos(
		IN HMSDWP hWinPosInfo,
		IN HMSWND hWnd,
		IN HMSWND hWndInsertAfter,
		IN int x,
		IN int y,
		IN int cx,
		IN int cy,
		IN UINT uFlags );

	 
		BOOL
		WINAPI
		MSEndDeferWindowPos(
		IN HMSDWP hWinPosInfo );

#endif /* !NODEFERWINDOWPOS */

	 
		BOOL
		WINAPI
		MSIsWindowVisible(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSIsIconic(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSAnyPopup(
		void );

	 
		BOOL
		WINAPI
		MSBringWindowToTop(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSIsZoomed(
		IN HMSWND hWnd );

	/*
	 * MSSetWindowPos Flags
	 */
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */
#define SWP_REDRAW			0x0800

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER

#if(WINVER >= 0x0400)
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000
#endif /* WINVER >= 0x0400 */

#undef HWND_TOP
#define HWND_TOP        ((HMSWND)0)
#undef HWND_BOTTOM
#define HWND_BOTTOM     ((HMSWND)1)
#undef HWND_TOPMOST
#define HWND_TOPMOST    ((HMSWND)-1)
#undef HWND_NOTOPMOST
#define HWND_NOTOPMOST  ((HMSWND)-2)

#ifndef NOCTLMGR

	/*
	 * WARNING:
	 * The following structures must NOT be DWORD padded because they are
	 * followed by strings, etc that do not have to be DWORD aligned.MS
	 */
	//#include <pshpack2.h>

	/*
	 * original NT 32 bit dialog template:
	 */
	typedef struct {
		DWORD style;
		DWORD dwExtendedStyle;
		WORD cdit;
		short x;
		short y;
		short cx;
		short cy;
	} MSDLGTEMPLATE;
	typedef MSDLGTEMPLATE *LPMSDLGTEMPLATEA;

	typedef LPMSDLGTEMPLATEA LPMSDLGTEMPLATE;
	typedef CONST MSDLGTEMPLATE *LPCMSDLGTEMPLATEA;
	typedef LPCMSDLGTEMPLATEA LPCMSDLGTEMPLATE;

	/*
	 * 32 bit Dialog item template.
	 */
	typedef struct {
		DWORD style;
		DWORD dwExtendedStyle;
		short x;
		short y;
		short cx;
		short cy;
		WORD id;
	} MSDLGITEMTEMPLATE;
	typedef MSDLGITEMTEMPLATE *PMSDLGITEMTEMPLATEA;

	typedef PMSDLGITEMTEMPLATEA PMSDLGITEMTEMPLATE;
	typedef MSDLGITEMTEMPLATE *LPMSDLGITEMTEMPLATEA;
	typedef LPMSDLGITEMTEMPLATEA LPMSDLGITEMTEMPLATE;


	//#include <poppack.h> 

	 
		HMSWND
		WINAPI
		MSCreateDialogParam(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpTemplateName,
		IN HMSWND hWndParent,
		IN MSDLGPROC lpDialogFunc,
		IN LPARAM dwInitParam );

	 
		HMSWND
		WINAPI
		MSCreateDialogIndirectParam(
		IN HMSINSTANCE hInstance,
		IN LPCMSDLGTEMPLATEA lpTemplate,
		IN HMSWND hWndParent,
		IN MSDLGPROC lpDialogFunc,
		IN LPARAM dwInitParam );
	 
		HMSWND
		WINAPI
		MSCreateDialog(
		HMSINSTANCE hInstance,  // handle to module
		LPCTSTR lpTemplate,   // dialog box template name
		HMSWND hWndParent,      // handle to owner window
		MSDLGPROC lpDialogFunc  // dialog box procedure
		);
	 
		HMSWND
		WINAPI
		MSCreateDialogIndirect(
		HMSINSTANCE hInstance,        // handle to module
		LPCMSDLGTEMPLATE lpTemplate,  // dialog box template
		HMSWND hWndParent,            // handle to owner window
		MSDLGPROC lpDialogFunc        // dialog box procedure
		);


	 
		INT_PTR
		WINAPI
		MSDialogBoxParam(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpTemplateName,
		IN HMSWND hWndParent,
		IN MSDLGPROC lpDialogFunc,
		IN LPARAM dwInitParam );

	 
		INT_PTR
		WINAPI
		MSDialogBoxIndirectParam(
		IN HMSINSTANCE hInstance,
		IN LPCMSDLGTEMPLATEA hDialogTemplate,
		IN HMSWND hWndParent,
		IN MSDLGPROC lpDialogFunc,
		IN LPARAM dwInitParam );

	 
		INT_PTR
		WINAPI
		MSDialogBox(
		HMSINSTANCE hInstance,  // handle to module
		LPCTSTR lpTemplate,   // dialog box template
		HMSWND hWndParent,      // handle to owner window
		MSDLGPROC lpDialogFunc  // dialog box procedure
		);
	 
		INT_PTR
		WINAPI
		MSDialogBoxIndirect(
		HMSINSTANCE hInstance,        // handle to module
		LPMSDLGTEMPLATE lpTemplate,  // dialog box template
		HMSWND hWndParent,            // handle to owner window
		MSDLGPROC lpDialogFunc        // dialog box procedure
		);

	//////////////////////////////////////////////////////////


	 
		BOOL
		WINAPI
		MSEndDialog(
		IN HMSWND hDlg,
		IN INT_PTR nResult );

	 
		HMSWND
		WINAPI
		MSGetDlgItem(
		IN HMSWND hDlg,
		IN int nIDDlgItem );

	 
		BOOL
		WINAPI
		MSSetDlgItemInt(
		IN HMSWND hDlg,
		IN int nIDDlgItem,
		IN UINT uValue,
		IN BOOL bSigned );

	 
		UINT
		WINAPI
		MSGetDlgItemInt(
		IN HMSWND hDlg,
		IN int nIDDlgItem,
		OUT BOOL *lpTranslated,
		IN BOOL bSigned );

	 
		BOOL
		WINAPI
		MSSetDlgItemText(
		IN HMSWND hDlg,
		IN int nIDDlgItem,
		IN LPCTSTR lpString );

	 
		UINT
		WINAPI
		MSGetDlgItemText(
		IN HMSWND hDlg,
		IN int nIDDlgItem,
		OUT LPTSTR lpString,
		IN int nMaxCount );


	 
		BOOL
		WINAPI
		MSCheckDlgButton(
		IN HMSWND hDlg,
		IN int nIDButton,
		IN UINT uCheck );

	 
		BOOL
		WINAPI
		MSCheckRadioButton(
		IN HMSWND hDlg,
		IN int nIDFirstButton,
		IN int nIDLastButton,
		IN int nIDCheckButton );

	 
		UINT
		WINAPI
		MSIsDlgButtonChecked(
		IN HMSWND hDlg,
		IN int nIDButton );

	 
		LRESULT
		WINAPI
		MSSendDlgItemMessage(
		IN HMSWND hDlg,
		IN int nIDDlgItem,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );

	 
		HMSWND
		WINAPI
		MSGetNextDlgGroupItem(
		IN HMSWND hDlg,
		IN HMSWND hCtl,
		IN BOOL bPrevious );

	 
		HMSWND
		WINAPI
		MSGetNextDlgTabItem(
		IN HMSWND hDlg,
		IN HMSWND hCtl,
		IN BOOL bPrevious );

	 
		int
		WINAPI
		MSGetDlgCtrlID(
		IN HMSWND hWnd );

	 
		long
		WINAPI
		MSGetDialogBaseUnits( void );

	 
#ifndef _MAC
		LRESULT
		WINAPI
#else
		LRESULT
		CALLBACK
#endif
		MSDefDlgProc(
		IN HMSWND hDlg,
		IN UINT Msg,
		IN WPARAM wParam,
		IN LPARAM lParam );

	/*
	 * Window extra byted needed for private dialog classes.
	 */
#ifndef _MAC
#define DLGWINDOWEXTRA 30
#else
#define DLGWINDOWEXTRA 48
#endif

#endif /* !NOCTLMGR */

#ifndef NOMSG

	 
		BOOL
		WINAPI
		MSCallMsgFilter(
		IN LPMSMSG lpMsg,
		IN int nCode );


#endif /* !NOMSG */

#ifndef NOCLIPBOARD

	/*
	 * Clipboard Manager Functions
	 */

	 
		BOOL
		WINAPI
		MSOpenClipboard(
		IN HMSWND hWndNewOwner );

	 
		BOOL
		WINAPI
		MSCloseClipboard(
		void );


#if(WINVER >= 0x0500)

	 
		DWORD
		WINAPI
		MSGetClipboardSequenceNumber(
		void );

#endif /* WINVER >= 0x0500 */

	 
		HMSWND
		WINAPI
		MSGetClipboardOwner(
		void );

	 
		HMSWND
		WINAPI
		MSSetClipboardViewer(
		IN HMSWND hWndNewViewer );

	 
		HMSWND
		WINAPI
		MSGetClipboardViewer(
		void );

	 
		BOOL
		WINAPI
		MSChangeClipboardChain(
		IN HMSWND hWndRemove,
		IN HMSWND hWndNewNext );

	 
		HMSHANDLE
		WINAPI
		MSSetClipboardData(
		IN UINT uFormat,
		IN HMSHANDLE hMem );

	 
		HMSHANDLE
		WINAPI
		MSGetClipboardData(
		IN UINT uFormat );

	 
		UINT
		WINAPI
		MSRegisterClipboardFormat(
		IN LPCTSTR lpszFormat );


	 
		int
		WINAPI
		MSCountClipboardFormats(
		void );

	 
		UINT
		WINAPI
		MSEnumClipboardFormats(
		IN UINT format );

	 
		int
		WINAPI
		MSGetClipboardFormatName(
		IN UINT format,
		OUT LPTSTR lpszFormatName,
		IN int cchMaxCount );

	 
		BOOL
		WINAPI
		MSEmptyClipboard(
		void );

	 
		BOOL
		WINAPI
		MSIsClipboardFormatAvailable(
		IN UINT format );

	 
		int
		WINAPI
		MSGetPriorityClipboardFormat(
		OUT UINT *paFormatPriorityList,
		IN int cFormats );

	 
		HMSWND
		WINAPI
		MSGetOpenClipboardWindow(
		void );

#endif /* !NOCLIPBOARD */

	/*
	 * Character Translation Routines
	 */

	 
		BOOL
		WINAPI
		MSCharToOem(
		IN LPCTSTR lpszSrc,
		OUT LPTSTR lpszDst );


	 
		BOOL
		WINAPI
		MSOemToChar(
		IN LPCTSTR lpszSrc,
		OUT LPTSTR lpszDst );


	 
		BOOL
		WINAPI
		MSCharToOemBuff(
		IN LPCTSTR lpszSrc,
		OUT LPTSTR lpszDst,
		IN DWORD cchDstLength );

	 
		BOOL
		WINAPI
		MSOemToCharBuff(
		IN LPCTSTR lpszSrc,
		OUT LPTSTR lpszDst,
		IN DWORD cchDstLength );


	 
		LPTSTR
		WINAPI
		MSCharUpper(
		IN OUT LPTSTR lpsz );


	 
		DWORD
		WINAPI
		MSCharUpperBuff(
		IN OUT LPTSTR lpsz,
		IN DWORD cchLength );


	 
		LPTSTR
		WINAPI
		MSCharLower(
		IN OUT LPTSTR lpsz );

	 
		DWORD
		WINAPI
		MSCharLowerBuff(
		IN OUT LPTSTR lpsz,
		IN DWORD cchLength );


	 
		LPTSTR
		WINAPI
		MSCharNext(
		IN LPCTSTR lpsz );

	 
		LPTSTR
		WINAPI
		MSCharPrev(
		IN LPCTSTR lpszStart,
		IN LPCTSTR lpszCurrent );


#if(WINVER >= 0x0400)
	 
		LPTSTR
		WINAPI
		MSCharNextExA(
		IN WORD CodePage,
		IN LPCTSTR lpCurrentChar,
		IN DWORD dwFlags );

	 
		LPTSTR
		WINAPI
		MSCharPrevExA(
		IN WORD CodePage,
		IN LPCTSTR lpStart,
		IN LPCTSTR lpCurrentChar,
		IN DWORD dwFlags );
#endif /* WINVER >= 0x0400 */

	/*
	 * Compatibility defines for character translation routines
	 */
#define MSAnsiToOem MSCharToOemA
#define MSOemToAnsi MSOemToCharA
#define MSAnsiToOemBuff MSCharToOemBuffA
#define MSOemToAnsiBuff MSOemToCharBuffA
#define MSAnsiUpper MSCharUpperA
#define MSAnsiUpperBuff MSCharUpperBuffA
#define MSAnsiLower MSCharLowerA
#define MSAnsiLowerBuff MSCharLowerBuffA
#define MSAnsiNext MSCharNextA
#define MSAnsiPrev MSCharPrevA

#ifndef  NOLANGUAGE
	/*
	 * Language dependent Routines
	 */

	 
		BOOL
		WINAPI
		MSIsCharAlpha(
		IN CHAR ch );

	 
		BOOL
		WINAPI
		MSIsCharAlphaNumeric(
		IN CHAR ch );


	 
		BOOL
		WINAPI
		MSIsCharUpper(
		IN CHAR ch );


	 
		BOOL
		WINAPI
		MSIsCharLower(
		IN CHAR ch );


#endif  /* !NOLANGUAGE */

	 
		HMSWND
		WINAPI
		MSSetFocus(
		IN HMSWND hWnd );

	 
		HMSWND
		WINAPI
		MSGetActiveWindow(
		void );

	 
		HMSWND
		WINAPI
		MSGetFocus(
		void );

	 
		UINT
		WINAPI
		MSGetKBCodePage(
		void );

	 
		SHORT
		WINAPI
		MSGetKeyState(
		IN int nVirtKey );

	 
		SHORT
		WINAPI
		MSGetAsyncKeyState(
		IN int vKey );

	 
		BOOL
		WINAPI
		MSGetKeyboardState(
		OUT PBYTE lpKeyState );

	 
		BOOL
		WINAPI
		MSSetKeyboardState(
		IN LPBYTE lpKeyState );

	 
		int
		WINAPI
		MSGetKeyNameText(
		IN LONG lParam,
		OUT LPTSTR lpString,
		IN int nSize
		);


	 
		int
		WINAPI
		MSGetKeyboardType(
		IN int nTypeFlag );

	 
		int
		WINAPI
		MSToAscii(
		IN UINT uVirtKey,
		IN UINT uScanCode,
		IN CONST BYTE *lpKeyState,
		OUT LPWORD lpChar,
		IN UINT uFlags );

#if(WINVER >= 0x0400)
	 
		int
		WINAPI
		MSToAsciiEx(
		IN UINT uVirtKey,
		IN UINT uScanCode,
		IN CONST BYTE *lpKeyState,
		OUT LPWORD lpChar,
		IN UINT uFlags,
		IN HMSKL dwhkl );
#endif /* WINVER >= 0x0400 */

	 
		int
		WINAPI
		MSToUnicode(
		IN UINT wVirtKey,
		IN UINT wScanCode,
		IN CONST BYTE *lpKeyState,
		OUT LPWSTR pwszBuff,
		IN int cchBuff,
		IN UINT wFlags );

	 
		DWORD
		WINAPI
		MSOemKeyScan(
		IN WORD wOemChar );

	 
		SHORT
		WINAPI
		MSVkKeyScan(
		IN CHAR ch );


#if(WINVER >= 0x0400)
	 
		SHORT
		WINAPI
		MSVkKeyScanEx(
		IN CHAR  ch,
		IN HMSKL   dwhkl );

#endif /* WINVER >= 0x0400 */
#define KEYEVENTF_EXTENDEDKEY 0x0001
#define KEYEVENTF_KEYUP       0x0002
#if(_WIN32_WINNT >= 0x0500)
#define KEYEVENTF_UNICODE     0x0004
#define KEYEVENTF_SCANCODE    0x0008
#endif /* _WIN32_WINNT >= 0x0500 */

	 
		void
		WINAPI
		MSkeybd_event(
		IN BYTE bVk,
		IN BYTE bScan,
		IN DWORD dwFlags,
		IN ULONG_PTR dwExtraInfo );

#define MOUSEEVENTF_MOVE        0x0001 /* mouse move */
#define MOUSEEVENTF_LEFTDOWN    0x0002 /* left button down */
#define MOUSEEVENTF_LEFTUP      0x0004 /* left button up */
#define MOUSEEVENTF_RIGHTDOWN   0x0008 /* right button down */
#define MOUSEEVENTF_RIGHTUP     0x0010 /* right button up */
#define MOUSEEVENTF_MIDDLEDOWN  0x0020 /* middle button down */
#define MOUSEEVENTF_MIDDLEUP    0x0040 /* middle button up */
#define MOUSEEVENTF_XDOWN       0x0080 /* x button down */
#define MOUSEEVENTF_XUP         0x0100 /* x button down */
#define MOUSEEVENTF_WHEEL       0x0800 /* wheel button rolled */
#define MOUSEEVENTF_VIRTUALDESK 0x4000 /* map to entire virtual desktop */
#define MOUSEEVENTF_ABSOLUTE    0x8000 /* absolute move */



	 
		void
		WINAPI
		MSmouse_event(
		IN DWORD dwFlags,
		IN DWORD dx,
		IN DWORD dy,
		IN DWORD dwData,
		IN ULONG_PTR dwExtraInfo );

#if (_WIN32_WINNT > 0x0400)

	typedef struct tagMSMOUSEINPUT {
		LONG    dx;
		LONG    dy;
		DWORD   mouseData;
		DWORD   dwFlags;
		DWORD   time;
		ULONG_PTR dwExtraInfo;
	} MSMOUSEINPUT, *PMSMOUSEINPUT, FAR* LPMSMOUSEINPUT;

	typedef struct tagMSKEYBDINPUT {
		WORD    wVk;
		WORD    wScan;
		DWORD   dwFlags;
		DWORD   time;
		ULONG_PTR dwExtraInfo;
	} MSKEYBDINPUT, *PMSKEYBDINPUT, FAR* LPMSKEYBDINPUT;

	typedef struct tagMSHARDWAREINPUT {
		DWORD   uMsg;
		WORD    wParamL;
		WORD    wParamH;
	} MSHARDWAREINPUT, *PMSHARDWAREINPUT, FAR* LPMSHARDWAREINPUT;

#define INPUT_MOUSE     0
#define INPUT_KEYBOARD  1
#define INPUT_HARDWARE  2

	typedef struct tagMSINPUT {
		DWORD   type;

		union
		{
			MSMOUSEINPUT      mi;
			MSKEYBDINPUT      ki;
			MSHARDWAREINPUT   hi;
		}u;
	} MSINPUT, *PMSINPUT, FAR* LPMSINPUT;

	 
		UINT
		WINAPI
		MSSendInput(
		IN UINT    cInputs,     // number of input in the array
		IN LPMSINPUT pInputs,     // array of inputs
		IN int     cbSize );     // sizeof(MSINPUT)

#endif // (_WIN32_WINNT > 0x0400)

#if(_WIN32_WINNT >= 0x0500)
	typedef struct tagMSLASTINPUTINFO {
		UINT cbSize;
		DWORD dwTime;
	} MSLASTINPUTINFO, *PMSLASTINPUTINFO;

	 
		BOOL
		WINAPI
		MSGetLastInputInfo(
		OUT PMSLASTINPUTINFO plii );
#endif /* _WIN32_WINNT >= 0x0500 */

	 
		UINT
		WINAPI
		MSMapVirtualKey(
		IN UINT uCode,
		IN UINT uMapType );


#if(WINVER >= 0x0400)
	 
		UINT
		WINAPI
		MSMapVirtualKeyEx(
		IN UINT uCode,
		IN UINT uMapType,
		IN HMSKL dwhkl );

#endif /* WINVER >= 0x0400 */

	 
		BOOL
		WINAPI
		MSGetInputState(
		void );

	 
		DWORD
		WINAPI
		MSGetQueueStatus(
		IN UINT flags );


	 
		HMSWND
		WINAPI
		MSGetCapture(
		void );

	 
		HMSWND
		WINAPI
		MSSetCapture(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSModifyCapture(
		void );

	 
		DWORD
		WINAPI
		MSMsgWaitForMultipleObjects(
		IN DWORD nCount,
		IN CONST HMSHANDLE *pHandles,
		IN BOOL fWaitAll,
		IN DWORD dwMilliseconds,
		IN DWORD dwWakeMask );

	 
		DWORD
		WINAPI
		MSMsgWaitForMultipleObjectsEx(
		IN DWORD nCount,
		IN CONST HMSHANDLE *pHandles,
		IN DWORD dwMilliseconds,
		IN DWORD dwWakeMask,
		IN DWORD dwFlags );


#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002
#define MWMO_INPUTAVAILABLE 0x0004

	/*
	 * Queue status flags for MSGetQueueStatus() and MsgWaitForMultipleObjects()
	 */
#define QS_KEY              0x0001
#define QS_MOUSEMOVE        0x0002
#define QS_MOUSEBUTTON      0x0004
#define QS_POSTMESSAGE      0x0008
#define QS_TIMER            0x0010
#define QS_PAINT            0x0020
#define QS_SENDMESSAGE      0x0040
#define QS_HOTKEY           0x0080
#define QS_ALLPOSTMESSAGE   0x0100
#if(_WIN32_WINNT >= 0x0501)
#define QS_RAWINPUT         0x0400
#endif /* _WIN32_WINNT >= 0x0501 */

#define QS_MOUSE           (QS_MOUSEMOVE     | \
	QS_MOUSEBUTTON )

#if (_WIN32_WINNT >= 0x0501)
#define QS_INPUT           (QS_MOUSE         | \
	QS_KEY | \
	QS_RAWINPUT )
#else
#define QS_INPUT           (QS_MOUSE         | \
	QS_KEY)
#endif // (_WIN32_WINNT >= 0x0501)

#define QS_ALLEVENTS       (QS_INPUT         | \
	QS_POSTMESSAGE | \
	QS_TIMER | \
	QS_PAINT | \
	QS_HOTKEY )

#define QS_ALLINPUT        (QS_INPUT         | \
	QS_POSTMESSAGE | \
	QS_TIMER | \
	QS_PAINT | \
	QS_HOTKEY | \
	QS_SENDMESSAGE )


	/*
	 * Windows Functions
	 */

	 
		UINT_PTR
		WINAPI
		MSSetTimer(
		IN HMSWND hWnd,
		IN UINT_PTR nIDEvent,
		IN UINT uElapse,
		IN MSTIMERPROC lpTimerFunc );

		UINT_PTR
		WINAPI
		MSSetTimerEx(
		IN HMSWND hWnd,
		IN UINT_PTR nIDEvent,
		IN UINT uElapse,
		IN UINT uUserData,
		IN MSTIMERPROC lpTimerFunc);

		UINT_PTR
		WINAPI
		MSGetTimerTimeout (
		IN HMSWND hWnd ,
		IN UINT_PTR nIDEvent );

	 
		BOOL
		WINAPI
		MSKillTimer(
		IN HMSWND hWnd,
		IN UINT_PTR uIDEvent );

	 
		BOOL
		WINAPI
		MSIsWindowUnicode(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSEnableWindow(
		IN HMSWND hWnd,
		IN BOOL bEnable );

	 
		BOOL
		WINAPI
		MSIsWindowEnabled(
		IN HMSWND hWnd );

	 
		HMSACCEL
		WINAPI
		MSLoadAccelerators(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpTableName );

	 
		HMSACCEL
		WINAPI
		MSCreateAcceleratorTable(
		IN LPMSACCEL, IN int );


	 
		BOOL
		WINAPI
		MSDestroyAcceleratorTable(
		IN HMSACCEL hAccel );

	 
		int
		WINAPI
		MSCopyAcceleratorTable(
		IN HMSACCEL hAccelSrc,
		OUT LPMSACCEL lpAccelDst,
		IN int cAccelEntries );


#ifndef NOMSG

	 
		int
		WINAPI
		MSTranslateAccelerator(
		IN HMSWND hWnd,
		IN HMSACCEL hAccTable,
		IN LPMSMSG lpMsg );


#endif /* !NOMSG */

#ifndef NOSYSMETRICS

	/*
	 * MSGetSystemMetrics() codes
	 */

#define SM_CXSCREEN             0
#define SM_CYSCREEN             1
#define SM_CXVSCROLL            2
#define SM_CYHSCROLL            3
#define SM_CYCAPTION            4
#define SM_CXBORDER             5
#define SM_CYBORDER             6
#define SM_CXDLGFRAME           7
#define SM_CYDLGFRAME           8
#define SM_CYVTHUMB             9
#define SM_CXHTHUMB             10
#define SM_CXICON               11
#define SM_CYICON               12
#define SM_CXCURSOR             13
#define SM_CYCURSOR             14
#define SM_CYMENU               15
#define SM_CXFULLSCREEN         16
#define SM_CYFULLSCREEN         17
#define SM_CYKANJIWINDOW        18
#define SM_MOUSEPRESENT         19
#define SM_CYVSCROLL            20
#define SM_CXHSCROLL            21
#define SM_DEBUG                22
#define SM_SWAPBUTTON           23
#define SM_RESERVED1            24
#define SM_RESERVED2            25
#define SM_RESERVED3            26
#define SM_RESERVED4            27
#define SM_CXMIN                28
#define SM_CYMIN                29
#define SM_CXSIZE               30
#define SM_CYSIZE               31
#define SM_CXFRAME              32
#define SM_CYFRAME              33
#define SM_CXMINTRACK           34
#define SM_CYMINTRACK           35
#define SM_CXDOUBLECLK          36
#define SM_CYDOUBLECLK          37
#define SM_CXICONSPACING        38
#define SM_CYICONSPACING        39
#define SM_MENUDROPALIGNMENT    40
#define SM_PENWINDOWS           41
#define SM_DBCSENABLED          42
#define SM_CMOUSEBUTTONS        43

#if(WINVER >= 0x0400)
#define SM_CXFIXEDFRAME           SM_CXDLGFRAME  /* ;win40 name change */
#define SM_CYFIXEDFRAME           SM_CYDLGFRAME  /* ;win40 name change */
#define SM_CXSIZEFRAME            SM_CXFRAME     /* ;win40 name change */
#define SM_CYSIZEFRAME            SM_CYFRAME     /* ;win40 name change */

#define SM_SECURE               44
#define SM_CXEDGE               45
#define SM_CYEDGE               46
#define SM_CXMINSPACING         47
#define SM_CYMINSPACING         48
#define SM_CXSMICON             49
#define SM_CYSMICON             50
#define SM_CYSMCAPTION          51
#define SM_CXSMSIZE             52
#define SM_CYSMSIZE             53
#define SM_CXMENUSIZE           54
#define SM_CYMENUSIZE           55
#define SM_ARRANGE              56
#define SM_CXMINIMIZED          57
#define SM_CYMINIMIZED          58
#define SM_CXMAXTRACK           59
#define SM_CYMAXTRACK           60
#define SM_CXMAXIMIZED          61
#define SM_CYMAXIMIZED          62
#define SM_NETWORK              63
#define SM_CLEANBOOT            67
#define SM_CXDRAG               68
#define SM_CYDRAG               69
#endif /* WINVER >= 0x0400 */
#define SM_SHOWSOUNDS           70
#if(WINVER >= 0x0400)
#define SM_CXMENUCHECK          71   /* Use instead of MSGetMenuCheckMarkDimensions()! */
#define SM_CYMENUCHECK          72
#define SM_SLOWMACHINE          73
#define SM_MIDEASTENABLED       74
#endif /* WINVER >= 0x0400 */

#if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
#define SM_MOUSEWHEELPRESENT    75
#endif
#if(WINVER >= 0x0500)
#define SM_XVIRTUALSCREEN       76
#define SM_YVIRTUALSCREEN       77
#define SM_CXVIRTUALSCREEN      78
#define SM_CYVIRTUALSCREEN      79
#define SM_CMONITORS            80
#define SM_SAMEDISPLAYFORMAT    81
#endif /* WINVER >= 0x0500 */
#if(_WIN32_WINNT >= 0x0500)
#define SM_IMMENABLED           82
#endif /* _WIN32_WINNT >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
#define SM_CXFOCUSBORDER        83
#define SM_CYFOCUSBORDER        84
#endif /* _WIN32_WINNT >= 0x0501 */

#if (WINVER < 0x0500) && (!defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0400))
#define SM_CMETRICS             76
#else
#define SM_CMETRICS             86
#endif

#if(WINVER >= 0x0500)
#define SM_REMOTESESSION        0x1000


#if(_WIN32_WINNT >= 0x0501)
#define SM_SHUTTINGDOWN         0x2000
#endif /* _WIN32_WINNT >= 0x0501 */

#endif /* WINVER >= 0x0500 */


	 
		int
		WINAPI
		MSGetSystemMetrics(
		IN int nIndex );


#endif /* !NOSYSMETRICS */

#ifndef NOMENUS

	 
		HMSMENU
		WINAPI
		MSLoadMenu(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpMenuName );

	 
		HMSMENU
		WINAPI
		MSLoadMenuIndirect(
		IN CONST MENUTEMPLATEA *lpMenuTemplate );


	 
		HMSMENU
		WINAPI
		MSGetMenu(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSSetMenu(
		IN HMSWND hWnd,
		IN HMSMENU hMenu );

	 
		BOOL
		WINAPI
		MSChangeMenu(
		IN HMSMENU hMenu,
		IN UINT cmd,
		IN LPCTSTR lpszNewItem,
		IN UINT cmdInsert,
		IN UINT flags );

	 
		BOOL
		WINAPI
		MSHiliteMenuItem(
		IN HMSWND hWnd,
		IN HMSMENU hMenu,
		IN UINT uIDHiliteItem,
		IN UINT uHilite );

	 
		int
		WINAPI
		MSGetMenuString(
		IN HMSMENU hMenu,
		IN UINT uIDItem,
		OUT LPTSTR lpString,
		IN int nMaxCount,
		IN UINT uFlag );

	 
		UINT
		WINAPI
		MSGetMenuState(
		IN HMSMENU hMenu,
		IN UINT uId,
		IN UINT uFlags );

	 
		BOOL
		WINAPI
		MSDrawMenuBar(
		IN HMSWND hWnd );

#if(_WIN32_WINNT >= 0x0501)
#define PMB_ACTIVE      0x00000001

#endif /* _WIN32_WINNT >= 0x0501 */


	 
		HMSMENU
		WINAPI
		MSGetSystemMenu(
		IN HMSWND hWnd,
		IN BOOL bRevert );


	 
		HMSMENU
		WINAPI
		MSCreateMenu(
		void );

	 
		HMSMENU
		WINAPI
		MSCreatePopupMenu(
		void );

	 
		BOOL
		WINAPI
		MSDestroyMenu(
		IN HMSMENU hMenu );

	 
		DWORD
		WINAPI
		MSCheckMenuItem(
		IN HMSMENU hMenu,
		IN UINT uIDCheckItem,
		IN UINT uCheck );

	 
		BOOL
		WINAPI
		MSEnableMenuItem(
		IN HMSMENU hMenu,
		IN UINT uIDEnableItem,
		IN UINT uEnable );

	 
		HMSMENU
		WINAPI
		MSGetSubMenu(
		IN HMSMENU hMenu,
		IN int nPos );

	 
		UINT
		WINAPI
		MSGetMenuItemID(
		IN HMSMENU hMenu,
		IN int nPos );

	 
		int
		WINAPI
		MSGetMenuItemCount(
		IN HMSMENU hMenu );

	 
		BOOL
		WINAPI
		MSInsertMenu(
		IN HMSMENU hMenu,
		IN UINT uPosition,
		IN UINT uFlags,
		IN UINT_PTR uIDNewItem,
		IN LPCTSTR lpNewItem
		);

	 
		BOOL
		WINAPI
		MSAppendMenu(
		IN HMSMENU hMenu,
		IN UINT uFlags,
		IN UINT_PTR uIDNewItem,
		IN LPCTSTR lpNewItem
		);

	 
		BOOL
		WINAPI
		MSModifyMenu(
		IN HMSMENU hMnu,
		IN UINT uPosition,
		IN UINT uFlags,
		IN UINT_PTR uIDNewItem,
		IN LPCTSTR lpNewItem
		);


	 
		BOOL
		WINAPI MSRemoveMenu(
		IN HMSMENU hMenu,
		IN UINT uPosition,
		IN UINT uFlags );

	 
		BOOL
		WINAPI
		MSDeleteMenu(
		IN HMSMENU hMenu,
		IN UINT uPosition,
		IN UINT uFlags );

	 
		BOOL
		WINAPI
		MSSetMenuItemBitmaps(
		IN HMSMENU hMenu,
		IN UINT uPosition,
		IN UINT uFlags,
		IN HMSBITMAP hBitmapUnchecked,
		IN HMSBITMAP hBitmapChecked );

	 
		LONG
		WINAPI
		MSGetMenuCheckMarkDimensions(
		void );

	 
		BOOL
		WINAPI
		MSTrackPopupMenu(
		IN HMSMENU hMenu,
		IN UINT uFlags,
		IN int x,
		IN int y,
		IN int nReserved,
		IN HMSWND hWnd,
		IN CONST MSRECT *prcRect );

#if(WINVER >= 0x0400)
	/* return codes for WM_MENUCHAR */
#define MNC_IGNORE  0
#define MNC_CLOSE   1
#define MNC_EXECUTE 2
#define MNC_SELECT  3

	typedef struct tagCSTPMPARAMS
	{
		UINT    cbSize;     /* Size of structure */
		MSRECT    rcExclude;  /* Screen coordinates of rectangle to exclude when positioning */
	}   MSTPMPARAMS;
	typedef MSTPMPARAMS FAR *LPMSTPMPARAMS;

	 
		BOOL
		WINAPI
		MSTrackPopupMenuEx(
		IN HMSMENU,
		IN UINT,
		IN int,
		IN int,
		IN HMSWND,
		IN LPMSTPMPARAMS );
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)

#define MNS_NOCHECK         0x80000000
#define MNS_MODELESS        0x40000000
#define MNS_DRAGDROP        0x20000000
#define MNS_AUTODISMISS     0x10000000
#define MNS_NOTIFYBYPOS     0x08000000
#define MNS_CHECKORBMP      0x04000000

#define MIM_MAXHEIGHT               0x00000001
#define MIM_BACKGROUND              0x00000002
#define MIM_HELPID                  0x00000004
#define MIM_MENUDATA                0x00000008
#define MIM_STYLE                   0x00000010
#define MIM_APPLYTOSUBMENUS         0x80000000

	typedef struct tagMSMENUINFO
	{
		DWORD   cbSize;
		DWORD   fMask;
		DWORD   dwStyle;
		UINT    cyMax;
		HMSBRUSH  hbrBack;
		DWORD   dwContextHelpID;
		ULONG_PTR dwMenuData;
	}   MSMENUINFO, FAR *LPMSMENUINFO;
	typedef MSMENUINFO CONST FAR *LPCMSMENUINFO;

	 
		BOOL
		WINAPI
		MSGetMenuInfo(
		IN HMSMENU,
		OUT LPCMSMENUINFO );

	 
		BOOL
		WINAPI
		MSSetMenuInfo(
		IN HMSMENU,
		IN LPCMSMENUINFO );

	 
		BOOL
		WINAPI
		MSEndMenu(
		void );

	/*
	 * WM_MENUDRAG return values.
	 */
#define MND_CONTINUE       0
#define MND_ENDMENU        1

	typedef struct tagMSMENUGETOBJECTINFO
	{
		DWORD dwFlags;
		UINT uPos;
		HMSMENU hmenu;
		PVOID riid;
		PVOID pvObj;
	} MSMENUGETOBJECTINFO, *PMSMENUGETOBJECTINFO;

	/*
	 * MSMENUGETOBJECTINFO dwFlags values
	 */
#define MNGOF_TOPGAP         0x00000001
#define MNGOF_BOTTOMGAP      0x00000002

	/*
	 * WM_MENUGETOBJECT return values
	 */
#define MNGO_NOINTERFACE     0x00000000
#define MNGO_NOERROR         0x00000001
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)
#define MIIM_STATE       0x00000001
#define MIIM_ID          0x00000002
#define MIIM_SUBMENU     0x00000004
#define MIIM_CHECKMARKS  0x00000008
#define MIIM_TYPE        0x00000010
#define MIIM_DATA        0x00000020
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#define MIIM_STRING      0x00000040
#define MIIM_BITMAP      0x00000080
#define MIIM_FTYPE       0x00000100
	/*
	#define HBMMENU_CALLBACK            ((HMSBITMAP) -1)
	#define HBMMENU_SYSTEM              ((HMSBITMAP)  1)
	#define HBMMENU_MBAR_RESTORE        ((HMSBITMAP)  2)
	#define HBMMENU_MBAR_MINIMIZE       ((HMSBITMAP)  3)
	#define HBMMENU_MBAR_CLOSE          ((HMSBITMAP)  5)
	#define HBMMENU_MBAR_CLOSE_D        ((HMSBITMAP)  6)
	#define HBMMENU_MBAR_MINIMIZE_D     ((HMSBITMAP)  7)
	#define HBMMENU_POPUP_CLOSE         ((HMSBITMAP)  8)
	#define HBMMENU_POPUP_RESTORE       ((HMSBITMAP)  9)
	#define HBMMENU_POPUP_MAXIMIZE      ((HMSBITMAP) 10)
	#define HBMMENU_POPUP_MINIMIZE      ((HMSBITMAP) 11)
	*/
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)
	typedef struct tagMSMENUITEMINFOA
	{
		UINT     cbSize;
		UINT     fMask;
		UINT     fType;         // used if MIIM_TYPE (4.0) or MIIM_FTYPE (>4.0)
		UINT     fState;        // used if MIIM_STATE
		UINT     wID;           // used if MIIM_ID
		HMSMENU    hSubMenu;      // used if MIIM_SUBMENU
		HMSBITMAP  hbmpChecked;   // used if MIIM_CHECKMARKS
		HMSBITMAP  hbmpUnchecked; // used if MIIM_CHECKMARKS
		ULONG_PTR dwItemData;   // used if MIIM_DATA
		LPTSTR    dwTypeData;    // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
		UINT     cch;           // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
#if(WINVER >= 0x0500)
		HMSBITMAP  hbmpItem;      // used if MIIM_BITMAP
#endif /* WINVER >= 0x0500 */
	}   MSMENUITEMINFOA, FAR *LPMSMENUITEMINFOA;

	typedef MSMENUITEMINFOA MSMENUITEMINFO;
	typedef LPMSMENUITEMINFOA LPMSMENUITEMINFO;
	typedef MSMENUITEMINFOA CONST FAR *LPCMSMENUITEMINFOA;
	typedef LPCMSMENUITEMINFOA LPCMSMENUITEMINFO;


	 
		BOOL
		WINAPI
		MSInsertMenuItem(
		IN HMSMENU,
		IN UINT,
		IN BOOL,
		IN LPCMSMENUITEMINFOA
		);


	 
		BOOL
		WINAPI
		MSGetMenuItemInfo(
		IN HMSMENU,
		IN UINT,
		IN BOOL,
		IN OUT LPMSMENUITEMINFOA
		);

	 
		BOOL
		WINAPI
		MSSetMenuItemInfo(
		IN HMSMENU,
		IN UINT,
		IN BOOL,
		IN LPMSMENUITEMINFOA
		);


#define GMDI_USEDISABLED    0x0001L
#define GMDI_GOINTOPOPUPS   0x0002L

	  UINT    WINAPI MSGetMenuDefaultItem( IN HMSMENU hMenu, IN UINT fByPos, IN UINT gmdiFlags );
	  BOOL    WINAPI MSSetMenuDefaultItem( IN HMSMENU hMenu, IN UINT uItem, IN UINT fByPos );

	  BOOL    WINAPI MSGetMenuItemRect( IN HMSWND hWnd, IN HMSMENU hMenu, IN UINT uItem, OUT LPMSRECT lprcItem );
	  int     WINAPI MSMenuItemFromPoint( IN HMSWND hWnd, IN HMSMENU hMenu, IN MSPOINT ptScreen );
#endif /* WINVER >= 0x0400 */

	/*
	 * Flags for MSTrackPopupMenu
	 */
#define TPM_LEFTBUTTON  0x0000L
#define TPM_RIGHTBUTTON 0x0002L
#define TPM_LEFTALIGN   0x0000L
#define TPM_CENTERALIGN 0x0004L
#define TPM_RIGHTALIGN  0x0008L
#if(WINVER >= 0x0400)
#define TPM_TOPALIGN        0x0000L
#define TPM_VCENTERALIGN    0x0010L
#define TPM_BOTTOMALIGN     0x0020L

#define TPM_HORIZONTAL      0x0000L     /* Horz alignment matters more */
#define TPM_VERTICAL        0x0040L     /* Vert alignment matters more */
#define TPM_NONOTIFY        0x0080L     /* Don't send any notification msgs */
#define TPM_RETURNCMD       0x0100L
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
#define TPM_RECURSE         0x0001L
#define TPM_HORPOSANIMATION 0x0400L
#define TPM_HORNEGANIMATION 0x0800L
#define TPM_VERPOSANIMATION 0x1000L
#define TPM_VERNEGANIMATION 0x2000L
#if(_WIN32_WINNT >= 0x0500)
#define TPM_NOANIMATION     0x4000L
#endif /* _WIN32_WINNT >= 0x0500 */
#if(_WIN32_WINNT >= 0x0501)
#define TPM_LAYOUTRTL       0x8000L
#endif /* _WIN32_WINNT >= 0x0501 */
#endif /* WINVER >= 0x0500 */


#endif /* !NOMENUS */


#if(WINVER >= 0x0400)
	//
	// MSDrag-and-drop support
	// Obsolete - use OLE instead
	//
	typedef struct tagMSDROPSTRUCT
	{
		HMSWND    hwndSource;
		HMSWND    hwndSink;
		DWORD   wFmt;
		ULONG_PTR dwData;
		MSPOINT   ptDrop;
		DWORD   dwControlData;
	} MSDROPSTRUCT, *PMSDROPSTRUCT, *LPMSDROPSTRUCT;

#define DOF_EXECUTABLE      0x8001      // wFmt flags
#define DOF_DOCUMENT        0x8002
#define DOF_DIRECTORY       0x8003
#define DOF_MULTIPLE        0x8004
#define DOF_PROGMAN         0x0001
#define DOF_SHELLDATA       0x0002

#define DO_DROPFILE         0x454C4946L
#define DO_PRINTFILE        0x544E5250L

	 
		DWORD
		WINAPI
		MSDragObject(
		IN HMSWND,
		IN HMSWND,
		IN UINT,
		IN ULONG_PTR,
		IN HMSCURSOR );

	 
		BOOL
		WINAPI
		MSDragDetect(
		IN HMSWND,
		IN MSPOINT );
#endif /* WINVER >= 0x0400 */

	 
		BOOL
		WINAPI
		MSDrawIcon(
		IN HMSDC hDC,
		IN int X,
		IN int Y,
		IN HMSICON hIcon );

#ifndef NODRAWTEXT

	/*
	 * MSDrawText() Format Flags
	 */
#define DT_TOP                      0x00000000
#define DT_LEFT                     0x00000000
#define DT_CENTER                   0x00000001
#define DT_RIGHT                    0x00000002
#define DT_VCENTER                  0x00000004
#define DT_BOTTOM                   0x00000008
#define DT_WORDBREAK                0x00000010
#define DT_SINGLELINE               0x00000020
#define DT_EXPANDTABS               0x00000040
#define DT_TABSTOP                  0x00000080
#define DT_NOCLIP                   0x00000100
#define DT_EXTERNALLEADING          0x00000200
#define DT_CALCRECT                 0x00000400
#define DT_NOPREFIX                 0x00000800
#define DT_INTERNAL                 0x00001000

#if(WINVER >= 0x0400)
#define DT_EDITCONTROL              0x00002000
#define DT_PATH_ELLIPSIS            0x00004000
#define DT_END_ELLIPSIS             0x00008000
#define DT_MODIFYSTRING             0x00010000
#define DT_RTLREADING               0x00020000
#define DT_WORD_ELLIPSIS            0x00040000
#if(WINVER >= 0x0500)
#define DT_NOFULLWIDTHCHARBREAK     0x00080000
#if(_WIN32_WINNT >= 0x0500)
#define DT_HIDEPREFIX               0x00100000
#define DT_PREFIXONLY               0x00200000
#endif /* _WIN32_WINNT >= 0x0500 */
#endif /* WINVER >= 0x0500 */

	typedef struct tagMSDRAWTEXTPARAMS
	{
		UINT    cbSize;
		int     iTabLength;
		int     iLeftMargin;
		int     iRightMargin;
		UINT    uiLengthDrawn;
	} MSDRAWTEXTPARAMS, FAR *LPMSDRAWTEXTPARAMS;
#endif /* WINVER >= 0x0400 */


	 
		int
		WINAPI
		MSDrawText(
		IN HMSDC hDC,
		IN LPCTSTR lpString,
		IN int nCount,
		IN OUT LPMSRECT lpRect,
		IN UINT uFormat );


		int
		WINAPI
		MSScrollDrawText (
		IN HMSDC hDC ,
		IN LPCTSTR lpString ,
		IN int nCount ,
		IN unsigned int unXWight , 
		IN unsigned int unYHight ,
		IN OUT LPMSRECT lpRect ,
		IN UINT uFormat ,
		unsigned int unXScrollInterval ,
		unsigned int unYScrollInterval );

#if(WINVER >= 0x0400)
	 
		int
		WINAPI
		MSDrawTextEx(
		IN HMSDC,
		IN OUT LPTSTR,
		IN int,
		IN OUT LPMSRECT,
		IN UINT,
		IN LPMSDRAWTEXTPARAMS );

#endif /* WINVER >= 0x0400 */

#endif /* !NODRAWTEXT */

	 
		BOOL
		WINAPI
		MSGrayString(
		IN HMSDC hDC,
		IN HMSBRUSH hBrush,
		IN MSGRAYSTRINGPROC lpOutputFunc,
		IN LPARAM lpData,
		IN int nCount,
		IN int X,
		IN int Y,
		IN int nWidth,
		IN int nHeight );

#if(WINVER >= 0x0400)
	/* Monolithic state-drawing routine */
	/* Image type */
#define DST_COMPLEX     0x0000
#define DST_TEXT        0x0001
#define DST_PREFIXTEXT  0x0002
#define DST_ICON        0x0003
#define DST_BITMAP      0x0004

	/* State type */
#define DSS_NORMAL      0x0000
#define DSS_UNION       0x0010  /* MSGray string appearance */
#define DSS_DISABLED    0x0020
#define DSS_MONO        0x0080
#if(_WIN32_WINNT >= 0x0500)
#define DSS_HIDEPREFIX  0x0200
#define DSS_PREFIXONLY  0x0400
#endif /* _WIN32_WINNT >= 0x0500 */
#define DSS_RIGHT       0x8000

	 
		BOOL
		WINAPI
		MSDrawState(
		IN HMSDC
		IN HMSBRUSH,
		IN MSDRAWSTATEPROC,
		IN LPARAM,
		IN WPARAM,
		IN int,
		IN int,
		IN int,
		IN int,
		IN UINT );

#endif /* WINVER >= 0x0400 */

	 
		LONG
		WINAPI
		MSTabbedTextOut(
		IN HMSDC hDC,
		IN int X,
		IN int Y,
		IN LPCTSTR lpString,
		IN int nCount,
		IN int nTabPositions,
		IN CONST LPINT lpnTabStopPositions,
		IN int nTabOrigin );


	 
		DWORD
		WINAPI
		MSGetTabbedTextExtent(
		IN HMSDC hDC,
		IN LPCTSTR lpString,
		IN int nCount,
		IN int nTabPositions,
		IN CONST INT *lpnTabStopPositions );

	 
		BOOL
		WINAPI
		MSUpdateWindow(
		IN HMSWND hWnd );

	 
		HMSWND
		WINAPI
		MSSetActiveWindow(
		IN HMSWND hWnd );

	 
		HMSWND
		WINAPI
		MSGetForegroundWindow(
		void );

#if(WINVER >= 0x0400)
	 
		BOOL
		WINAPI
		MSPaintDesktop(
		IN HMSDC hdc );

#endif /* WINVER >= 0x0400 */

	 
		BOOL
		WINAPI
		MSSetForegroundWindow(
		IN HMSWND hWnd );

#if(_WIN32_WINNT >= 0x0500)
	 
		BOOL
		WINAPI
		MSAllowSetForegroundWindow(
		DWORD dwProcessId );

#define ASFW_ANY    ((DWORD)-1)

	 
		BOOL
		WINAPI
		MSLockSetForegroundWindow(
		UINT uLockCode );

#define LSFW_LOCK       1
#define LSFW_UNLOCK     2

#endif /* _WIN32_WINNT >= 0x0500 */

	 
		HMSWND
		WINAPI
		MSWindowFromDC(
		IN HMSDC hDC );

	 
		HMSDC
		WINAPI
		MSGetDC(
		IN HMSWND hWnd );

	 
		HMSDC
		WINAPI
		MSGetDCEx(
		IN HMSWND hWnd,
		IN HMSRGN hrgnClip,
		IN DWORD flags );

	/*
	 * MSGetDCEx() flags
	 */
#define DCX_WINDOW           0x00000001L
#define DCX_CACHE            0x00000002L
#define DCX_NORESETATTRS     0x00000004L
#define DCX_CLIPCHILDREN     0x00000008L
#define DCX_CLIPSIBLINGS     0x00000010L
#define DCX_PARENTCLIP       0x00000020L
#define DCX_EXCLUDERGN       0x00000040L
#define DCX_INTERSECTRGN     0x00000080L
#define DCX_EXCLUDEUPDATE    0x00000100L
#define DCX_INTERSECTUPDATE  0x00000200L
#define DCX_LOCKWINDOWUPDATE 0x00000400L

#define DCX_VALIDATE         0x00200000L

	 
		HMSDC
		WINAPI
		MSGetWindowDC(
		IN HMSWND hWnd );

	 
		int
		WINAPI
		MSReleaseDC(
		IN HMSWND hWnd,
		IN HMSDC hDC );

	 
		HMSDC
		WINAPI
		MSBeginPaint(
		IN HMSWND hWnd,
		OUT LPMSPAINTSTRUCT lpPaint );

	 
		BOOL
		WINAPI
		MSEndPaint(
		IN HMSWND hWnd,
		IN CONST MSPAINTSTRUCT *lpPaint );

	 
		BOOL
		WINAPI
		MSGetUpdateRect(
		IN HMSWND hWnd,
		OUT LPMSRECT lpRect,
		IN BOOL bErase );

	 
		int
		WINAPI
		MSGetUpdateRgn(
		IN HMSWND hWnd,
		IN HMSRGN hRgn,
		IN BOOL bErase );

	 
		int
		WINAPI
		MSSetWindowRgn(
		IN HMSWND hWnd,
		IN HMSRGN hRgn,
		IN BOOL bRedraw );


	 
		int
		WINAPI
		MSGetWindowRgn(
		IN HMSWND hWnd,
		IN HMSRGN hRgn );

#if(_WIN32_WINNT >= 0x0501)

	 
		int
		WINAPI
		MSGetWindowRgnBox(
		IN HMSWND hWnd,
		OUT LPMSRECT lprc );

#endif /* _WIN32_WINNT >= 0x0501 */

	 
		int
		WINAPI
		MSExcludeUpdateRgn(
		IN HMSDC hDC,
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSInvalidateRect(
		IN HMSWND hWnd,
		IN CONST MSRECT *lpRect,
		IN BOOL bErase );

	 
		BOOL
		WINAPI
		MSValidateRect(
		IN HMSWND hWnd,
		IN CONST MSRECT *lpRect );

	 
		BOOL
		WINAPI
		MSInvalidateRgn(
		IN HMSWND hWnd,
		IN HMSRGN hRgn,
		IN BOOL bErase );

	 
		BOOL
		WINAPI
		MSValidateRgn(
		IN HMSWND hWnd,
		IN HMSRGN hRgn );


	 
		BOOL
		WINAPI
		MSRedrawWindow(
		IN HMSWND hWnd,
		IN CONST MSRECT *lprcUpdate,
		IN HMSRGN hrgnUpdate,
		IN UINT flags );

	/*
	 * RedrawWindow() flags
	 */
#define RDW_INVALIDATE          0x0001
#define RDW_INTERNALPAINT       0x0002
#define RDW_ERASE               0x0004

#define RDW_VALIDATE            0x0008
#define RDW_NOINTERNALPAINT     0x0010
#define RDW_NOERASE             0x0020

#define RDW_NOCHILDREN          0x0040
#define RDW_ALLCHILDREN         0x0080

#define RDW_UPDATENOW           0x0100
#define RDW_ERASENOW            0x0200

#define RDW_FRAME               0x0400
#define RDW_NOFRAME             0x0800


	/*
	 * LockWindowUpdate API
	 */

	 
		BOOL
		WINAPI
		MSLockWindowUpdate(
		IN HMSWND hWndLock );

	 
		BOOL
		WINAPI
		MSScrollWindow(
		IN HMSWND hWnd,
		IN int XAmount,
		IN int YAmount,
		IN CONST MSRECT *lpRect,
		IN CONST MSRECT *lpClipRect );

	 
		BOOL
		WINAPI
		MSScrollDC(
		IN HMSDC hDC,
		IN int dx,
		IN int dy,
		IN CONST MSRECT *lprcScroll,
		IN CONST MSRECT *lprcClip,
		IN HMSRGN hrgnUpdate,
		OUT LPMSRECT lprcUpdate );

	 
		int
		WINAPI
		MSScrollWindowEx(
		IN HMSWND hWnd,
		IN int dx,
		IN int dy,
		IN CONST MSRECT *prcScroll,
		IN CONST MSRECT *prcClip,
		IN HMSRGN hrgnUpdate,
		OUT LPMSRECT prcUpdate,
		IN UINT flags );

#define SW_SCROLLCHILDREN   0x0001  /* Scroll children within *lprcScroll. */
#define SW_INVALIDATE       0x0002  /* Invalidate after scrolling */
#define SW_ERASE            0x0004  /* If SW_INVALIDATE, don't send WM_ERASEBACKGROUND */
#if(WINVER >= 0x0500)
#define SW_SMOOTHSCROLL     0x0010  /* Use smooth scrolling */
#endif /* WINVER >= 0x0500 */

#ifndef NOSCROLL

	 
		int
		WINAPI
		MSSetScrollPos(
		IN HMSWND hWnd,
		IN int nBar,
		IN int nPos,
		IN BOOL bRedraw );

	 
		int
		WINAPI
		MSGetScrollPos(
		IN HMSWND hWnd,
		IN int nBar );

	 
		BOOL
		WINAPI
		MSSetScrollRange(
		IN HMSWND hWnd,
		IN int nBar,
		IN int nMinPos,
		IN int nMaxPos,
		IN BOOL bRedraw );

	 
		BOOL
		WINAPI
		MSGetScrollRange(
		IN HMSWND hWnd,
		IN int nBar,
		OUT LPINT lpMinPos,
		OUT LPINT lpMaxPos );

	 
		BOOL
		WINAPI
		MSShowScrollBar(
		IN HMSWND hWnd,
		IN int wBar,
		IN BOOL bShow );

	 
		BOOL
		WINAPI
		MSEnableScrollBar(
		IN HMSWND hWnd,
		IN UINT wSBflags,
		IN UINT wArrows );


	/*
	 * MSEnableScrollBar() flags
	 */
#define ESB_ENABLE_BOTH     0x0000
#define ESB_DISABLE_BOTH    0x0003

#define ESB_DISABLE_LEFT    0x0001
#define ESB_DISABLE_RIGHT   0x0002

#define ESB_DISABLE_UP      0x0001
#define ESB_DISABLE_DOWN    0x0002

#define ESB_DISABLE_LTUP    ESB_DISABLE_LEFT
#define ESB_DISABLE_RTDN    ESB_DISABLE_RIGHT


#endif  /* !NOSCROLL */

	 
		BOOL
		WINAPI
		MSSetProp(
		IN HMSWND hWnd,
		IN LPCTSTR lpString,
		IN HMSHANDLE hData );


	 
		HMSHANDLE
		WINAPI
		MSGetProp(
		IN HMSWND hWnd,
		IN LPCTSTR lpString );


	 
		HMSHANDLE
		WINAPI
		MSRemoveProp(
		IN HMSWND hWnd,
		IN LPCTSTR lpString );

	 
		int
		WINAPI
		MSEnumPropsEx(
		IN HMSWND hWnd,
		IN MSPROPENUMPROCEXA lpEnumFunc,
		IN LPARAM lParam );

	 
		int
		WINAPI
		MSEnumProps(
		IN HMSWND hWnd,
		IN MSPROPENUMPROCA lpEnumFunc );

	 
		BOOL
		WINAPI
		MSSetWindowText(
		IN HMSWND hWnd,
		IN LPCTSTR lpString );


	 
		int
		WINAPI
		MSGetWindowText(
		IN HMSWND hWnd,
		OUT LPTSTR lpString,
		IN int nMaxCount );


	 
		int
		WINAPI
		MSGetWindowTextLength(
		IN HMSWND hWnd );


	 
		BOOL
		WINAPI
		MSGetClientRect(
		IN HMSWND hWnd,
		OUT LPMSRECT lpRect );

	 
		BOOL
		WINAPI
		MSGetWindowRect(
		IN HMSWND hWnd,
		OUT LPMSRECT lpRect );

	 
		BOOL
		WINAPI
		MSAdjustWindowRect(
		IN OUT LPMSRECT lpRect,
		IN DWORD dwStyle,
		IN BOOL bMenu );

	 
		BOOL
		WINAPI
		MSAdjustWindowRectEx(
		IN OUT LPMSRECT lpRect,
		IN DWORD dwStyle,
		IN BOOL bMenu,
		IN DWORD dwExStyle );


#if(WINVER >= 0x0400)
#define HELPINFO_WINDOW    0x0001
#define HELPINFO_MENUITEM  0x0002
	typedef struct tagMSHELPINFO      /* Structure pointed to by lParam of WM_HELP */
	{
		UINT    cbSize;             /* Size in bytes of this struct  */
		int     iContextType;       /* Either HELPINFO_WINDOW or HELPINFO_MENUITEM */
		int     iCtrlId;            /* Control Id or a Menu item Id. */
		HMSHANDLE  hItemHandle;        /* hWnd of control or hMenu.     */
		DWORD_PTR dwContextId;      /* Context Id associated with this item */
		MSPOINT   MousePos;           /* Mouse Position in screen co-ordinates */
	}  MSHELPINFO, FAR *LPMSHELPINFO;

	 
		BOOL
		WINAPI
		MSSetWindowContextHelpId(
		IN HMSWND,
		IN DWORD );

	 
		DWORD
		WINAPI
		MSGetWindowContextHelpId(
		IN HMSWND );

	 
		BOOL
		WINAPI
		MSSetMenuContextHelpId(
		IN HMSMENU,
		IN DWORD );

	 
		DWORD
		WINAPI
		MSGetMenuContextHelpId(
		IN HMSMENU );

#endif /* WINVER >= 0x0400 */


#ifndef NOMB

	/*
	 * MessageBox() Flags
	 */
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L
#if(WINVER >= 0x0500)
#define MB_CANCELTRYCONTINUE        0x00000006L
#endif /* WINVER >= 0x0500 */


#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L

#if(WINVER >= 0x0400)
#define MB_USERICON                 0x00000080L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONERROR                MB_ICONHAND
#endif /* WINVER >= 0x0400 */

#define MB_ICONINFORMATION          MB_ICONASTERISK
#define MB_ICONSTOP                 MB_ICONHAND

#define MB_DEFBUTTON1               0x00000000L
#define MB_DEFBUTTON2               0x00000100L
#define MB_DEFBUTTON3               0x00000200L
#if(WINVER >= 0x0400)
#define MB_DEFBUTTON4               0x00000300L
#endif /* WINVER >= 0x0400 */

#define MB_APPLMODAL                0x00000000L
#define MB_SYSTEMMODAL              0x00001000L
#define MB_TASKMODAL                0x00002000L
#if(WINVER >= 0x0400)
#define MB_HELP                     0x00004000L // Help Button
#endif /* WINVER >= 0x0400 */

#define MB_NOFOCUS                  0x00008000L
#define MB_SETFOREGROUND            0x00010000L
#define MB_DEFAULT_DESKTOP_ONLY     0x00020000L

#if(WINVER >= 0x0400)
#define MB_TOPMOST                  0x00040000L
#define MB_RIGHT                    0x00080000L
#define MB_RTLREADING               0x00100000L


#endif /* WINVER >= 0x0400 */

#ifdef _WIN32_WINNT
#if (_WIN32_WINNT >= 0x0400)
#define MB_SERVICE_NOTIFICATION          0x00200000L
#else
#define MB_SERVICE_NOTIFICATION          0x00040000L
#endif
#define MB_SERVICE_NOTIFICATION_NT3X     0x00040000L
#endif

#define MB_TYPEMASK                 0x0000000FL
#define MB_ICONMASK                 0x000000F0L
#define MB_DEFMASK                  0x00000F00L
#define MB_MODEMASK                 0x00003000L
#define MB_MISCMASK                 0x0000C000L

	 
		int
		WINAPI
		MSMessageBox(
		IN HMSWND hWnd,
		IN LPCTSTR lpText,
		IN LPCTSTR lpCaption,
		IN UINT uType );

	 
		int
		WINAPI
		MSMessageBoxEx(
		IN HMSWND hWnd,
		IN LPCTSTR lpText,
		IN LPCTSTR lpCaption,
		IN UINT uType,
		IN WORD wLanguageId );

#if(WINVER >= 0x0400)

	typedef void ( CALLBACK *MSMSGBOXCALLBACK )( LPMSHELPINFO lpHelpInfo );

	typedef struct tagMSMSGBOXPARAMSA
	{
		UINT        cbSize;
		HMSWND        hwndOwner;
		HMSINSTANCE   hInstance;
		LPCTSTR      lpszText;
		LPCTSTR      lpszCaption;
		DWORD       dwStyle;
		LPCTSTR      lpszIcon;
		DWORD_PTR   dwContextHelpId;
		MSMSGBOXCALLBACK      lpfnMsgBoxCallback;
		DWORD       dwLanguageId;
	} MSMSGBOXPARAMSA, *PMSMSGBOXPARAMSA, *LPMSMSGBOXPARAMSA;

	typedef MSMSGBOXPARAMSA MSMSGBOXPARAMS;
	typedef PMSMSGBOXPARAMSA PMSMSGBOXPARAMS;
	typedef LPMSMSGBOXPARAMSA LPMSMSGBOXPARAMS;

	 
		int
		WINAPI
		MSMessageBoxIndirect(
		IN CONST LPMSMSGBOXPARAMS );

#endif /* WINVER >= 0x0400 */


	 
		BOOL
		WINAPI
		MSMessageBeep(
		IN UINT uType );

#endif /* !NOMB */

	 
		int
		WINAPI
		MSShowCursor(
		IN BOOL bShow );

	 
		BOOL
		WINAPI
		MSSetCursorPos(
		IN int X,
		IN int Y );

	 
		HMSCURSOR
		WINAPI
		MSSetCursor(
		IN HMSCURSOR hCursor );

	 
		BOOL
		WINAPI
		MSGetCursorPos(
		OUT LPMSPOINT lpPoint );

	 
		BOOL
		WINAPI
		MSClipCursor(
		IN CONST MSRECT *lpRect );

	 
		BOOL
		WINAPI
		MSGetClipCursor(
		OUT LPMSRECT lpRect );

	 
		HMSCURSOR
		WINAPI
		MSGetCursor(
		void );

	 
		BOOL
		WINAPI
		MSCreateCaret(
		IN HMSWND hWnd,
		IN HMSBITMAP hBitmap,
		IN int nWidth,
		IN int nHeight );

	 
		UINT
		WINAPI
		MSGetCaretBlinkTime(
		void );

	 
		BOOL
		WINAPI
		MSSetCaretBlinkTime(
		IN UINT uMSeconds );

	 
		BOOL
		WINAPI
		MSDestroyCaret(
		void );

	 
		BOOL
		WINAPI
		MSHideCaret(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSShowCaret(
		IN HMSWND hWnd );

	 
		BOOL
		WINAPI
		MSSetCaretPos(
		IN int X,
		IN int Y );

	 
		BOOL
		WINAPI
		MSGetCaretPos(
		OUT LPMSPOINT lpPoint );

	 
		BOOL
		WINAPI
		MSClientToScreen(
		IN HMSWND hWnd,
		IN OUT LPMSPOINT lpPoint );

	 
		BOOL
		WINAPI
		MSScreenToClient(
		IN HMSWND hWnd,
		IN OUT LPMSPOINT lpPoint );

	 
		int
		WINAPI
		MSMapWindowPoints(
		IN HMSWND hWndFrom,
		IN HMSWND hWndTo,
		IN OUT LPMSPOINT lpPoints,
		IN UINT cPoints );

	 
		HMSWND
		WINAPI
		MSWindowFromPoint(
		IN MSPOINT Point );

	 
		HMSWND
		WINAPI
		MSChildWindowFromPoint(
		IN HMSWND hWndParent,
		IN MSPOINT Point );

#if(WINVER >= 0x0400)
#define CWP_ALL             0x0000
#define CWP_SKIPINVISIBLE   0x0001
#define CWP_SKIPDISABLED    0x0002
#define CWP_SKIPTRANSPARENT 0x0004

	  HMSWND    WINAPI MSChildWindowFromPointEx( IN HMSWND, IN MSPOINT, IN UINT );
#endif /* WINVER >= 0x0400 */

#ifndef NOCOLOR

	/*
	 * Color Types
	 */
#define CTLCOLOR_MSGBOX         0
#define CTLCOLOR_EDIT           1
#define CTLCOLOR_LISTBOX        2
#define CTLCOLOR_BTN            3
#define CTLCOLOR_DLG            4
#define CTLCOLOR_SCROLLBAR      5
#define CTLCOLOR_STATIC         6
#define CTLCOLOR_MAX            7

#define COLOR_SCROLLBAR         0
#define COLOR_BACKGROUND        1
#define COLOR_ACTIVECAPTION     2
#define COLOR_INACTIVECAPTION   3
#define COLOR_MENU              4
#define COLOR_WINDOW            5
#define COLOR_WINDOWFRAME       6
#define COLOR_MENUTEXT          7
#define COLOR_WINDOWTEXT        8
#define COLOR_CAPTIONTEXT       9
#define COLOR_ACTIVEBORDER      10
#define COLOR_INACTIVEBORDER    11
#define COLOR_APPWORKSPACE      12
#define COLOR_HIGHLIGHT         13
#define COLOR_HIGHLIGHTTEXT     14
#define COLOR_BTNFACE           15
#define COLOR_BTNSHADOW         16
#define COLOR_GRAYTEXT          17
#define COLOR_BTNTEXT           18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT      20

#if(WINVER >= 0x0400)
#define COLOR_3DDKSHADOW        21
#define COLOR_3DLIGHT           22
#define COLOR_INFOTEXT          23
#define COLOR_INFOBK            24
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#define COLOR_HOTLIGHT          26
#define COLOR_GRADIENTACTIVECAPTION 27
#define COLOR_GRADIENTINACTIVECAPTION 28
#if(WINVER >= 0x0501)
#define COLOR_MENUHILIGHT       29
#define COLOR_MENUBAR           30
#endif /* WINVER >= 0x0501 */
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)
#define COLOR_DESKTOP           COLOR_BACKGROUND
#define COLOR_3DFACE            COLOR_BTNFACE
#define COLOR_3DSHADOW          COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT
#endif /* WINVER >= 0x0400 */


	 
		DWORD
		WINAPI
		MSGetSysColor(
		IN int nIndex );

#if(WINVER >= 0x0400)
	 
		HMSBRUSH
		WINAPI
		MSGetSysColorBrush(
		IN int nIndex );


#endif /* WINVER >= 0x0400 */

	 
		BOOL
		WINAPI
		MSSetSysColors(
		IN int cElements,
		IN CONST INT * lpaElements,
		IN CONST COLORREF * lpaRgbValues );

#endif /* !NOCOLOR */

	 
		BOOL
		WINAPI
		MSDrawFocusRect(
		IN HMSDC hDC,
		IN CONST MSRECT * lprc );

	 
		int
		WINAPI
		MSFillRect(
		IN HMSDC hDC,
		IN CONST MSRECT *lprc,
		IN HMSBRUSH hbr );

	 
		int
		WINAPI
		MSFrameRect(
		IN HMSDC hDC,
		IN CONST MSRECT *lprc,
		IN HMSBRUSH hbr );

	 
		BOOL
		WINAPI
		MSInvertRect(
		IN HMSDC hDC,
		IN CONST MSRECT *lprc );

	 
		BOOL
		WINAPI
		MSSetRect(
		OUT LPMSRECT lprc,
		IN int xLeft,
		IN int yTop,
		IN int xRight,
		IN int yBottom );

	 
		BOOL
		WINAPI
		MSSetRectEmpty(
		OUT LPMSRECT lprc );

	 
		BOOL
		WINAPI
		MSCopyRect(
		OUT LPMSRECT lprcDst,
		IN CONST MSRECT *lprcSrc );

	 
		BOOL
		WINAPI
		MSInflateRect(
		IN OUT LPMSRECT lprc,
		IN int dx,
		IN int dy );

	 
		BOOL
		WINAPI
		MSIntersectRect(
		OUT LPMSRECT lprcDst,
		IN CONST MSRECT *lprcSrc1,
		IN CONST MSRECT *lprcSrc2 );

	 
		BOOL
		WINAPI
		MSUnionRect(
		OUT LPMSRECT lprcDst,
		IN CONST MSRECT *lprcSrc1,
		IN CONST MSRECT *lprcSrc2 );

	 
		BOOL
		WINAPI
		MSSubtractRect(
		OUT LPMSRECT lprcDst,
		IN CONST MSRECT *lprcSrc1,
		IN CONST MSRECT *lprcSrc2 );

	 
		BOOL
		WINAPI
		MSOffsetRect(
		IN OUT LPMSRECT lprc,
		IN int dx,
		IN int dy );

	 
		BOOL
		WINAPI
		MSIsRectEmpty(
		IN CONST MSRECT *lprc );

	 
		BOOL
		WINAPI
		MSEqualRect(
		IN CONST MSRECT *lprc1,
		IN CONST MSRECT *lprc2 );

	 
		BOOL
		WINAPI
		MSPtInRect(
		IN CONST MSRECT *lprc,
		IN MSPOINT pt );

#ifndef NOWINOFFSETS

	 
		WORD
		WINAPI
		MSGetWindowWord(
		IN HMSWND hWnd,
		IN int nIndex );

	 
		WORD
		WINAPI
		MSSetWindowWord(
		IN HMSWND hWnd,
		IN int nIndex,
		IN WORD wNewWord );

	 
		LONG
		WINAPI
		MSGetWindowLong(
		IN HMSWND hWnd,
		IN int nIndex );


	 
		LONG
		WINAPI
		MSSetWindowLong(
		IN HMSWND hWnd,
		IN int nIndex,
		IN LONG dwNewLong );

#ifdef _WIN64

	 
		LONG_PTR
		WINAPI
		MSGetWindowLongPtr(
		HMSWND hWnd,
		int nIndex);


	 
		LONG_PTR
		WINAPI
		MSSetWindowLongPtr(
		HMSWND hWnd,
		int nIndex,
		LONG_PTR dwNewLong);


#else  /* _WIN64 */

#define MSGetWindowLongPtrA   MSGetWindowLongA
#define MSGetWindowLongPtr  MSGetWindowLongPtrA

#define MSSetWindowLongPtrA   MSSetWindowLongA
#define MSSetWindowLongPtr  MSSetWindowLongPtrA

#endif /* _WIN64 */

	 
		WORD
		WINAPI
		MSGetClassWord(
		IN HMSWND hWnd,
		IN int nIndex );

	 
		WORD
		WINAPI
		MSSetClassWord(
		IN HMSWND hWnd,
		IN int nIndex,
		IN WORD wNewWord );

	 
		DWORD
		WINAPI
		MSGetClassLong(
		IN HMSWND hWnd,
		IN int nIndex );

	 
		DWORD
		WINAPI
		MSSetClassLong(
		IN HMSWND hWnd,
		IN int nIndex,
		IN LONG dwNewLong );


#ifdef _WIN64

	 
		ULONG_PTR
		WINAPI
		MSGetClassLongPtr(
		IN HMSWND hWnd,
		IN int nIndex);


	 
		ULONG_PTR
		WINAPI
		MSSetClassLongPtr(
		IN HMSWND hWnd,
		IN int nIndex,
		IN LONG_PTR dwNewLong);


#else  /* _WIN64 */

#define MSGetClassLongPtrA    MSGetClassLongA
#define MSGetClassLongPtr  MSGetClassLongPtrA

#define MSSetClassLongPtrA    MSSetClassLongA
#define MSSetClassLongPtr  MSSetClassLongPtrA

#endif /* _WIN64 */

#endif /* !NOWINOFFSETS */

#if(WINVER >= 0x0500)
	 
		BOOL
		WINAPI
		MSGetProcessDefaultLayout(
		OUT DWORD *pdwDefaultLayout );

	 
		BOOL
		WINAPI
		MSSetProcessDefaultLayout(
		IN DWORD dwDefaultLayout );
#endif /* WINVER >= 0x0500 */

	 
		HMSWND
		WINAPI
		MSGetDesktopWindow(
		void );


	 
		HMSWND
		WINAPI
		MSGetParent(
		IN HMSWND hWnd );

	 
		HMSWND
		WINAPI
		MSSetParent(
		IN HMSWND hWndChild,
		IN HMSWND hWndNewParent );

	 
		BOOL
		WINAPI
		MSEnumChildWindows(
		IN HMSWND hWndParent,
		IN MSWNDENUMPROC lpEnumFunc,
		IN LPARAM lParam );

	 
		HMSWND
		WINAPI
		MSFindWindow(
		IN LPCTSTR lpClassName,
		IN LPCTSTR lpWindowName );


#if(WINVER >= 0x0400)
	  HMSWND    WINAPI MSFindWindowEx( IN HMSWND, IN HMSWND, IN LPCTSTR, IN LPCTSTR );
#endif /* WINVER >= 0x0400 */


	 
		BOOL
		WINAPI
		MSEnumWindows(
		IN MSWNDENUMPROC lpEnumFunc,
		IN LPARAM lParam );

	 
		BOOL
		WINAPI
		MSEnumThreadWindows(
		IN DWORD dwThreadId,
		IN MSWNDENUMPROC lpfn,
		IN LPARAM lParam );

#define MSEnumTaskWindows(hTask, lpfn, lParam) MSEnumThreadWindows(HandleToUlong(hTask), lpfn, lParam)

	 
		int
		WINAPI
		MSGetClassName(
		IN HMSWND hWnd,
		OUT LPTSTR lpClassName,
		IN int nMaxCount );


	 
		HMSWND
		WINAPI
		MSGetTopWindow(
		IN HMSWND hWnd );

#define MSGetNextWindow(hWnd, wCmd) MSGetWindow(hWnd, wCmd)
#define MSGetSysModalWindow() (NULL)
#define MSSetSysModalWindow(hWnd) (NULL)

	 
		DWORD
		WINAPI
		MSGetWindowThreadProcessId(
		IN HMSWND hWnd,
		OUT LPDWORD lpdwProcessId );

#if(_WIN32_WINNT >= 0x0501)
	 
		BOOL
		WINAPI
		MSIsGUIThread(
		BOOL bConvert );

#endif /* _WIN32_WINNT >= 0x0501 */

#define MSGetWindowTask(hWnd) \
	( ( HMSHANDLE )( DWORD_PTR )MSGetWindowThreadProcessId( hWnd, NULL ) )

	 
		HMSWND
		WINAPI
		MSGetLastActivePopup(
		IN HMSWND hWnd );

	/*
	 * MSGetWindow() Constants
	 */
#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif

	 
		HMSWND
		WINAPI
		MSGetWindow(
		IN HMSWND hWnd,
		IN UINT uCmd );



#ifndef NOWH

#ifdef STRICT

	 
		HMSHOOK
		WINAPI
		MSSetWindowsHook(
		IN int nFilterType,
		IN MSHOOKPROC pfnFilterProc );


#else /* !STRICT */

	 
		MSHOOKPROC
		WINAPI
		MSSetWindowsHook(
		IN int nFilterType,
		IN MSHOOKPROC pfnFilterProc);

#endif /* !STRICT */

	 
		BOOL
		WINAPI
		MSUnhookWindowsHook(
		IN int nCode,
		IN MSHOOKPROC pfnFilterProc );

	 
		HMSHOOK
		WINAPI
		MSSetWindowsHookEx(
		IN int idHook,
		IN MSHOOKPROC lpfn,
		IN HMSINSTANCE hmod,
		IN DWORD dwThreadId );


	 
		BOOL
		WINAPI
		MSUnhookWindowsHookEx(
		IN HMSHOOK hhk );

	 
		LRESULT
		WINAPI
		MSCallNextHookEx(
		IN HMSHOOK hhk,
		IN int nCode,
		IN WPARAM wParam,
		IN LPARAM lParam );

	/*
	 * Macros for source-level compatibility with old functions.
	 */
#ifdef STRICT
#define MSDefHookProc(nCode, wParam, lParam, phhk)\
	MSCallNextHookEx( *phhk, nCode, wParam, lParam )
#else
#define MSDefHookProc(nCode, wParam, lParam, phhk)\
	MSCallNextHookEx((HMSHOOK)*phhk, nCode, wParam, lParam)
#endif /* STRICT */
#endif /* !NOWH */

#ifndef NOMENUS


	/* ;win40  -- A lot of MF_* flags have been renamed as MFT_* and MFS_* flags */
	/*
	 * Menu flags for Add/Check/MSEnableMenuItem()
	 */
#define MF_INSERT           0x00000000L
#define MF_CHANGE           0x00000080L
#define MF_APPEND           0x00000100L
#define MF_DELETE           0x00000200L
#define MF_REMOVE           0x00001000L

#define MF_BYCOMMAND        0x00000000L
#define MF_BYPOSITION       0x00000400L

#define MF_SEPARATOR        0x00000800L

#define MF_ENABLED          0x00000000L
#define MF_GRAYED           0x00000001L
#define MF_DISABLED         0x00000002L

#define MF_UNCHECKED        0x00000000L
#define MF_CHECKED          0x00000008L
#define MF_USECHECKBITMAPS  0x00000200L

#define MF_STRING           0x00000000L
#define MF_BITMAP           0x00000004L
#define MF_OWNERDRAW        0x00000100L

#define MF_POPUP            0x00000010L
#define MF_MENUBARBREAK     0x00000020L
#define MF_MENUBREAK        0x00000040L

#define MF_UNHILITE         0x00000000L
#define MF_HILITE           0x00000080L

#if(WINVER >= 0x0400)
#define MF_DEFAULT          0x00001000L
#endif /* WINVER >= 0x0400 */
#define MF_SYSMENU          0x00002000L
#define MF_HELP             0x00004000L
#if(WINVER >= 0x0400)
#define MF_RIGHTJUSTIFY     0x00004000L
#endif /* WINVER >= 0x0400 */

#define MF_MOUSESELECT      0x00008000L
#if(WINVER >= 0x0400)
#define MF_END              0x00000080L  /* Obsolete -- only used by old RES files */
#endif /* WINVER >= 0x0400 */


#if(WINVER >= 0x0400)
#define MFT_STRING          MF_STRING
#define MFT_BITMAP          MF_BITMAP
#define MFT_MENUBARBREAK    MF_MENUBARBREAK
#define MFT_MENUBREAK       MF_MENUBREAK
#define MFT_OWNERDRAW       MF_OWNERDRAW
#define MFT_RADIOCHECK      0x00000200L
#define MFT_SEPARATOR       MF_SEPARATOR
#define MFT_RIGHTORDER      0x00002000L
#define MFT_RIGHTJUSTIFY    MF_RIGHTJUSTIFY

	/* Menu flags for Add/Check/MSEnableMenuItem() */
#define MFS_GRAYED          0x00000003L
#define MFS_DISABLED        MFS_GRAYED
#define MFS_CHECKED         MF_CHECKED
#define MFS_HILITE          MF_HILITE
#define MFS_ENABLED         MF_ENABLED
#define MFS_UNCHECKED       MF_UNCHECKED
#define MFS_UNHILITE        MF_UNHILITE
#define MFS_DEFAULT         MF_DEFAULT
#endif /* WINVER >= 0x0400 */


#if(WINVER >= 0x0400)

	 
		BOOL
		WINAPI
		MSCheckMenuRadioItem(
		IN HMSMENU,
		IN UINT,
		IN UINT,
		IN UINT,
		IN UINT );
#endif /* WINVER >= 0x0400 */

	/*
	 * Menu item resource format
	 */
	typedef struct {
		WORD versionNumber;
		WORD offset;
	} MSMENUITEMTEMPLATEHEADER, *PMSMENUITEMTEMPLATEHEADER;

	typedef struct {        // version 0
		WORD mtOption;
		WORD mtID;
		WCHAR mtString[ 1 ];
	} MSMENUITEMTEMPLATE, *PMSMENUITEMTEMPLATE;
#define MF_END             0x00000080L

#endif /* !NOMENUS */

#ifndef NOSYSCOMMANDS

	/*
	 * System Menu Command Values
	 */
#define SC_SIZE         0xF000
#define SC_MOVE         0xF010
#define SC_MINIMIZE     0xF020
#define SC_MAXIMIZE     0xF030
#define SC_NEXTWINDOW   0xF040
#define SC_PREVWINDOW   0xF050
#define SC_CLOSE        0xF060
#define SC_VSCROLL      0xF070
#define SC_HSCROLL      0xF080
#define SC_MOUSEMENU    0xF090
#define SC_KEYMENU      0xF100
#define SC_ARRANGE      0xF110
#define SC_RESTORE      0xF120
#define SC_TASKLIST     0xF130
#define SC_SCREENSAVE   0xF140
#define SC_HOTKEY       0xF150
#if(WINVER >= 0x0400)
#define SC_DEFAULT      0xF160
#define SC_MONITORPOWER 0xF170
#define SC_CONTEXTHELP  0xF180
#define SC_SEPARATOR    0xF00F
#endif /* WINVER >= 0x0400 */

	/*
	 * Obsolete names
	 */
#define SC_ICON         SC_MINIMIZE
#define SC_ZOOM         SC_MAXIMIZE

#endif /* !NOSYSCOMMANDS */

	/*
	 * Resource MSLoading Routines
	 */

	 
		HMSBITMAP
		WINAPI
		MSLoadBitmap(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpBitmapName );

	 
		HMSCURSOR
		WINAPI
		MSLoadCursor(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpCursorName );


	 
		HMSCURSOR
		WINAPI
		MSLoadCursorFromFile(
		IN LPCTSTR lpFileName );


	 
		HMSCURSOR
		WINAPI
		MSCreateCursor(
		IN HMSINSTANCE hInst,
		IN int xHotSpot,
		IN int yHotSpot,
		IN int nWidth,
		IN int nHeight,
		IN CONST void *pvANDPlane,
		IN CONST void *pvXORPlane );

	 
		BOOL
		WINAPI
		MSDestroyCursor(
		IN HMSCURSOR hCursor );

#ifndef _MAC
#define MSCopyCursor(pcur) ((HMSCURSOR)MSCopyIcon((HMSICON)(pcur)))
#else
	 
		HMSCURSOR
		WINAPI
		MSCopyCursor(
		IN HMSCURSOR hCursor);
#endif

	/*
	 * Standard Cursor IDs
	 */
#define IDC_ARROW           MAKEINTRESOURCE(32512)
#define IDC_IBEAM           MAKEINTRESOURCE(32513)
#define IDC_WAIT            MAKEINTRESOURCE(32514)
#define IDC_CROSS           MAKEINTRESOURCE(32515)
#define IDC_UPARROW         MAKEINTRESOURCE(32516)
#define IDC_SIZE            MAKEINTRESOURCE(32640)  /* OBSOLETE: use IDC_SIZEALL */
#define IDC_ICON            MAKEINTRESOURCE(32641)  /* OBSOLETE: use IDC_ARROW */
#define IDC_SIZENWSE        MAKEINTRESOURCE(32642)
#define IDC_SIZENESW        MAKEINTRESOURCE(32643)
#define IDC_SIZEWE          MAKEINTRESOURCE(32644)
#define IDC_SIZENS          MAKEINTRESOURCE(32645)
#define IDC_SIZEALL         MAKEINTRESOURCE(32646)
#define IDC_NO              MAKEINTRESOURCE(32648) /*not in win3.1 */
#if(WINVER >= 0x0500)
#define IDC_HAND            MAKEINTRESOURCE(32649)
#endif /* WINVER >= 0x0500 */
#define IDC_APPSTARTING     MAKEINTRESOURCE(32650) /*not in win3.1 */
#if(WINVER >= 0x0400)
#define IDC_HELP            MAKEINTRESOURCE(32651)
#endif /* WINVER >= 0x0400 */

	 
		BOOL
		WINAPI
		MSSetSystemCursor(
		IN HMSCURSOR hcur,
		IN DWORD   id );

	typedef struct _MSICONINFO {
		BOOL    fIcon;
		DWORD   xHotspot;
		DWORD   yHotspot;
		HMSBITMAP hbmMask;
		HMSBITMAP hbmColor;
	} MSICONINFO;
	typedef MSICONINFO *PMSICONINFO;

	 
		HMSICON
		WINAPI
		MSLoadIcon(
		IN HMSINSTANCE hInstance,
		IN LPCTSTR lpIconName );


	 
		HMSICON
		WINAPI
		MSCreateIcon(
		IN HMSINSTANCE hInstance,
		IN int nWidth,
		IN int nHeight,
		IN BYTE cPlanes,
		IN BYTE cBitsPixel,
		IN CONST BYTE *lpbANDbits,
		IN CONST BYTE *lpbXORbits );

	 
		BOOL
		WINAPI
		MSDestroyIcon(
		IN HMSICON hIcon );

	 
		int
		WINAPI
		MSLookupIconIdFromDirectory(
		IN PBYTE presbits,
		IN BOOL fIcon );

#if(WINVER >= 0x0400)
	 
		int
		WINAPI
		MSLookupIconIdFromDirectoryEx(
		IN PBYTE presbits,
		IN BOOL  fIcon,
		IN int   cxDesired,
		IN int   cyDesired,
		IN UINT  Flags );
#endif /* WINVER >= 0x0400 */

	 
		HMSICON
		WINAPI
		MSCreateIconFromResource(
		IN PBYTE presbits,
		IN DWORD dwResSize,
		IN BOOL fIcon,
		IN DWORD dwVer );

#if(WINVER >= 0x0400)
	 
		HMSICON
		WINAPI
		MSCreateIconFromResourceEx(
		IN PBYTE presbits,
		IN DWORD dwResSize,
		IN BOOL  fIcon,
		IN DWORD dwVer,
		IN int   cxDesired,
		IN int   cyDesired,
		IN UINT  Flags );

	/* Icon/Cursor header */
	typedef struct tagMSCURSORSHAPE
	{
		int     xHotSpot;
		int     yHotSpot;
		int     cx;
		int     cy;
		int     cbWidth;
		BYTE    Planes;
		BYTE    BitsPixel;
	} MSCURSORSHAPE, FAR *LPMSCURSORSHAPE;
#endif /* WINVER >= 0x0400 */

#define IMAGE_BITMAP        0
#define IMAGE_ICON          1
#define IMAGE_CURSOR        2
#if(WINVER >= 0x0400)
#define IMAGE_ENHMETAFILE   3

#define LR_DEFAULTCOLOR     0x0000
#define LR_MONOCHROME       0x0001
#define LR_COLOR            0x0002
#define LR_COPYRETURNORG    0x0004
#define LR_COPYDELETEORG    0x0008
#define LR_LOADFROMFILE     0x0010
#define LR_LOADTRANSPARENT  0x0020
#define LR_DEFAULTSIZE      0x0040
#define LR_VGACOLOR         0x0080
#define LR_LOADMAP3DCOLORS  0x1000
#define LR_CREATEDIBSECTION 0x2000
#define LR_COPYFROMRESOURCE 0x4000
#define LR_SHARED           0x8000

	 
		HMSHANDLE
		WINAPI
		MSLoadImage(
		IN HMSINSTANCE,
		IN LPCTSTR,
		IN UINT,
		IN int,
		IN int,
		IN UINT );


	 
		HMSHANDLE
		WINAPI
		MSCopyImage(
		IN HMSHANDLE,
		IN UINT,
		IN int,
		IN int,
		IN UINT );

#define DI_MASK         0x0001
#define DI_IMAGE        0x0002
#define DI_NORMAL       0x0003
#define DI_COMPAT       0x0004
#define DI_DEFAULTSIZE  0x0008
#if(_WIN32_WINNT >= 0x0501)
#define DI_NOMIRROR     0x0010
#endif /* _WIN32_WINNT >= 0x0501 */

	  BOOL WINAPI MSDrawIconEx( IN HMSDC hdc, IN int xLeft, IN int yTop,
		IN HMSICON hIcon, IN int cxWidth, IN int cyWidth,
		IN UINT istepIfAniCur, IN HMSBRUSH hbrFlickerFreeDraw, IN UINT diFlags );
#endif /* WINVER >= 0x0400 */

	 
		HMSICON
		WINAPI
		MSCreateIconIndirect(
		IN PMSICONINFO piconinfo );

	 
		HMSICON
		WINAPI
		MSCopyIcon(
		IN HMSICON hIcon );

	 
		BOOL
		WINAPI
		MSGetIconInfo(
		IN HMSICON hIcon,
		OUT PMSICONINFO piconinfo );

#if(WINVER >= 0x0400)
#define RES_ICON    1
#define RES_CURSOR  2
#endif /* WINVER >= 0x0400 */

#ifdef OEMRESOURCE


	/*
	 * OEM Resource Ordinal Numbers
	 */
#define OBM_CLOSE           32754
#define OBM_UPARROW         32753
#define OBM_DNARROW         32752
#define OBM_RGARROW         32751
#define OBM_LFARROW         32750
#define OBM_REDUCE          32749
#define OBM_ZOOM            32748
#define OBM_RESTORE         32747
#define OBM_REDUCED         32746
#define OBM_ZOOMD           32745
#define OBM_RESTORED        32744
#define OBM_UPARROWD        32743
#define OBM_DNARROWD        32742
#define OBM_RGARROWD        32741
#define OBM_LFARROWD        32740
#define OBM_MNARROW         32739
#define OBM_COMBO           32738
#define OBM_UPARROWI        32737
#define OBM_DNARROWI        32736
#define OBM_RGARROWI        32735
#define OBM_LFARROWI        32734

#define OBM_OLD_CLOSE       32767
#define OBM_SIZE            32766
#define OBM_OLD_UPARROW     32765
#define OBM_OLD_DNARROW     32764
#define OBM_OLD_RGARROW     32763
#define OBM_OLD_LFARROW     32762
#define OBM_BTSIZE          32761
#define OBM_CHECK           32760
#define OBM_CHECKBOXES      32759
#define OBM_BTNCORNERS      32758
#define OBM_OLD_REDUCE      32757
#define OBM_OLD_ZOOM        32756
#define OBM_OLD_RESTORE     32755


#define OCR_NORMAL          32512
#define OCR_IBEAM           32513
#define OCR_WAIT            32514
#define OCR_CROSS           32515
#define OCR_UP              32516
#define OCR_SIZE            32640   /* OBSOLETE: use OCR_SIZEALL */
#define OCR_ICON            32641   /* OBSOLETE: use OCR_NORMAL */
#define OCR_SIZENWSE        32642
#define OCR_SIZENESW        32643
#define OCR_SIZEWE          32644
#define OCR_SIZENS          32645
#define OCR_SIZEALL         32646
#define OCR_ICOCUR          32647   /* OBSOLETE: use OIC_WINLOGO */
#define OCR_NO              32648
#if(WINVER >= 0x0500)
#define OCR_HAND            32649
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0400)
#define OCR_APPSTARTING     32650
#endif /* WINVER >= 0x0400 */


#define OIC_SAMPLE          32512
#define OIC_HAND            32513
#define OIC_QUES            32514
#define OIC_BANG            32515
#define OIC_NOTE            32516
#if(WINVER >= 0x0400)
#define OIC_WINLOGO         32517
#define OIC_WARNING         OIC_BANG
#define OIC_ERROR           OIC_HAND
#define OIC_INFORMATION     OIC_NOTE
#endif /* WINVER >= 0x0400 */



#endif /* OEMRESOURCE */

#define ORD_LANGDRIVER    1     /* The ordinal number for the entry point of
	 ** language drivers.
	 */

#ifndef NOICONS

	/*
	 * Standard Icon IDs
	 */
#ifdef RC_INVOKED
#define IDI_APPLICATION     32512
#define IDI_HAND            32513
#define IDI_QUESTION        32514
#define IDI_EXCLAMATION     32515
#define IDI_ASTERISK        32516
#if(WINVER >= 0x0400)
#define IDI_WINLOGO         32517
#endif /* WINVER >= 0x0400 */
#else
#define IDI_APPLICATION     MAKEINTRESOURCE(32512)
#define IDI_HAND            MAKEINTRESOURCE(32513)
#define IDI_QUESTION        MAKEINTRESOURCE(32514)
#define IDI_EXCLAMATION     MAKEINTRESOURCE(32515)
#define IDI_ASTERISK        MAKEINTRESOURCE(32516)
#if(WINVER >= 0x0400)
#define IDI_WINLOGO         MAKEINTRESOURCE(32517)
#endif /* WINVER >= 0x0400 */
#endif /* RC_INVOKED */

#if(WINVER >= 0x0400)
#define IDI_WARNING     IDI_EXCLAMATION
#define IDI_ERROR       IDI_HAND
#define IDI_INFORMATION IDI_ASTERISK
#endif /* WINVER >= 0x0400 */


#endif /* !NOICONS */

	 
		int
		WINAPI
		MSLoadString(
		IN HMSINSTANCE hInstance,
		IN UINT uID,
		OUT LPTSTR lpBuffer,
		IN int nBufferMax );


	/*
	 * Dialog Box Command IDs
	 */
#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7
#if(WINVER >= 0x0400)
#define IDCLOSE         8
#define IDHELP          9
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#define IDTRYAGAIN      10
#define IDCONTINUE      11
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0501)
#ifndef IDTIMEOUT
#define IDTIMEOUT 32000
#endif
#endif /* WINVER >= 0x0501 */


#ifndef NOCTLMGR

	/*
	 * Control Manager Structures and Definitions
	 */

#ifndef NOWINSTYLES


	/*
	 * Edit Control Styles
	 */
#define ES_LEFT             0x0000L
#define ES_CENTER           0x0001L
#define ES_RIGHT            0x0002L
#define ES_MULTILINE        0x0004L
#define ES_UPPERCASE        0x0008L
#define ES_LOWERCASE        0x0010L
#define ES_PASSWORD         0x0020L
#define ES_AUTOVSCROLL      0x0040L
#define ES_AUTOHSCROLL      0x0080L
#define ES_NOHIDESEL        0x0100L
#define ES_OEMCONVERT       0x0400L
#define ES_READONLY         0x0800L
#define ES_WANTRETURN       0x1000L
#if(WINVER >= 0x0400)
#define ES_NUMBER           0x2000L
#endif /* WINVER >= 0x0400 */


#endif /* !NOWINSTYLES */

	/*
	 * Edit Control Notification Codes
	 */
#define EN_SETFOCUS         0x0100
#define EN_KILLFOCUS        0x0200
#define EN_CHANGE           0x0300
#define EN_UPDATE           0x0400
#define EN_ERRSPACE         0x0500
#define EN_MAXTEXT          0x0501
#define EN_HSCROLL          0x0601
#define EN_VSCROLL          0x0602

#if(_WIN32_WINNT >= 0x0500)
#define EN_ALIGN_LTR_EC     0x0700
#define EN_ALIGN_RTL_EC     0x0701
#endif /* _WIN32_WINNT >= 0x0500 */

#if(WINVER >= 0x0400)
	/* Edit control EM_SETMARGIN parameters */
#define EC_LEFTMARGIN       0x0001
#define EC_RIGHTMARGIN      0x0002
#define EC_USEFONTINFO      0xffff
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
	/* wParam of EM_GET/SETIMESTATUS  */
#define EMSIS_COMPOSITIONSTRING        0x0001

	/* lParam for EMSIS_COMPOSITIONSTRING  */
#define EIMES_GETCOMPSTRATONCE         0x0001
#define EIMES_CANCELCOMPSTRINFOCUS     0x0002
#define EIMES_COMPLETECOMPSTRKILLFOCUS 0x0004
#endif /* WINVER >= 0x0500 */

#ifndef NOWINMESSAGES


	/*
	 * Edit Control MSMessages
	 */
#define EM_GETSEL               0x00B0
#define EM_SETSEL               0x00B1
#define EM_GETRECT              0x00B2
#define EM_SETRECT              0x00B3
#define EM_SETRECTNP            0x00B4
#define EM_SCROLL               0x00B5
#define EM_LINESCROLL           0x00B6
#define EM_SCROLLCARET          0x00B7
#define EM_GETMODIFY            0x00B8
#define EM_SETMODIFY            0x00B9
#define EM_GETLINECOUNT         0x00BA
#define EM_LINEINDEX            0x00BB
#define EM_SETHANDLE            0x00BC
#define EM_GETHANDLE            0x00BD
#define EM_GETTHUMB             0x00BE
#define EM_LINELENGTH           0x00C1
#define EM_REPLACESEL           0x00C2
#define EM_GETLINE              0x00C4
#define EM_LIMITTEXT            0x00C5
#define EM_CANUNDO              0x00C6
#define EM_UNDO                 0x00C7
#define EM_FMTLINES             0x00C8
#define EM_LINEFROMCHAR         0x00C9
#define EM_SETTABSTOPS          0x00CB
#define EM_SETPASSWORDCHAR      0x00CC
#define EM_EMPTYUNDOBUFFER      0x00CD
#define EM_GETFIRSTVISIBLELINE  0x00CE
#define EM_SETREADONLY          0x00CF
#define EM_SETWORDBREAKPROC     0x00D0
#define EM_GETWORDBREAKPROC     0x00D1
#define EM_GETPASSWORDCHAR      0x00D2
#if(WINVER >= 0x0400)
#define EM_SETMARGINS           0x00D3
#define EM_GETMARGINS           0x00D4
#define EM_SETLIMITTEXT         EM_LIMITTEXT   /* ;win40 Name change */
#define EM_GETLIMITTEXT         0x00D5
#define EM_POSFROMCHAR          0x00D6
#define EM_CHARFROMPOS          0x00D7
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#define EM_SETIMESTATUS         0x00D8
#define EM_GETIMESTATUS         0x00D9
#endif /* WINVER >= 0x0500 */


#endif /* !NOWINMESSAGES */

	/*
	 * EDITWORDBREAKPROC code values
	 */
#define WB_LEFT            0
#define WB_RIGHT           1
#define WB_ISDELIMITER     2


	/*
	 * Button Control Styles
	 */
#define BS_PUSHBUTTON       0x00000000L
#define BS_DEFPUSHBUTTON    0x00000001L
#define BS_CHECKBOX         0x00000002L
#define BS_AUTOCHECKBOX     0x00000003L
#define BS_RADIOBUTTON      0x00000004L
#define BS_3STATE           0x00000005L
#define BS_AUTO3STATE       0x00000006L
#define BS_GROUPBOX         0x00000007L
#define BS_USERBUTTON       0x00000008L
#define BS_AUTORADIOBUTTON  0x00000009L
#define BS_OWNERDRAW        0x0000000BL
#define BS_LEFTTEXT         0x00000020L
#if(WINVER >= 0x0400)
#define BS_TEXT             0x00000000L
#define BS_ICON             0x00000040L
#define BS_BITMAP           0x00000080L
#define BS_LEFT             0x00000100L
#define BS_RIGHT            0x00000200L
#define BS_CENTER           0x00000300L
#define BS_TOP              0x00000400L
#define BS_BOTTOM           0x00000800L
#define BS_VCENTER          0x00000C00L
#define BS_PUSHLIKE         0x00001000L
#define BS_MULTILINE        0x00002000L
#define BS_NOTIFY           0x00004000L
#define BS_FLAT             0x00008000L
#define BS_RIGHTBUTTON      BS_LEFTTEXT
#endif /* WINVER >= 0x0400 */

	/*
	 * User Button Notification Codes
	 */
#define BN_CLICKED          0
#define BN_PAINT            1
#define BN_HILITE           2
#define BN_UNHILITE         3
#define BN_DISABLE          4
#define BN_DOUBLECLICKED    5
#if(WINVER >= 0x0400)
#define BN_PUSHED           BN_HILITE
#define BN_UNPUSHED         BN_UNHILITE
#define BN_DBLCLK           BN_DOUBLECLICKED
#define BN_SETFOCUS         6
#define BN_KILLFOCUS        7
#endif /* WINVER >= 0x0400 */

	/*
	 * Button Control MSMessages
	 */
#define BM_GETCHECK        0x00F0
#define BM_SETCHECK        0x00F1
#define BM_GETSTATE        0x00F2
#define BM_SETSTATE        0x00F3
#define BM_SETSTYLE        0x00F4
#if(WINVER >= 0x0400)
#define BM_CLICK           0x00F5
#define BM_GETIMAGE        0x00F6
#define BM_SETIMAGE        0x00F7

#define BST_UNCHECKED      0x0000
#define BST_CHECKED        0x0001
#define BST_INDETERMINATE  0x0002
#define BST_PUSHED         0x0004
#define BST_FOCUS          0x0008
#endif /* WINVER >= 0x0400 */

	/*
	 * Static Control Constants
	 */
#define SS_LEFT             0x00000000L
#define SS_CENTER           0x00000001L
#define SS_RIGHT            0x00000002L
#define SS_ICON             0x00000003L
#define SS_BLACKRECT        0x00000004L
#define SS_GRAYRECT         0x00000005L
#define SS_WHITERECT        0x00000006L
#define SS_BLACKFRAME       0x00000007L
#define SS_GRAYFRAME        0x00000008L
#define SS_WHITEFRAME       0x00000009L
#define SS_USERITEM         0x0000000AL
#define SS_SIMPLE           0x0000000BL
#define SS_LEFTNOWORDWRAP   0x0000000CL
#if(WINVER >= 0x0400)
#define SS_OWNERDRAW        0x0000000DL
#define SS_BITMAP           0x0000000EL
#define SS_ENHMETAFILE      0x0000000FL
#define SS_ETCHEDHORZ       0x00000010L
#define SS_ETCHEDVERT       0x00000011L
#define SS_ETCHEDFRAME      0x00000012L
#define SS_TYPEMASK         0x0000001FL
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0501)
#define SS_REALSIZECONTROL  0x00000040L
#endif /* WINVER >= 0x0501 */
#define SS_NOPREFIX         0x00000080L /* Don't do "&" character translation */
#if(WINVER >= 0x0400)
#define SS_NOTIFY           0x00000100L
#define SS_CENTERIMAGE      0x00000200L
#define SS_RIGHTJUST        0x00000400L
#define SS_REALSIZEIMAGE    0x00000800L
#define SS_SUNKEN           0x00001000L
#define SS_ENDELLIPSIS      0x00004000L
#define SS_PATHELLIPSIS     0x00008000L
#define SS_WORDELLIPSIS     0x0000C000L
#define SS_ELLIPSISMASK     0x0000C000L
#endif /* WINVER >= 0x0400 */



#ifndef NOWINMESSAGES
	/*
	 * Static Control Mesages
	 */
#define STM_SETICON         0x0170
#define STM_GETICON         0x0171
#if(WINVER >= 0x0400)
#define STM_SETIMAGE        0x0172
#define STM_GETIMAGE        0x0173
#define STN_CLICKED         0
#define STN_DBLCLK          1
#define STN_ENABLE          2
#define STN_DISABLE         3
#endif /* WINVER >= 0x0400 */
#define STM_MSGMAX          0x0174
#endif /* !NOWINMESSAGES */
#define STM_SETTXTFORMAT  0x0175

	/*
	 * Dialog window class
	 */
#define WC_DIALOG       (MAKEINTATOM(0x8002))

	/*
	 * MSGet/MSSetWindowWord/Long offsets for use with WC_DIALOG windows
	 */
#define DWL_MSGRESULT   0
#define DWL_DLGPROC     4
#define DWL_USER        8

#ifdef _WIN64

#undef DWL_MSGRESULT
#undef DWL_DLGPROC
#undef DWL_USER

#endif /* _WIN64 */

#define DWLP_MSGRESULT  0
#define DWLP_DLGPROC    DWLP_MSGRESULT + sizeof(LRESULT)
#undef DWLP_USER
#define DWLP_USER       DWLP_DLGPROC + sizeof(MSDLGPROC)

	/*
	 * Dialog Manager Routines
	 */

#ifndef NOMSG

	 
		BOOL
		WINAPI
		MSIsDialogMessage(
		IN HMSWND hDlg,
		IN LPMSMSG lpMsg );


#endif /* !NOMSG */

	 
		BOOL
		WINAPI
		MSMapDialogRect(
		IN HMSWND hDlg,
		IN OUT LPMSRECT lpRect );

	 
		int
		WINAPI
		MSDlgDirList(
		IN HMSWND hDlg,
		IN OUT LPTSTR lpPathSpec,
		IN int nIDListBox,
		IN int nIDStaticPath,
		IN UINT uFileType );

	/*
	 * DlgDirList, DlgDirListComboBox flags values
	 */
#define DDL_READWRITE       0x0000
#define DDL_READONLY        0x0001
#define DDL_HIDDEN          0x0002
#define DDL_SYSTEM          0x0004
#define DDL_DIRECTORY       0x0010
#define DDL_ARCHIVE         0x0020

#define DDL_POSTMSGS        0x2000
#define DDL_DRIVES          0x4000
#define DDL_EXCLUSIVE       0x8000

	 
		BOOL
		WINAPI
		MSDlgDirSelectEx(
		IN HMSWND hDlg,
		OUT LPTSTR lpString,
		IN int nCount,
		IN int nIDListBox );

	 
		int
		WINAPI
		MSDlgDirListComboBox(
		IN HMSWND hDlg,
		IN OUT LPTSTR lpPathSpec,
		IN int nIDComboBox,
		IN int nIDStaticPath,
		IN UINT uFiletype );

	 
		BOOL
		WINAPI
		MSDlgDirSelectComboBoxEx(
		IN HMSWND hDlg,
		OUT LPTSTR lpString,
		IN int nCount,
		IN int nIDComboBox );




	/*
	 * Dialog Styles
	 */
#define DS_ABSALIGN         0x01L
#define DS_SYSMODAL         0x02L
#define DS_LOCALEDIT        0x20L   /* Edit items get Local storage. */
#define DS_SETFONT          0x40L   /* User specified font for Dlg controls */
#define DS_MODALFRAME       0x80L   /* Can be combined with WS_CAPTION  */
#define DS_NOIDLEMSG        0x100L  /* WM_ENTERIDLE message will not be sent */
#define DS_SETFOREGROUND    0x200L  /* not in win3.1 */


#if(WINVER >= 0x0400)
#define DS_3DLOOK           0x0004L
#define DS_FIXEDSYS         0x0008L
#define DS_NOFAILCREATE     0x0010L
#define DS_CONTROL          0x0400L
#define DS_CENTER           0x0800L
#define DS_CENTERMOUSE      0x1000L
#define DS_CONTEXTHELP      0x2000L

#define DS_SHELLFONT        (DS_SETFONT | DS_FIXEDSYS)
#endif /* WINVER >= 0x0400 */


#define DM_GETDEFID         (WM_USER+0)
#define DM_SETDEFID         (WM_USER+1)

#if(WINVER >= 0x0400)
#define DM_REPOSITION       (WM_USER+2)
#endif /* WINVER >= 0x0400 */
	/*
	 * Returned in HIWORD() of DM_GETDEFID result if msg is supported
	 */
#define DC_HASDEFID         0x534B

	/*
	 * Dialog Codes
	 */
#define DLGC_WANTARROWS     0x0001      /* Control wants arrow keys         */
#define DLGC_WANTTAB        0x0002      /* Control wants tab keys           */
#define DLGC_WANTALLKEYS    0x0004      /* Control wants all keys           */
#define DLGC_WANTMESSAGE    0x0004      /* Pass message to control          */
#define DLGC_HASSETSEL      0x0008      /* Understands EM_SETSEL message    */
#define DLGC_DEFPUSHBUTTON  0x0010      /* Default pushbutton               */
#define DLGC_UNDEFPUSHBUTTON 0x0020     /* Non-default pushbutton           */
#define DLGC_RADIOBUTTON    0x0040      /* Radio button                     */
#define DLGC_WANTCHARS      0x0080      /* Want WM_CHAR messages            */
#define DLGC_STATIC         0x0100      /* Static item: don't include       */
#define DLGC_BUTTON         0x2000      /* Button item: can be checked      */

	//	Add By hxc 2003.3.14
#define DLGC_WANTLEFTARROWS     0x0200      /* Control wants arrow keys         */
#define DLGC_WANTRIGHTARROWS    0x0400      /* Control wants arrow keys         */
#define DLGC_WANTDOWNARROWS     0x0800      /* Control wants arrow keys         */
#define DLGC_WANTUPARROWS       0x1000      /* Control wants arrow keys         */
#define DLGC_WANTALLARROWS	DLGC_WANTLEFTARROWS|DLGC_WANTRIGHTARROWS|DLGC_WANTDOWNARROWS|DLGC_WANTUPARROWS

	//	Add By hxc 2003.3.14

#define LB_CTLCODE          0L

	/*
	 * Listbox Return Values
	 */
#define LB_OKAY             0
#define LB_ERR              (-1)
#define LB_ERRSPACE         (-2)

	/*
	**  The idStaticPath parameter to MSDlgDirList can have the following values
	**  ORed if the list box should show other details of the files along with
	**  the name of the files;
	*/
	/* all other details also will be returned */


	/*
	 * Listbox Notification Codes
	 */
#define LBN_ERRSPACE        (-2)
#define LBN_SELCHANGE       1
#define LBN_DBLCLK          2
#define LBN_SELCANCEL       3
#define LBN_SETFOCUS        4
#define LBN_KILLFOCUS       5



#ifndef NOWINMESSAGES

	/*
	 * Listbox messages
	 */
#define LB_ADDSTRING            0x0180
#define LB_INSERTSTRING         0x0181
#define LB_DELETESTRING         0x0182
#define LB_SELITEMRANGEEX       0x0183
#define LB_RESETCONTENT         0x0184
#define LB_SETSEL               0x0185
#define LB_SETCURSEL            0x0186
#define LB_GETSEL               0x0187
#define LB_GETCURSEL            0x0188
#define LB_GETTEXT              0x0189
#define LB_GETTEXTLEN           0x018A
#define LB_GETCOUNT             0x018B
#define LB_SELECTSTRING         0x018C
#define LB_DIR                  0x018D
#define LB_GETTOPINDEX          0x018E
#define LB_FINDSTRING           0x018F
#define LB_GETSELCOUNT          0x0190
#define LB_GETSELITEMS          0x0191
#define LB_SETTABSTOPS          0x0192
#define LB_GETHORIZONTALEXTENT  0x0193
#define LB_SETHORIZONTALEXTENT  0x0194
#define LB_SETCOLUMNWIDTH       0x0195
#define LB_ADDFILE              0x0196
#define LB_SETTOPINDEX          0x0197
#define LB_GETITEMRECT          0x0198
#define LB_GETITEMDATA          0x0199
#define LB_SETITEMDATA          0x019A
#define LB_SELITEMRANGE         0x019B
#define LB_SETANCHORINDEX       0x019C
#define LB_GETANCHORINDEX       0x019D
#define LB_SETCARETINDEX        0x019E
#define LB_GETCARETINDEX        0x019F
#define LB_SETITEMHEIGHT        0x01A0
#define LB_GETITEMHEIGHT        0x01A1
#define LB_FINDSTRINGEXACT      0x01A2
#define LB_SETLOCALE            0x01A5
#define LB_GETLOCALE            0x01A6
#define LB_SETCOUNT             0x01A7
#if(WINVER >= 0x0400)
#define LB_INITSTORAGE          0x01A8
#define LB_ITEMFROMPOINT        0x01A9
#endif /* WINVER >= 0x0400 */
#if(_WIN32_WCE >= 0x0400)
#define LB_MULTIPLEADDSTRING    0x01B1
#endif


#if(_WIN32_WINNT >= 0x0501)
#define LB_GETLISTBOXINFO       0x01B2
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0501)
#define LB_MSGMAX               0x01B3
#elif(_WIN32_WCE >= 0x0400)
#undef LB_MSGMAX
#define LB_MSGMAX               0x01B1
#elif(WINVER >= 0x0400)
#define LB_MSGMAX               0x01B0
#else
#define LB_MSGMAX               0x01A8
#endif

#endif /* !NOWINMESSAGES */

#ifndef NOWINSTYLES


	/*
	 * Listbox Styles
	 */
#define LBS_NOTIFY            0x0001L
#define LBS_SORT              0x0002L
#define LBS_NOREDRAW          0x0004L
#define LBS_MULTIPLESEL       0x0008L
#define LBS_OWNERDRAWFIXED    0x0010L
#define LBS_OWNERDRAWVARIABLE 0x0020L
#define LBS_HASSTRINGS        0x0040L
#define LBS_USETABSTOPS       0x0080L
#define LBS_NOINTEGRALHEIGHT  0x0100L
#define LBS_MULTICOLUMN       0x0200L
#define LBS_WANTKEYBOARDINPUT 0x0400L
#define LBS_EXTENDEDSEL       0x0800L
#define LBS_DISABLENOSCROLL   0x1000L
#define LBS_NODATA            0x2000L
#if(WINVER >= 0x0400)
#define LBS_NOSEL             0x4000L
#endif /* WINVER >= 0x0400 */
#define LBS_STANDARD          (LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER)


#endif /* !NOWINSTYLES */


	/*
	 * Combo Box return Values
	 */
#define CB_OKAY             0
#define CB_ERR              (-1)
#define CB_ERRSPACE         (-2)


	/*
	 * Combo Box Notification Codes
	 */
#define CBN_ERRSPACE        (-1)
#define CBN_SELCHANGE       1
#define CBN_DBLCLK          2
#define CBN_SETFOCUS        3
#define CBN_KILLFOCUS       4
#define CBN_EDITCHANGE      5
#define CBN_EDITUPDATE      6
#define CBN_DROPDOWN        7
#define CBN_CLOSEUP         8
#define CBN_SELENDOK        9
#define CBN_SELENDCANCEL    10

#ifndef NOWINSTYLES

	/*
	 * Combo Box styles
	 */
#define CBS_SIMPLE            0x0001L
#define CBS_DROPDOWN          0x0002L
#define CBS_DROPDOWNLIST      0x0003L
#define CBS_OWNERDRAWFIXED    0x0010L
#define CBS_OWNERDRAWVARIABLE 0x0020L
#define CBS_AUTOHSCROLL       0x0040L
#define CBS_OEMCONVERT        0x0080L
#define CBS_SORT              0x0100L
#define CBS_HASSTRINGS        0x0200L
#define CBS_NOINTEGRALHEIGHT  0x0400L
#define CBS_DISABLENOSCROLL   0x0800L
#if(WINVER >= 0x0400)
#define CBS_UPPERCASE           0x2000L
#define CBS_LOWERCASE           0x4000L
#endif /* WINVER >= 0x0400 */

#endif  /* !NOWINSTYLES */


	/*
	 * Combo Box messages
	 */
#ifndef NOWINMESSAGES
#define CB_GETEDITSEL               0x0140
#define CB_LIMITTEXT                0x0141
#define CB_SETEDITSEL               0x0142
#define CB_ADDSTRING                0x0143
#define CB_DELETESTRING             0x0144
#define CB_DIR                      0x0145
#define CB_GETCOUNT                 0x0146
#define CB_GETCURSEL                0x0147
#define CB_GETLBTEXT                0x0148
#define CB_GETLBTEXTLEN             0x0149
#define CB_INSERTSTRING             0x014A
#define CB_RESETCONTENT             0x014B
#define CB_FINDSTRING               0x014C
#define CB_SELECTSTRING             0x014D
#define CB_SETCURSEL                0x014E
#define CB_SHOWDROPDOWN             0x014F
#define CB_GETITEMDATA              0x0150
#define CB_SETITEMDATA              0x0151
#define CB_GETDROPPEDCONTROLRECT    0x0152
#define CB_SETITEMHEIGHT            0x0153
#define CB_GETITEMHEIGHT            0x0154
#define CB_SETEXTENDEDUI            0x0155
#define CB_GETEXTENDEDUI            0x0156
#define CB_GETDROPPEDSTATE          0x0157
#define CB_FINDSTRINGEXACT          0x0158
#define CB_SETLOCALE                0x0159
#define CB_GETLOCALE                0x015A
#if(WINVER >= 0x0400)
#define CB_GETTOPINDEX              0x015b
#define CB_SETTOPINDEX              0x015c
#define CB_GETHORIZONTALEXTENT      0x015d
#define CB_SETHORIZONTALEXTENT      0x015e
#define CB_GETDROPPEDWIDTH          0x015f
#define CB_SETDROPPEDWIDTH          0x0160
#define CB_INITSTORAGE              0x0161
#if(_WIN32_WCE >= 0x0400)
#define CB_MULTIPLEADDSTRING        0x0163
#endif
#endif /* WINVER >= 0x0400 */


#define CB_GETCOMBOBOXINFO          0x0164


#if(_WIN32_WINNT >= 0x0501)
#define CB_MSGMAX                   0x0165
#elif(_WIN32_WCE >= 0x0400)
#undef CB_MSGMAX
#define CB_MSGMAX                   0x0163
#elif(WINVER >= 0x0400)
#define CB_MSGMAX                   0x0162
#else
#define CB_MSGMAX                   0x015B
#endif
#endif  /* !NOWINMESSAGES */



#ifndef NOWINSTYLES


	/*
	 * Scroll Bar Styles
	 */
#define SBS_HORZ                    0x0000L
#define SBS_VERT                    0x0001L
#define SBS_TOPALIGN                0x0002L
#define SBS_LEFTALIGN               0x0002L
#define SBS_BOTTOMALIGN             0x0004L
#define SBS_RIGHTALIGN              0x0004L
#define SBS_SIZEBOXTOPLEFTALIGN     0x0002L
#define SBS_SIZEBOXBOTTOMRIGHTALIGN 0x0004L
#define SBS_SIZEBOX                 0x0008L
#if(WINVER >= 0x0400)
#define SBS_SIZEGRIP                0x0010L
#endif /* WINVER >= 0x0400 */


#endif /* !NOWINSTYLES */

	/*
	 * Scroll bar messages
	 */
#ifndef NOWINMESSAGES
#define SBM_SETPOS                  0x00E0 /*not in win3.1 */
#define SBM_GETPOS                  0x00E1 /*not in win3.1 */
#define SBM_SETRANGE                0x00E2 /*not in win3.1 */
#define SBM_SETRANGEREDRAW          0x00E6 /*not in win3.1 */
#define SBM_GETRANGE                0x00E3 /*not in win3.1 */
#define SBM_ENABLE_ARROWS           0x00E4 /*not in win3.1 */
#if(WINVER >= 0x0400)
#define SBM_SETSCROLLINFO           0x00E9
#define SBM_GETSCROLLINFO           0x00EA
#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0501)
#define SBM_GETSCROLLBARINFO        0x00EB
#endif /* _WIN32_WINNT >= 0x0501 */

#if(WINVER >= 0x0400)
#define SIF_RANGE           0x0001
#define SIF_PAGE            0x0002
#define SIF_POS             0x0004
#define SIF_DISABLENOSCROLL 0x0008
#define SIF_TRACKPOS        0x0010
#define SIF_ALL             (SIF_RANGE | SIF_PAGE | SIF_POS | SIF_TRACKPOS)

	typedef struct tagMSSCROLLINFO
	{
		UINT    cbSize;
		UINT    fMask;
		int     nMin;
		int     nMax;
		UINT    nPage;
		int     nPos;
		int     nTrackPos;
	}   MSSCROLLINFO, FAR *LPMSSCROLLINFO;
	typedef MSSCROLLINFO CONST FAR *LPCMSSCROLLINFO;

	  int     WINAPI MSSetScrollInfo( IN HMSWND, IN int, IN LPCMSSCROLLINFO, IN BOOL );
	  BOOL    WINAPI MSGetScrollInfo( IN HMSWND, IN int, IN OUT LPMSSCROLLINFO );

#endif /* WINVER >= 0x0400 */
#endif /* !NOWINMESSAGES */
#endif /* !NOCTLMGR */

#ifndef NOMDI

	/*
	 * MDI client style bits
	 */
#define MDIS_ALLCHILDSTYLES    0x0001

	/*
	 * wParam Flags for WM_MDITILE and WM_MDICASCADE messages.
	 */
#define MDITILE_VERTICAL       0x0000 /*not in win3.1 */
#define MDITILE_HORIZONTAL     0x0001 /*not in win3.1 */
#define MDITILE_SKIPDISABLED   0x0002 /*not in win3.1 */
#if(_WIN32_WINNT >= 0x0500)
#define MDITILE_ZORDER         0x0004
#endif /* _WIN32_WINNT >= 0x0500 */

	typedef struct tagMSMDICREATESTRUCTA {
		LPCTSTR   szClass;
		LPCTSTR   szTitle;
		HMSHANDLE hOwner;
		int x;
		int y;
		int cx;
		int cy;
		DWORD style;
		LPARAM lParam;        /* app-defined stuff */
	} MSMDICREATESTRUCTA, *LPMSMDICREATESTRUCTA;

	typedef MSMDICREATESTRUCTA MSMDICREATESTRUCT;
	typedef LPMSMDICREATESTRUCTA LPMSMDICREATESTRUCT;

	typedef struct tagMSCLIENTCREATESTRUCT {
		HMSHANDLE hWindowMenu;
		UINT idFirstChild;
	} MSCLIENTCREATESTRUCT, *LPMSCLIENTCREATESTRUCT;

	 
		LRESULT
		WINAPI
		MSDefFrameProc(
		IN HMSWND hWnd,
		IN HMSWND hWndMDIClient,
		IN UINT uMsg,
		IN WPARAM wParam,
		IN LPARAM lParam );


	 
#ifndef _MAC
		LRESULT
		WINAPI
#else
		LRESULT
		CALLBACK
#endif
		MSDefMDIChildProc(
		IN HMSWND hWnd,
		IN UINT uMsg,
		IN WPARAM wParam,
		IN LPARAM lParam );

#ifndef NOMSG

	 
		BOOL
		WINAPI
		MSTranslateMDISysAccel(
		IN HMSWND hWndClient,
		IN LPMSMSG lpMsg );

#endif /* !NOMSG */

	 
		UINT
		WINAPI
		MSArrangeIconicWindows(
		IN HMSWND hWnd );

	 
		HMSWND
		WINAPI
		MSCreateMDIWindow(
		IN LPCTSTR lpClassName,
		IN LPCTSTR lpWindowName,
		IN DWORD dwStyle,
		IN int X,
		IN int Y,
		IN int nWidth,
		IN int nHeight,
		IN HMSWND hWndParent,
		IN HMSINSTANCE hInstance,
		IN LPARAM lParam
		);


#if(WINVER >= 0x0400)
	  WORD    WINAPI MSTileWindows( IN HMSWND hwndParent, IN UINT wHow, IN CONST MSRECT * lpRect, IN UINT cKids, IN const HMSWND FAR * lpKids );
	  WORD    WINAPI MSCascadeWindows( IN HMSWND hwndParent, IN UINT wHow, IN CONST MSRECT * lpRect, IN UINT cKids, IN const HMSWND FAR * lpKids );
#endif /* WINVER >= 0x0400 */
#endif /* !NOMDI */

#endif /* !NOUSER */

	/****** Help support ********************************************************/

#ifndef NOHELP

	typedef DWORD HELPPOLY;
	typedef struct tagMSMULTIKEYHELPA {
#ifndef _MAC
		DWORD  mkSize;
#else
		WORD   mkSize;
#endif
		CHAR   mkKeylist;
		CHAR   szKeyphrase[ 1 ];
	} MSMULTIKEYHELPA, *PMSMULTIKEYHELPA, *LPMSMULTIKEYHELPA;

	typedef MSMULTIKEYHELPA MSMULTIKEYHELP;
	typedef PMSMULTIKEYHELPA PMSMULTIKEYHELP;
	typedef LPMSMULTIKEYHELPA LPMSMULTIKEYHELP;

	typedef struct tagMSHELPWININFOA {
		int  wStructSize;
		int  x;
		int  y;
		int  dx;
		int  dy;
		int  wMax;
		CHAR   rgchMember[ 2 ];
	} MSHELPWININFOA, *PMSHELPWININFOA, *LPMSHELPWININFOA;

	typedef MSHELPWININFOA MSHELPWININFO;
	typedef PMSHELPWININFOA PMSHELPWININFO;
	typedef LPMSHELPWININFOA LPMSHELPWININFO;


	/*
	 * Commands to pass to WinHelp()
	 */
#define HELP_CONTEXT      0x0001L  /* Display topic in ulTopic */
#define HELP_QUIT         0x0002L  /* Terminate help */
#define HELP_INDEX        0x0003L  /* Display index */
#define HELP_CONTENTS     0x0003L
#define HELP_HELPONHELP   0x0004L  /* Display help on using help */
#define HELP_SETINDEX     0x0005L  /* MSSet current Index for multi index help */
#define HELP_SETCONTENTS  0x0005L
#define HELP_CONTEXTPOPUP 0x0008L
#define HELP_FORCEFILE    0x0009L
#define HELP_KEY          0x0101L  /* Display topic for keyword in offabData */
#define HELP_COMMAND      0x0102L
#define HELP_PARTIALKEY   0x0105L
#define HELP_MULTIKEY     0x0201L
#define HELP_SETWINPOS    0x0203L
#if(WINVER >= 0x0400)
#define HELP_CONTEXTMENU  0x000a
#define HELP_FINDER       0x000b
#define HELP_WM_HELP      0x000c
#define HELP_SETPOPUP_POS 0x000d

#define HELP_TCARD              0x8000
#define HELP_TCARD_DATA         0x0010
#define HELP_TCARD_OTHER_CALLER 0x0011

	// These are in winhelp.h in Win95.
#define IDH_NO_HELP                     28440
#define IDH_MISSING_CONTEXT             28441 // Control doesn't have matching help context
#define IDH_GENERIC_HELP_BUTTON         28442 // Property sheet help button
#define IDH_OK                          28443
#define IDH_CANCEL                      28444
#define IDH_HELP                        28445

#endif /* WINVER >= 0x0400 */



	 
		BOOL
		WINAPI
		MSWinHelp(
		IN HMSWND hWndMain,
		IN LPCTSTR lpszHelp,
		IN UINT uCommand,
		IN ULONG_PTR dwData
		);

#endif /* !NOHELP */

#if(WINVER >= 0x0500)

#define GR_GDIOBJECTS     0       /* Count of GDI objects */
#define GR_USEROBJECTS    1       /* Count of USER objects */

	 
		DWORD
		WINAPI
		MSGetGuiResources(
		IN HMSHANDLE hProcess,
		IN DWORD uiFlags );

#endif /* WINVER >= 0x0500 */


#ifndef NOSYSPARAMSINFO

	/*
	 * Parameter for SystemParametersInfo()
	 */

#define SPI_GETBEEP                 0x0001
#define SPI_SETBEEP                 0x0002
#define SPI_GETMOUSE                0x0003
#define SPI_SETMOUSE                0x0004
#define SPI_GETBORDER               0x0005
#define SPI_SETBORDER               0x0006
#define SPI_GETKEYBOARDSPEED        0x000A
#define SPI_SETKEYBOARDSPEED        0x000B
#define SPI_LANGDRIVER              0x000C
#define SPI_ICONHORIZONTALSPACING   0x000D
#define SPI_GETSCREENSAVETIMEOUT    0x000E
#define SPI_SETSCREENSAVETIMEOUT    0x000F
#define SPI_GETSCREENSAVEACTIVE     0x0010
#define SPI_SETSCREENSAVEACTIVE     0x0011
#define SPI_GETGRIDGRANULARITY      0x0012
#define SPI_SETGRIDGRANULARITY      0x0013
#define SPI_SETDESKWALLPAPER        0x0014
#define SPI_SETDESKPATTERN          0x0015
#define SPI_GETKEYBOARDDELAY        0x0016
#define SPI_SETKEYBOARDDELAY        0x0017
#define SPI_ICONVERTICALSPACING     0x0018
#define SPI_GETICONTITLEWRAP        0x0019
#define SPI_SETICONTITLEWRAP        0x001A
#define SPI_GETMENUDROPALIGNMENT    0x001B
#define SPI_SETMENUDROPALIGNMENT    0x001C
#define SPI_SETDOUBLECLKWIDTH       0x001D
#define SPI_SETDOUBLECLKHEIGHT      0x001E
#define SPI_GETICONTITLELOGFONT     0x001F
#define SPI_SETDOUBLECLICKTIME      0x0020
#define SPI_SETMOUSEBUTTONSWAP      0x0021
#define SPI_SETICONTITLELOGFONT     0x0022
#define SPI_GETFASTTASKSWITCH       0x0023
#define SPI_SETFASTTASKSWITCH       0x0024
#if(WINVER >= 0x0400)
#define SPI_SETDRAGFULLWINDOWS      0x0025
#define SPI_GETDRAGFULLWINDOWS      0x0026
#define SPI_GETNONCLIENTMETRICS     0x0029
#define SPI_SETNONCLIENTMETRICS     0x002A
#define SPI_GETCSMINIMIZEDMETRICS     0x002B
#define SPI_SETCSMINIMIZEDMETRICS     0x002C
#define SPI_GETICONMETRICS          0x002D
#define SPI_SETICONMETRICS          0x002E
#define SPI_SETWORKAREA             0x002F
#define SPI_GETWORKAREA             0x0030
#define SPI_SETPENWINDOWS           0x0031

#define SPI_GETHIGHCONTRAST         0x0042
#define SPI_SETHIGHCONTRAST         0x0043
#define SPI_GETKEYBOARDPREF         0x0044
#define SPI_SETKEYBOARDPREF         0x0045
#define SPI_GETSCREENREADER         0x0046
#define SPI_SETSCREENREADER         0x0047
#define SPI_GETANIMATION            0x0048
#define SPI_SETANIMATION            0x0049
#define SPI_GETFONTSMOOTHING        0x004A
#define SPI_SETFONTSMOOTHING        0x004B
#define SPI_SETDRAGWIDTH            0x004C
#define SPI_SETDRAGHEIGHT           0x004D
#define SPI_SETHANDHELD             0x004E
#define SPI_GETLOWPOWERTIMEOUT      0x004F
#define SPI_GETPOWEROFFTIMEOUT      0x0050
#define SPI_SETLOWPOWERTIMEOUT      0x0051
#define SPI_SETPOWEROFFTIMEOUT      0x0052
#define SPI_GETLOWPOWERACTIVE       0x0053
#define SPI_GETPOWEROFFACTIVE       0x0054
#define SPI_SETLOWPOWERACTIVE       0x0055
#define SPI_SETPOWEROFFACTIVE       0x0056
#define SPI_SETCURSORS              0x0057
#define SPI_SETICONS                0x0058
#define SPI_GETDEFAULTINPUTLANG     0x0059
#define SPI_SETDEFAULTINPUTLANG     0x005A
#define SPI_SETLANGTOGGLE           0x005B
#define SPI_GETWINDOWSEXTENSION     0x005C
#define SPI_SETMOUSETRAILS          0x005D
#define SPI_GETMOUSETRAILS          0x005E
#define SPI_SETSCREENSAVERRUNNING   0x0061
#define SPI_SCREENSAVERRUNNING     SPI_SETSCREENSAVERRUNNING
#endif /* WINVER >= 0x0400 */
#define SPI_GETFILTERKEYS          0x0032
#define SPI_SETFILTERKEYS          0x0033
#define SPI_GETTOGGLEKEYS          0x0034
#define SPI_SETTOGGLEKEYS          0x0035
#define SPI_GETMOUSEKEYS           0x0036
#define SPI_SETMOUSEKEYS           0x0037
#define SPI_GETSHOWSOUNDS          0x0038
#define SPI_SETSHOWSOUNDS          0x0039
#define SPI_GETSTICKYKEYS          0x003A
#define SPI_SETSTICKYKEYS          0x003B
#define SPI_GETACCESSTIMEOUT       0x003C
#define SPI_SETACCESSTIMEOUT       0x003D
#if(WINVER >= 0x0400)
#define SPI_GETSERIALKEYS          0x003E
#define SPI_SETSERIALKEYS          0x003F
#endif /* WINVER >= 0x0400 */
#define SPI_GETSOUNDSENTRY         0x0040
#define SPI_SETSOUNDSENTRY         0x0041
#if(_WIN32_WINNT >= 0x0400)
#define SPI_GETSNAPTODEFBUTTON     0x005F
#define SPI_SETSNAPTODEFBUTTON     0x0060
#endif /* _WIN32_WINNT >= 0x0400 */
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define SPI_GETMOUSEHOVERWIDTH     0x0062
#define SPI_SETMOUSEHOVERWIDTH     0x0063
#define SPI_GETMOUSEHOVERHEIGHT    0x0064
#define SPI_SETMOUSEHOVERHEIGHT    0x0065
#define SPI_GETMOUSEHOVERTIME      0x0066
#define SPI_SETMOUSEHOVERTIME      0x0067
#define SPI_GETWHEELSCROLLLINES    0x0068
#define SPI_SETWHEELSCROLLLINES    0x0069
#define SPI_GETMENUSHOWDELAY       0x006A
#define SPI_SETMENUSHOWDELAY       0x006B


#define SPI_GETSHOWIMEUI          0x006E
#define SPI_SETSHOWIMEUI          0x006F
#endif


#if(WINVER >= 0x0500)
#define SPI_GETMOUSESPEED         0x0070
#define SPI_SETMOUSESPEED         0x0071
#define SPI_GETSCREENSAVERRUNNING 0x0072
#define SPI_GETDESKWALLPAPER      0x0073
#endif /* WINVER >= 0x0500 */


#if(WINVER >= 0x0500)
#define SPI_GETACTIVEWINDOWTRACKING         0x1000
#define SPI_SETACTIVEWINDOWTRACKING         0x1001
#define SPI_GETMENUANIMATION                0x1002
#define SPI_SETMENUANIMATION                0x1003
#define SPI_GETCOMBOBOXANIMATION            0x1004
#define SPI_SETCOMBOBOXANIMATION            0x1005
#define SPI_GETLISTBOXSMOOTHSCROLLING       0x1006
#define SPI_SETLISTBOXSMOOTHSCROLLING       0x1007
#define SPI_GETGRADIENTCAPTIONS             0x1008
#define SPI_SETGRADIENTCAPTIONS             0x1009
#define SPI_GETKEYBOARDCUES                 0x100A
#define SPI_SETKEYBOARDCUES                 0x100B
#define SPI_GETMENUUNDERLINES               SPI_GETKEYBOARDCUES
#define SPI_SETMENUUNDERLINES               SPI_SETKEYBOARDCUES
#define SPI_GETACTIVEWNDTRKZORDER           0x100C
#define SPI_SETACTIVEWNDTRKZORDER           0x100D
#define SPI_GETHOTTRACKING                  0x100E
#define SPI_SETHOTTRACKING                  0x100F
#define SPI_GETMENUFADE                     0x1012
#define SPI_SETMENUFADE                     0x1013
#define SPI_GETSELECTIONFADE                0x1014
#define SPI_SETSELECTIONFADE                0x1015
#define SPI_GETTOOLTIPANIMATION             0x1016
#define SPI_SETTOOLTIPANIMATION             0x1017
#define SPI_GETTOOLTIPFADE                  0x1018
#define SPI_SETTOOLTIPFADE                  0x1019
#define SPI_GETCURSORSHADOW                 0x101A
#define SPI_SETCURSORSHADOW                 0x101B
#if(_WIN32_WINNT >= 0x0501)
#define SPI_GETMOUSESONAR                   0x101C
#define SPI_SETMOUSESONAR                   0x101D
#define SPI_GETMOUSECLICKLOCK               0x101E
#define SPI_SETMOUSECLICKLOCK               0x101F
#define SPI_GETMOUSEVANISH                  0x1020
#define SPI_SETMOUSEVANISH                  0x1021
#define SPI_GETFLATMENU                     0x1022
#define SPI_SETFLATMENU                     0x1023
#define SPI_GETDROPSHADOW                   0x1024
#define SPI_SETDROPSHADOW                   0x1025
#endif /* _WIN32_WINNT >= 0x0501 */

#define SPI_GETUIEFFECTS                    0x103E
#define SPI_SETUIEFFECTS                    0x103F

#define SPI_GETFOREGROUNDLOCKTIMEOUT        0x2000
#define SPI_SETFOREGROUNDLOCKTIMEOUT        0x2001
#define SPI_GETACTIVEWNDTRKTIMEOUT          0x2002
#define SPI_SETACTIVEWNDTRKTIMEOUT          0x2003
#define SPI_GETFOREGROUNDFLASHCOUNT         0x2004
#define SPI_SETFOREGROUNDFLASHCOUNT         0x2005
#define SPI_GETCARETWIDTH                   0x2006
#define SPI_SETCARETWIDTH                   0x2007

#if(_WIN32_WINNT >= 0x0501)
#define SPI_GETMOUSECLICKLOCKTIME           0x2008
#define SPI_SETMOUSECLICKLOCKTIME           0x2009
#define SPI_GETFONTSMOOTHINGTYPE            0x200A
#define SPI_SETFONTSMOOTHINGTYPE            0x200B

	/* constants for SPI_GETFONTSMOOTHINGTYPE and SPI_SETFONTSMOOTHINGTYPE: */
#define FE_FONTSMOOTHINGSTANDARD            0x0001
#define FE_FONTSMOOTHINGCLEARTYPE           0x0002
#define FE_FONTSMOOTHINGDOCKING             0x8000

#define SPI_GETFONTSMOOTHINGCONTRAST           0x200C
#define SPI_SETFONTSMOOTHINGCONTRAST           0x200D

#define SPI_GETFOCUSBORDERWIDTH             0x200E
#define SPI_SETFOCUSBORDERWIDTH             0x200F
#define SPI_GETFOCUSBORDERHEIGHT            0x2010
#define SPI_SETFOCUSBORDERHEIGHT            0x2011
#endif /* _WIN32_WINNT >= 0x0501 */

#endif /* WINVER >= 0x0500 */

	/*
	 * Flags
	 */
#define SPIF_UPDATEINIFILE    0x0001
#define SPIF_SENDWININICHANGE 0x0002
#define SPIF_SENDCHANGE       SPIF_SENDWININICHANGE


#define METRICS_USEDEFAULT -1
#ifdef _WINGDI_
#ifndef NOGDI
	typedef struct tagMSNONCLIENTMETRICSA
	{
		UINT    cbSize;
		int     iBorderWidth;
		int     iScrollWidth;
		int     iScrollHeight;
		int     iCaptionWidth;
		int     iCaptionHeight;
		LOGFONTA lfCaptionFont;
		int     iSmCaptionWidth;
		int     iSmCaptionHeight;
		LOGFONTA lfSmCaptionFont;
		int     iMenuWidth;
		int     iMenuHeight;
		LOGFONTA lfMenuFont;
		LOGFONTA lfStatusFont;
		LOGFONTA lfMessageFont;
	}   MSNONCLIENTMETRICSA, *PMSNONCLIENTMETRICSA, FAR* LPMSNONCLIENTMETRICSA;

	typedef MSNONCLIENTMETRICSA MSNONCLIENTMETRICS;
	typedef PMSNONCLIENTMETRICSA PMSNONCLIENTMETRICS;
	typedef LPMSNONCLIENTMETRICSA LPMSNONCLIENTMETRICS;
#endif /* NOGDI */
#endif /* _WINGDI_ */

#define ARW_BOTTOMLEFT              0x0000L
#define ARW_BOTTOMRIGHT             0x0001L
#define ARW_TOPLEFT                 0x0002L
#define ARW_TOPRIGHT                0x0003L
#define ARW_STARTMASK               0x0003L
#define ARW_STARTRIGHT              0x0001L
#define ARW_STARTTOP                0x0002L

#define ARW_LEFT                    0x0000L
#define ARW_RIGHT                   0x0000L
#define ARW_UP                      0x0004L
#define ARW_DOWN                    0x0004L
#define ARW_HIDE                    0x0008L

	typedef struct tagMSMINIMIZEDMETRICS
	{
		UINT    cbSize;
		int     iWidth;
		int     iHorzGap;
		int     iVertGap;
		int     iArrange;
	}   MSMINIMIZEDMETRICS, *PMSMINIMIZEDMETRICS, *LPMSMINIMIZEDMETRICS;

#ifdef _WINGDI_
#ifndef NOGDI
	typedef struct tagMSICONMETRICSA
	{
		UINT    cbSize;
		int     iHorzSpacing;
		int     iVertSpacing;
		int     iTitleWrap;
		LOGFONTA lfFont;
	}   MSICONMETRICSA, *PMSICONMETRICSA, *LPMSICONMETRICSA;

	typedef MSICONMETRICSA MSICONMETRICS;
	typedef PMSICONMETRICSA PMSICONMETRICS;
	typedef LPMSICONMETRICSA LPMSICONMETRICS;
#endif /* NOGDI */
#endif /* _WINGDI_ */

	typedef struct tagMSANIMATIONINFO
	{
		UINT    cbSize;
		int     iMinAnimate;
	}   MSANIMATIONINFO, *LPMSANIMATIONINFO;

	typedef struct tagMSSERIALKEYSA
	{
		UINT    cbSize;
		DWORD   dwFlags;
		LPTSTR     lpszActivePort;
		LPTSTR     lpszPort;
		UINT    iBaudRate;
		UINT    iPortState;
		UINT    iActive;
	}   MSSERIALKEYSA, *LPMSSERIALKEYSA;

	typedef MSSERIALKEYSA MSSERIALKEYS;
	typedef LPMSSERIALKEYSA LPMSSERIALKEYS;

	/* flags for SERIALKEYS dwFlags field */
#define SERKF_SERIALKEYSON  0x00000001
#define SERKF_AVAILABLE     0x00000002
#define SERKF_INDICATOR     0x00000004


	typedef struct tagMSHIGHCONTRASTA
	{
		UINT    cbSize;
		DWORD   dwFlags;
		LPTSTR   lpszDefaultScheme;
	}   MSHIGHCONTRASTA, *LPMSHIGHCONTRASTA;

	typedef MSHIGHCONTRASTA MSHIGHCONTRAST;
	typedef LPMSHIGHCONTRASTA LPMSHIGHCONTRAST;

	/* flags for HIGHCONTRAST dwFlags field */
#define HCF_HIGHCONTRASTON  0x00000001
#define HCF_AVAILABLE       0x00000002
#define HCF_HOTKEYACTIVE    0x00000004
#define HCF_CONFIRMHOTKEY   0x00000008
#define HCF_HOTKEYSOUND     0x00000010
#define HCF_INDICATOR       0x00000020
#define HCF_HOTKEYAVAILABLE 0x00000040

	/* Flags for MSChangeDisplayCSSettings */
#define CDS_UPDATEREGISTRY  0x00000001
#define CDS_TEST            0x00000002
#define CDS_FULLSCREEN      0x00000004
#define CDS_GLOBAL          0x00000008
#define CDS_SET_PRIMARY     0x00000010
#define CDS_VIDEOPARAMETERS 0x00000020
#define CDS_RESET           0x40000000
#define CDS_NORESET         0x10000000

	//#include <tvout.h>

	/* Return values for MSChangeDisplayCSSettings */
#define DISP_CHANGE_SUCCESSFUL       0
#define DISP_CHANGE_RESTART          1
#define DISP_CHANGE_FAILED          -1
#define DISP_CHANGE_BADMODE         -2
#define DISP_CHANGE_NOTUPDATED      -3
#define DISP_CHANGE_BADFLAGS        -4
#define DISP_CHANGE_BADPARAM        -5
#if(_WIN32_WINNT >= 0x0501)
#define DISP_CHANGE_BADDUALVIEW     -6
#endif /* _WIN32_WINNT >= 0x0501 */

#ifdef _WINGDI_
#ifndef NOGDI

	 
		LONG
		WINAPI
		MSChangeDisplaySettings(
		IN LPMSDEVMODEA  lpDevMode,
		IN DWORD       dwFlags );

	 
		LONG
		WINAPI
		MSChangeDisplaySettingsEx(
		IN LPCTSTR    lpszDeviceName,
		IN LPMSDEVMODEA  lpDevMode,
		IN HMSWND        hwnd,
		IN DWORD       dwflags,
		IN LPVOID      lParam );


#define ENUM_CURRENT_SETTINGS       ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS      ((DWORD)-2)

	 
		BOOL
		WINAPI
		MSEnumDisplaySettings(
		IN LPCTSTR lpszDeviceName,
		IN DWORD iModeNum,
		OUT LPMSDEVMODEA lpDevMode );

#if(WINVER >= 0x0500)

	 
		BOOL
		WINAPI
		MSEnumDisplaySettingsEx(
		IN LPCTSTR lpszDeviceName,
		IN DWORD iModeNum,
		OUT LPMSDEVMODEA lpDevMode,
		IN DWORD dwFlags );


	/* Flags for MSEnumDisplaySettingsEx */
#define EDS_RAWMODE                   0x00000002

	 
		BOOL
		WINAPI
		MSEnumDisplayDevices(
		IN LPCTSTR lpDevice,
		IN DWORD iDevNum,
		OUT PDISPLAY_DEVICEA lpDisplayDevice,
		IN DWORD dwFlags );

#endif /* WINVER >= 0x0500 */

#endif /* NOGDI */
#endif /* _WINGDI_ */


	 
		BOOL
		WINAPI
		MSSystemParametersInfo(
		IN UINT uiAction,
		IN UINT uiParam,
		IN OUT PVOID pvParam,
		IN UINT fWinIni );

#endif  /* !NOSYSPARAMSINFO  */

	/*
	 * Accessibility support
	 */
	typedef struct tagMSFILTERKEYS
	{
		UINT  cbSize;
		DWORD dwFlags;
		DWORD iWaitMSec;            // Acceptance Delay
		DWORD iDelayMSec;           // Delay Until Repeat
		DWORD iRepeatMSec;          // Repeat Rate
		DWORD iBounceMSec;          // Debounce Time
	} MSFILTERKEYS, *LPMSFILTERKEYS;

	/*
	 * MSFILTERKEYS dwFlags field
	 */
#define FKF_FILTERKEYSON    0x00000001
#define FKF_AVAILABLE       0x00000002
#define FKF_HOTKEYACTIVE    0x00000004
#define FKF_CONFIRMHOTKEY   0x00000008
#define FKF_HOTKEYSOUND     0x00000010
#define FKF_INDICATOR       0x00000020
#define FKF_CLICKON         0x00000040

	typedef struct tagMSSTICKYKEYS
	{
		UINT  cbSize;
		DWORD dwFlags;
	} MSSTICKYKEYS, *LPMSSTICKYKEYS;

	/*
	 * MSSTICKYKEYS dwFlags field
	 */
#define SKF_STICKYKEYSON    0x00000001
#define SKF_AVAILABLE       0x00000002
#define SKF_HOTKEYACTIVE    0x00000004
#define SKF_CONFIRMHOTKEY   0x00000008
#define SKF_HOTKEYSOUND     0x00000010
#define SKF_INDICATOR       0x00000020
#define SKF_AUDIBLEFEEDBACK 0x00000040
#define SKF_TRISTATE        0x00000080
#define SKF_TWOKEYSOFF      0x00000100
#if(_WIN32_WINNT >= 0x0500)
#define SKF_LALTLATCHED       0x10000000
#define SKF_LCTLLATCHED       0x04000000
#define SKF_LSHIFTLATCHED     0x01000000
#define SKF_RALTLATCHED       0x20000000
#define SKF_RCTLLATCHED       0x08000000
#define SKF_RSHIFTLATCHED     0x02000000
#define SKF_LWINLATCHED       0x40000000
#define SKF_RWINLATCHED       0x80000000
#define SKF_LALTLOCKED        0x00100000
#define SKF_LCTLLOCKED        0x00040000
#define SKF_LSHIFTLOCKED      0x00010000
#define SKF_RALTLOCKED        0x00200000
#define SKF_RCTLLOCKED        0x00080000
#define SKF_RSHIFTLOCKED      0x00020000
#define SKF_LWINLOCKED        0x00400000
#define SKF_RWINLOCKED        0x00800000
#endif /* _WIN32_WINNT >= 0x0500 */

	typedef struct tagMSMOUSEKEYS
	{
		UINT cbSize;
		DWORD dwFlags;
		DWORD iMaxSpeed;
		DWORD iTimeToMaxSpeed;
		DWORD iCtrlSpeed;
		DWORD dwReserved1;
		DWORD dwReserved2;
	} MSMOUSEKEYS, *LPMSMOUSEKEYS;

	/*
	 * MSMOUSEKEYS dwFlags field
	 */
#define MKF_MOUSEKEYSON     0x00000001
#define MKF_AVAILABLE       0x00000002
#define MKF_HOTKEYACTIVE    0x00000004
#define MKF_CONFIRMHOTKEY   0x00000008
#define MKF_HOTKEYSOUND     0x00000010
#define MKF_INDICATOR       0x00000020
#define MKF_MODIFIERS       0x00000040
#define MKF_REPLACENUMBERS  0x00000080
#if(_WIN32_WINNT >= 0x0500)
#define MKF_LEFTBUTTONSEL   0x10000000
#define MKF_RIGHTBUTTONSEL  0x20000000
#define MKF_LEFTBUTTONDOWN  0x01000000
#define MKF_RIGHTBUTTONDOWN 0x02000000
#define MKF_MOUSEMODE       0x80000000
#endif /* _WIN32_WINNT >= 0x0500 */

	typedef struct tagMSACCESSTIMEOUT
	{
		UINT  cbSize;
		DWORD dwFlags;
		DWORD iTimeOutMSec;
	} MSACCESSTIMEOUT, *LPMSACCESSTIMEOUT;

	/*
	 * MSACCESSTIMEOUT dwFlags field
	 */
#define ATF_TIMEOUTON       0x00000001
#define ATF_ONOFFFEEDBACK   0x00000002

	/* values for SOUNDSENTRY iFSGrafEffect field */
#define SSGF_NONE       0
#define SSGF_DISPLAY    3

	/* values for SOUNDSENTRY iFSTextEffect field */
#define SSTF_NONE       0
#define SSTF_CHARS      1
#define SSTF_BORDER     2
#define SSTF_DISPLAY    3

	/* values for SOUNDSENTRY iWindowsEffect field */
#define SSWF_NONE     0
#define SSWF_TITLE    1
#define SSWF_WINDOW   2
#define SSWF_DISPLAY  3
#define SSWF_CUSTOM   4

	typedef struct tagMSSOUNDSENTRYA
	{
		UINT cbSize;
		DWORD dwFlags;
		DWORD iFSTextEffect;
		DWORD iFSTextEffectMSec;
		DWORD iFSTextEffectColorBits;
		DWORD iFSGrafEffect;
		DWORD iFSGrafEffectMSec;
		DWORD iFSGrafEffectColor;
		DWORD iWindowsEffect;
		DWORD iWindowsEffectMSec;
		LPTSTR   lpszWindowsEffectDLL;
		DWORD iWindowsEffectOrdinal;
	} MSSOUNDSENTRYA, *LPMSSOUNDSENTRYA;

	typedef MSSOUNDSENTRYA MSSOUNDSENTRY;
	typedef LPMSSOUNDSENTRYA LPMSSOUNDSENTRY;

	/*
	 * SOUNDSENTRY dwFlags field
	 */
#define SSF_SOUNDSENTRYON   0x00000001
#define SSF_AVAILABLE       0x00000002
#define SSF_INDICATOR       0x00000004

	typedef struct tagMSTOGGLEKEYS
	{
		UINT cbSize;
		DWORD dwFlags;
	} MSTOGGLEKEYS, *LPMSTOGGLEKEYS;

	/*
	 * MSTOGGLEKEYS dwFlags field
	 */
#define TKF_TOGGLEKEYSON    0x00000001
#define TKF_AVAILABLE       0x00000002
#define TKF_HOTKEYACTIVE    0x00000004
#define TKF_CONFIRMHOTKEY   0x00000008
#define TKF_HOTKEYSOUND     0x00000010
#define TKF_INDICATOR       0x00000020

	/*
	 * Set debug level
	 */

	 
		void
		WINAPI
		MSSetDebugErrorLevel(
		IN DWORD dwLevel
		);

	/*
	 * MSSetLastErrorEx() types.
	 */

#define SLE_ERROR       0x00000001
#define SLE_MINORERROR  0x00000002
#define SLE_WARNING     0x00000003

	 
		void
		WINAPI
		MSSetLastErrorEx(
		IN DWORD dwErrCode,
		IN DWORD dwType
		);


#if(WINVER >= 0x0500)

	/*
	 * Multimonitor API.
	 */

#define MONITOR_DEFAULTTONULL       0x00000000
#define MONITOR_DEFAULTTOPRIMARY    0x00000001
#define MONITOR_DEFAULTTONEAREST    0x00000002

	 
		HMSMONITOR
		WINAPI
		MSMonitorFromPoint(
		IN MSPOINT pt,
		IN DWORD dwFlags );

	 
		HMSMONITOR
		WINAPI
		MSMonitorFromRect(
		IN LPMSRECT lprc,
		IN DWORD dwFlags );

	 
		HMSMONITOR
		WINAPI
		MSMonitorFromWindow( IN HMSWND hwnd, IN DWORD dwFlags );

#define MONITORINFOF_PRIMARY        0x00000001

#ifndef CCHDEVICENAME
#define CCHDEVICENAME 32
#endif

	typedef struct tagMSMONITORINFO
	{
		DWORD   cbSize;
		MSRECT    rcMonitor;
		MSRECT    rcWork;
		DWORD   dwFlags;
	} MSMONITORINFO, *LPMSMONITORINFO;

#ifdef __cplusplus
	typedef struct tagMSMONITORINFOEXA : public tagMSMONITORINFO
	{
		CHAR        szDevice[ CCHDEVICENAME ];
	} MSMONITORINFOEXA, *LPMSMONITORINFOEXA;

	typedef MSMONITORINFOEXA MSMONITORINFOEX;
	typedef LPMSMONITORINFOEXA LPMSMONITORINFOEX;
#else // ndef __cplusplus
	typedef struct tagMSMONITORINFOEXA
	{
		MSMONITORINFO u;
		CHAR        szDevice[CCHDEVICENAME];
	} MSMONITORINFOEXA, *LPMSMONITORINFOEXA;

	typedef MSMONITORINFOEXA MSMONITORINFOEX;
	typedef LPMSMONITORINFOEXA LPMSMONITORINFOEX;
#endif

	  BOOL WINAPI MSGetMonitorInfo( IN HMSMONITOR hMonitor, OUT LPMSMONITORINFO lpmi );

	typedef BOOL( CALLBACK* MSMONITORENUMPROC )( HMSMONITOR, HMSDC, LPMSRECT, LPARAM );

	 
		BOOL
		WINAPI
		MSEnumDisplayMonitors(
		IN HMSDC             hdc,
		IN LPMSRECT         lprcClip,
		IN MSMONITORENUMPROC lpfnEnum,
		IN LPARAM          dwData );


#ifndef NOWINABLE

	/*
	 * WinEvents - Active Accessibility hooks
	 */

	 
		void
		WINAPI
		MSNotifyWinEvent(
		IN DWORD event,
		IN HMSWND  hwnd,
		IN LONG  idObject,
		IN LONG  idChild );

	typedef void ( CALLBACK* MSWINEVENTPROC )(
		HMSWINEVENTHOOK hWinEventHook,
		DWORD         event,
		HMSWND          hwnd,
		LONG          idObject,
		LONG          idChild,
		DWORD         idEventThread,
		DWORD         dwmsEventTime );

	 
		HMSWINEVENTHOOK
		WINAPI
		MSSetWinEventHook(
		IN DWORD        eventMin,
		IN DWORD        eventMax,
		IN HMSMODULE      hmodWinEventProc,
		IN MSWINEVENTPROC pfnWinEventProc,
		IN DWORD        idProcess,
		IN DWORD        idThread,
		IN DWORD        dwFlags );

#if(_WIN32_WINNT >= 0x0501)
	 
		BOOL
		WINAPI
		MSIsWinEventHookInstalled(
		IN DWORD event );
#endif /* _WIN32_WINNT >= 0x0501 */

	/*
	 * dwFlags for MSSetWinEventHook
	 */
#define WINEVENT_OUTOFCONTEXT   0x0000  // Events are ASYNC
#define WINEVENT_SKIPOWNTHREAD  0x0001  // Don't call back for events on installer's thread
#define WINEVENT_SKIPOWNPROCESS 0x0002  // Don't call back for events on installer's process
#define WINEVENT_INCONTEXT      0x0004  // Events are SYNC, this causes your dll to be injected into every process

	 
		BOOL
		WINAPI
		MSUnhookWinEvent(
		IN HMSWINEVENTHOOK hWinEventHook );

	/*
	 * idObject values for WinEventProc and NotifyWinEvent
	 */

	/*
	 * hwnd + idObject can be used with OLEACC.DLL's OleMSGetObjectFromWindow()
	 * to get an interface pointer to the container.  indexChild is the item
	 * within the container in question.  MSSetup a VARIANT with vt VT_I4 and
	 * lVal the indexChild and pass that in to all methods.  Then you
	 * are raring to go.
	 */


	/*
	 * Common object IDs (cookies, only for sending WM_GETOBJECT to get at the
	 * thing in question).  Positive IDs are reserved for apps (app specific),
	 * negative IDs are system things and are global, 0 means "just little old
	 * me".
	 */
#define     CHILDID_SELF        0
#define     INDEXID_OBJECT      0
#define     INDEXID_CONTAINER   0

	/*
	 * Reserved IDs for system objects
	 */
#define     OBJID_WINDOW        ((LONG)0x00000000)
#define     OBJID_SYSMENU       ((LONG)0xFFFFFFFF)
#define     OBJID_TITLEBAR      ((LONG)0xFFFFFFFE)
#define     OBJID_MENU          ((LONG)0xFFFFFFFD)
#define     OBJID_CLIENT        ((LONG)0xFFFFFFFC)
#define     OBJID_VSCROLL       ((LONG)0xFFFFFFFB)
#define     OBJID_HSCROLL       ((LONG)0xFFFFFFFA)
#define     OBJID_SIZEGRIP      ((LONG)0xFFFFFFF9)
#define     OBJID_CARET         ((LONG)0xFFFFFFF8)
#define     OBJID_CURSOR        ((LONG)0xFFFFFFF7)
#define     OBJID_ALERT         ((LONG)0xFFFFFFF6)
#define     OBJID_SOUND         ((LONG)0xFFFFFFF5)
#define     OBJID_QUERYCLASSNAMEIDX ((LONG)0xFFFFFFF4)
#define     OBJID_NATIVEOM      ((LONG)0xFFFFFFF0)

	/*
	 * EVENT DEFINITION
	 */
#define EVENT_MIN           0x00000001
#define EVENT_MAX           0x7FFFFFFF


	/*
	 *  EVENT_SYSTEM_SOUND
	 *  Sent when a sound is played.  Currently nothing is generating this, we
	 *  this event when a system sound (for menus, etc) is played.  Apps
	 *  generate this, if accessible, when a private sound is played.  For
	 *  example, if Mail plays a "New Mail" sound.
	 *
	 *  MSSystem Sounds:
	 *  (Generated by PlaySoundEvent in USER itself)
	 *      hwnd            is NULL
	 *      idObject        is OBJID_SOUND
	 *      idChild         is sound child ID if one
	 *  App Sounds:
	 *  (PlaySoundEvent won't generate notification; up to app)
	 *      hwnd + idObject gets interface pointer to Sound object
	 *      idChild identifies the sound in question
	 *  are going to be cleaning up the SOUNDSENTRY feature in the control panel
	 *  and will use this at that time.  Applications implementing WinEvents
	 *  are perfectly welcome to use it.  Clients of IAccessible* will simply
	 *  turn around and get back a non-visual object that describes the sound.
	 */
#define EVENT_SYSTEM_SOUND              0x0001

	/*
	 * EVENT_SYSTEM_ALERT
	 * MSSystem Alerts:
	 * (Generated by MessageBox() calls for example)
	 *      hwnd            is hwndMessageBox
	 *      idObject        is OBJID_ALERT
	 * App Alerts:
	 * (Generated whenever)
	 *      hwnd+idObject gets interface pointer to Alert
	 */
#define EVENT_SYSTEM_ALERT              0x0002

	/*
	 * EVENT_SYSTEM_FOREGROUND
	 * Sent when the foreground (active) window changes, even if it is changing
	 * to another window in the same thread as the previous one.
	 *      hwnd            is hwndNewForeground
	 *      idObject        is OBJID_WINDOW
	 *      idChild    is INDEXID_OBJECT
	 */
#define EVENT_SYSTEM_FOREGROUND         0x0003

	/*
	 * Menu
	 *      hwnd            is window (top level window or popup menu window)
	 *      idObject        is ID of control (OBJID_MENU, OBJID_SYSMENU, OBJID_SELF for popup)
	 *      idChild         is CHILDID_SELF
	 *
	 * EVENT_SYSTEM_MENUSTART
	 * EVENT_SYSTEM_MENUEND
	 * For MENUSTART, hwnd+idObject+idChild refers to the control with the menu bar,
	 *  or the control bringing up the context menu.
	 *
	 * Sent when entering into and leaving from menu mode (system, app bar, and
	 * track popups).
	 */
#define EVENT_SYSTEM_MENUSTART          0x0004
#define EVENT_SYSTEM_MENUEND            0x0005

	/*
	 * EVENT_SYSTEM_MENUPOPUPSTART
	 * EVENT_SYSTEM_MENUPOPUPEND
	 * Sent when a menu popup comes up and just before it is taken down.  Note
	 * that for a call to TrackPopupMenu(), a client will see EVENT_SYSTEM_MENUSTART
	 * followed almost immediately by EVENT_SYSTEM_MENUPOPUPSTART for the popup
	 * being shown.
	 *
	 * For MENUPOPUP, hwnd+idObject+idChild refers to the NEW popup coming up, not the
	 * parent item which is hierarchical.  You can get the parent menu/popup by
	 * asking for the accParent object.
	 */
#define EVENT_SYSTEM_MENUPOPUPSTART     0x0006
#define EVENT_SYSTEM_MENUPOPUPEND       0x0007


	/*
	 * EVENT_SYSTEM_CAPTURESTART
	 * EVENT_SYSTEM_CAPTUREEND
	 * Sent when a window takes the capture and releases the capture.
	 */
#define EVENT_SYSTEM_CAPTURESTART       0x0008
#define EVENT_SYSTEM_CAPTUREEND         0x0009

	/*
	 * MSMove Size
	 * EVENT_SYSTEM_MOVESIZESTART
	 * EVENT_SYSTEM_MOVESIZEEND
	 * Sent when a window enters and leaves move-size dragging mode.
	 */
#define EVENT_SYSTEM_MOVESIZESTART      0x000A
#define EVENT_SYSTEM_MOVESIZEEND        0x000B

	/*
	 * Context Help
	 * EVENT_SYSTEM_CONTEXTHELPSTART
	 * EVENT_SYSTEM_CONTEXTHELPEND
	 * Sent when a window enters and leaves context sensitive help mode.
	 */
#define EVENT_SYSTEM_CONTEXTHELPSTART   0x000C
#define EVENT_SYSTEM_CONTEXTHELPEND     0x000D

	/*
	 * MSDrag & Drop
	 * EVENT_SYSTEM_DRAGDROPSTART
	 * EVENT_SYSTEM_DRAGDROPEND
	 * MSSend the START notification just before going into drag&drop loop.  MSSend
	 * the END notification just after canceling out.
	 * Note that it is up to apps and OLE to generate this, since the system
	 * doesn't know.  Like EVENT_SYSTEM_SOUND, it will be a while before this
	 * is prevalent.
	 */
#define EVENT_SYSTEM_DRAGDROPSTART      0x000E
#define EVENT_SYSTEM_DRAGDROPEND        0x000F

	/*
	 * Dialog
	 * MSSend the START notification right after the dialog is completely
	 *  initialized and visible.  MSSend the END right before the dialog
	 *  is hidden and goes away.
	 * EVENT_SYSTEM_DIALOGSTART
	 * EVENT_SYSTEM_DIALOGEND
	 */
#define EVENT_SYSTEM_DIALOGSTART        0x0010
#define EVENT_SYSTEM_DIALOGEND          0x0011

	/*
	 * EVENT_SYSTEM_SCROLLING
	 * EVENT_SYSTEM_SCROLLINGSTART
	 * EVENT_SYSTEM_SCROLLINGEND
	 * Sent when beginning and ending the tracking of a scrollbar in a window,
	 * and also for scrollbar controls.
	 */
#define EVENT_SYSTEM_SCROLLINGSTART     0x0012
#define EVENT_SYSTEM_SCROLLINGEND       0x0013

	/*
	 * Alt-Tab Window
	 * MSSend the START notification right after the switch window is initialized
	 * and visible.  MSSend the END right before it is hidden and goes away.
	 * EVENT_SYSTEM_SWITCHSTART
	 * EVENT_SYSTEM_SWITCHEND
	 */
#define EVENT_SYSTEM_SWITCHSTART        0x0014
#define EVENT_SYSTEM_SWITCHEND          0x0015

	/*
	 * EVENT_SYSTEM_MINIMIZESTART
	 * EVENT_SYSTEM_MINIMIZEEND
	 * Sent when a window minimizes and just before it restores.
	 */
#define EVENT_SYSTEM_MINIMIZESTART      0x0016
#define EVENT_SYSTEM_MINIMIZEEND        0x0017


#if(_WIN32_WINNT >= 0x0501)
#define EVENT_CONSOLE_CARET             0x4001
#define EVENT_CONSOLE_UPDATE_REGION     0x4002
#define EVENT_CONSOLE_UPDATE_SIMPLE     0x4003
#define EVENT_CONSOLE_UPDATE_SCROLL     0x4004
#define EVENT_CONSOLE_LAYOUT            0x4005
#define EVENT_CONSOLE_START_APPLICATION 0x4006
#define EVENT_CONSOLE_END_APPLICATION   0x4007

	/*
	 * Flags for EVENT_CONSOLE_START/END_APPLICATION.
	 */
#define CONSOLE_APPLICATION_16BIT       0x0001

	/*
	 * Flags for EVENT_CONSOLE_CARET
	 */
#define CONSOLE_CARET_SELECTION         0x0001
#define CONSOLE_CARET_VISIBLE           0x0002
#endif /* _WIN32_WINNT >= 0x0501 */

	/*
	 * Object events
	 *
	 * The system AND apps generate these.  The system generates these for
	 * real windows.  Apps generate these for objects within their window which
	 * act like a separate control, e.g. an item in a list view.
	 *
	 * When the system generate them, dwParam2 is always WMOBJID_SELF.  When
	 * apps generate them, apps put the has-meaning-to-the-app-only ID value
	 * in dwParam2.
	 * For all events, if you want detailed accessibility information, callers
	 * should
	 *      * MSCall AccessibleObjectFromWindow() with the hwnd, idObject parameters
	 *          of the event, and IID_IAccessible as the REFIID, to get back an
	 *          IAccessible* to talk to
	 *      * Initialize and fill in a VARIANT as VT_I4 with lVal the idChild
	 *          parameter of the event.
	 *      * If idChild isn't zero, call get_accChild() in the container to see
	 *          if the child is an object in its own right.  If so, you will get
	 *          back an IMSDispatch* object for the child.  You should release the
	 *          parent, and call QueryInterface() on the child object to get its
	 *          IAccessible*.  Then you talk directly to the child.  Otherwise,
	 *          if get_accChild() returns you nothing, you should continue to
	 *          use the child VARIANT.  You will ask the container for the properties
	 *          of the child identified by the VARIANT.  In other words, the
	 *          child in this case is accessible but not a full-blown object.
	 *          Like a button on a titlebar which is 'small' and has no children.
	 */

	/*
	 * For all EVENT_OBJECT events,
	 *      hwnd is the dude to MSSend the WM_GETOBJECT message to (unless NULL,
	 *          see above for system things)
	 *      idObject is the ID of the object that can resolve any queries a
	 *          client might have.  It's a way to deal with windowless controls,
	 *          controls that are just drawn on the screen in some larger parent
	 *          window (like SDM), or standard frame elements of a window.
	 *      idChild is the piece inside of the object that is affected.  This
	 *          allows clients to access things that are too small to have full
	 *          blown objects in their own right.  Like the thumb of a scrollbar.
	 *          The hwnd/idObject pair gets you to the container, the dude you
	 *          probably want to talk to most of the time anyway.  The idChild
	 *          can then be passed into the acc properties to get the name/value
	 *          of it as needed.
	 *
	 * Example #1:
	 *      MSSystem propagating a listbox selection change
	 *      EVENT_OBJECT_SELECTION
	 *          hwnd == listbox hwnd
	 *          idObject == OBJID_WINDOW
	 *          idChild == new selected item, or CHILDID_SELF if
	 *              nothing now selected within container.
	 *      Word '97 propagating a listbox selection change
	 *          hwnd == SDM window
	 *          idObject == SDM ID to get at listbox 'control'
	 *          idChild == new selected item, or CHILDID_SELF if
	 *              nothing
	 *
	 * Example #2:
	 *      MSSystem propagating a menu item selection on the menu bar
	 *      EVENT_OBJECT_SELECTION
	 *          hwnd == top level window
	 *          idObject == OBJID_MENU
	 *          idChild == ID of child menu bar item selected
	 *
	 * Example #3:
	 *      System propagating a dropdown coming off of said menu bar item
	 *      EVENT_OBJECT_CREATE
	 *          hwnd == popup item
	 *          idObject == OBJID_WINDOW
	 *          idChild == CHILDID_SELF
	 *
	 * Example #4:
	 *
	 * For EVENT_OBJECT_REORDER, the object referred to by hwnd/idObject is the
	 * PARENT container in which the zorder is occurring.  This is because if
	 * one child is zordering, all of them are changing their relative zorder.
	 */
#define EVENT_OBJECT_CREATE                 0x8000  // hwnd + ID + idChild is created item
#define EVENT_OBJECT_DESTROY                0x8001  // hwnd + ID + idChild is destroyed item
#define EVENT_OBJECT_SHOW                   0x8002  // hwnd + ID + idChild is shown item
#define EVENT_OBJECT_HIDE                   0x8003  // hwnd + ID + idChild is hidden item
#define EVENT_OBJECT_REORDER                0x8004  // hwnd + ID + idChild is parent of zordering children
	/*
	 * NOTE:
	 * Minimize the number of notifications!
	 *
	 * When you are hiding a parent object, obviously all child objects are no
	 * longer visible on screen.  They still have the same "visible" status,
	 * but are not truly visible.  Hence do not send HIDE notifications for the
	 * children also.  One implies all.  The same goes for SHOW.
	 */


#define EVENT_OBJECT_FOCUS                  0x8005  // hwnd + ID + idChild is focused item
#define EVENT_OBJECT_SELECTION              0x8006  // hwnd + ID + idChild is selected item (if only one), or idChild is OBJID_WINDOW if complex
#define EVENT_OBJECT_SELECTIONADD           0x8007  // hwnd + ID + idChild is item added
#define EVENT_OBJECT_SELECTIONREMOVE        0x8008  // hwnd + ID + idChild is item removed
#define EVENT_OBJECT_SELECTIONWITHIN        0x8009  // hwnd + ID + idChild is parent of changed selected items

	/*
	 * NOTES:
	 * There is only one "focused" child item in a parent.  This is the place
	 * keystrokes are going at a given moment.  Hence only send a notification
	 * about where the NEW focus is going.  A NEW item getting the focus already
	 * implies that the OLD item is losing it.
	 *
	 * SELECTION however can be multiple.  Hence the different SELECTION
	 * notifications.  Here's when to use each:
	 *
	 * (1) MSSend a SELECTION notification in the simple single selection
	 *     case (like the focus) when the item with the selection is
	 *     merely moving to a different item within a container.  hwnd + ID
	 *     is the container control, idChildItem is the new child with the
	 *     selection.
	 *
	 * (2) MSSend a SELECTIONADD notification when a new item has simply been added
	 *     to the selection within a container.  This is appropriate when the
	 *     number of newly selected items is very small.  hwnd + ID is the
	 *     container control, idChildItem is the new child added to the selection.
	 *
	 * (3) MSSend a SELECTIONREMOVE notification when a new item has simply been
	 *     removed from the selection within a container.  This is appropriate
	 *     when the number of newly selected items is very small, just like
	 *     SELECTIONADD.  hwnd + ID is the container control, idChildItem is the
	 *     new child removed from the selection.
	 *
	 * (4) MSSend a SELECTIONWITHIN notification when the selected items within a
	 *     control have changed substantially.  Rather than propagate a large
	 *     number of changes to reflect removal for some items, addition of
	 *     others, just tell somebody who cares that a lot happened.  It will
	 *     be faster an easier for somebody watching to just turn around and
	 *     query the container control what the new bunch of selected items
	 *     are.
	 */

#define EVENT_OBJECT_STATECHANGE            0x800A  // hwnd + ID + idChild is item w/ state change
	/*
	 * Examples of when to send an EVENT_OBJECT_STATECHANGE include
	 *      * It is being enabled/disabled (USER does for windows)
	 *      * It is being pressed/released (USER does for buttons)
	 *      * It is being checked/unchecked (USER does for radio/check buttons)
	 */
#define EVENT_OBJECT_LOCATIONCHANGE         0x800B  // hwnd + ID + idChild is moved/sized item

	/*
	 * Note:
	 * A LOCATIONCHANGE is not sent for every child object when the parent
	 * changes shape/moves.  MSSend one notification for the topmost object
	 * that is changing.  For example, if the user resizes a top level window,
	 * USER will generate a LOCATIONCHANGE for it, but not for the menu bar,
	 * title bar, scrollbars, etc.  that are also changing shape/moving.
	 *
	 * In other words, it only generates LOCATIONCHANGE notifications for
	 * real windows that are moving/sizing.  It will not generate a LOCATIONCHANGE
	 * for every non-floating child window when the parent moves (the children are
	 * logically moving also on screen, but not relative to the parent).
	 *
	 * Now, if the app itself resizes child windows as a result of being
	 * sized, USER will generate LOCATIONCHANGEs for those dudes also because
	 * it doesn't know better.
	 *
	 * Note also that USER will generate LOCATIONCHANGE notifications for two
	 * non-window sys objects:
	 *      (1) System caret
	 *      (2) Cursor
	 */

#define EVENT_OBJECT_NAMECHANGE             0x800C  // hwnd + ID + idChild is item w/ name change
#define EVENT_OBJECT_DESCRIPTIONCHANGE      0x800D  // hwnd + ID + idChild is item w/ desc change
#define EVENT_OBJECT_VALUECHANGE            0x800E  // hwnd + ID + idChild is item w/ value change
#define EVENT_OBJECT_PARENTCHANGE           0x800F  // hwnd + ID + idChild is item w/ new parent
#define EVENT_OBJECT_HELPCHANGE             0x8010  // hwnd + ID + idChild is item w/ help change
#define EVENT_OBJECT_DEFACTIONCHANGE        0x8011  // hwnd + ID + idChild is item w/ def action change
#define EVENT_OBJECT_ACCELERATORCHANGE      0x8012  // hwnd + ID + idChild is item w/ keybd accel change

	/*
	 * Child IDs
	 */

	/*
	 * System Sounds (idChild of system SOUND notification)
	 */
#define SOUND_SYSTEM_STARTUP            1
#define SOUND_SYSTEM_SHUTDOWN           2
#define SOUND_SYSTEM_BEEP               3
#define SOUND_SYSTEM_ERROR              4
#define SOUND_SYSTEM_QUESTION           5
#define SOUND_SYSTEM_WARNING            6
#define SOUND_SYSTEM_INFORMATION        7
#define SOUND_SYSTEM_MAXIMIZE           8
#define SOUND_SYSTEM_MINIMIZE           9
#define SOUND_SYSTEM_RESTOREUP          10
#define SOUND_SYSTEM_RESTOREDOWN        11
#define SOUND_SYSTEM_APPSTART           12
#define SOUND_SYSTEM_FAULT              13
#define SOUND_SYSTEM_APPEND             14
#define SOUND_SYSTEM_MENUCOMMAND        15
#define SOUND_SYSTEM_MENUPOPUP          16
#define MSOUND_SYSTEM                   16

	/*
	 * System Alerts (indexChild of system ALERT notification)
	 */
#define ALERT_SYSTEM_INFORMATIONAL      1       // MB_INFORMATION
#define ALERT_SYSTEM_WARNING            2       // MB_WARNING
#define ALERT_SYSTEM_ERROR              3       // MB_ERROR
#define ALERT_SYSTEM_QUERY              4       // MB_QUESTION
#define ALERT_SYSTEM_CRITICAL           5       // HardSysErrBox
#define CALERT_SYSTEM                   6

	typedef struct tagMSGUITHREADINFO
	{
		DWORD   cbSize;
		DWORD   flags;
		HMSWND    hwndActive;
		HMSWND    hwndFocus;
		HMSWND    hwndCapture;
		HMSWND    hwndMenuOwner;
		HMSWND    hwndMoveSize;
		HMSWND    hwndCaret;
		MSRECT    rcCaret;
	} MSGUITHREADINFO, *PMSGUITHREADINFO, FAR * LPMSGUITHREADINFO;

#define GUI_CARETBLINKING   0x00000001
#define GUI_INMOVESIZE      0x00000002
#define GUI_INMENUMODE      0x00000004
#define GUI_SYSTEMMENUMODE  0x00000008
#define GUI_POPUPMENUMODE   0x00000010
#if(_WIN32_WINNT >= 0x0501)
#define GUI_16BITTASK       0x00000020
#endif /* _WIN32_WINNT >= 0x0501 */

	 
		BOOL
		WINAPI
		MSGetGUIThreadInfo(
		IN DWORD idThread,
		OUT PMSGUITHREADINFO pgui );

	 
		UINT
		WINAPI
		MSGetWindowModuleFileName(
		IN HMSWND     hwnd,
		OUT LPTSTR pszFileName,
		IN UINT     cchFileNameMax );

#ifndef NO_STATE_FLAGS
#define STATE_SYSTEM_UNAVAILABLE        0x00000001  // Disabled
#define STATE_SYSTEM_SELECTED           0x00000002
#define STATE_SYSTEM_FOCUSED            0x00000004
#define STATE_SYSTEM_PRESSED            0x00000008
#define STATE_SYSTEM_CHECKED            0x00000010
#define STATE_SYSTEM_MIXED              0x00000020  // 3-state checkbox or toolbar button
#define STATE_SYSTEM_INDETERMINATE      STATE_SYSTEM_MIXED
#define STATE_SYSTEM_READONLY           0x00000040
#define STATE_SYSTEM_HOTTRACKED         0x00000080
#define STATE_SYSTEM_DEFAULT            0x00000100
#define STATE_SYSTEM_EXPANDED           0x00000200
#define STATE_SYSTEM_COLLAPSED          0x00000400
#define STATE_SYSTEM_BUSY               0x00000800
#define STATE_SYSTEM_FLOATING           0x00001000  // Children "owned" not "contained" by parent
#define STATE_SYSTEM_MARQUEED           0x00002000
#define STATE_SYSTEM_ANIMATED           0x00004000
#define STATE_SYSTEM_INVISIBLE          0x00008000
#define STATE_SYSTEM_OFFSCREEN          0x00010000
#define STATE_SYSTEM_SIZEABLE           0x00020000
#define STATE_SYSTEM_MOVEABLE           0x00040000
#define STATE_SYSTEM_SELFVOICING        0x00080000
#define STATE_SYSTEM_FOCUSABLE          0x00100000
#define STATE_SYSTEM_SELECTABLE         0x00200000
#define STATE_SYSTEM_LINKED             0x00400000
#define STATE_SYSTEM_TRAVERSED          0x00800000
#define STATE_SYSTEM_MULTISELECTABLE    0x01000000  // Supports multiple selection
#define STATE_SYSTEM_EXTSELECTABLE      0x02000000  // Supports extended selection
#define STATE_SYSTEM_ALERT_LOW          0x04000000  // This information is of low priority
#define STATE_SYSTEM_ALERT_MEDIUM       0x08000000  // This information is of medium priority
#define STATE_SYSTEM_ALERT_HIGH         0x10000000  // This information is of high priority
#define STATE_SYSTEM_PROTECTED          0x20000000  // access to this is restricted
#define STATE_SYSTEM_VALID              0x3FFFFFFF
#endif

#define CCHILDREN_TITLEBAR              5
#define CCHILDREN_SCROLLBAR             5

	/*
	 * Information about the global cursor.
	 */
	typedef struct tagMSCURSORINFO
	{
		DWORD   cbSize;
		DWORD   flags;
		HMSCURSOR hCursor;
		MSPOINT   ptScreenPos;
	} MSCURSORINFO, *PMSCURSORINFO, *LPMSCURSORINFO;

#define CURSOR_SHOWING     0x00000001

	 
		BOOL
		WINAPI
		MSGetCursorInfo(
		OUT PMSCURSORINFO pci
		);

	/*
	 * Window information snapshot
	 */
	typedef struct tagMSWINDOWINFO
	{
		DWORD cbSize;
		MSRECT  rcWindow;
		MSRECT  rcClient;
		DWORD dwStyle;
		DWORD dwExStyle;
		DWORD dwWindowStatus;
		UINT  cxWindowBorders;
		UINT  cyWindowBorders;
		ATOM  atomWindowType;
		WORD  wCreatorVersion;
	} MSWINDOWINFO, *PMSWINDOWINFO, *LPMSWINDOWINFO;

#define WS_ACTIVECAPTION    0x0001

	 
		BOOL
		WINAPI
		MSGetWindowInfo(
		IN HMSWND hwnd,
		OUT PMSWINDOWINFO pwi
		);

	/*
	 * Titlebar information.
	 */
	typedef struct tagMSTITLEBARINFO
	{
		DWORD cbSize;
		MSRECT  rcTitleBar;
		DWORD rgstate[ CCHILDREN_TITLEBAR + 1 ];
	} MSTITLEBARINFO, *PMSTITLEBARINFO, *LPMSTITLEBARINFO;

	 
		BOOL
		WINAPI
		MSGetTitleBarInfo(
		IN HMSWND hwnd,
		OUT PMSTITLEBARINFO pti
		);

	/*
	 * Menubar information
	 */
	typedef struct tagMSMENUBARINFO
	{
		DWORD cbSize;
		MSRECT  rcBar;          // rect of bar, popup, item
		HMSMENU hMenu;          // real menu handle of bar, popup
		HMSWND  hwndMenu;       // hwnd of item submenu if one
		BOOL  fBarFocused : 1;  // bar, popup has the focus
		BOOL  fFocused : 1;     // item has the focus
	} MSMENUBARINFO, *PMSMENUBARINFO, *LPMSMENUBARINFO;

	 
		BOOL
		WINAPI
		MSGetMenuBarInfo(
		IN HMSWND hwnd,
		IN LONG idObject,
		IN LONG idItem,
		OUT PMSMENUBARINFO pmbi
		);

	/*
	 * Scrollbar information
	 */
	typedef struct tagMSSCROLLBARINFO
	{
		DWORD cbSize;
		MSRECT  rcScrollBar;
		int   dxyLineButton;
		int   xyThumbTop;
		int   xyThumbBottom;
		int   reserved;
		DWORD rgstate[ CCHILDREN_SCROLLBAR + 1 ];
	} MSSCROLLBARINFO, *PMSSCROLLBARINFO, *LPMSSCROLLBARINFO;

	 
		BOOL
		WINAPI
		MSGetScrollBarInfo(
		IN HMSWND hwnd,
		IN LONG idObject,
		OUT PMSSCROLLBARINFO psbi
		);

	/*
	 * Combobox information
	 */
	typedef struct tagMSCOMBOBOXINFO
	{
		DWORD cbSize;
		MSRECT  rcItem;
		MSRECT  rcButton;
		DWORD stateButton;
		HMSWND  hwndCombo;
		HMSWND  hwndItem;
		HMSWND  hwndList;
	} MSCOMBOBOXINFO, *PMSCOMBOBOXINFO, *LPMSCOMBOBOXINFO;

	 
		BOOL
		WINAPI
		MSGetComboBoxInfo(
		IN HMSWND hwndCombo,
		OUT PMSCOMBOBOXINFO pcbi
		);

	/*
	 * The "real" ancestor window
	 */
#define     GA_PARENT       1
#define     GA_ROOT         2
#define     GA_ROOTOWNER    3

	 
		HMSWND
		WINAPI
		MSGetAncestor(
		IN HMSWND hwnd,
		IN UINT gaFlags
		);


	/*
	 * This gets the REAL child window at the point.  If it is in the dead
	 * space of a group box, it will try a sibling behind it.  But static
	 * fields will get returned.  In other words, it is kind of a cross between
	 * ChildWindowFromPointEx and WindowFromPoint.
	 */
	 
		HMSWND
		WINAPI
		MSRealChildWindowFromPoint(
		IN HMSWND hwndParent,
		IN MSPOINT ptParentClientCoords
		);


	/*
	 * This gets the name of the window TYPE, not class.  This allows us to
	 * recognize ThunderButton32 et al.
	 */
	 
		UINT
		WINAPI
		MSRealGetWindowClass(
		IN HMSWND  hwnd,
		OUT LPTSTR pszType,
		IN UINT  cchType
		);
	/*
	 * This gets the name of the window TYPE, not class.  This allows us to
	 * recognize ThunderButton32 et al.
	 */

	/*
	 * Alt-Tab MSSwitch window information.
	 */
	typedef struct tagMSALTTABINFO
	{
		DWORD cbSize;
		int   cItems;
		int   cColumns;
		int   cRows;
		int   iColFocus;
		int   iRowFocus;
		int   cxItem;
		int   cyItem;
		MSPOINT ptStart;
	} MSALTTABINFO, *PMSALTTABINFO, *LPMSALTTABINFO;

	 
		BOOL
		WINAPI
		MSGetAltTabInfo(
		IN HMSWND hwnd,
		IN int iItem,
		OUT PMSALTTABINFO pati,
		OUT LPTSTR pszItemText,
		IN UINT cchItemText
		);

	/*
	 * Listbox information.
	 * Returns the number of items per row.
	 */
	 
		DWORD
		WINAPI
		MSGetListBoxInfo(
		IN HMSWND hwnd
		);

#endif /* NOWINABLE */
#endif /* WINVER >= 0x0500 */


#if(_WIN32_WINNT >= 0x0500)
	 
		BOOL
		WINAPI
		MSLockWorkStation(
		void );
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0500)

	 
		BOOL
		WINAPI
		MSUserHandleGrantAccess(
		HMSHANDLE hUserHandle,
		HMSHANDLE hJob,
		BOOL   bGrant );

#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)

	/*
	 * Raw Input Messages.
	 */


	/*
	 * WM_INPUT wParam
	 */

	/*
	 * Use this macro to get the input code from wParam.
	 */
#define GET_RAWINPUT_CODE_WPARAM(wParam)    ((wParam) & 0xff)

	/*
	 * The input is in the regular message flow,
	 * the app is required to call DefWindowProc
	 * so that the system can perform clean ups.
	 */
#define RIM_INPUT       0

	/*
	 * The input is sink only. The app is expected
	 * to behave nicely, honoring RIM_FOREGROUND etc.
	 */
#define RIM_INPUTSINK   1


	/*
	 * Raw Input data header
	 */
	typedef struct tagMSRAWINPUTHEADER {
		DWORD dwType;
		DWORD dwSize;
		HMSHANDLE hDevice;
		WPARAM wParam;
	} MSRAWINPUTHEADER, *PMSRAWINPUTHEADER, *LPMSRAWINPUTHEADER;

	/*
	 * Type of the raw input
	 */
#define RIM_TYPEMOUSE       0
#define RIM_TYPEKEYBOARD    1
#define RIM_TYPEHID         2

	/*
	 * Raw format of the mouse input
	 */
	typedef struct tagMSRAWMOUSE {
		/*
		 * Indicator flags.
		 */
		USHORT usFlags;

		/*
		 * The transition state of the mouse buttons.
		 */
		union {
			ULONG ulButtons;
			struct  {
				USHORT  usButtonFlags;
				USHORT  usButtonData;
			}u;
		}u1;


		/*
		 * The raw state of the mouse buttons.
		 */
		ULONG ulRawButtons;

		/*
		 * The signed relative or absolute motion in the X direction.
		 */
		LONG lLastX;

		/*
		 * The signed relative or absolute motion in the Y direction.
		 */
		LONG lLastY;

		/*
		 * Device-specific additional information for the event.
		 */
		ULONG ulExtraInformation;

	} MSRAWMOUSE, *PMSRAWMOUSE, *LPMSRAWMOUSE;

	/*
	 * Define the mouse button state indicators.
	 */

#define RI_MOUSE_LEFT_BUTTON_DOWN   0x0001  // Left Button changed to down.
#define RI_MOUSE_LEFT_BUTTON_UP     0x0002  // Left Button changed to up.
#define RI_MOUSE_RIGHT_BUTTON_DOWN  0x0004  // Right Button changed to down.
#define RI_MOUSE_RIGHT_BUTTON_UP    0x0008  // Right Button changed to up.
#define RI_MOUSE_MIDDLE_BUTTON_DOWN 0x0010  // Middle Button changed to down.
#define RI_MOUSE_MIDDLE_BUTTON_UP   0x0020  // Middle Button changed to up.

#define RI_MOUSE_BUTTON_1_DOWN      RI_MOUSE_LEFT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_1_UP        RI_MOUSE_LEFT_BUTTON_UP
#define RI_MOUSE_BUTTON_2_DOWN      RI_MOUSE_RIGHT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_2_UP        RI_MOUSE_RIGHT_BUTTON_UP
#define RI_MOUSE_BUTTON_3_DOWN      RI_MOUSE_MIDDLE_BUTTON_DOWN
#define RI_MOUSE_BUTTON_3_UP        RI_MOUSE_MIDDLE_BUTTON_UP

#define RI_MOUSE_BUTTON_4_DOWN      0x0040
#define RI_MOUSE_BUTTON_4_UP        0x0080
#define RI_MOUSE_BUTTON_5_DOWN      0x0100
#define RI_MOUSE_BUTTON_5_UP        0x0200

	/*
	 * If usButtonFlags has RI_MOUSE_WHEEL, the wheel delta is stored in usButtonData.
	 * Take it as a signed value.
	 */
#define RI_MOUSE_WHEEL              0x0400

	/*
	 * Define the mouse indicator flags.
	 */
#define MOUSE_MOVE_RELATIVE         0
#define MOUSE_MOVE_ABSOLUTE         1
#define MOUSE_VIRTUAL_DESKTOP    0x02  // the coordinates are mapped to the virtual desktop
#define MOUSE_ATTRIBUTES_CHANGED 0x04  // requery for mouse attributes


	/*
	 * Raw format of the keyboard input
	 */
	typedef struct tagMSRAWKEYBOARD {
		/*
		 * The "make" scan code (key depression).
		 */
		USHORT MakeCode;

		/*
		 * The flags field indicates a "break" (key release) and other
		 * miscellaneous scan code information defined in ntddkbd.h.
		 */
		USHORT Flags;

		USHORT Reserved;

		/*
		 * Windows message compatible information
		 */
		USHORT VKey;
		UINT   Message;

		/*
		 * Device-specific additional information for the event.
		 */
		ULONG ExtraInformation;


	} MSRAWKEYBOARD, *PMSRAWKEYBOARD, *LPMSRAWKEYBOARD;


	/*
	 * Define the keyboard overrun MakeCode.
	 */

#define KEYBOARD_OVERRUN_MAKE_CODE    0xFF

	/*
	 * Define the keyboard input data Flags.
	 */
#define RI_KEY_MAKE             0
#define RI_KEY_BREAK            1
#define RI_KEY_E0               2
#define RI_KEY_E1               4
#define RI_KEY_TERMSRV_SET_LED  8
#define RI_KEY_TERMSRV_SHADOW   0x10


	/*
	 * Raw format of the input from Human Input Devices
	 */
	typedef struct tagMSRAWHID {
		DWORD dwSizeHid;    // byte size of each report
		DWORD dwCount;      // number of input packed
		BYTE bRawData[ 1 ];
	} MSRAWHID, *PMSRAWHID, *LPMSRAWHID;

	/*
	 * MSRAWINPUT data structure.
	 */
	typedef struct tagMSRAWINPUT {
		MSRAWINPUTHEADER header;
		union {
			MSRAWMOUSE    mouse;
			MSRAWKEYBOARD keyboard;
			MSRAWHID      hid;
		} data;
	} MSRAWINPUT, *PMSRAWINPUT, *LPMSRAWINPUT;

#ifdef _WIN64
#define RAWINPUT_ALIGN(x)   (((x) + sizeof(QWORD) - 1) & ~(sizeof(QWORD) - 1))
#else   // _WIN64
#define RAWINPUT_ALIGN(x)   (((x) + sizeof(DWORD) - 1) & ~(sizeof(DWORD) - 1))
#endif  // _WIN64
#undef NEXTRAWINPUTBLOCK
#define NEXTRAWINPUTBLOCK(ptr) ((PMSRAWINPUT)RAWINPUT_ALIGN((ULONG_PTR)((PBYTE)(ptr) + (ptr)->header.dwSize)))

	/*
	 * Flags for MSGetRawInputData
	 */

#define RID_INPUT               0x10000003
#define RID_HEADER              0x10000005

	 
		UINT
		WINAPI
		MSGetRawInputData(
		IN HMSRAWINPUT    hRawInput,
		IN UINT         uiCommand,
		OUT LPVOID      pData,
		IN OUT PUINT    pcbSize,
		IN UINT         cbSizeHeader );

	/*
	 * Raw Input Device Information
	 */
#define RIDI_PREPARSEDDATA      0x20000005
#define RIDI_DEVICENAME         0x20000007  // the return valus is the character length, not the byte size
#define RIDI_DEVICEINFO         0x2000000b

	typedef struct tagMSRID_DEVICE_INFO_MOUSE {
		DWORD dwId;
		DWORD dwNumberOfButtons;
		DWORD dwSampleRate;
	} MSRID_DEVICE_INFO_MOUSE, *PMSRID_DEVICE_INFO_MOUSE;

	typedef struct tagMSRID_DEVICE_INFO_KEYBOARD {
		DWORD dwType;
		DWORD dwSubType;
		DWORD dwKeyboardMode;
		DWORD dwNumberOfFunctionKeys;
		DWORD dwNumberOfIndicators;
		DWORD dwNumberOfKeysTotal;
	} MSRID_DEVICE_INFO_KEYBOARD, *PMSRID_DEVICE_INFO_KEYBOARD;

	typedef struct tagMSRID_DEVICE_INFO_HID {
		DWORD dwVendorId;
		DWORD dwProductId;
		DWORD dwVersionNumber;

		/*
		 * Top level collection UsagePage and Usage
		 */
		USHORT usUsagePage;
		USHORT usUsage;
	} MSRID_DEVICE_INFO_HID, *PMSRID_DEVICE_INFO_HID;

	typedef struct tagMSRID_DEVICE_INFO {
		DWORD cbSize;
		DWORD dwType;
		union {
			MSRID_DEVICE_INFO_MOUSE mouse;
			MSRID_DEVICE_INFO_KEYBOARD keyboard;
			MSRID_DEVICE_INFO_HID hid;
		}u;
	} MSRID_DEVICE_INFO, *PMSRID_DEVICE_INFO, *LPMSRID_DEVICE_INFO;

	 
		UINT
		WINAPI
		MSGetRawInputDeviceInfo(
		IN HMSHANDLE hDevice,
		IN UINT uiCommand,
		OUT LPVOID pData,
		IN OUT PUINT pcbSize );


	/*
	 * Raw Input Bulk Read: MSGetRawInputBuffer
	 */
	 
		UINT
		WINAPI
		MSGetRawInputBuffer(
		OUT PMSRAWINPUT   pData,
		IN OUT PUINT    pcbSize,
		IN UINT         cbSizeHeader );

	/*
	 * Raw Input request APCSIs
	 */
	typedef struct tagMSRAWINPUTDEVICE {
		USHORT usUsagePage; // Toplevel collection UsagePage
		USHORT usUsage;     // Toplevel collection Usage
		DWORD dwFlags;
		HMSWND hwndTarget;    // Target hwnd. NULL = follows keyboard focus
	} MSRAWINPUTDEVICE, *PMSRAWINPUTDEVICE, *LPMSRAWINPUTDEVICE;

	typedef CONST MSRAWINPUTDEVICE* PCMSRAWINPUTDEVICE;

#define RIDEV_REMOVE            0x00000001
#define RIDEV_EXCLUDE           0x00000010
#define RIDEV_PAGEONLY          0x00000020
#define RIDEV_NOLEGACY          0x00000030
#define RIDEV_CAPTUREMOUSE      0x00000200  // effective when mouse nolegacy is specified, otherwise it would be an error
#define RIDEV_NOHOTKEYS         0x00000200  // effective for keyboard.
#define RIDEV_EXMODEMASK        0x000000F0

#define RIDEV_EXMODE(mode)  ((mode) & RIDEV_EXMODEMASK)

	 
		BOOL
		WINAPI
		MSRegisterRawInputDevices(
		IN PCMSRAWINPUTDEVICE pRawInputDevices,
		IN UINT uiNumDevices,
		IN UINT cbSize );

	 
		UINT
		WINAPI
		MSGetRegisteredRawInputDevices(
		OUT PMSRAWINPUTDEVICE pRawInputDevices,
		IN OUT PUINT puiNumDevices,
		IN UINT cbSize );


	typedef struct tagMSRAWINPUTDEVICELIST {
		HMSHANDLE hDevice;
		DWORD dwType;
	} MSRAWINPUTDEVICELIST, *PMSRAWINPUTDEVICELIST;

	 
		UINT
		WINAPI
		MSGetRawInputDeviceList(
		OUT PMSRAWINPUTDEVICELIST pRawInputDeviceList,
		IN OUT PUINT puiNumDevices,
		IN UINT cbSize );


	 
		LRESULT
		WINAPI
		MSDefRawInputProc(
		IN PMSRAWINPUT* paRawInput,
		IN INT nInput,
		IN UINT cbSizeHeader );


#endif /* _WIN32_WINNT >= 0x0501 */




#if !defined(RC_INVOKED) /* RC complains about long symbols in #ifs */
#if ISOLATION_AWARE_ENABLED
#include "winuser.inl"
#endif /* ISOLATION_AWARE_ENABLED */
#endif /* RC */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* !_WINUSER_ */





