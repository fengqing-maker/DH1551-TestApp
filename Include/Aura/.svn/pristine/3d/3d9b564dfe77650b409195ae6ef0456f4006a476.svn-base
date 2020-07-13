
/*****************************************************************************\
*                                                                             *
* commctrl.h - - Interface for the Windows Common Controls                    *
*                                                                             *
* Version 1.2                                                                 *
*                                                                             *
* Copyright (c) CastPal Corporation. All rights reserved.                   *
*                                                                             *
\*****************************************************************************/




#ifndef _MSCOMMCTRL_H
#define _MSCOMMCTRL_H

#ifndef _WINRESRC_
#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#else
#if (_WIN32_IE < 0x0400) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0500)
#error _WIN32_IE setting conflicts with _WIN32_WINNT setting
#endif
#endif
#endif

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;
#endif // _HRESULT_DEFINED

#ifndef NOUSER

#ifdef __cplusplus
extern "C" {
#endif

//
// Users of this header may define any number of these constants to avoid
// the definitions of each functional group.
//
//    NOTOOLBAR    Customizable bitmap-button toolbar control.
//    NOUPDOWN     Up and Down arrow increment/decrement control.
//    NOSTATUSBAR  Status bar control.
//    NOMENUHELP   APIs to help manage menus, especially with a status bar.
//    NOTRACKBAR   Customizable column-width tracking control.
//    NODRAGLIST   APIs to make a listbox source and sink drag&drop actions.
//    NOPROGRESS   Progress gas gauge.
//    NOHOTKEY     HotKey control
//    NOHEADER     Header bar control.
//    NOIMAGEAPIS  ImageList apis.
//    NOLISTVIEW   ListView control.
//    NOTREEVIEW   TreeView control.
//    NOTABCONTROL Tab control.
//    NOANIMATE    Animate control.
//    NOBUTTON     Button control.
//    NOSTATIC     Static control.
//    NOEDIT       Edit control.
//    NOLISTBOX    Listbox control.
//    NOCOMBOBOX   Combobox control.
//    NOSCROLLBAR  Scrollbar control.
//
//=============================================================================

//#include <prsht.h>
#undef SNDMSG
#define SNDMSG MSSendMessage

void WINAPI CSInitCommonControls(void);

#if (_WIN32_IE >= 0x0300)
typedef struct tagMSINITCOMMONCONTROLSEX {
    DWORD dwSize;             // size of this structure
    DWORD dwICC;              // flags indicating which classes to be initialized
} MSINITCOMMONCONTROLSEX, *LPMSINITCOMMONCONTROLSEX;
#define ICC_LISTVIEW_CLASSES   0x00000001 // listview, header
#define ICC_TREEVIEW_CLASSES   0x00000002 // treeview, tooltips
#define ICC_BAR_CLASSES        0x00000004 // toolbar, statusbar, trackbar, tooltips
#define ICC_TAB_CLASSES        0x00000008 // tab, tooltips
#define ICC_UPDOWN_CLASS       0x00000010 // updown
#define ICC_PROGRESS_CLASS     0x00000020 // progress
#define ICC_HOTKEY_CLASS       0x00000040 // hotkey
#define ICC_ANIMATE_CLASS      0x00000080 // animate
#define ICC_WIN95_CLASSES      0x000000FF
#define ICC_DATE_CLASSES       0x00000100 // month picker, date picker, time picker, updown
#define ICC_USEREX_CLASSES     0x00000200 // comboex
#define ICC_COOL_CLASSES       0x00000400 // rebar (coolbar) control
#if (_WIN32_IE >= 0x0400)
#define ICC_INTERNET_CLASSES   0x00000800
#define ICC_PAGESCROLLER_CLASS 0x00001000   // page scroller
#define ICC_NATIVEFNTCTL_CLASS 0x00002000   // native font control
#endif
#if (_WIN32_WINNT >= 0x501)
#define ICC_STANDARD_CLASSES   0x00004000
#define ICC_LINK_CLASS         0x00008000
#endif


BOOL WINAPI MSInitCommonControlsEx( LPMSINITCOMMONCONTROLSEX );
#endif      // _WIN32_IE >= 0x0300

#define ODT_HEADER              100
#define ODT_TAB                 101
#define ODT_LISTVIEW            102


//====== Ranges for control message IDs =======================================

#define LVM_FIRST               0x1000      // ListView messages
#define TV_FIRST                0x1100      // TreeView messages
#define HDM_FIRST               0x1200      // Header messages
#define TCM_FIRST               0x1300      // Tab control messages

#if (_WIN32_IE >= 0x0400)
#define PGM_FIRST               0x1400      // Pager control messages
#define ECM_FIRST               0x1500      // Edit control messages
#define BCM_FIRST               0x1600      // Button control messages
#define CBM_FIRST               0x1700      // Combobox control messages
#define CCM_FIRST               0x2000      // Common control shared messages
#define CCM_LAST                (CCM_FIRST + 0x200)


#define CCM_SETBKCOLOR          (CCM_FIRST + 1) // lParam is bkColor

typedef struct tagMSCOLORSCHEME {
   DWORD            dwSize;
   COLORREF         clrBtnHighlight;       // highlight color
   COLORREF         clrBtnShadow;          // shadow color
} MSCOLORSCHEME, *LPMSCOLORSCHEME;

#define CCM_SETCOLORSCHEME      (CCM_FIRST + 2) // lParam is color scheme
#define CCM_GETCOLORSCHEME      (CCM_FIRST + 3) // fills in COLORSCHEME pointed to by lParam
#define CCM_GETDROPTARGET       (CCM_FIRST + 4)
#define CCM_SETUNICODEFORMAT    (CCM_FIRST + 5)
#define CCM_GETUNICODEFORMAT    (CCM_FIRST + 6)

#if (_WIN32_IE >= 0x0500)
#if (_WIN32_WINNT >= 0x501)
#define COMCTL32_VERSION  6
#else
#define COMCTL32_VERSION  5
#endif

#define CCM_SETVERSION          (CCM_FIRST + 0x7)
#define CCM_GETVERSION          (CCM_FIRST + 0x8)
#define CCM_SETNOTIFYWINDOW     (CCM_FIRST + 0x9) // wParam == hwndParent.
#if (_WIN32_WINNT >= 0x501)
#define CCM_SETWINDOWTHEME      (CCM_FIRST + 0xb)
#define CCM_DPISCALE            (CCM_FIRST + 0xc) // wParam == Awareness
#endif 
#endif // (_WIN32_IE >= 0x0500)

#endif // (_WIN32_IE >= 0x0400)

#if (_WIN32_IE >= 0x0400)
// for tooltips
#define INFOTIPSIZE 1024
#endif
/*
//====== WM_NOTIFY Macros =====================================================

#define HANDLE_WM_NOTIFY(hwnd, wParam, lParam, fn) \
    (fn)((hwnd), (int)(wParam), (MSNMHDR *)(lParam))
#define FORWARD_WM_NOTIFY(hwnd, idFrom, pnmhdr, fn) \
    (LRESULT)(fn)((hwnd), WM_NOTIFY, (WPARAM)(int)(idFrom), (LPARAM)(MSNMHDR *)(pnmhdr))

*/
//====== Generic WM_NOTIFY notification codes =================================

#define NM_OUTOFMEMORY          (NM_FIRST-1)
#define NM_CLICK                (NM_FIRST-2)    // uses NMCLICK struct
#define NM_DBLCLK               (NM_FIRST-3)
#define NM_RETURN               (NM_FIRST-4)
#define NM_RCLICK               (NM_FIRST-5)    // uses NMCLICK struct
#define NM_RDBLCLK              (NM_FIRST-6)
#define NM_SETFOCUS             (NM_FIRST-7)
#define NM_KILLFOCUS            (NM_FIRST-8)
#if (_WIN32_IE >= 0x0300)
#define NM_CUSTOMDRAW           (NM_FIRST-12)
#define NM_HOVER                (NM_FIRST-13)
#endif
#if (_WIN32_IE >= 0x0400)
#define NM_NCHITTEST            (NM_FIRST-14)   // uses MSNMMOUSE struct
#define NM_KEYDOWN              (NM_FIRST-15)   // uses MSNMKEY struct
#define NM_RELEASEDCAPTURE      (NM_FIRST-16)
#define NM_SETCURSOR            (NM_FIRST-17)   // uses MSNMMOUSE struct
#define NM_CHAR                 (NM_FIRST-18)   // uses MSNMCHAR struct
#endif
#if (_WIN32_IE >= 0x0401)
#define NM_TOOLTIPSCREATED      (NM_FIRST-19)   // notify of when the tooltips window is create
#endif
#if (_WIN32_IE >= 0x0500)
#define NM_LDOWN                (NM_FIRST-20)
#define NM_RDOWN                (NM_FIRST-21)
#define NM_THEMECHANGED         (NM_FIRST-22)
#endif

#ifndef CCSIZEOF_STRUCT
#define CCSIZEOF_STRUCT(structname, member)  (((int)((LPBYTE)(&((structname*)0)->member) - ((LPBYTE)((structname*)0)))) + sizeof(((structname*)0)->member))
#endif

//====== Generic WM_NOTIFY notification structures ============================
#if (_WIN32_IE >= 0x0401)
#if 0
typedef struct tagNMTOOLTIPSCREATED
{
    MSNMHDR hdr;
    HMSWND hwndToolTips;
} NMTOOLTIPSCREATED, * LPNMTOOLTIPSCREATED;
#endif
#endif

#if (_WIN32_IE >= 0x0400)
typedef struct tagMSNMMOUSE {
    MSNMHDR   hdr;
    DWORD_PTR dwItemSpec;
    DWORD_PTR dwItemData;
    MSPOINT   pt;
    LPARAM  dwHitInfo; // any specifics about where on the item or control the mouse is
} MSNMMOUSE, *LPMSNMMOUSE;

typedef MSNMMOUSE MSNMCLICK;
typedef LPMSNMMOUSE LPMSNMCLICK;

// Generic structure to request an object of a specific type.

typedef struct tagMSNMOBJECTNOTIFY {
    MSNMHDR   hdr;
    int     iItem;
#ifdef __IID_DEFINED__
    const IID *piid;
#else
    const void *piid;
#endif
    void *pObject;
    HRESULT hResult;
    DWORD dwFlags;    // control specific flags (hints as to where in iItem it hit)
} MSNMOBJECTNOTIFY, *LPMSNMOBJECTNOTIFY;

// Generic structure for a key

typedef struct tagMSNMKEY
{
    MSNMHDR hdr;
    UINT  nVKey;
    UINT  uFlags;
} MSNMKEY, *LPMSNMKEY;

// Generic structure for a character

typedef struct tagMSNMCHAR {
    MSNMHDR   hdr;
    UINT    ch;
    DWORD   dwItemPrev;     // Item previously selected
    DWORD   dwItemNext;     // Item to be selected
} MSNMCHAR, *LPMSNMCHAR;

#endif           // _WIN32_IE >= 0x0400

//====== WM_NOTIFY codes (MSNMHDR.code values) ==================================

#define NM_FIRST                (0U-  0U)       // generic to all controls
#define NM_LAST                 (0U- 99U)

#define LVN_FIRST               (0U-100U)       // listview
#define LVN_LAST                (0U-199U)

// Property sheet reserved      (0U-200U) -  (0U-299U) - see prsht.h

#define HDN_FIRST               (0U-300U)       // header
#define HDN_LAST                (0U-399U)

#define TVN_FIRST               (0U-400U)       // treeview
#define TVN_LAST                (0U-499U)

#define TTN_FIRST               (0U-520U)       // tooltips
#define TTN_LAST                (0U-549U)

#define TCN_FIRST               (0U-550U)       // tab control
#define TCN_LAST                (0U-580U)

// Shell reserved               (0U-580U) -  (0U-589U)

#define CDN_FIRST               (0U-601U)       // common dialog (new)
#define CDN_LAST                (0U-699U)

#define TBN_FIRST               (0U-700U)       // toolbar
#define TBN_LAST                (0U-720U)

#define UDN_FIRST               (0U-721)        // updown
#define UDN_LAST                (0U-740)
#if (_WIN32_IE >= 0x0300)
#define MCN_FIRST               (0U-750U)       // monthcal
#define MCN_LAST                (0U-759U)

#define DTN_FIRST               (0U-760U)       // datetimepick
#define DTN_LAST                (0U-799U)

#define CBEN_FIRST              (0U-800U)       // combo box ex
#define CBEN_LAST               (0U-830U)

#define RBN_FIRST               (0U-831U)       // rebar
#define RBN_LAST                (0U-859U)
#endif

#if (_WIN32_IE >= 0x0400)
#define IPN_FIRST               (0U-860U)       // internet address
#define IPN_LAST                (0U-879U)       // internet address

#define SBN_FIRST               (0U-880U)       // status bar
#define SBN_LAST                (0U-899U)

#define PGN_FIRST               (0U-900U)       // Pager Control
#define PGN_LAST                (0U-950U)

#endif

#if (_WIN32_IE >= 0x0500)
#ifndef WMN_FIRST
#define WMN_FIRST               (0U-1000U)
#define WMN_LAST                (0U-1200U)
#endif
#endif

#if (_WIN32_WINNT >= 0x0501)
#define BCN_FIRST               (0U-1250U)
#define BCN_LAST                (0U-1350U)
#endif

#define MSGF_COMMCTRL_BEGINDRAG     0x4200
#define MSGF_COMMCTRL_SIZEHEADER    0x4201
#define MSGF_COMMCTRL_DRAGSELECT    0x4202
#define MSGF_COMMCTRL_TOOLBARCUST   0x4203

#if (_WIN32_IE >= 0x0300)
//==================== CUSTOM DRAW ==========================================


// custom draw return flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDRF_DODEFAULT          0x00000000
#define CDRF_NEWFONT            0x00000002
#define CDRF_SKIPDEFAULT        0x00000004


#define CDRF_NOTIFYPOSTPAINT    0x00000010
#define CDRF_NOTIFYITEMDRAW     0x00000020
#if (_WIN32_IE >= 0x0400)
#define CDRF_NOTIFYSUBITEMDRAW  0x00000020  // flags are the same, we can distinguish by context
#endif
#define CDRF_NOTIFYPOSTERASE    0x00000040

// drawstage flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDDS_PREPAINT           0x00000001
#define CDDS_POSTPAINT          0x00000002
#define CDDS_PREERASE           0x00000003
#define CDDS_POSTERASE          0x00000004
// the 0x000010000 bit means it's individual item specific
#define CDDS_ITEM               0x00010000
#define CDDS_ITEMPREPAINT       (CDDS_ITEM | CDDS_PREPAINT)
#define CDDS_ITEMPOSTPAINT      (CDDS_ITEM | CDDS_POSTPAINT)
#define CDDS_ITEMPREERASE       (CDDS_ITEM | CDDS_PREERASE)
#define CDDS_ITEMPOSTERASE      (CDDS_ITEM | CDDS_POSTERASE)
#if (_WIN32_IE >= 0x0400)
#define CDDS_SUBITEM            0x00020000
#endif

// itemState flags
#define CDIS_SELECTED       0x0001
#define CDIS_GRAYED         0x0002
#define CDIS_DISABLED       0x0004
#define CDIS_CHECKED        0x0008
#define CDIS_FOCUS          0x0010
#define CDIS_DEFAULT        0x0020
#define CDIS_HOT            0x0040
#define CDIS_MARKED         0x0080
#define CDIS_INDETERMINATE  0x0100
#if (_WIN32_WINNT >= 0x501)
#define CDIS_SHOWKEYBOARDCUES   0x0200
#endif

typedef struct tagMSNMCUSTOMDRAWINFO
{
    MSNMHDR hdr;
    DWORD dwDrawStage;
    HMSDC hdc;
    MSRECT rc;
    DWORD_PTR dwItemSpec;  // this is control specific, but it's how to specify an item.  valid only with CDDS_ITEM bit set
    UINT  uItemState;
    LPARAM lItemlParam;
} MSNMCUSTOMDRAW, *LPMSNMCUSTOMDRAW;

typedef struct tagMSNMTTCUSTOMDRAW
{
    MSNMCUSTOMDRAW nmcd;
    UINT uDrawFlags;
} MSNMTTCUSTOMDRAW, *LPMSNMTTCUSTOMDRAW;

#endif      // _WIN32_IE >= 0x0300


//====== IMAGE APIS ===========================================================

#ifndef NOIMAGEAPIS

#define CLR_NONE                0xFFFFFFFFL
#define CLR_DEFAULT             0xFF000000L


#ifndef HMSIMAGELIST
struct _MSIMAGELIST;
typedef struct _MSIMAGELIST* HMSIMAGELIST;
#endif

#ifndef MSIMAGELISTDRAWPARAMS
#if (_WIN32_IE >= 0x0300)
typedef struct _MSIMAGELISTDRAWPARAMS 
{
    DWORD       cbSize;
    HMSIMAGELIST  himl;
    int         i;
    HMSDC         hdcDst;
    int         x;
    int         y;
    int         cx;
    int         cy;
    int         xBitmap;        // x offest from the upperleft of bitmap
    int         yBitmap;        // y offset from the upperleft of bitmap
    COLORREF    rgbBk;
    COLORREF    rgbFg;
    UINT        fStyle;
    DWORD       dwRop;
#if (_WIN32_WINNT >= 0x501)
    DWORD       fState;
    DWORD       Frame;
    COLORREF    crEffect;
#endif
} MSIMAGELISTDRAWPARAMS, *LPMSIMAGELISTDRAWPARAMS;

#define MSIMAGELISTDRAWPARAMS_V3_SIZE CCSIZEOF_STRUCT(MSIMAGELISTDRAWPARAMS, dwRop)

#endif      // _WIN32_IE >= 0x0300
#endif

#define ILC_MASK                0x00000001
#define ILC_COLOR               0x00000000
#define ILC_COLORDDB            0x000000FE
#define ILC_COLOR4              0x00000004
#define ILC_COLOR8              0x00000008
#define ILC_COLOR16             0x00000010
#define ILC_COLOR24             0x00000018
#define ILC_COLOR32             0x00000020
#define ILC_PALETTE             0x00000800      // (not implemented)
#if (_WIN32_WINNT >= 0x501)
#define ILC_MIRROR              0x00002000      // Mirror the icons contained, if the process is mirrored
#define ILC_PERITEMMIRROR       0x00008000      // Causes the mirroring code to mirror each item when inserting a set of images, verses the whole strip
#endif
HMSIMAGELIST  WINAPI MSImageList_Create(int cx, int cy, UINT flags, int cInitial, int cGrow);
BOOL        WINAPI MSImageList_Destroy(HMSIMAGELIST himl);

int         WINAPI MSImageList_GetImageCount(HMSIMAGELIST himl);
#if (_WIN32_IE >= 0x0300)
BOOL        WINAPI MSImageList_SetImageCount(HMSIMAGELIST himl, UINT uNewCount);
#endif

int         WINAPI MSImageList_Add(HMSIMAGELIST himl, HMSBITMAP hbmImage, HMSBITMAP hbmMask);

int         WINAPI MSImageList_ReplaceIcon(HMSIMAGELIST himl, int i, HMSICON hicon);
COLORREF    WINAPI MSImageList_SetBkColor(HMSIMAGELIST himl, COLORREF clrBk);
COLORREF    WINAPI MSImageList_GetBkColor(HMSIMAGELIST himl);
BOOL        WINAPI MSImageList_SetOverlayImage(HMSIMAGELIST himl, int iImage, int iOverlay);

#define     MSImageList_AddIcon(himl, hicon) MSImageList_ReplaceIcon(himl, -1, hicon)

#define ILD_NORMAL              0x00000000
#define ILD_TRANSPARENT         0x00000001
#define ILD_MASK                0x00000010
#define ILD_IMAGE               0x00000020
#if (_WIN32_IE >= 0x0300)
#define ILD_ROP                 0x00000040
#endif
#define ILD_BLEND25             0x00000002
#define ILD_BLEND50             0x00000004
#define ILD_OVERLAYMASK         0x00000F00
#define INDEXTOOVERLAYMASK(i)   ((i) << 8)
#define ILD_PRESERVEALPHA       0x00001000  // This preserves the alpha channel in dest
#define ILD_SCALE               0x00002000  // Causes the image to be scaled to cx, cy instead of clipped
#define ILD_DPISCALE            0x00004000

#define ILD_SELECTED            ILD_BLEND50
#define ILD_FOCUS               ILD_BLEND25
#define ILD_BLEND               ILD_BLEND50
#define CLR_HILIGHT             CLR_DEFAULT

#define ILS_NORMAL              0x00000000 
#define ILS_GLOW                0x00000001
#define ILS_SHADOW              0x00000002
#define ILS_SATURATE            0x00000004
#define ILS_ALPHA               0x00000008

BOOL WINAPI MSImageList_Draw(HMSIMAGELIST himl, int i, HMSDC hdcDst, int x, int y, UINT fStyle);


#ifdef _WIN32

BOOL        WINAPI MSImageList_Replace(HMSIMAGELIST himl, int i, HMSBITMAP hbmImage, HMSBITMAP hbmMask);

int         WINAPI MSImageList_AddMasked(HMSIMAGELIST himl, HMSBITMAP hbmImage, COLORREF crMask);
BOOL        WINAPI MSImageList_DrawEx(HMSIMAGELIST himl, int i, HMSDC hdcDst, int x, int y, int dx, int dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
#if (_WIN32_IE >= 0x0300)
BOOL        WINAPI MSImageList_DrawIndirect(MSIMAGELISTDRAWPARAMS* pimldp);
#endif
BOOL        WINAPI MSImageList_Remove(HMSIMAGELIST himl, int i);
HMSICON       WINAPI MSImageList_GetIcon(HMSIMAGELIST himl, int i, UINT flags);
HMSIMAGELIST  WINAPI MSImageList_LoadImage(HMSINSTANCE hi, LPCSTR lpbmp, int cx, int cGrow, COLORREF crMask, UINT uType, UINT uFlags);


#if (_WIN32_IE >= 0x0300)
#define ILCF_MOVE   (0x00000000)
#define ILCF_SWAP   (0x00000001)
BOOL        WINAPI MSImageList_Copy(HMSIMAGELIST himlDst, int iDst, HMSIMAGELIST himlSrc, int iSrc, UINT uFlags);
#endif

BOOL        WINAPI MSImageList_BeginDrag(HMSIMAGELIST himlTrack, int iTrack, int dxHotspot, int dyHotspot);
void        WINAPI MSImageList_EndDrag(void);
BOOL        WINAPI MSImageList_DragEnter(HMSWND hwndLock, int x, int y);
BOOL        WINAPI MSImageList_DragLeave(HMSWND hwndLock);
BOOL        WINAPI MSImageList_DragMove(int x, int y);
BOOL        WINAPI MSImageList_SetDragCursorImage(HMSIMAGELIST himlDrag, int iDrag, int dxHotspot, int dyHotspot);

BOOL        WINAPI MSImageList_DragShowNolock(BOOL fShow);
HMSIMAGELIST  WINAPI MSImageList_GetDragImage(MSPOINT *ppt,MSPOINT *pptHotspot);

#define     MSImageList_RemoveAll(himl) MSImageList_Remove(himl, -1)
#define     MSImageList_ExtractIcon(hi, himl, i) MSImageList_GetIcon(himl, i, 0)
#define     MSImageList_LoadBitmap(hi, lpbmp, cx, cGrow, crMask) MSImageList_LoadImage(hi, lpbmp, cx, cGrow, crMask, IMAGE_BITMAP, 0)

#ifdef __IStream_INTERFACE_DEFINED__

HMSIMAGELIST WINAPI MSImageList_Read(LPSTREAM pstm);
BOOL       WINAPI MSImageList_Write(HMSIMAGELIST himl, LPSTREAM pstm);

#if (_WIN32_WINNT >= 0x0501)
#define ILP_NORMAL          0           // Writes or reads the stream using new sematics for this version of comctl32
#define ILP_DOWNLEVEL       1           // Write or reads the stream using downlevel sematics.


HRESULT WINAPI MSImageList_ReadEx(DWORD dwFlags, LPSTREAM pstm, REFIID riid, PVOID* ppv);
HRESULT WINAPI MSImageList_WriteEx(HMSIMAGELIST himl, DWORD dwFlags, LPSTREAM pstm);
#endif

#endif

#ifndef MSIMAGEINFO
typedef struct _MSIMAGEINFO
{
    HMSBITMAP hbmImage;
    HMSBITMAP hbmMask;
    int     Unused1;
    int     Unused2;
    MSRECT    rcImage;
} MSIMAGEINFO, *LPMSIMAGEINFO;
#endif

BOOL        WINAPI MSImageList_GetIconSize(HMSIMAGELIST himl, int *cx, int *cy);
BOOL        WINAPI MSImageList_SetIconSize(HMSIMAGELIST himl, int cx, int cy);
BOOL        WINAPI MSImageList_GetImageInfo(HMSIMAGELIST himl, int i, MSIMAGEINFO *pImageInfo);
HMSIMAGELIST  WINAPI MSImageList_Merge(HMSIMAGELIST himl1, int i1, HMSIMAGELIST himl2, int i2, int dx, int dy);
#if (_WIN32_IE >= 0x0400)
HMSIMAGELIST  WINAPI MSImageList_Duplicate(HMSIMAGELIST himl);
#endif


#endif


#endif


//====== LRBUTTON CONTROL =======================================================

#ifndef NOLRBUTTON
#define WC_LRBUTTON				"LRButton"
// beign message
#define LRM_GETPOS              (WM_USER)
//	 wParam = 0; 
//   lParam = 0; 
#define LRM_GETRANGEMIN         (WM_USER+1)
//	 wParam = 0; 
//   lParam = 0; 
#define LRM_GETRANGEMAX         (WM_USER+2)
//	 wParam = 0; 
//   lParam = 0; 
#define LRM_SETPOS              (WM_USER+3)
//  wParam = (WPARAM) (BOOL) fRedraw; 
//  lParam = (LPARAM) (LONG) lPosition; 
#define LRM_SETRANGE            (WM_USER+4)
//   wParam = (WPARAM) (BOOL) fRedraw; 
//   lParam = (LPARAM) MAKELONG(lMinimum, lMaximum); 
#define LRM_SETRANGEMIN         (WM_USER+5)
//   wParam = (WPARAM) fRedraw; 
//   lParam = (LPARAM) lMinimum; 
#define LRM_SETRANGEMAX         (WM_USER+6)
//  wParam = (WPARAM) fRedraw; 
//  lParam = (LPARAM) lMaximum; 
#define LRM_GETITEMTEXT         (WM_USER+7)
//  wParam = (WPARAM) (int) iItem;  item index
//  lParam = (LPARAM) (char*)szText;receives string (LPCSTR)
#define LRM_GETITEMTEXTLEN       (WM_USER+8)
//  wParam = (WPARAM) (int) iItem;  item index
//  lParam = (LPARAM) 0;
#define LRM_SETTEXTCOLOR		(WM_USER+9)
//  wParam = (WPARAM) (COLORREF) clrText;  Text Color;
//  lParam = (LPARAM) 0;
#define LRM_SETTEXTBKCOLOR		(WM_USER+10)
//  wParam = (WPARAM) (COLORREF) clrTextBk;  Text BackGround Color;
//  lParam = (LPARAM) 0;
#define LRM_SETARROWCOLOR		(WM_USER+11)
//  wParam = (WPARAM) (COLORREF) clrArrow;  Arrow Color;
//  lParam = (LPARAM) 0;
#define LRM_SETARROWBKCOLOR		(WM_USER+12)
//  wParam = (WPARAM) (COLORREF) clrArrowBk;  Arrow BackGround Color;
//  lParam = (LPARAM) 0;
#define LRM_SETTEXTRECT			(WM_USER+13)
//  wParam = (WPARAM) (MSRECT*) lpRect;  Text Rect;
//  lParam = (LPARAM) 0;
#define LRM_SETSTYLE			(WM_USER+14)
//  wParam = (WPARAM) Style;
//  lParam = (LPARAM) 0;


//notify message
#define LRN_KEYDOWN             (WM_USER+22)
#define LRN_GETDISPINFO         (WM_USER+23)

//LRButton style
#define LRS_NORMAL			0x00000000
#define LRS_ONLYRIGHT		0x00000001

//end message
//begin macro 
#define MSLRButton_GetPos(hwndLR) \
	(BOOL)SNDMSG((hwndLR), LRM_GETPOS, 0L, 0L)
#define MSLRButton_GetRangeMin(hwndLR) \
	(BOOL)SNDMSG((hwndLR), LRM_GETRANGEMIN, 0L, 0L)
#define MSLRButton_GetRangeMax(hwndLR) \
	(BOOL)SNDMSG((hwndLR), LRM_GETRANGEMAX, 0L, 0L)
#define MSLRButton_SetPos(hwndLR,fRedraw,lPosition) \
	(BOOL)SNDMSG((hwndLR), LRM_SETPOS,(WPARAM)fRedraw, (LPARAM)lPosition)
#define MSLRButton_SetRange(hwndLR,fRedraw,lMinimum,lMaximum) \
	(BOOL)SNDMSG((hwndLR), LRM_SETRANGE,(WPARAM)fRedraw, (LPARAM) MAKELONG(lMinimum, lMaximum))
#define MSLRButton_SetRangeMin(hwndLR,fRedraw,lMinimum) \
	(BOOL)SNDMSG((hwndLR), LRM_SETRANGEMIN,(WPARAM)fRedraw, (LPARAM) lMinimum)
#define MSLRButton_SetRangeMax(hwndLR,fRedraw,lMaximum) \
	(BOOL)SNDMSG((hwndLR), LRM_SETRANGEMAX,(WPARAM)fRedraw, (LPARAM) lMaximum)
#define MSLRButton_GetItemText(hwndLR,iItem,szText) \
	(BOOL)SNDMSG((hwndLR), LRM_GETITEMTEXT,(WPARAM) (int) iItem, (LPARAM) (char*)szText)
#define MSLRButton_GetItemTextLen(hwndLR,iItem) \
	(BOOL)SNDMSG((hwndLR), LRM_GETITEMTEXT,(WPARAM) (int) iItem, (LPARAM) 0)
#define MSLRButton_SetTextColor(hwndLR, clrText) \
	(BOOL)SNDMSG((hwndLR),LRM_SETTEXTCOLOR,(WPARAM) (COLORREF) clrText,(LPARAM) 0)
#define MSLRButton_SetTextBkColor(hwndLR, clrTextBk) \
	(BOOL)SNDMSG((hwndLR),LRM_SETTEXTBKCOLOR,(WPARAM) (COLORREF) clrTextBk,(LPARAM) 0)
#define MSLRButton_SetArrowColor(hwndLR, clrArrow) \
	(BOOL)SNDMSG((hwndLR),LRM_SETARROWCOLOR,(WPARAM) (COLORREF) clrArrow,(LPARAM) 0)
#define MSLRButton_SetArrowBkColor(hwndLR, clrArrowBk) \
	(BOOL)SNDMSG((hwndLR),LRM_SETARROWBKCOLOR,(WPARAM) (COLORREF) clrArrowBk,(LPARAM) 0)
#define MSLRButton_SetTextRect(hwndLR, lpRect) \
	(BOOL)SNDMSG((hwndLR),LRM_SETTEXTRECT,(WPARAM) (MSRECT*) lpRect,(LPARAM) 0)
#define MSLRButton_SetStyle(hwndLR, style) \
	(BOOL)SNDMSG((hwndLR),LRM_SETSTYLE,(WPARAM) style,(LPARAM) 0)
	
//end macro







typedef struct tagLRDISPINFO {
    MSNMHDR hdr;
    LPTSTR pszText; 
    int cchTextMax; 
    int iIndex; 
    LPARAM lParam;
} MSNMLRDISPINFO, FAR *LPMSNMLRDISPINFO;
typedef struct tagLRKEYDOWN {
    MSNMHDR hdr;
    WORD  wVKey;
    UINT  flags;
} MSNMLRKEYDOWN, FAR *LPMSNMLRKEYDOWN;

#endif


//====== HEADER CONTROL =======================================================

#ifndef NOHEADER

#ifdef _WIN32
#define WC_HEADERA              "SysHeader32"

#define WC_HEADER               WC_HEADERA

#else
#define WC_HEADER               "SysHeader"
#endif

// begin_r_commctrl

#define HDS_HORZ                0x0000
#define HDS_BUTTONS             0x0002
#if (_WIN32_IE >= 0x0300)
#define HDS_HOTTRACK            0x0004
#endif
#define HDS_HIDDEN              0x0008

#if (_WIN32_IE >= 0x0300)
#define HDS_DRAGDROP            0x0040
#define HDS_FULLDRAG            0x0080
#endif
#if (_WIN32_IE >= 0x0500)
#define HDS_FILTERBAR           0x0100
#endif

#if (_WIN32_WINNT >= 0x501)
#define HDS_FLAT                0x0200
#endif
// end_r_commctrl

#if (_WIN32_IE >= 0x0500)

#define HDFT_ISSTRING       0x0000      // HD_ITEM.pvFilter points to a HD_TEXTFILTER
#define HDFT_ISNUMBER       0x0001      // HD_ITEM.pvFilter points to a INT

#define HDFT_HASNOVALUE     0x8000      // clear the filter, by setting this bit

#define HD_TEXTFILTER HD_TEXTFILTERA
#define HDTEXTFILTER HD_TEXTFILTERA
#define LPHD_TEXTFILTER LPHD_TEXTFILTERA
#define LPHDTEXTFILTER LPHD_TEXTFILTERA

#if 0
typedef struct _HD_TEXTFILTERA
{
    LPSTR pszText;                      // [in] pointer to the buffer containing the filter (ANSI)
    INT cchTextMax;                     // [in] max size of buffer/edit control buffer
} HD_TEXTFILTERA, *LPHD_TEXTFILTERA;
#endif

#endif  // _WIN32_IE >= 0x0500

#if (_WIN32_IE >= 0x0300)
#define MSHD_ITEMA MSHDITEMA
#else
#define MSHDITEMA  MSHD_ITEMA
#endif
#define MSHD_ITEM MSHDITEM

typedef struct MS_HD_ITEMA
{
    UINT    mask;
    int     cxy;
    LPSTR   pszText;
    HMSBITMAP hbm;
    int     cchTextMax;
    int     fmt;
    LPARAM  lParam;
#if (_WIN32_IE >= 0x0300)
    int     iImage;        // index of bitmap in ImageList
    int     iOrder;        // where to draw this item
#endif
#if (_WIN32_IE >= 0x0500)
    UINT    type;           // [in] filter type (defined what pvFilter is a pointer to)
    void *  pvFilter;       // [in] fillter data see above
#endif
} MSHDITEMA, *LPMSHDITEMA;

#define MSHDITEMA_V1_SIZE CCSIZEOF_STRUCT(MSHDITEMA, lParam)
#define MSHDITEMW_V1_SIZE CCSIZEOF_STRUCT(MSHDITEMW, lParam)



#define MSHDITEM MSHDITEMA
#define LPMSHDITEM LPMSHDITEMA
#define MSHDITEM_V1_SIZE MSHDITEMA_V1_SIZE


#define HDI_WIDTH               0x0001
#define HDI_HEIGHT              HDI_WIDTH
#define HDI_TEXT                0x0002
#define HDI_FORMAT              0x0004
#define HDI_LPARAM              0x0008
#define HDI_BITMAP              0x0010
#if (_WIN32_IE >= 0x0300)
#define HDI_IMAGE               0x0020
#define HDI_DI_SETITEM          0x0040
#define HDI_ORDER               0x0080
#endif
#if (_WIN32_IE >= 0x0500)
#define HDI_FILTER              0x0100
#endif

#define HDF_LEFT                0x0000
#define HDF_RIGHT               0x0001
#define HDF_CENTER              0x0002
#define HDF_JUSTIFYMASK         0x0003
#define HDF_RTLREADING          0x0004

#define HDF_OWNERDRAW           0x8000
#define HDF_STRING              0x4000
#define HDF_BITMAP              0x2000
#if (_WIN32_IE >= 0x0300)
#define HDF_BITMAP_ON_RIGHT     0x1000
#define HDF_IMAGE               0x0800
#endif

#if (_WIN32_WINNT >= 0x501)
#define HDF_SORTUP              0x0400
#define HDF_SORTDOWN            0x0200
#endif

#define HDM_GETITEMCOUNT        (HDM_FIRST + 0)
#define MSHeader_GetItemCount(hwndHD) \
    (int)SNDMSG((hwndHD), HDM_GETITEMCOUNT, 0, 0L)


#define HDM_INSERTITEMA         (HDM_FIRST + 1)

#define HDM_INSERTITEM          HDM_INSERTITEMA

#define MSHeader_InsertItem(hwndHD, i, phdi) \
    (int)SNDMSG((hwndHD), HDM_INSERTITEM, (WPARAM)(int)(i), (LPARAM)(const HD_ITEM *)(phdi))


#define HDM_DELETEITEM          (HDM_FIRST + 2)
#define MSHeader_DeleteItem(hwndHD, i) \
    (BOOL)SNDMSG((hwndHD), HDM_DELETEITEM, (WPARAM)(int)(i), 0L)


#define HDM_GETITEMA            (HDM_FIRST + 3)

#define HDM_GETITEM             HDM_GETITEMA

#define MSHeader_GetItem(hwndHD, i, phdi) \
    (BOOL)SNDMSG((hwndHD), HDM_GETITEM, (WPARAM)(int)(i), (LPARAM)(HD_ITEM *)(phdi))


#define HDM_SETITEMA            (HDM_FIRST + 4)

#define HDM_SETITEM             HDM_SETITEMA

#define MSHeader_SetItem(hwndHD, i, phdi) \
    (BOOL)SNDMSG((hwndHD), HDM_SETITEM, (WPARAM)(int)(i), (LPARAM)(const HD_ITEM *)(phdi))

#if (_WIN32_IE >= 0x0300)
#define CSHD_LAYOUT  MSHDLAYOUT
#else
#define MSHDLAYOUT   CSHD_LAYOUT
#endif

typedef struct tagMSHDLAYOUT
{
    MSRECT *prc;
    MSWINDOWPOS *pwpos;
} MSHDLAYOUT, *LPMSHDLAYOUT;


#define HDM_LAYOUT              (HDM_FIRST + 5)
#define MSHeader_Layout(hwndHD, playout) \
    (BOOL)SNDMSG((hwndHD), HDM_LAYOUT, 0, (LPARAM)(CSHD_LAYOUT *)(playout))


#define HHT_NOWHERE             0x0001
#define HHT_ONHEADER            0x0002
#define HHT_ONDIVIDER           0x0004
#define HHT_ONDIVOPEN           0x0008
#if (_WIN32_IE >= 0x0500)
#define HHT_ONFILTER            0x0010
#define HHT_ONFILTERBUTTON      0x0020
#endif
#define HHT_ABOVE               0x0100
#define HHT_BELOW               0x0200
#define HHT_TORIGHT             0x0400
#define HHT_TOLEFT              0x0800

#if (_WIN32_IE >= 0x0300)
#define MSHD_HITTESTINFO MSHDHITTESTINFO
#else
#define MSHDHITTESTINFO  MSHD_HITTESTINFO
#endif

typedef struct MS_HD_HITTESTINFO
{
    MSPOINT pt;
    UINT flags;
    int iItem;
} MSHDHITTESTINFO, *LPMSHDHITTESTINFO;


#define HDM_HITTEST             (HDM_FIRST + 6)

#if (_WIN32_IE >= 0x0300)

#define HDM_GETITEMRECT         (HDM_FIRST + 7)
#define MSHeader_GetItemRect(hwnd, iItem, lprc) \
        (BOOL)SNDMSG((hwnd), HDM_GETITEMRECT, (WPARAM)(iItem), (LPARAM)(lprc))

#define HDM_SETIMAGELIST        (HDM_FIRST + 8)
#define MSHeader_SetImageList(hwnd, himl) \
        (HMSIMAGELIST)SNDMSG((hwnd), HDM_SETIMAGELIST, 0, (LPARAM)(himl))

#define HDM_GETIMAGELIST        (HDM_FIRST + 9)
#define MSHeader_GetImageList(hwnd) \
        (HMSIMAGELIST)SNDMSG((hwnd), HDM_GETIMAGELIST, 0, 0)


#define HDM_ORDERTOINDEX        (HDM_FIRST + 15)
#define MSHeader_OrderToIndex(hwnd, i) \
        (int)SNDMSG((hwnd), HDM_ORDERTOINDEX, (WPARAM)(i), 0)

#define HDM_CREATEDRAGIMAGE     (HDM_FIRST + 16)  // wparam = which item (by index)
#define MSHeader_CreateDragImage(hwnd, i) \
        (HMSIMAGELIST)SNDMSG((hwnd), HDM_CREATEDRAGIMAGE, (WPARAM)(i), 0)

#define HDM_GETORDERARRAY       (HDM_FIRST + 17)
#define MSHeader_GetOrderArray(hwnd, iCount, lpi) \
        (BOOL)SNDMSG((hwnd), HDM_GETORDERARRAY, (WPARAM)(iCount), (LPARAM)(lpi))

#define HDM_SETORDERARRAY       (HDM_FIRST + 18)
#define MSHeader_SetOrderArray(hwnd, iCount, lpi) \
        (BOOL)SNDMSG((hwnd), HDM_SETORDERARRAY, (WPARAM)(iCount), (LPARAM)(lpi))
// lparam = int array of size HDM_GETITEMCOUNT
// the array specifies the order that all items should be displayed.
// e.g.  { 2, 0, 1}
// says the index 2 item should be shown in the 0ths position
//      index 0 should be shown in the 1st position
//      index 1 should be shown in the 2nd position


#define HDM_SETHOTDIVIDER          (HDM_FIRST + 19)
#define MSHeader_SetHotDivider(hwnd, fPos, dw) \
        (int)SNDMSG((hwnd), HDM_SETHOTDIVIDER, (WPARAM)(fPos), (LPARAM)(dw))
// convenience message for external dragdrop
// wParam = BOOL  specifying whether the lParam is a dwPos of the cursor
//              position or the index of which divider to hotlight
// lParam = depends on wParam  (-1 and wParm = FALSE turns off hotlight)
#endif      // _WIN32_IE >= 0x0300

#if (_WIN32_IE >= 0x0500)

#define HDM_SETBITMAPMARGIN          (HDM_FIRST + 20)
#define MSHeader_SetBitmapMargin(hwnd, iWidth) \
        (int)SNDMSG((hwnd), HDM_SETBITMAPMARGIN, (WPARAM)(iWidth), 0)

#define HDM_GETBITMAPMARGIN          (HDM_FIRST + 21)
#define MSHeader_GetBitmapMargin(hwnd) \
        (int)SNDMSG((hwnd), HDM_GETBITMAPMARGIN, 0, 0)
#endif


#if (_WIN32_IE >= 0x0400)
#define HDM_SETUNICODEFORMAT   CCM_SETUNICODEFORMAT
#define MSHeader_SetUnicodeFormat(hwnd, fUnicode)  \
    (BOOL)SNDMSG((hwnd), HDM_SETUNICODEFORMAT, (WPARAM)(fUnicode), 0)

#define HDM_GETUNICODEFORMAT   CCM_GETUNICODEFORMAT
#define MSHeader_GetUnicodeFormat(hwnd)  \
    (BOOL)SNDMSG((hwnd), HDM_GETUNICODEFORMAT, 0, 0)
#endif

#if (_WIN32_IE >= 0x0500)
#define HDM_SETFILTERCHANGETIMEOUT  (HDM_FIRST+22)
#define MSHeader_SetFilterChangeTimeout(hwnd, i) \
        (int)SNDMSG((hwnd), HDM_SETFILTERCHANGETIMEOUT, 0, (LPARAM)(i))

#define HDM_EDITFILTER          (HDM_FIRST+23)
#define MSHeader_EditFilter(hwnd, i, fDiscardChanges) \
        (int)SNDMSG((hwnd), HDM_EDITFILTER, (WPARAM)(i), MAKELPARAM(fDiscardChanges, 0))

// Clear filter takes -1 as a column value to indicate that all
// the filter should be cleared.  When this happens you will
// only receive a single filter changed notification.

#define HDM_CLEARFILTER         (HDM_FIRST+24)
#define MSHeader_ClearFilter(hwnd, i) \
        (int)SNDMSG((hwnd), HDM_CLEARFILTER, (WPARAM)(i), 0)
#define MSHeader_ClearAllFilters(hwnd) \
        (int)SNDMSG((hwnd), HDM_CLEARFILTER, (WPARAM)-1, 0)
#endif

#define HDN_ITEMCHANGINGA           (HDN_FIRST-0)
#define HDN_ITEMCHANGEDA        (HDN_FIRST-1)
#define HDN_ITEMCLICKA          (HDN_FIRST-2)
#define HDN_ITEMDBLCLICKA       (HDN_FIRST-3)
#define HDN_DIVIDERDBLCLICKA    (HDN_FIRST-5)
#define HDN_BEGINTRACKA         (HDN_FIRST-6)
#define HDN_ENDTRACKA           (HDN_FIRST-7)
#define HDN_TRACKA              (HDN_FIRST-8)
#if (_WIN32_IE >= 0x0300)
#define HDN_GETDISPINFOA        (HDN_FIRST-9)
#define HDN_BEGINDRAG           (HDN_FIRST-10)
#define HDN_ENDDRAG             (HDN_FIRST-11)
#endif
#if (_WIN32_IE >= 0x0500)
#define HDN_FILTERCHANGE        (HDN_FIRST-12)
#define HDN_FILTERBTNCLICK      (HDN_FIRST-13)
#endif

#define HDN_ITEMCHANGING         HDN_ITEMCHANGINGA
#define HDN_ITEMCHANGED          HDN_ITEMCHANGEDA
#define HDN_ITEMCLICK            HDN_ITEMCLICKA
#define HDN_ITEMDBLCLICK         HDN_ITEMDBLCLICKA
#define HDN_DIVIDERDBLCLICK      HDN_DIVIDERDBLCLICKA
#define HDN_BEGINTRACK           HDN_BEGINTRACKA
#define HDN_ENDTRACK             HDN_ENDTRACKA
#define HDN_TRACK                HDN_TRACKA
#if (_WIN32_IE >= 0x0300)
#define HDN_GETDISPINFO          HDN_GETDISPINFOA
#endif



#if (_WIN32_IE >= 0x0300)
#define MSHD_NOTIFYA              MSNMHEADERA
#else
#define tagMSNMHEADERA            _HD_NOTIFY
#define MSNMHEADERA               MSHD_NOTIFYA
#endif
#define HD_NOTIFY               NMHEADER

typedef struct tagMSNMHEADERA
{
    MSNMHDR   hdr;
    int     iItem;
    int     iButton;
    MSHDITEMA *pitem;
}  MSNMHEADERA, *LPMSNMHEADERA;



#define MSNMHEADER                MSNMHEADERA
#define LPMSNMHEADER              LPMSNMHEADERA


typedef struct tagMSNMHDDISPINFOA
{
    MSNMHDR   hdr;
    int     iItem;
    UINT    mask;
    LPSTR   pszText;
    int     cchTextMax;
    int     iImage;
    LPARAM  lParam;
} MSNMHDDISPINFOA, *LPMSNMHDDISPINFOA;



#define MSNMHDDISPINFO            MSNMHDDISPINFOA
#define LPMSNMHDDISPINFO          LPMSNMHDDISPINFOA

#if (_WIN32_IE >= 0x0500)
#if 0
typedef struct tagNMHDFILTERBTNCLICK
{
    MSNMHDR hdr;
    INT iItem;
    MSRECT rc;
} NMHDFILTERBTNCLICK, *LPNMHDFILTERBTNCLICK;
#endif
#endif

#endif      // NOHEADER


//====== TOOLBAR CONTROL ======================================================

#ifndef NOTOOLBAR

#ifdef _WIN32
#define TOOLBARCLASSNAMEA       "ToolbarWindow32"

#define TOOLBARCLASSNAME        TOOLBARCLASSNAMEA

#else
#define TOOLBARCLASSNAME        "ToolbarWindow"
#endif

typedef struct tagMSTBBUTTON {
    int iBitmap;
    int idCommand;
    BYTE fsState;
    BYTE fsStyle;
#ifdef _WIN64
    BYTE bReserved[6];          // padding for alignment
#elif defined(_WIN32)
    BYTE bReserved[2];          // padding for alignment
#endif
    DWORD_PTR dwData;
    INT_PTR iString;
} MSTBBUTTON, NEAR* PMSTBBUTTON, *LPMSTBBUTTON;
typedef const MSTBBUTTON *LPCMSTBBUTTON;


typedef struct _MSCOLORMAP {
    COLORREF from;
    COLORREF to;
} MSCOLORMAP, *LPMSCOLORMAP;

HMSWND WINAPI MSCreateToolbarEx(HMSWND hwnd, DWORD ws, UINT wID, int nBitmaps,
                        HMSINSTANCE hBMInst, UINT_PTR wBMID, LPCMSTBBUTTON lpButtons,
                        int iNumButtons, int dxButton, int dyButton,
                        int dxBitmap, int dyBitmap, UINT uStructSize);

HMSBITMAP WINAPI MSCreateMappedBitmap(HMSINSTANCE hInstance, INT_PTR idBitmap,
                                  UINT wFlags, LPMSCOLORMAP lpColorMap,
                                  int iNumMaps);

#define CMB_MASKED              0x02
#define TBSTATE_CHECKED         0x01
#define TBSTATE_PRESSED         0x02
#define TBSTATE_ENABLED         0x04
#define TBSTATE_HIDDEN          0x08
#define TBSTATE_INDETERMINATE   0x10
#define TBSTATE_WRAP            0x20
#if (_WIN32_IE >= 0x0300)
#define TBSTATE_ELLIPSES        0x40
#endif
#if (_WIN32_IE >= 0x0400)
#define TBSTATE_MARKED          0x80
#endif

#define TBSTYLE_BUTTON          0x0000  // obsolete; use BTNS_BUTTON instead
#define TBSTYLE_SEP             0x0001  // obsolete; use BTNS_SEP instead
#define TBSTYLE_CHECK           0x0002  // obsolete; use BTNS_CHECK instead
#define TBSTYLE_GROUP           0x0004  // obsolete; use BTNS_GROUP instead
#define TBSTYLE_CHECKGROUP      (TBSTYLE_GROUP | TBSTYLE_CHECK)     // obsolete; use BTNS_CHECKGROUP instead
#if (_WIN32_IE >= 0x0300)
#define TBSTYLE_DROPDOWN        0x0008  // obsolete; use BTNS_DROPDOWN instead
#endif
#if (_WIN32_IE >= 0x0400)
#define TBSTYLE_AUTOSIZE        0x0010  // obsolete; use BTNS_AUTOSIZE instead
#define TBSTYLE_NOPREFIX        0x0020  // obsolete; use BTNS_NOPREFIX instead
#endif

#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#if (_WIN32_IE >= 0x0300)
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#endif
#if (_WIN32_IE >= 0x0400)
#define TBSTYLE_REGISTERDROP    0x4000
#define TBSTYLE_TRANSPARENT     0x8000
#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#endif

#if (_WIN32_IE >= 0x0500)
#define BTNS_BUTTON     TBSTYLE_BUTTON      // 0x0000
#define BTNS_SEP        TBSTYLE_SEP         // 0x0001
#define BTNS_CHECK      TBSTYLE_CHECK       // 0x0002
#define BTNS_GROUP      TBSTYLE_GROUP       // 0x0004
#define BTNS_CHECKGROUP TBSTYLE_CHECKGROUP  // (TBSTYLE_GROUP | TBSTYLE_CHECK)
#define BTNS_DROPDOWN   TBSTYLE_DROPDOWN    // 0x0008
#define BTNS_AUTOSIZE   TBSTYLE_AUTOSIZE    // 0x0010; automatically calculate the cx of the button
#define BTNS_NOPREFIX   TBSTYLE_NOPREFIX    // 0x0020; this button should not have accel prefix
#if (_WIN32_IE >= 0x0501)
#define BTNS_SHOWTEXT   0x0040              // ignored unless TBSTYLE_EX_MIXEDBUTTONS is set
#endif  // 0x0501
#define BTNS_WHOLEDROPDOWN  0x0080          // draw drop-down arrow, but without split arrow section
#endif

#if (_WIN32_IE >= 0x0501)
#define TBSTYLE_EX_MIXEDBUTTONS             0x00000008
#define TBSTYLE_EX_HIDECLIPPEDBUTTONS       0x00000010  // don't show partially obscured buttons
#endif  // 0x0501


#if (_WIN32_WINNT >= 0x501)
#define TBSTYLE_EX_DOUBLEBUFFER             0x00000080 // Double Buffer the toolbar
#endif

#if (_WIN32_IE >= 0x0400)
// Custom Draw Structure
typedef struct tagMSNMTBCUSTOMDRAW {
    MSNMCUSTOMDRAW nmcd;
    HMSBRUSH hbrMonoDither;
    HMSBRUSH hbrLines;                // For drawing lines on buttons
    HMSPEN hpenLines;                 // For drawing lines on buttons

    COLORREF clrText;               // Color of text
    COLORREF clrMark;               // Color of text bk when marked. (only if TBSTATE_MARKED)
    COLORREF clrTextHighlight;      // Color of text when highlighted
    COLORREF clrBtnFace;            // Background of the button
    COLORREF clrBtnHighlight;       // 3D highlight
    COLORREF clrHighlightHotTrack;  // In conjunction with fHighlightHotTrack
                                    // will cause button to highlight like a menu
    MSRECT rcText;                    // Rect for text

    int nStringBkMode;
    int nHLStringBkMode;
#if (_WIN32_WINNT >= 0x501)
    int iListGap;
#endif
} MSNMTBCUSTOMDRAW, * LPMSNMTBCUSTOMDRAW;

// Toolbar custom draw return flags
#define TBCDRF_NOEDGES              0x00010000  // Don't draw button edges
#define TBCDRF_HILITEHOTTRACK       0x00020000  // Use color of the button bk when hottracked
#define TBCDRF_NOOFFSET             0x00040000  // Don't offset button if pressed
#define TBCDRF_NOMARK               0x00080000  // Don't draw default highlight of image/text for TBSTATE_MARKED
#define TBCDRF_NOETCHEDEFFECT       0x00100000  // Don't draw etched effect for disabled items
#endif

#if (_WIN32_IE >= 0x0500)
#define TBCDRF_BLENDICON            0x00200000  // Use ILD_BLEND50 on the icon image
#define TBCDRF_NOBACKGROUND         0x00400000  // Use ILD_BLEND50 on the icon image
#endif


#define TB_ENABLEBUTTON         (WM_USER + 1)
#define TB_CHECKBUTTON          (WM_USER + 2)
#define TB_PRESSBUTTON          (WM_USER + 3)
#define TB_HIDEBUTTON           (WM_USER + 4)
#define TB_INDETERMINATE        (WM_USER + 5)
#if (_WIN32_IE >= 0x0400)
#define TB_MARKBUTTON           (WM_USER + 6)
#endif
#define TB_ISBUTTONENABLED      (WM_USER + 9)
#define TB_ISBUTTONCHECKED      (WM_USER + 10)
#define TB_ISBUTTONPRESSED      (WM_USER + 11)
#define TB_ISBUTTONHIDDEN       (WM_USER + 12)
#define TB_ISBUTTONINDETERMINATE (WM_USER + 13)
#if (_WIN32_IE >= 0x0400)
#define TB_ISBUTTONHIGHLIGHTED  (WM_USER + 14)
#endif
#define TB_SETSTATE             (WM_USER + 17)
#define TB_GETSTATE             (WM_USER + 18)
#define TB_ADDBITMAP            (WM_USER + 19)

#ifdef _WIN32
typedef struct tagMSTBADDBITMAP {
        HMSINSTANCE       hInst;
        UINT_PTR        nID;
} MSTBADDBITMAP, *LPMSTBADDBITMAP;

#define HCSINST_COMMCTRL          ((HMSINSTANCE)-1)
#define IDB_STD_SMALL_COLOR     0
#define IDB_STD_LARGE_COLOR     1
#define IDB_VIEW_SMALL_COLOR    4
#define IDB_VIEW_LARGE_COLOR    5
#if (_WIN32_IE >= 0x0300)
#define IDB_HIST_SMALL_COLOR    8
#define IDB_HIST_LARGE_COLOR    9
#endif

// icon indexes for standard bitmap

#define STD_CUT                 0
#define STD_COPY                1
#define STD_PASTE               2
#define STD_UNDO                3
#define STD_REDOW               4
#define STD_DELETE              5
#define STD_FILENEW             6
#define STD_FILEOPEN            7
#define STD_FILESAVE            8
#define STD_PRINTPRE            9
#define STD_PROPERTIES          10
#define STD_HELP                11
#define STD_FIND                12
#define STD_REPLACE             13
#define STD_PRINT               14

// icon indexes for standard view bitmap

#define VIEW_LARGEICONS         0
#define VIEW_SMALLICONS         1
#define VIEW_LIST               2
#define VIEW_DETAILS            3
#define VIEW_SORTNAME           4
#define VIEW_SORTSIZE           5
#define VIEW_SORTDATE           6
#define VIEW_SORTTYPE           7
#define VIEW_PARENTFOLDER       8
#define VIEW_NETCONNECT         9
#define VIEW_NETDISCONNECT      10
#define VIEW_NEWFOLDER          11
#if (_WIN32_IE >= 0x0400)
#define VIEW_VIEWMENU           12
#endif

#if (_WIN32_IE >= 0x0300)
#define HIST_BACK               0
#define HIST_FORWARD            1
#define HIST_FAVORITES          2
#define HIST_ADDTOFAVORITES     3
#define HIST_VIEWTREE           4
#endif

#endif

#if (_WIN32_IE >= 0x0400)
#define TB_ADDBUTTONSA          (WM_USER + 20)
#define TB_INSERTBUTTONA        (WM_USER + 21)
#else
#define TB_ADDBUTTONS           (WM_USER + 20)
#define TB_INSERTBUTTON         (WM_USER + 21)
#endif

#define TB_DELETEBUTTON         (WM_USER + 22)
#define TB_GETBUTTON            (WM_USER + 23)
#define TB_BUTTONCOUNT          (WM_USER + 24)
#define TB_COMMANDTOINDEX       (WM_USER + 25)

#ifdef _WIN32

typedef struct tagMSTBSAVEPARAMSA {
    HMSKEY hkr;
    LPCSTR pszSubKey;
    LPCSTR pszValueName;
} MSTBSAVEPARAMSA, *LPMSTBSAVEPARAMSA;


#define CSTBSAVEPARAMS            MSTBSAVEPARAMSA
#define LPCSTBSAVEPARAMS          LPMSTBSAVEPARAMSA

#endif  // _WIN32

#define TB_SAVERESTOREA         (WM_USER + 26)
#define TB_CUSTOMIZE            (WM_USER + 27)
#define TB_ADDSTRINGA           (WM_USER + 28)
#define TB_GETITEMRECT          (WM_USER + 29)
#define TB_BUTTONSTRUCTSIZE     (WM_USER + 30)
#define TB_SETBUTTONSIZE        (WM_USER + 31)
#define TB_SETBITMAPSIZE        (WM_USER + 32)
#define TB_AUTOSIZE             (WM_USER + 33)
#define TB_GETTOOLTIPS          (WM_USER + 35)
#define TB_SETTOOLTIPS          (WM_USER + 36)
#define TB_SETPARENT            (WM_USER + 37)
#define TB_SETROWS              (WM_USER + 39)
#define TB_GETROWS              (WM_USER + 40)
#define TB_SETCMDID             (WM_USER + 42)
#define TB_CHANGEBITMAP         (WM_USER + 43)
#define TB_GETBITMAP            (WM_USER + 44)
#define TB_GETBUTTONTEXTA       (WM_USER + 45)
#define TB_REPLACEBITMAP        (WM_USER + 46)
#if (_WIN32_IE >= 0x0300)
#define TB_SETINDENT            (WM_USER + 47)
#define TB_SETIMAGELIST         (WM_USER + 48)
#define TB_GETIMAGELIST         (WM_USER + 49)
#define TB_LOADIMAGES           (WM_USER + 50)
#define TB_GETRECT              (WM_USER + 51) // wParam is the Cmd instead of index
#define TB_SETHOTIMAGELIST      (WM_USER + 52)
#define TB_GETHOTIMAGELIST      (WM_USER + 53)
#define TB_SETDISABLEDIMAGELIST (WM_USER + 54)
#define TB_GETDISABLEDIMAGELIST (WM_USER + 55)
#define TB_SETSTYLE             (WM_USER + 56)
#define TB_GETSTYLE             (WM_USER + 57)
#define TB_GETBUTTONSIZE        (WM_USER + 58)
#define TB_SETBUTTONWIDTH       (WM_USER + 59)
#define TB_SETMAXTEXTROWS       (WM_USER + 60)
#define TB_GETTEXTROWS          (WM_USER + 61)
#endif      // _WIN32_IE >= 0x0300

#define TB_GETBUTTONTEXT        TB_GETBUTTONTEXTA
#define TB_SAVERESTORE          TB_SAVERESTOREA
#define TB_ADDSTRING            TB_ADDSTRINGA

#if (_WIN32_IE >= 0x0400)
#define TB_GETOBJECT            (WM_USER + 62)  // wParam == IID, lParam void **ppv
#define TB_GETHOTITEM           (WM_USER + 71)
#define TB_SETHOTITEM           (WM_USER + 72)  // wParam == iHotItem
#define TB_SETANCHORHIGHLIGHT   (WM_USER + 73)  // wParam == TRUE/FALSE
#define TB_GETANCHORHIGHLIGHT   (WM_USER + 74)
#define TB_MAPACCELERATORA      (WM_USER + 78)  // wParam == ch, lParam int * pidBtn

typedef struct {
    int   iButton;
    DWORD dwFlags;
} CSTBINSERTMARK, * LPCSTBINSERTMARK;
#define TBIMHT_AFTER      0x00000001 // TRUE = insert After iButton, otherwise before
#define TBIMHT_BACKGROUND 0x00000002 // TRUE iff missed buttons completely

#define TB_GETINSERTMARK        (WM_USER + 79)  // lParam == LPCSTBINSERTMARK
#define TB_SETINSERTMARK        (WM_USER + 80)  // lParam == LPCSTBINSERTMARK
#define TB_INSERTMARKHITTEST    (WM_USER + 81)  // wParam == LPMSPOINT lParam == LPCSTBINSERTMARK
#define TB_MOVEBUTTON           (WM_USER + 82)
#define TB_GETMAXSIZE           (WM_USER + 83)  // lParam == LPSIZE
#define TB_SETEXTENDEDSTYLE     (WM_USER + 84)  // For TBSTYLE_EX_*
#define TB_GETEXTENDEDSTYLE     (WM_USER + 85)  // For TBSTYLE_EX_*
#define TB_GETPADDING           (WM_USER + 86)
#define TB_SETPADDING           (WM_USER + 87)
#define TB_SETINSERTMARKCOLOR   (WM_USER + 88)
#define TB_GETINSERTMARKCOLOR   (WM_USER + 89)

#define TB_SETCOLORSCHEME       CCM_SETCOLORSCHEME  // lParam is color scheme
#define TB_GETCOLORSCHEME       CCM_GETCOLORSCHEME      // fills in COLORSCHEME pointed to by lParam

#define TB_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define TB_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT

#define TB_MAPACCELERATOR       TB_MAPACCELERATORA

#endif  // _WIN32_IE >= 0x0400

typedef struct {
    HMSINSTANCE       hInstOld;
    UINT_PTR        nIDOld;
    HMSINSTANCE       hInstNew;
    UINT_PTR        nIDNew;
    int             nButtons;
} MSTBREPLACEBITMAP, *LPMSTBREPLACEBITMAP;

#ifdef _WIN32

#define TBBF_LARGE              0x0001

#define TB_GETBITMAPFLAGS       (WM_USER + 41)

#if (_WIN32_IE >= 0x0400)
#define TBIF_IMAGE              0x00000001
#define TBIF_TEXT               0x00000002
#define TBIF_STATE              0x00000004
#define TBIF_STYLE              0x00000008
#define TBIF_LPARAM             0x00000010
#define TBIF_COMMAND            0x00000020
#define TBIF_SIZE               0x00000040

#if (_WIN32_IE >= 0x0500)
#define TBIF_BYINDEX            0x80000000 // this specifies that the wparam in Get/SetButtonInfo is an index, not id
#endif


typedef struct {
    UINT cbSize;
    DWORD dwMask;
    int idCommand;
    int iImage;
    BYTE fsState;
    BYTE fsStyle;
    WORD cx;
    DWORD_PTR lParam;
    LPSTR pszText;
    int cchText;
} MSTBBUTTONINFOA, *LPMSTBBUTTONINFOA;



#define MSTBBUTTONINFO MSTBBUTTONINFOA
#define LPMSTBBUTTONINFO LPMSTBBUTTONINFOA


// BUTTONINFO APIs do NOT support the string pool.
#define TB_GETBUTTONINFOA        (WM_USER + 65)
#define TB_SETBUTTONINFOA        (WM_USER + 66)
#define TB_GETBUTTONINFO        TB_GETBUTTONINFOA
#define TB_SETBUTTONINFO        TB_SETBUTTONINFOA



#define TB_HITTEST              (WM_USER + 69)

// New post Win95/NT4 for InsertButton and AddButton.  if iString member
// is a pointer to a string, it will be handled as a string like listview
// (although LPSTR_TEXTCALLBACK is not supported).
#define TB_INSERTBUTTON         TB_INSERTBUTTONA
#define TB_ADDBUTTONS           TB_ADDBUTTONSA

#define TB_SETDRAWTEXTFLAGS     (WM_USER + 70)  // wParam == mask lParam == bit values

#endif  // _WIN32_IE >= 0x0400

#if (_WIN32_IE >= 0x0500)

#define TB_GETSTRINGA           (WM_USER + 92)
#define TB_GETSTRING            TB_GETSTRINGA


#endif  // _WIN32_IE >= 0x0500

#if (_WIN32_WINNT >= 0x501)
#define TBMF_PAD                0x00000001
#define TBMF_BARPAD             0x00000002
#define TBMF_BUTTONSPACING      0x00000004

#if 0
typedef struct {
    UINT cbSize;
    DWORD dwMask;

    int cxPad;        // PAD
    int cyPad;
    int cxBarPad;     // BARPAD
    int cyBarPad;
    int cxButtonSpacing;   // BUTTONSPACING
    int cyButtonSpacing;
} TBMETRICS, * LPTBMETRICS;
#endif

#define TB_GETMETRICS           (WM_USER + 101)
#define TB_SETMETRICS           (WM_USER + 102)
#endif


#if (_WIN32_WINNT >= 0x501)
#define TB_SETWINDOWTHEME       CCM_SETWINDOWTHEME
#endif

#define TBN_GETBUTTONINFOA      (TBN_FIRST-0)
#define TBN_BEGINDRAG           (TBN_FIRST-1)
#define TBN_ENDDRAG             (TBN_FIRST-2)
#define TBN_BEGINADJUST         (TBN_FIRST-3)
#define TBN_ENDADJUST           (TBN_FIRST-4)
#define TBN_RESET               (TBN_FIRST-5)
#define TBN_QUERYINSERT         (TBN_FIRST-6)
#define TBN_QUERYDELETE         (TBN_FIRST-7)
#define TBN_TOOLBARCHANGE       (TBN_FIRST-8)
#define TBN_CUSTHELP            (TBN_FIRST-9)
#if (_WIN32_IE >= 0x0300)
#define TBN_DROPDOWN            (TBN_FIRST - 10)
#endif
#if (_WIN32_IE >= 0x0400)
#define TBN_GETOBJECT           (TBN_FIRST - 12)

// Structure for TBN_HOTITEMCHANGE notification
//
typedef struct tagCSNMTBHOTITEM
{
    MSNMHDR   hdr;
    int     idOld;
    int     idNew;
    DWORD   dwFlags;           // HICF_*
} CSNMTBHOTITEM, * LPCSNMTBHOTITEM;

// Hot item change flags
#define HICF_OTHER          0x00000000
#define HICF_MOUSE          0x00000001          // Triggered by mouse
#define HICF_ARROWKEYS      0x00000002          // Triggered by arrow keys
#define HICF_ACCELERATOR    0x00000004          // Triggered by accelerator
#define HICF_DUPACCEL       0x00000008          // This accelerator is not unique
#define HICF_ENTERING       0x00000010          // idOld is invalid
#define HICF_LEAVING        0x00000020          // idNew is invalid
#define HICF_RESELECT       0x00000040          // hot item reselected
#define HICF_LMOUSE         0x00000080          // left mouse button selected
#define HICF_TOGGLEDROPDOWN 0x00000100          // Toggle button's dropdown state


#define TBN_HOTITEMCHANGE       (TBN_FIRST - 13)
#define TBN_DRAGOUT             (TBN_FIRST - 14) // this is sent when the user clicks down on a button then drags off the button
#define TBN_DELETINGBUTTON      (TBN_FIRST - 15) // uses TBNOTIFY
#define TBN_GETDISPINFOA        (TBN_FIRST - 16) // This is sent when the  toolbar needs  some display information
#define TBN_GETDISPINFOW        (TBN_FIRST - 17) // This is sent when the  toolbar needs  some display information
#define TBN_GETINFOTIPA         (TBN_FIRST - 18)
#define TBN_GETINFOTIPW         (TBN_FIRST - 19)
#define TBN_GETBUTTONINFOW      (TBN_FIRST - 20)
#if (_WIN32_IE >= 0x0500)
#define TBN_RESTORE             (TBN_FIRST - 21)
#define TBN_SAVE                (TBN_FIRST - 22)
#define TBN_INITCUSTOMIZE       (TBN_FIRST - 23)
#define    TBNRF_HIDEHELP       0x00000001
#define    TBNRF_ENDCUSTOMIZE   0x00000002
#endif // (_WIN32_IE >= 0x0500)



#if (_WIN32_IE >= 0x0500)

#if 0
typedef struct tagNMTBSAVE
{
    MSNMHDR hdr;
    DWORD* pData;
    DWORD* pCurrent;
    UINT cbData;
    int iItem;
    int cButtons;
    MSTBBUTTON tbButton;
} NMTBSAVE, *LPNMTBSAVE;
#endif
#if 0
typedef struct tagNMTBRESTORE
{
    MSNMHDR hdr;
    DWORD* pData;
    DWORD* pCurrent;
    UINT cbData;
    int iItem;
    int cButtons;
    int cbBytesPerRecord;
    MSTBBUTTON tbButton;
} NMTBRESTORE, *LPNMTBRESTORE;
#endif
#endif // (_WIN32_IE >= 0x0500)

typedef struct tagMSNMTBGETINFOTIPA
{
    MSNMHDR hdr;
    LPSTR pszText;
    int cchTextMax;
    int iItem;
    LPARAM lParam;
} MSNMTBGETINFOTIPA, *LPMSNMTBGETINFOTIPA;

#define TBN_GETINFOTIP          TBN_GETINFOTIPA
#define MSNMTBGETINFOTIP          MSNMTBGETINFOTIPA
#define LPMSNMTBGETINFOTIP        LPMSNMTBGETINFOTIPA

#define TBNF_IMAGE              0x00000001
#define TBNF_TEXT               0x00000002
#define TBNF_DI_SETITEM         0x10000000

typedef struct {
    MSNMHDR  hdr;
    DWORD dwMask;     // [in] Specifies the values requested .[out] Client ask the data to be set for future use
    int idCommand;    // [in] id of button we're requesting info for
    DWORD_PTR lParam;  // [in] lParam of button
    int iImage;       // [out] image index
    LPSTR pszText;    // [out] new text for item
    int cchText;      // [in] size of buffer pointed to by pszText
} MSNMTBDISPINFOA, *LPMSNMTBDISPINFOA;


#define TBN_GETDISPINFO       TBN_GETDISPINFOA
#define MSNMTBDISPINFO          MSNMTBDISPINFOA
#define LPMSNMTBDISPINFO        LPMSNMTBDISPINFOA

// Return codes for TBN_DROPDOWN
#define TBDDRET_DEFAULT         0
#define TBDDRET_NODEFAULT       1
#define TBDDRET_TREATPRESSED    2       // Treat as a standard press button

#endif


#define TBN_GETBUTTONINFO       TBN_GETBUTTONINFOA

#if (_WIN32_IE >= 0x0300)
#define MSTBNOTIFYA MSNMTOOLBARA
#define LPMSTBNOTIFYA LPMSNMTOOLBARA
#else
#define tagMSNMTOOLBARA  tagMSTBNOTIFYA
#define MSNMTOOLBARA     MSTBNOTIFYA
#define LPMSNMTOOLBARA   LPMSTBNOTIFYA
#endif

#define TBNOTIFY       NMTOOLBAR
#define LPTBNOTIFY     LPNMTOOLBAR

#if (_WIN32_IE >= 0x0300)
typedef struct tagMSNMTOOLBARA {
    MSNMHDR   hdr;
    int     iItem;
    MSTBBUTTON tbButton;
    int     cchText;
    LPSTR   pszText;
#if (_WIN32_IE >= 0x500)
    MSRECT    rcButton;
#endif
} MSNMTOOLBARA, *LPMSNMTOOLBARA;
#endif




#define MSNMTOOLBAR               MSNMTOOLBARA
#define LPMSNMTOOLBAR             LPMSNMTOOLBARA

#endif

#endif      // NOTOOLBAR


#if (_WIN32_IE >= 0x0300)
//====== REBAR CONTROL ========================================================

#ifndef NOREBAR

#ifdef _WIN32
#define REBARCLASSNAMEA         "ReBarWindow32"

#define REBARCLASSNAME          REBARCLASSNAMEA

#else
#define REBARCLASSNAME          "ReBarWindow"
#endif

#define RBIM_IMAGELIST  0x00000001

// begin_r_commctrl

#if (_WIN32_IE >= 0x0400)
#define RBS_TOOLTIPS        0x0100
#define RBS_VARHEIGHT       0x0200
#define RBS_BANDBORDERS     0x0400
#define RBS_FIXEDORDER      0x0800
#define RBS_REGISTERDROP    0x1000
#define RBS_AUTOSIZE        0x2000
#define RBS_VERTICALGRIPPER 0x4000  // this always has the vertical gripper (default for horizontal mode)
#define RBS_DBLCLKTOGGLE    0x8000
#else
#define RBS_TOOLTIPS        0x00000100
#define RBS_VARHEIGHT       0x00000200
#define RBS_BANDBORDERS     0x00000400
#define RBS_FIXEDORDER      0x00000800
#endif      // _WIN32_IE >= 0x0400


// end_r_commctrl

typedef struct tagMSREBARINFO
{
    UINT        cbSize;
    UINT        fMask;
#ifndef NOIMAGEAPIS
    HMSIMAGELIST  himl;
#else
    HMSHANDLE      himl;
#endif
}   MSREBARINFO, *LPMSREBARINFO;

#define RBBS_BREAK          0x00000001  // break to new line
#define RBBS_FIXEDSIZE      0x00000002  // band can't be sized
#define RBBS_CHILDEDGE      0x00000004  // edge around top & bottom of child window
#define RBBS_HIDDEN         0x00000008  // don't show
#define RBBS_NOVERT         0x00000010  // don't show when vertical
#define RBBS_FIXEDBMP       0x00000020  // bitmap doesn't move during band resize
#if (_WIN32_IE >= 0x0400)               //
#define RBBS_VARIABLEHEIGHT 0x00000040  // allow autosizing of this child vertically
#define RBBS_GRIPPERALWAYS  0x00000080  // always show the gripper
#define RBBS_NOGRIPPER      0x00000100  // never show the gripper
#if (_WIN32_IE >= 0x0500)               //
#define RBBS_USECHEVRON     0x00000200  // display drop-down button for this band if it's sized smaller than ideal width
#if (_WIN32_IE >= 0x0501)               //
#define RBBS_HIDETITLE      0x00000400  // keep band title hidden
#define RBBS_TOPALIGN       0x00000800  // keep band title hidden
#endif // 0x0501                        //
#endif // 0x0500                        //
#endif // 0x0400                        //

#define RBBIM_STYLE         0x00000001
#define RBBIM_COLORS        0x00000002
#define RBBIM_TEXT          0x00000004
#define RBBIM_IMAGE         0x00000008
#define RBBIM_CHILD         0x00000010
#define RBBIM_CHILDSIZE     0x00000020
#define RBBIM_SIZE          0x00000040
#define RBBIM_BACKGROUND    0x00000080
#define RBBIM_ID            0x00000100
#if (_WIN32_IE >= 0x0400)
#define RBBIM_IDEALSIZE     0x00000200
#define RBBIM_LPARAM        0x00000400
#define RBBIM_HEADERSIZE    0x00000800  // control the size of the header
#endif

typedef struct tagMSREBARBANDINFOA
{
    UINT        cbSize;
    UINT        fMask;
    UINT        fStyle;
    COLORREF    clrFore;
    COLORREF    clrBack;
    LPSTR       lpText;
    UINT        cch;
    int         iImage;
    HMSWND        hwndChild;
    UINT        cxMinChild;
    UINT        cyMinChild;
    UINT        cx;
    HMSBITMAP     hbmBack;
    UINT        wID;
#if (_WIN32_IE >= 0x0400)
    UINT        cyChild;
    UINT        cyMaxChild;
    UINT        cyIntegral;
    UINT        cxIdeal;
    LPARAM      lParam;
    UINT        cxHeader;
#endif
}   MSREBARBANDINFOA, *LPMSREBARBANDINFOA;
typedef MSREBARBANDINFOA CONST *LPCMSREBARBANDINFOA;

#define MSREBARBANDINFOA_V3_SIZE CCSIZEOF_STRUCT(MSREBARBANDINFOA, wID)


#define MSREBARBANDINFO       MSREBARBANDINFOA
#define LPMSREBARBANDINFO     LPMSREBARBANDINFOA
#define LPCMSREBARBANDINFO    LPCMSREBARBANDINFOA
#define MSREBARBANDINFO_V3_SIZE MSREBARBANDINFOA_V3_SIZE

#define RB_INSERTBANDA  (WM_USER +  1)
#define RB_DELETEBAND   (WM_USER +  2)
#define RB_GETBARINFO   (WM_USER +  3)
#define RB_SETBARINFO   (WM_USER +  4)
#if (_WIN32_IE < 0x0400)
#define RB_GETBANDINFO  (WM_USER +  5)
#endif
#define RB_SETBANDINFOA (WM_USER +  6)
#define RB_SETPARENT    (WM_USER +  7)
#if (_WIN32_IE >= 0x0400)
#define RB_HITTEST      (WM_USER +  8)
#define RB_GETRECT      (WM_USER +  9)
#endif
#define RB_INSERTBANDW  (WM_USER +  10)
#define RB_SETBANDINFOW (WM_USER +  11)
#define RB_GETBANDCOUNT (WM_USER +  12)
#define RB_GETROWCOUNT  (WM_USER +  13)
#define RB_GETROWHEIGHT (WM_USER +  14)
#if (_WIN32_IE >= 0x0400)
#define RB_IDTOINDEX    (WM_USER +  16) // wParam == id
#define RB_GETTOOLTIPS  (WM_USER +  17)
#define RB_SETTOOLTIPS  (WM_USER +  18)
#define RB_SETBKCOLOR   (WM_USER +  19) // sets the default BK color
#define RB_GETBKCOLOR   (WM_USER +  20) // defaults to CLR_NONE
#define RB_SETTEXTCOLOR (WM_USER +  21)
#define RB_GETTEXTCOLOR (WM_USER +  22) // defaults to 0x00000000

#if (_WIN32_WINNT >= 0x0501)
#define RBSTR_CHANGERECT            0x0001   // flags for RB_SIZETORECT
#endif

#define RB_SIZETORECT   (WM_USER +  23) // resize the rebar/break bands and such to this rect (lparam)
#endif      // _WIN32_IE >= 0x0400

#define RB_SETCOLORSCHEME   CCM_SETCOLORSCHEME  // lParam is color scheme
#define RB_GETCOLORSCHEME   CCM_GETCOLORSCHEME  // fills in COLORSCHEME pointed to by lParam

#define RB_INSERTBAND   RB_INSERTBANDA
#define RB_SETBANDINFO   RB_SETBANDINFOA

#if (_WIN32_IE >= 0x0400)
// for manual drag control
// lparam == cursor pos
        // -1 means do it yourself.
        // -2 means use what you had saved before
#define RB_BEGINDRAG    (WM_USER + 24)
#define RB_ENDDRAG      (WM_USER + 25)
#define RB_DRAGMOVE     (WM_USER + 26)
#define RB_GETBARHEIGHT (WM_USER + 27)
#define RB_GETBANDINFOA (WM_USER + 29)

#define RB_GETBANDINFO   RB_GETBANDINFOA

#define RB_MINIMIZEBAND (WM_USER + 30)
#define RB_MAXIMIZEBAND (WM_USER + 31)

#define RB_GETDROPTARGET (CCM_GETDROPTARGET)

#define RB_GETBANDBORDERS (WM_USER + 34)  // returns in lparam = lprc the amount of edges added to band wparam

#define RB_SHOWBAND     (WM_USER + 35)      // show/hide band
#define RB_SETPALETTE   (WM_USER + 37)
#define RB_GETPALETTE   (WM_USER + 38)
#define RB_MOVEBAND     (WM_USER + 39)

#define RB_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define RB_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT

#endif      // _WIN32_IE >= 0x0400

#if (_WIN32_WINNT >= 0x501)
#define RB_GETBANDMARGINS   (WM_USER + 40)
#define RB_SETWINDOWTHEME       CCM_SETWINDOWTHEME
#endif

#if (_WIN32_IE >= 0x0500)
#define RB_PUSHCHEVRON  (WM_USER + 43)
#endif      // _WIN32_IE >= 0x0500

#define RBN_HEIGHTCHANGE    (RBN_FIRST - 0)

#if (_WIN32_IE >= 0x0400)
#define RBN_GETOBJECT       (RBN_FIRST - 1)
#define RBN_LAYOUTCHANGED   (RBN_FIRST - 2)
#define RBN_AUTOSIZE        (RBN_FIRST - 3)
#define RBN_BEGINDRAG       (RBN_FIRST - 4)
#define RBN_ENDDRAG         (RBN_FIRST - 5)
#define RBN_DELETINGBAND    (RBN_FIRST - 6)     // Uses MSNMREBAR
#define RBN_DELETEDBAND     (RBN_FIRST - 7)     // Uses MSNMREBAR
#define RBN_CHILDSIZE       (RBN_FIRST - 8)

#if (_WIN32_IE >= 0x0500)
#define RBN_CHEVRONPUSHED   (RBN_FIRST - 10)
#endif      // _WIN32_IE >= 0x0500


#if (_WIN32_IE >= 0x0500)
#define RBN_MINMAX          (RBN_FIRST - 21)
#endif

#if (_WIN32_WINNT >= 0x0501)
#define RBN_AUTOBREAK       (RBN_FIRST - 22)
#endif

typedef struct tagMSNMREBARCHILDSIZE
{
    MSNMHDR hdr;
    UINT uBand;
    UINT wID;
    MSRECT rcChild;
    MSRECT rcBand;
} MSNMREBARCHILDSIZE, *LPMSNMREBARCHILDSIZE;

typedef struct tagMSNMREBAR
{
    MSNMHDR   hdr;
    DWORD   dwMask;           // RBNM_*
    UINT    uBand;
    UINT    fStyle;
    UINT    wID;
    LPARAM  lParam;
} MSNMREBAR, *LPMSNMREBAR;

// Mask flags for MSNMREBAR
#define RBNM_ID         0x00000001
#define RBNM_STYLE      0x00000002
#define RBNM_LPARAM     0x00000004


typedef struct tagMSNMRBAUTOSIZE
{
    MSNMHDR hdr;
    BOOL fChanged;
    MSRECT rcTarget;
    MSRECT rcActual;
} MSNMRBAUTOSIZE, *LPMSNMRBAUTOSIZE;

#if (_WIN32_IE >= 0x0500)
typedef struct tagMSNMREBARCHEVRON
{
    MSNMHDR hdr;
    UINT uBand;
    UINT wID;
    LPARAM lParam;
    MSRECT rc;
    LPARAM lParamNM;
} MSNMREBARCHEVRON, *LPMSNMREBARCHEVRON;
#endif

#if (_WIN32_WINNT >= 0x0501)
#define RBAB_AUTOSIZE   0x0001   // These are not flags and are all mutually exclusive
#define RBAB_ADDBAND    0x0002

typedef struct tagMSNMREBARAUTOBREAK
{
    MSNMHDR hdr;
    UINT uBand;
    UINT wID;
    LPARAM lParam;
    UINT uMsg;
    UINT fStyleCurrent;
    BOOL fAutoBreak;
} MSNMREBARAUTOBREAK, *LPMSNMREBARAUTOBREAK;
#endif

#define RBHT_NOWHERE    0x0001
#define RBHT_CAPTION    0x0002
#define RBHT_CLIENT     0x0003
#define RBHT_GRABBER    0x0004
#if (_WIN32_IE >= 0x0500)
#define RBHT_CHEVRON    0x0008
#endif

typedef struct tagRB_HITTESTINFO
{
    MSPOINT pt;
    UINT flags;
    int iBand;
} MSRBHITTESTINFO, *LPMSRBHITTESTINFO;

#endif      // _WIN32_IE >= 0x0400

#endif      // NOREBAR

#endif      // _WIN32_IE >= 0x0300

//====== TOOLTIPS CONTROL =====================================================

#ifndef NOTOOLTIPS

#ifdef _WIN32

#define TOOLTIPS_CLASSA         "tooltips_class32"

#define TOOLTIPS_CLASS          TOOLTIPS_CLASSA

#else
#define TOOLTIPS_CLASS          "tooltips_class"
#endif

#if (_WIN32_IE >= 0x0300)
#define LPMSTOOLINFOA   LPMSTTTOOLINFOA
#define MSTOOLINFOA       MSTTTOOLINFOA
#else
#define   MSTTTOOLINFOA   MSTOOLINFOA
#define LPMSTTTOOLINFOA LPMSTOOLINFOA
#endif

#define LPTOOLINFO    LPTTTOOLINFO
#define TOOLINFO        TTTOOLINFO

#define MSTTTOOLINFOA_V1_SIZE CCSIZEOF_STRUCT(MSTTTOOLINFOA, lpszText)
#define MSTTTOOLINFOA_V2_SIZE CCSIZEOF_STRUCT(MSTTTOOLINFOA, lParam)
#define MSTTTOOLINFOA_V3_SIZE CCSIZEOF_STRUCT(MSTTTOOLINFOA, lpReserved)


typedef struct tagMSTOOLINFOA {
    UINT cbSize;
    UINT uFlags;
    HMSWND hwnd;
    UINT_PTR uId;
    MSRECT rect;
    HMSINSTANCE hinst;
    LPSTR lpszText;
#if (_WIN32_IE >= 0x0300)
    LPARAM lParam;
#endif
#if (_WIN32_WINNT >= 0x0501)
    void *lpReserved;
#endif
} MSTTTOOLINFOA, NEAR *PMSTOOLINFOA, *LPMSTTTOOLINFOA;


#define PMSTOOLINFO               PMSTOOLINFOA
#define MSTTTOOLINFO              MSTTTOOLINFOA
#define LPMSTTTOOLINFO            LPMSTTTOOLINFOA
#define MSTTTOOLINFO_V1_SIZE MSTTTOOLINFOA_V1_SIZE

// begin_r_commctrl

#define TTS_ALWAYSTIP           0x01
#define TTS_NOPREFIX            0x02
#if (_WIN32_IE >= 0x0500)
#define TTS_NOANIMATE           0x10
#define TTS_NOFADE              0x20
#define TTS_BALLOON             0x40
#define TTS_CLOSE               0x80
#endif

// end_r_commctrl

#define TTF_IDISHMSWND            0x0001

// Use this to center around trackpoint in trackmode
// -OR- to center around tool in normal mode.
// Use TTF_ABSOLUTE to place the tip exactly at the track coords when
// in tracking mode.  TTF_ABSOLUTE can be used in conjunction with TTF_CENTERTIP
// to center the tip absolutely about the track point.

#define TTF_CENTERTIP           0x0002
#define TTF_RTLREADING          0x0004
#define TTF_SUBCLASS            0x0010
#if (_WIN32_IE >= 0x0300)
#define TTF_TRACK               0x0020
#define TTF_ABSOLUTE            0x0080
#define TTF_TRANSPARENT         0x0100
#if (_WIN32_IE >= 0x0501)
#define TTF_PARSELINKS          0x1000
#endif // _WIN32_IE >= 0x0501
#define TTF_DI_SETITEM          0x8000       // valid only on the TTN_NEEDTEXT callback
#endif      // _WIN32_IE >= 0x0300


#define TTDT_AUTOMATIC          0
#define TTDT_RESHOW             1
#define TTDT_AUTOPOP            2
#define TTDT_INITIAL            3

// ToolTip Icons (Set with TTM_SETTITLE)
#define TTI_NONE                0
#define TTI_INFO                1
#define TTI_WARNING             2
#define TTI_ERROR               3

// Tool Tip Messages
#define TTM_ACTIVATE            (WM_USER + 1)
#define TTM_SETDELAYTIME        (WM_USER + 3)
#define TTM_ADDTOOLA            (WM_USER + 4)
#define TTM_DELTOOLA            (WM_USER + 5)
#define TTM_NEWTOOLRECTA        (WM_USER + 6)
#define TTM_RELAYEVENT          (WM_USER + 7)

#define TTM_GETTOOLINFOA        (WM_USER + 8)

#define TTM_SETTOOLINFOA        (WM_USER + 9)

#define TTM_HITTESTA            (WM_USER +10)
#define TTM_GETTEXTA            (WM_USER +11)
#define TTM_UPDATETIPTEXTA      (WM_USER +12)
#define TTM_GETTOOLCOUNT        (WM_USER +13)
#define TTM_ENUMTOOLSA          (WM_USER +14)
#define TTM_GETCURRENTTOOLA     (WM_USER + 15)
#define TTM_WINDOWFROMMSPOINT     (WM_USER + 16)
#if (_WIN32_IE >= 0x0300)
#define TTM_TRACKACTIVATE       (WM_USER + 17)  // wParam = TRUE/FALSE start end  lparam = LPTOOLINFO
#define TTM_TRACKPOSITION       (WM_USER + 18)  // lParam = dwPos
#define TTM_SETTIPBKCOLOR       (WM_USER + 19)
#define TTM_SETTIPTEXTCOLOR     (WM_USER + 20)
#define TTM_GETDELAYTIME        (WM_USER + 21)
#define TTM_GETTIPBKCOLOR       (WM_USER + 22)
#define TTM_GETTIPTEXTCOLOR     (WM_USER + 23)
#define TTM_SETMAXTIPWIDTH      (WM_USER + 24)
#define TTM_GETMAXTIPWIDTH      (WM_USER + 25)
#define TTM_SETMARGIN           (WM_USER + 26)  // lParam = lprc
#define TTM_GETMARGIN           (WM_USER + 27)  // lParam = lprc
#define TTM_POP                 (WM_USER + 28)
#endif
#if (_WIN32_IE >= 0x0400)
#define TTM_UPDATE              (WM_USER + 29)
#endif
#if (_WIN32_IE >= 0x0500)
#define TTM_GETBUBBLESIZE       (WM_USER + 30)
#define TTM_ADJUSTRECT          (WM_USER + 31)
#define TTM_SETTITLEA           (WM_USER + 32)  // wParam = TTI_*, lParam = char* szTitle
#endif

#if (_WIN32_WINNT >= 0x0501)
#define TTM_POPUP               (WM_USER + 34)
#define TTM_GETTITLE            (WM_USER + 35) // wParam = 0, lParam = TTGETTITLE*

#if 0
typedef struct _TTGETTITLE
{
    DWORD dwSize;
    UINT uTitleBitmap;
    UINT cch;
    WCHAR* pszTitle;
} TTGETTITLE, *PTTGETTITLE;
#endif
#endif


#define TTM_ADDTOOL             TTM_ADDTOOLA
#define TTM_DELTOOL             TTM_DELTOOLA
#define TTM_NEWTOOLRECT         TTM_NEWTOOLRECTA
#define TTM_GETTOOLINFO         TTM_GETTOOLINFOA
#define TTM_SETTOOLINFO         TTM_SETTOOLINFOA
#define TTM_HITTEST             TTM_HITTESTA
#define TTM_GETTEXT             TTM_GETTEXTA
#define TTM_UPDATETIPTEXT       TTM_UPDATETIPTEXTA
#define TTM_ENUMTOOLS           TTM_ENUMTOOLSA
#define TTM_GETCURRENTTOOL      TTM_GETCURRENTTOOLA
#if (_WIN32_IE >= 0x0500)
#define TTM_SETTITLE            TTM_SETTITLEA
#endif

#if (_WIN32_WINNT >= 0x501)
#define TTM_SETWINDOWTHEME      CCM_SETWINDOWTHEME
#endif


#if (_WIN32_IE >= 0x0300)
#define LPMSHITTESTINFOA    LPMSTTHITTESTINFOA
#else
#define LPMSTTHITTESTINFOA  LPMSHITTESTINFOA
#endif

#define LPCSHITTESTINFO     LPMSTTHITTESTINFO

typedef struct tagTT_HITTESTINFOA {
    HMSWND hwnd;
    MSPOINT pt;
    MSTTTOOLINFOA ti;
} MSTTHITTESTINFOA, *LPMSTTHITTESTINFOA;


#define MSTTHITTESTINFO           MSTTHITTESTINFOA
#define LPMSTTHITTESTINFO         LPMSTTHITTESTINFOA

#define TTN_GETDISPINFOA        (TTN_FIRST - 0)
#define TTN_SHOW                (TTN_FIRST - 1)
#define TTN_POP                 (TTN_FIRST - 2)
#define TTN_LINKCLICK           (TTN_FIRST - 3)

#define TTN_GETDISPINFO         TTN_GETDISPINFOA

#define TTN_NEEDTEXT            TTN_GETDISPINFO
#define TTN_NEEDTEXTA           TTN_GETDISPINFOA

#if (_WIN32_IE >= 0x0300)
#define MSTOOLTIPTEXTA MSNMTTDISPINFOA
#define LPMSTOOLTIPTEXTA LPMSNMTTDISPINFOA
#else
#define tagMSNMTTDISPINFOA  tagMSTOOLTIPTEXTA
#define MSNMTTDISPINFOA     MSTOOLTIPTEXTA
#define LPMSNMTTDISPINFOA   LPMSTOOLTIPTEXTA
#endif

#define TOOLTIPTEXT    NMTTDISPINFO
#define LPTOOLTIPTEXT  LPNMTTDISPINFO

#define MSNMTTDISPINFOA_V1_SIZE CCSIZEOF_STRUCT(MSNMTTDISPINFOA, uFlags)
#define MSNMTTDISPINFOW_V1_SIZE CCSIZEOF_STRUCT(MSNMTTDISPINFOW, uFlags)

typedef struct tagMSNMTTDISPINFOA {
    MSNMHDR hdr;
    LPSTR lpszText;
    char szText[80];
    HMSINSTANCE hinst;
    UINT uFlags;
#if (_WIN32_IE >= 0x0300)
    LPARAM lParam;
#endif
} MSNMTTDISPINFOA, *LPMSNMTTDISPINFOA;


#define MSNMTTDISPINFO            MSNMTTDISPINFOA
#define LPMSNMTTDISPINFO          LPMSNMTTDISPINFOA
#define MSNMTTDISPINFO_V1_SIZE MSNMTTDISPINFOA_V1_SIZE

#endif      // NOTOOLTIPS


//====== STATUS BAR CONTROL ===================================================

#ifndef NOSTATUSBAR

// begin_r_commctrl

#define SBARS_SIZEGRIP          0x0100
#if (_WIN32_IE >= 0x0500)
#define SBARS_TOOLTIPS          0x0800
#endif

#if (_WIN32_IE >= 0x0400)
// this is a status bar flag, preference to SBARS_TOOLTIPS
#define SBT_TOOLTIPS            0x0800
#endif

// end_r_commctrl

void WINAPI MSDrawStatusText(HMSDC hDC, LPMSRECT lprc, LPCSTR pszText, UINT uFlags);

HMSWND WINAPI MSCreateStatusWindow(LONG style, LPCSTR lpszText, HMSWND hwndParent, UINT wID);


#ifdef _WIN32
#define STATUSCLASSNAMEA        "msctls_statusbar32"

#define STATUSCLASSNAME         STATUSCLASSNAMEA

#else
#define STATUSCLASSNAME         "msctls_statusbar"
#endif

#define SB_SETTEXTA             (WM_USER+1)
#define SB_GETTEXTA             (WM_USER+2)
#define SB_GETTEXTLENGTHA       (WM_USER+3)

#define SB_GETTEXT              SB_GETTEXTA
#define SB_SETTEXT              SB_SETTEXTA
#define SB_GETTEXTLENGTH        SB_GETTEXTLENGTHA
#if (_WIN32_IE >= 0x0400)
#define SB_SETTIPTEXT           SB_SETTIPTEXTA
#define SB_GETTIPTEXT           SB_GETTIPTEXTA
#endif


#define SB_SETPARTS             (WM_USER+4)
#define SB_GETPARTS             (WM_USER+6)
#define SB_GETBORDERS           (WM_USER+7)
#define SB_SETMINHEIGHT         (WM_USER+8)
#define SB_SIMPLE               (WM_USER+9)
#define SB_GETRECT              (WM_USER+10)
#if (_WIN32_IE >= 0x0300)
#define SB_ISSIMPLE             (WM_USER+14)
#endif
#if (_WIN32_IE >= 0x0400)
#define SB_SETICON              (WM_USER+15)
#define SB_SETTIPTEXTA          (WM_USER+16)
#define SB_GETTIPTEXTA          (WM_USER+18)
#define SB_GETICON              (WM_USER+20)
#define SB_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define SB_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT
#endif

#define SBT_OWNERDRAW            0x1000
#define SBT_NOBORDERS            0x0100
#define SBT_POPOUT               0x0200
#define SBT_RTLREADING           0x0400
#if (_WIN32_IE >= 0x0500)
#define SBT_NOTABPARSING         0x0800
#endif

#define SB_SETBKCOLOR           CCM_SETBKCOLOR      // lParam = bkColor

/// status bar notifications
#if (_WIN32_IE >= 0x0400)
#define SBN_SIMPLEMODECHANGE    (SBN_FIRST - 0)
#endif

#if (_WIN32_IE >= 0x0500)
// refers to the data saved for simple mode
#define SB_SIMPLEID  0x00ff
#endif

#endif      // NOSTATUSBAR

//====== MENU HELP ============================================================

#ifndef NOMENUHELP

void WINAPI MSMenuHelp(UINT uMsg, WPARAM wParam, LPARAM lParam, HMSMENU hMainMenu, HMSINSTANCE hInst, HMSWND hwndStatus, UINT *lpwIDs);
BOOL WINAPI MSShowHideMenuCtl(HMSWND hWnd, UINT_PTR uFlags, LPINT lpInfo);
void WINAPI MSGetEffectiveClientRect(HMSWND hWnd, LPMSRECT lprc, LPINT lpInfo);

#define MINSYSCOMMAND   SC_SIZE

#endif


//====== TRACKBAR CONTROL =====================================================

#ifndef NOTRACKBAR
struct _TRACKBARSTYTLE;
typedef struct _TRACKBARSTYTLE* HTRACKBAR;

#ifdef _WIN32

#define TRACKBAR_CLASSA         "msctls_trackbar32"

#define  TRACKBAR_CLASS         TRACKBAR_CLASSA

#else
#define TRACKBAR_CLASS          "msctls_trackbar"
#endif


// begin_r_commctrl

#define TBS_AUTOTICKS           0x0001
#define TBS_VERT                0x0002
#define TBS_HORZ                0x0000
#define TBS_TOP                 0x0004
#define TBS_BOTTOM              0x0000
#define TBS_LEFT                0x0004
#define TBS_RIGHT               0x0000
#define TBS_BOTH                0x0008
#define TBS_NOTICKS             0x0010
#define TBS_ENABLESELRANGE      0x0020
#define TBS_FIXEDLENGTH         0x0040
#define TBS_NOTHUMB             0x0080
#if (_WIN32_IE >= 0x0300)
#define TBS_TOOLTIPS            0x0100
#endif
#if (_WIN32_IE >= 0x0500)
#define TBS_REVERSED            0x0200  // Accessibility hint: the smaller number (usually the min value) means "high" and the larger number (usually the max value) means "low"
#endif

#if (_WIN32_IE >= 0x0501)
#define TBS_DOWNISLEFT          0x0400  // Down=Left and Up=Right (default is Down=Right and Up=Left)
#endif

// end_r_commctrl

#define TBM_GETPOS              (WM_USER)
#define TBM_GETRANGEMIN         (WM_USER+1)
#define TBM_GETRANGEMAX         (WM_USER+2)
#define TBM_GETTIC              (WM_USER+3)
#define TBM_SETTIC              (WM_USER+4)
#define TBM_SETPOS              (WM_USER+5)
#define TBM_SETRANGE            (WM_USER+6)
#define TBM_SETRANGEMIN         (WM_USER+7)
#define TBM_SETRANGEMAX         (WM_USER+8)
#define TBM_CLEARTICS           (WM_USER+9)
#define TBM_SETSEL              (WM_USER+10)
#define TBM_SETSELSTART         (WM_USER+11)
#define TBM_SETSELEND           (WM_USER+12)
#define TBM_GETPTICS            (WM_USER+14)
#define TBM_GETTICPOS           (WM_USER+15)
#define TBM_GETNUMTICS          (WM_USER+16)
#define TBM_GETSELSTART         (WM_USER+17)
#define TBM_GETSELEND           (WM_USER+18)
#define TBM_CLEARSEL            (WM_USER+19)
#define TBM_SETTICFREQ          (WM_USER+20)
#define TBM_SETPAGESIZE         (WM_USER+21)
#define TBM_GETPAGESIZE         (WM_USER+22)
#define TBM_SETLINESIZE         (WM_USER+23)
#define TBM_GETLINESIZE         (WM_USER+24)
#define TBM_GETTHUMBRECT        (WM_USER+25)
#define TBM_GETCHANNELRECT      (WM_USER+26)
#define TBM_SETTHUMBLENGTH      (WM_USER+27)
#define TBM_GETTHUMBLENGTH      (WM_USER+28)
#if (_WIN32_IE >= 0x0300)
#define TBM_SETTOOLTIPS         (WM_USER+29)
#define TBM_GETTOOLTIPS         (WM_USER+30)
#define TBM_SETTIPSIDE          (WM_USER+31)
// TrackBar Tip Side flags
#define TBTS_TOP                0
#define TBTS_LEFT               1
#define TBTS_BOTTOM             2
#define TBTS_RIGHT              3

#define TBM_SETBUDDY            (WM_USER+32) // wparam = BOOL fLeft; (or right)
#define TBM_GETBUDDY            (WM_USER+33) // wparam = BOOL fLeft; (or right)
#endif
#if (_WIN32_IE >= 0x0400)
#define TBM_SETUNICODEFORMAT    CCM_SETUNICODEFORMAT
#define TBM_GETUNICODEFORMAT    CCM_GETUNICODEFORMAT
#endif


#define TB_LINEUP               0
#define TB_LINEDOWN             1
#define TB_PAGEUP               2
#define TB_PAGEDOWN             3
#define TB_THUMBPOSITION        4
#define TB_THUMBTRACK           5
#define TB_TOP                  6
#define TB_BOTTOM               7
#define TB_ENDTRACK             8


#if (_WIN32_IE >= 0x0300)
// custom draw item specs
#define TBCD_TICS    0x0001
#define TBCD_THUMB   0x0002
#define TBCD_CHANNEL 0x0003
#endif

#endif // trackbar

//====== DRAG LIST CONTROL ====================================================

#ifndef NODRAGLIST

typedef struct tagMSDRAGLISTINFO {
    UINT uNotification;
    HMSWND hWnd;
    MSPOINT ptCursor;
} MSDRAGLISTINFO, *LPMSDRAGLISTINFO;

#define DL_BEGINDRAG            (WM_USER+133)
#define DL_DRAGGING             (WM_USER+134)
#define DL_DROPPED              (WM_USER+135)
#define DL_CANCELDRAG           (WM_USER+136)

#define DL_CURSORSET            0
#define DL_STOPCURSOR           1
#define DL_COPYCURSOR           2
#define DL_MOVECURSOR           3

#define DRAGLISTMSGSTRING       TEXT("commctrl_DragListMsg")

BOOL WINAPI MSMakeDragList(HMSWND hLB);
void WINAPI MSDrawInsert(HMSWND handParent, HMSWND hLB, int nItem);

int WINAPI MSLBItemFromPt(HMSWND hLB, MSPOINT pt, BOOL bAutoScroll);

#endif


//====== UPDOWN CONTROL =======================================================

#ifndef NOUPDOWN
struct _UPDOWNSTYLE;
typedef struct _UPDOWNSTYLE* HUPDOWN;

#ifdef _WIN32

#define UPDOWN_CLASSA           "msctls_updown32"

#define  UPDOWN_CLASS           UPDOWN_CLASSA

#else
#define UPDOWN_CLASS            "msctls_updown"
#endif


typedef struct tagMSUDACCEL {
    UINT nSec;
    UINT nInc;
} MSUDACCEL, *LPMSUDACCEL;

#define UD_MAXVAL               0x7fff
#define UD_MINVAL               (-UD_MAXVAL)

// begin_r_commctrl

#define UDS_WRAP                0x0001
#define UDS_SETBUDDYINT         0x0002
#define UDS_ALIGNRIGHT          0x0004
#define UDS_ALIGNLEFT           0x0008
#define UDS_AUTOBUDDY           0x0010
#define UDS_ARROWKEYS           0x0020
#define UDS_HORZ                0x0040
#define UDS_NOTHOUSANDS         0x0080
#if (_WIN32_IE >= 0x0300)
#define UDS_HOTTRACK            0x0100
#endif

// end_r_commctrl

#define UDM_SETRANGE            (WM_USER+101)
#define UDM_GETRANGE            (WM_USER+102)
#define UDM_SETPOS              (WM_USER+103)
#define UDM_GETPOS              (WM_USER+104)
#define UDM_SETBUDDY            (WM_USER+105)
#define UDM_GETBUDDY            (WM_USER+106)
#define UDM_SETACCEL            (WM_USER+107)
#define UDM_GETACCEL            (WM_USER+108)
#define UDM_SETBASE             (WM_USER+109)
#define UDM_GETBASE             (WM_USER+110)
#if (_WIN32_IE >= 0x0400)
#define UDM_SETRANGE32          (WM_USER+111)
#define UDM_GETRANGE32          (WM_USER+112) // wParam & lParam are LPINT
#define UDM_SETUNICODEFORMAT    CCM_SETUNICODEFORMAT
#define UDM_GETUNICODEFORMAT    CCM_GETUNICODEFORMAT
#endif
#if (_WIN32_IE >= 0x0500)
#define UDM_SETPOS32            (WM_USER+113)
#define UDM_GETPOS32            (WM_USER+114)
#endif

HMSWND WINAPI MSCreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy,
                                HMSWND hParent, int nID, HMSINSTANCE hInst,
                                HMSWND hBuddy,
                                int nUpper, int nLower, int nPos);

#if (_WIN32_IE >= 0x0300)
#define CSNM_UPDOWN      MSNMUPDOWN
#define LPCSNM_UPDOWN  LPMSNMUPDOWN
#else
#define MSNMUPDOWN      CSNM_UPDOWN
#define LPMSNMUPDOWN  LPCSNM_UPDOWN
#endif

typedef struct tagNM_UPDOWN
{
    MSNMHDR hdr;
    int iPos;
    int iDelta;
} MSNMUPDOWN, *LPMSNMUPDOWN;

#define UDN_DELTAPOS            (UDN_FIRST - 1)

#endif  // NOUPDOWN


//====== PROGRESS CONTROL =====================================================

#ifndef NOPROGRESS

#ifdef _WIN32

#define PROGRESS_CLASSA         "msctls_progress32"

#define  PROGRESS_CLASS         PROGRESS_CLASSA

#else
#define PROGRESS_CLASS          "msctls_progress"
#endif

// begin_r_commctrl

#if (_WIN32_IE >= 0x0300)
#define PBS_SMOOTH              0x01
#define PBS_VERTICAL            0x04
#endif

// end_r_commctrl

#define PBM_SETRANGE            (WM_USER+1)
#define PBM_SETPOS              (WM_USER+2)
#define PBM_DELTAPOS            (WM_USER+3)
#define PBM_SETSTEP             (WM_USER+4)
#define PBM_STEPIT              (WM_USER+5)
#if (_WIN32_IE >= 0x0300)
#define PBM_SETRANGE32          (WM_USER+6)  // lParam = high, wParam = low
typedef struct
{
   int iLow;
   int iHigh;
} CSPBRANGE, *PCSPBRANGE;
#define PBM_GETRANGE            (WM_USER+7)  // wParam = return (TRUE ? low : high). lParam = PCSPBRANGE or NULL
#define PBM_GETPOS              (WM_USER+8)
#if (_WIN32_IE >= 0x0400)
#define PBM_SETBARCOLOR         (WM_USER+9)             // lParam = bar color
#endif      // _WIN32_IE >= 0x0400
#define PBM_SETBKCOLOR          CCM_SETBKCOLOR  // lParam = bkColor
#endif      // _WIN32_IE >= 0x0300


#endif  // NOPROGRESS


//====== HOTKEY CONTROL =======================================================

#ifndef NOHOTKEY

#define HOTKEYF_SHIFT           0x01
#define HOTKEYF_CONTROL         0x02
#define HOTKEYF_ALT             0x04
#ifdef _MAC
#define HOTKEYF_EXT             0x80
#else
#define HOTKEYF_EXT             0x08
#endif

#define HKCOMB_NONE             0x0001
#define HKCOMB_S                0x0002
#define HKCOMB_C                0x0004
#define HKCOMB_A                0x0008
#define HKCOMB_SC               0x0010
#define HKCOMB_SA               0x0020
#define HKCOMB_CA               0x0040
#define HKCOMB_SCA              0x0080


#define HKM_SETHOTKEY           (WM_USER+1)
#define HKM_GETHOTKEY           (WM_USER+2)
#define HKM_SETRULES            (WM_USER+3)

#ifdef _WIN32

#define HOTKEY_CLASSA           "msctls_hotkey32"

#define HOTKEY_CLASS            HOTKEY_CLASSA

#else
#define HOTKEY_CLASS            "msctls_hotkey"
#endif

#endif  // NOHOTKEY

// begin_r_commctrl

//====== COMMON CONTROL STYLES ================================================

#define CCS_TOP                 0x00000001L
#define CCS_NOMOVEY             0x00000002L
#define CCS_BOTTOM              0x00000003L
#define CCS_NORESIZE            0x00000004L
#define CCS_NOPARENTALIGN       0x00000008L
#define CCS_ADJUSTABLE          0x00000020L
#define CCS_NODIVIDER           0x00000040L
#if (_WIN32_IE >= 0x0300)
#define CCS_VERT                0x00000080L
#define CCS_LEFT                (CCS_VERT | CCS_TOP)
#define CCS_RIGHT               (CCS_VERT | CCS_BOTTOM)
#define CCS_NOMOVEX             (CCS_VERT | CCS_NOMOVEY)
#endif

// end_r_commctrl

//====== LISTVIEW CONTROL =====================================================

#ifndef NOLISTVIEW
struct _LISTVIEWSTYLE;
typedef struct _LISTVIEWSTYLE *HLISTVIEW;

#ifdef _WIN32

#define WC_LISTVIEWA            "SysListView32"

#define WC_LISTVIEW             WC_LISTVIEWA

#else
#define WC_LISTVIEW             "SysListView"
#endif

// begin_r_commctrl

#define LVS_ICON                0x0000
#define LVS_REPORT              0x0001
#define LVS_SMALLICON           0x0002
#define LVS_LIST                0x0003
#define LVS_TYPEMASK            0x0003
#define LVS_SINGLESEL           0x0004
#define LVS_SHOWSELALWAYS       0x0008
#define LVS_SORTASCENDING       0x0010
#define LVS_SORTDESCENDING      0x0020
#define LVS_SHAREIMAGELISTS     0x0040
#define LVS_NOLABELWRAP         0x0080
#define LVS_AUTOARRANGE         0x0100
#define LVS_EDITLABELS          0x0200
#if (_WIN32_IE >= 0x0300)
#define LVS_OWNERDATA           0x1000
#endif
#define LVS_NOSCROLL            0x2000

#define LVS_TYPESTYLEMASK       0xfc00

#define LVS_ALIGNTOP            0x0000
#define LVS_ALIGNLEFT           0x0800
#define LVS_ALIGNMASK           0x0c00

#define LVS_OWNERDRAWFIXED      0x0400
#define LVS_NOCOLUMNHEADER      0x4000
#define LVS_NOSORTHEADER        0x8000

// end_r_commctrl

#if (_WIN32_IE >= 0x0400)
#define LVM_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define MSListView_SetUnicodeFormat(hwnd, fUnicode)  \
    (BOOL)SNDMSG((hwnd), LVM_SETUNICODEFORMAT, (WPARAM)(fUnicode), 0)

#define LVM_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT
#define MSListView_GetUnicodeFormat(hwnd)  \
    (BOOL)SNDMSG((hwnd), LVM_GETUNICODEFORMAT, 0, 0)
#endif

#define LVM_GETBKCOLOR          (LVM_FIRST + 0)
#define MSListView_GetBkColor(hwnd)  \
    (COLORREF)SNDMSG((hwnd), LVM_GETBKCOLOR, 0, 0L)

#define LVM_SETBKCOLOR          (LVM_FIRST + 1)
#define MSListView_SetBkColor(hwnd, clrBk) \
    (BOOL)SNDMSG((hwnd), LVM_SETBKCOLOR, 0, (LPARAM)(COLORREF)(clrBk))

#define LVM_GETIMAGELIST        (LVM_FIRST + 2)
#define MSListView_GetImageList(hwnd, iImageList) \
    (HMSIMAGELIST)SNDMSG((hwnd), LVM_GETIMAGELIST, (WPARAM)(INT)(iImageList), 0L)

#define LVSIL_NORMAL            0
#define LVSIL_SMALL             1
#define LVSIL_STATE             2

#define LVM_SETIMAGELIST        (LVM_FIRST + 3)
#define MSListView_SetImageList(hwnd, himl, iImageList) \
    (HMSIMAGELIST)SNDMSG((hwnd), LVM_SETIMAGELIST, (WPARAM)(iImageList), (LPARAM)(HMSIMAGELIST)(himl))

#define LVM_GETITEMCOUNT        (LVM_FIRST + 4)
#define MSListView_GetItemCount(hwnd) \
    (int)SNDMSG((hwnd), LVM_GETITEMCOUNT, 0, 0L)


#define LVIF_TEXT               0x0001
#define LVIF_IMAGE              0x0002
#define LVIF_PARAM              0x0004
#define LVIF_STATE              0x0008
#if (_WIN32_IE >= 0x0300)
#define LVIF_INDENT             0x0010
#define LVIF_NORECOMPUTE        0x0800
#endif
#if (_WIN32_WINNT >= 0x501)
#define LVIF_GROUPID            0x0100
#define LVIF_COLUMNS            0x0200
#endif

#define LVIS_FOCUSED            0x0001
#define LVIS_SELECTED           0x0002
#define LVIS_CUT                0x0004
#define LVIS_DROPHILITED        0x0008
#define LVIS_GLOW               0x0010
#define LVIS_ACTIVATING         0x0020

#define LVIS_OVERLAYMASK        0x0F00
#define LVIS_STATEIMAGEMASK     0xF000

#define INDEXTOSTATEIMAGEMASK(i) ((i) << 12)

#if (_WIN32_IE >= 0x0300)
#define I_INDENTCALLBACK        (-1)
#define MSLV_ITEMA MSLVITEMA
#define MSLV_ITEMW MSLVITEMW
#else
#define tagMSLVITEMA    _MSLV_ITEMA
#define MSLVITEMA       MSLV_ITEMA
#define tagMSLVITEMW    _MSLV_ITEMW
#define MSLVITEMW       MSLV_ITEMW
#endif

#if (_WIN32_WINNT >= 0x501)
#define I_GROUPIDCALLBACK   (-1)
#define I_GROUPIDNONE       (-2)
#endif
#define MSLV_ITEM MSLVITEM

#define MSLVITEMA_V1_SIZE CCSIZEOF_STRUCT(MSLVITEMA, lParam)
#define MSLVITEMW_V1_SIZE CCSIZEOF_STRUCT(MSLVITEMW, lParam)

typedef struct tagMSLVITEMA
{
    UINT mask;
    int iItem;
    int iSubItem;
    UINT state;
    UINT stateMask;
    LPSTR pszText;
    int cchTextMax;
    int iImage;
    LPARAM lParam;
#if (_WIN32_IE >= 0x0300)
    int iIndent;
#endif
#if (_WIN32_WINNT >= 0x501)
    int iGroupId;
    UINT cColumns; // tile view columns
    PUINT puColumns;
#endif
} MSLVITEMA, *LPMSLVITEMA;


#define MSLVITEM    MSLVITEMA
#define LPMSLVITEM  LPMSLVITEMA
#define MSLVITEM_V1_SIZE MSLVITEMA_V1_SIZE


#define LPSTR_TEXTCALLBACKA     ((LPSTR)-1L)
#define LPSTR_TEXTCALLBACK      LPSTR_TEXTCALLBACKA

#define I_IMAGECALLBACK         (-1)
#if (_WIN32_IE >= 0x0501)
#define I_IMAGENONE             (-2)
#endif  // 0x0501

#if (_WIN32_WINNT >= 0x501)
// For tileview
#define I_COLUMNSCALLBACK       ((UINT)-1)
#endif

#define LVM_GETITEMA            (LVM_FIRST + 5)
#define LVM_GETITEM             LVM_GETITEMA

#define MSListView_GetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), LVM_GETITEM, 0, (LPARAM)(MSLV_ITEM *)(pitem))


#define LVM_SETITEMA            (LVM_FIRST + 6)
#define LVM_SETITEM             LVM_SETITEMA

#define MSListView_SetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), LVM_SETITEM, 0, (LPARAM)(const MSLV_ITEM *)(pitem))


#define LVM_INSERTITEMA         (LVM_FIRST + 7)
#define LVM_INSERTITEM          LVM_INSERTITEMA
#define MSListView_InsertItem(hwnd, pitem)   \
    (int)SNDMSG((hwnd), LVM_INSERTITEM, 0, (LPARAM)(const MSLV_ITEM *)(pitem))


#define LVM_DELETEITEM          (LVM_FIRST + 8)
#define MSListView_DeleteItem(hwnd, i) \
    (BOOL)SNDMSG((hwnd), LVM_DELETEITEM, (WPARAM)(int)(i), 0L)


#define LVM_DELETEALLITEMS      (LVM_FIRST + 9)
#define MSListView_DeleteAllItems(hwnd) \
    (BOOL)SNDMSG((hwnd), LVM_DELETEALLITEMS, 0, 0L)


#define LVM_GETCALLBACKMASK     (LVM_FIRST + 10)
#define MSListView_GetCallbackMask(hwnd) \
    (BOOL)SNDMSG((hwnd), LVM_GETCALLBACKMASK, 0, 0)


#define LVM_SETCALLBACKMASK     (LVM_FIRST + 11)
#define MSListView_SetCallbackMask(hwnd, mask) \
    (BOOL)SNDMSG((hwnd), LVM_SETCALLBACKMASK, (WPARAM)(UINT)(mask), 0)


#define LVNI_ALL                0x0000
#define LVNI_FOCUSED            0x0001
#define LVNI_SELECTED           0x0002
#define LVNI_CUT                0x0004
#define LVNI_DROPHILITED        0x0008

#define LVNI_ABOVE              0x0100
#define LVNI_BELOW              0x0200
#define LVNI_TOLEFT             0x0400
#define LVNI_TORIGHT            0x0800


#define LVM_GETNEXTITEM         (LVM_FIRST + 12)
#define MSListView_GetNextItem(hwnd, i, flags) \
    (int)SNDMSG((hwnd), LVM_GETNEXTITEM, (WPARAM)(int)(i), MAKELPARAM((flags), 0))


#define LVFI_PARAM              0x0001
#define LVFI_STRING             0x0002
#define LVFI_PARTIAL            0x0008
#define LVFI_WRAP               0x0020
#define LVFI_NEARESTXY          0x0040

#if (_WIN32_IE >= 0x0300)
#define MSLV_FINDINFOA    MSLVFINDINFOA
#else
#define tagMSLVFINDINFOA  _MSLV_FINDINFOA
#define    MSLVFINDINFOA   MSLV_FINDINFOA
#endif

#define MSLV_FINDINFO  MSLVFINDINFO

typedef struct tagMSLVFINDINFOA
{
    UINT flags;
    LPCSTR psz;
    LPARAM lParam;
    MSPOINT pt;
    UINT vkDirection;
} MSLVFINDINFOA, *LPCSFINDINFOA;


#define  MSLVFINDINFO            MSLVFINDINFOA
#define  LPMSLVFINDINFO		   LPCSFINDINFOA  //added by yin

#define LVM_FINDITEMA           (LVM_FIRST + 13)
#define  LVM_FINDITEM           LVM_FINDITEMA

#define MSListView_FindItem(hwnd, iStart, plvfi) \
    (int)SNDMSG((hwnd), LVM_FINDITEM, (WPARAM)(int)(iStart), (LPARAM)(const LV_FINDINFO *)(plvfi))

#define LVIR_BOUNDS             0
#define LVIR_ICON               1
#define LVIR_LABEL              2
#define LVIR_SELECTBOUNDS       3


#define LVM_GETITEMRECT         (LVM_FIRST + 14)
#define MSListView_GetItemRect(hwnd, i, prc, code) \
     (BOOL)SNDMSG((hwnd), LVM_GETITEMRECT, (WPARAM)(int)(i), \
           ((prc) ? (((MSRECT *)(prc))->left = (code),(LPARAM)(MSRECT *)(prc)) : (LPARAM)(MSRECT *)NULL))


#define LVM_SETITEMPOSITION     (LVM_FIRST + 15)
#define MSListView_SetItemPosition(hwndLV, i, x, y) \
    (BOOL)SNDMSG((hwndLV), LVM_SETITEMPOSITION, (WPARAM)(int)(i), MAKELPARAM((x), (y)))


#define LVM_GETITEMPOSITION     (LVM_FIRST + 16)
#define MSListView_GetItemPosition(hwndLV, i, ppt) \
    (BOOL)SNDMSG((hwndLV), LVM_GETITEMPOSITION, (WPARAM)(int)(i), (LPARAM)(MSPOINT *)(ppt))


#define LVM_GETSTRINGWIDTHA     (LVM_FIRST + 17)
#define  LVM_GETSTRINGWIDTH     LVM_GETSTRINGWIDTHA

#define MSListView_GetStringWidth(hwndLV, psz) \
    (int)SNDMSG((hwndLV), LVM_GETSTRINGWIDTH, 0, (LPARAM)(LPCTSTR)(psz))


#define LVHT_NOWHERE            0x0001
#define LVHT_ONITEMICON         0x0002
#define LVHT_ONITEMLABEL        0x0004
#define LVHT_ONITEMSTATEICON    0x0008
#define LVHT_ONITEM             (LVHT_ONITEMICON | LVHT_ONITEMLABEL | LVHT_ONITEMSTATEICON)

#define LVHT_ABOVE              0x0008
#define LVHT_BELOW              0x0010
#define LVHT_TORIGHT            0x0020
#define LVHT_TOLEFT             0x0040


#if (_WIN32_IE >= 0x0300)
#define MSLV_HITTESTINFO MSLVHITTESTINFO
#else
#define tagMSLVHITTESTINFO  _MSLV_HITTESTINFO
#define    MSLVHITTESTINFO   MSLV_HITTESTINFO
#endif

#define MSLVHITTESTINFO_V1_SIZE CCSIZEOF_STRUCT(MSLVHITTESTINFO, iItem)

typedef struct tagMSLVHITTESTINFO
{
    MSPOINT pt;
    UINT flags;
    int iItem;
#if (_WIN32_IE >= 0x0300)
    int iSubItem;    // this is was NOT in win95.  valid only for LVM_SUBITEMHITTEST
#endif
} MSLVHITTESTINFO, *LPMSLVHITTESTINFO;

#define LVM_HITTEST             (LVM_FIRST + 18)
#define MSListView_HitTest(hwndLV, pinfo) \
    (int)SNDMSG((hwndLV), LVM_HITTEST, 0, (LPARAM)(MSLV_HITTESTINFO *)(pinfo))


#define LVM_ENSUREVISIBLE       (LVM_FIRST + 19)
#define MSListView_EnsureVisible(hwndLV, i, fPartialOK) \
    (BOOL)SNDMSG((hwndLV), LVM_ENSUREVISIBLE, (WPARAM)(int)(i), MAKELPARAM((fPartialOK), 0))


#define LVM_SCROLL              (LVM_FIRST + 20)
#define MSListView_Scroll(hwndLV, dx, dy) \
    (BOOL)SNDMSG((hwndLV), LVM_SCROLL, (WPARAM)(int)(dx), (LPARAM)(int)(dy))


#define LVM_REDRAWITEMS         (LVM_FIRST + 21)
#define MSListView_RedrawItems(hwndLV, iFirst, iLast) \
    (BOOL)SNDMSG((hwndLV), LVM_REDRAWITEMS, (WPARAM)(int)(iFirst), (LPARAM)(int)(iLast))


#define LVA_DEFAULT             0x0000
#define LVA_ALIGNLEFT           0x0001
#define LVA_ALIGNTOP            0x0002
#define LVA_SNAPTOGRID          0x0005


#define LVM_ARRANGE             (LVM_FIRST + 22)
#define MSListView_Arrange(hwndLV, code) \
    (BOOL)SNDMSG((hwndLV), LVM_ARRANGE, (WPARAM)(UINT)(code), 0L)


#define LVM_EDITLABELA          (LVM_FIRST + 23)
#define LVM_EDITLABEL           LVM_EDITLABELA

#define MSListView_EditLabel(hwndLV, i) \
    (HMSWND)SNDMSG((hwndLV), LVM_EDITLABEL, (WPARAM)(int)(i), 0L)


#define LVM_GETEDITCONTROL      (LVM_FIRST + 24)
#define MSListView_GetEditControl(hwndLV) \
    (HMSWND)SNDMSG((hwndLV), LVM_GETEDITCONTROL, 0, 0L)


#if (_WIN32_IE >= 0x0300)
#define MSLV_COLUMNA      MSLVCOLUMNA
#else
#define tagMSLVCOLUMNA    _MSLV_COLUMNA
#define    MSLVCOLUMNA     MSLV_COLUMNA
#endif

#define MSLV_COLUMN       AURALVCOLUMN

#define MSLVCOLUMNA_V1_SIZE CCSIZEOF_STRUCT(MSLVCOLUMNA, iSubItem)
#define MSLVCOLUMNW_V1_SIZE CCSIZEOF_STRUCT(AURALVCOLUMNW, iSubItem)

typedef struct tagMSLVCOLUMNA
{
    UINT mask;
    int fmt;
    int cx;
    LPSTR pszText;
    int cchTextMax;
    int iSubItem;
#if (_WIN32_IE >= 0x0300)
    int iImage;
    int iOrder;
#endif
} MSLVCOLUMNA, *LPMSLVCOLUMNA;


#define  AURALVCOLUMN               MSLVCOLUMNA
#define  LPAURALVCOLUMN             LPMSLVCOLUMNA
#define AURALVCOLUMN_V1_SIZE MSLVCOLUMNA_V1_SIZE


#define LVCF_FMT                0x0001
#define LVCF_WIDTH              0x0002
#define LVCF_TEXT               0x0004
#define LVCF_SUBITEM            0x0008
#if (_WIN32_IE >= 0x0300)
#define LVCF_IMAGE              0x0010
#define LVCF_ORDER              0x0020
#endif

#define LVCFMT_LEFT             0x0000
#define LVCFMT_RIGHT            0x0001
#define LVCFMT_CENTER           0x0002
#define LVCFMT_JUSTIFYMASK      0x0003

#if (_WIN32_IE >= 0x0300)
#define LVCFMT_IMAGE            0x0800
#define LVCFMT_BITMAP_ON_RIGHT  0x1000
#define LVCFMT_COL_HAS_IMAGES   0x8000
#endif

#define LVM_GETCOLUMNA          (LVM_FIRST + 25)
#define  LVM_GETCOLUMN          LVM_GETCOLUMNA

#define MSListView_GetColumn(hwnd, iCol, pcol) \
    (BOOL)SNDMSG((hwnd), LVM_GETCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(MSLV_COLUMN *)(pcol))


#define LVM_SETCOLUMNA          (LVM_FIRST + 26)
#define  LVM_SETCOLUMN          LVM_SETCOLUMNA

#define MSListView_SetColumn(hwnd, iCol, pcol) \
    (BOOL)SNDMSG((hwnd), LVM_SETCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(const MSLV_COLUMN *)(pcol))


#define LVM_INSERTCOLUMNA       (LVM_FIRST + 27)
#   define  LVM_INSERTCOLUMN    LVM_INSERTCOLUMNA

#define MSListView_InsertColumn(hwnd, iCol, pcol) \
    (int)SNDMSG((hwnd), LVM_INSERTCOLUMN, (WPARAM)(int)(iCol), (LPARAM)(const MSLV_COLUMN *)(pcol))


#define LVM_DELETECOLUMN        (LVM_FIRST + 28)
#define MSListView_DeleteColumn(hwnd, iCol) \
    (BOOL)SNDMSG((hwnd), LVM_DELETECOLUMN, (WPARAM)(int)(iCol), 0)


#define LVM_GETCOLUMNWIDTH      (LVM_FIRST + 29)
#define MSListView_GetColumnWidth(hwnd, iCol) \
    (int)SNDMSG((hwnd), LVM_GETCOLUMNWIDTH, (WPARAM)(int)(iCol), 0)


#define LVSCW_AUTOSIZE              -1
#define LVSCW_AUTOSIZE_USEHEADER    -2
#define LVM_SETCOLUMNWIDTH          (LVM_FIRST + 30)

#define MSListView_SetColumnWidth(hwnd, iCol, cx) \
    (BOOL)SNDMSG((hwnd), LVM_SETCOLUMNWIDTH, (WPARAM)(int)(iCol), MAKELPARAM((cx), 0))

#if (_WIN32_IE >= 0x0300)
#define LVM_GETHEADER               (LVM_FIRST + 31)
#define MSListView_GetHeader(hwnd)\
    (HMSWND)SNDMSG((hwnd), LVM_GETHEADER, 0, 0L)
#endif

#define LVM_CREATEDRAGIMAGE     (LVM_FIRST + 33)
#define MSListView_CreateDragImage(hwnd, i, lpptUpLeft) \
    (HMSIMAGELIST)SNDMSG((hwnd), LVM_CREATEDRAGIMAGE, (WPARAM)(int)(i), (LPARAM)(LPMSPOINT)(lpptUpLeft))


#define LVM_GETVIEWRECT         (LVM_FIRST + 34)
#define MSListView_GetViewRect(hwnd, prc) \
    (BOOL)SNDMSG((hwnd), LVM_GETVIEWRECT, 0, (LPARAM)(MSRECT *)(prc))


#define LVM_GETTEXTCOLOR        (LVM_FIRST + 35)
#define MSListView_GetTextColor(hwnd)  \
    (COLORREF)SNDMSG((hwnd), LVM_GETTEXTCOLOR, 0, 0L)


#define LVM_SETTEXTCOLOR        (LVM_FIRST + 36)
#define MSListView_SetTextColor(hwnd, clrText) \
    (BOOL)SNDMSG((hwnd), LVM_SETTEXTCOLOR, 0, (LPARAM)(COLORREF)(clrText))


#define LVM_GETTEXTBKCOLOR      (LVM_FIRST + 37)
#define MSListView_GetTextBkColor(hwnd)  \
    (COLORREF)SNDMSG((hwnd), LVM_GETTEXTBKCOLOR, 0, 0L)


#define LVM_SETTEXTBKCOLOR      (LVM_FIRST + 38)
#define MSListView_SetTextBkColor(hwnd, clrTextBk) \
    (BOOL)SNDMSG((hwnd), LVM_SETTEXTBKCOLOR, 0, (LPARAM)(COLORREF)(clrTextBk))


#define LVM_GETTOPINDEX         (LVM_FIRST + 39)
#define MSListView_GetTopIndex(hwndLV) \
    (int)SNDMSG((hwndLV), LVM_GETTOPINDEX, 0, 0)


#define LVM_GETCOUNTPERPAGE     (LVM_FIRST + 40)
#define MSListView_GetCountPerPage(hwndLV) \
    (int)SNDMSG((hwndLV), LVM_GETCOUNTPERPAGE, 0, 0)


#define LVM_GETORIGIN           (LVM_FIRST + 41)
#define MSListView_GetOrigin(hwndLV, ppt) \
    (BOOL)SNDMSG((hwndLV), LVM_GETORIGIN, (WPARAM)0, (LPARAM)(MSPOINT *)(ppt))


#define LVM_UPDATE              (LVM_FIRST + 42)
#define MSListView_Update(hwndLV, i) \
    (BOOL)SNDMSG((hwndLV), LVM_UPDATE, (WPARAM)(i), 0L)


#define LVM_SETITEMSTATE        (LVM_FIRST + 43)
#define MSListView_SetItemState(hwndLV, i, data, mask) \
{ MSLV_ITEM _ms_lvi;\
  _ms_lvi.stateMask = mask;\
  _ms_lvi.state = data;\
  SNDMSG((hwndLV), LVM_SETITEMSTATE, (WPARAM)(i), (LPARAM)(MSLV_ITEM *)&_ms_lvi);\
}

#if (_WIN32_IE >= 0x0300)
#define MSListView_SetCheckState(hwndLV, i, fCheck) \
  ListView_SetItemState(hwndLV, i, INDEXTOSTATEIMAGEMASK((fCheck)?2:1), LVIS_STATEIMAGEMASK)
#endif

#define LVM_GETITEMSTATE        (LVM_FIRST + 44)
#define MSListView_GetItemState(hwndLV, i, mask) \
   (UINT)SNDMSG((hwndLV), LVM_GETITEMSTATE, (WPARAM)(i), (LPARAM)(mask))

#if (_WIN32_IE >= 0x0300)
#define MSListView_GetCheckState(hwndLV, i) \
   ((((UINT)(SNDMSG((hwndLV), LVM_GETITEMSTATE, (WPARAM)(i), LVIS_STATEIMAGEMASK))) >> 12) -1)
#endif

#define LVM_GETITEMTEXTA        (LVM_FIRST + 45)

#define  LVM_GETITEMTEXT        LVM_GETITEMTEXTA

#define MSListView_GetItemText(hwndLV, i, iSubItem_, pszText_, cchTextMax_) \
{ MSLV_ITEM _ms_lvi;\
  _ms_lvi.iSubItem = iSubItem_;\
  _ms_lvi.cchTextMax = cchTextMax_;\
  _ms_lvi.pszText = pszText_;\
  SNDMSG((hwndLV), LVM_GETITEMTEXT, (WPARAM)(i), (LPARAM)(MSLV_ITEM *)&_ms_lvi);\
}


#define LVM_SETITEMTEXTA        (LVM_FIRST + 46)
#define  LVM_SETITEMTEXT        LVM_SETITEMTEXTA

#define MSListView_SetItemText(hwndLV, i, iSubItem_, pszText_) \
{ MSLV_ITEM _ms_lvi;\
  _ms_lvi.iSubItem = iSubItem_;\
  _ms_lvi.pszText = pszText_;\
  SNDMSG((hwndLV), LVM_SETITEMTEXT, (WPARAM)(i), (LPARAM)(MSLV_ITEM *)&_ms_lvi);\
}

#if (_WIN32_IE >= 0x0300)
// these flags only apply to LVS_OWNERDATA listviews in report or list mode
#define LVSICF_NOINVALIDATEALL  0x00000001
#define LVSICF_NOSCROLL         0x00000002
#endif

#define LVM_SETITEMCOUNT        (LVM_FIRST + 47)
#define MSListView_SetItemCount(hwndLV, cItems) \
  SNDMSG((hwndLV), LVM_SETITEMCOUNT, (WPARAM)(cItems), 0)

#if (_WIN32_IE >= 0x0300)
#define MSListView_SetItemCountEx(hwndLV, cItems, dwFlags) \
  SNDMSG((hwndLV), LVM_SETITEMCOUNT, (WPARAM)(cItems), (LPARAM)(dwFlags))
#endif

typedef int (CALLBACK *PFNLVCOMPARE)(LPARAM, LPARAM, LPARAM);


#define LVM_SORTITEMS           (LVM_FIRST + 48)
#define MSListView_SortItems(hwndLV, _pfnCompare, _lPrm) \
  (BOOL)SNDMSG((hwndLV), LVM_SORTITEMS, (WPARAM)(LPARAM)(_lPrm), \
  (LPARAM)(PFNLVCOMPARE)(_pfnCompare))


#define LVM_SETITEMPOSITION32   (LVM_FIRST + 49)
#define MSListView_SetItemPosition32(hwndLV, i, x0, y0) \
{   MSPOINT ptNewPos; \
    ptNewPos.x = x0; ptNewPos.y = y0; \
    SNDMSG((hwndLV), LVM_SETITEMPOSITION32, (WPARAM)(int)(i), (LPARAM)&ptNewPos); \
}


#define LVM_GETSELECTEDCOUNT    (LVM_FIRST + 50)
#define MSListView_GetSelectedCount(hwndLV) \
    (UINT)SNDMSG((hwndLV), LVM_GETSELECTEDCOUNT, 0, 0L)

#define LVM_GETITEMSPACING      (LVM_FIRST + 51)
#define MSListView_GetItemSpacing(hwndLV, fSmall) \
        (DWORD)SNDMSG((hwndLV), LVM_GETITEMSPACING, fSmall, 0L)


#define LVM_GETISEARCHSTRINGA   (LVM_FIRST + 52)

#define LVM_GETISEARCHSTRING    LVM_GETISEARCHSTRINGA

#define MSListView_GetISearchString(hwndLV, lpsz) \
        (BOOL)SNDMSG((hwndLV), LVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)(lpsz))

#if (_WIN32_IE >= 0x0300)
#define LVM_SETICONSPACING      (LVM_FIRST + 53)
// -1 for cx and cy means we'll use the default (system settings)
// 0 for cx or cy means use the current setting (allows you to change just one param)
#define MSListView_SetIconSpacing(hwndLV, cx, cy) \
        (DWORD)SNDMSG((hwndLV), LVM_SETICONSPACING, 0, MAKELONG(cx,cy))


#define LVM_SETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 54)   // optional wParam == mask
#define MSListView_SetExtendedListViewStyle(hwndLV, dw)\
        (DWORD)SNDMSG((hwndLV), LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dw)
#if (_WIN32_IE >= 0x0400)
#define MSListView_SetExtendedListViewStyleEx(hwndLV, dwMask, dw)\
        (DWORD)SNDMSG((hwndLV), LVM_SETEXTENDEDLISTVIEWSTYLE, dwMask, dw)
#endif

#define LVM_GETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 55)
#define MSListView_GetExtendedListViewStyle(hwndLV)\
        (DWORD)SNDMSG((hwndLV), LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0)

#define LVS_EX_GRIDLINES        0x00000001
#define LVS_EX_SUBITEMIMAGES    0x00000002
#define LVS_EX_CHECKBOXES       0x00000004
#define LVS_EX_TRACKSELECT      0x00000008
#define LVS_EX_HEADERDRAGDROP   0x00000010
#define LVS_EX_FULLROWSELECT    0x00000020 // applies to report mode only
#define LVS_EX_ONECLICKACTIVATE 0x00000040
#define LVS_EX_TWOCLICKACTIVATE 0x00000080
#if (_WIN32_IE >= 0x0400)
#define LVS_EX_FLATSB           0x00000100
#define LVS_EX_REGIONAL         0x00000200
#define LVS_EX_INFOTIP          0x00000400 // listview does InfoTips for you
#define LVS_EX_UNDERLINEHOT     0x00000800
#define LVS_EX_UNDERLINECOLD    0x00001000
#define LVS_EX_MULTIWORKAREAS   0x00002000
#endif
#if (_WIN32_IE >= 0x0500)
#define LVS_EX_LABELTIP         0x00004000 // listview unfolds partly hidden labels if it does not have infotip text
#define LVS_EX_BORDERSELECT     0x00008000 // border selection style instead of highlight
#endif  // End (_WIN32_IE >= 0x0500)
#if (_WIN32_WINNT >= 0x501)
#define LVS_EX_DOUBLEBUFFER     0x00010000
#define LVS_EX_HIDELABELS       0x00020000
#define LVS_EX_SINGLEROW        0x00040000
#define LVS_EX_SNAPTOGRID       0x00080000  // Icons automatically snap to grid.
#define LVS_EX_SIMPLESELECT     0x00100000  // Also changes overlay rendering to top right for icon mode.
#endif

#define LVS_EX_RIGHTSCROLL     0x00200000
#define LVM_GETSUBITEMRECT      (LVM_FIRST + 56)
#define MSListView_GetSubItemRect(hwnd, iItem, iSubItem, code, prc) \
        (BOOL)SNDMSG((hwnd), LVM_GETSUBITEMRECT, (WPARAM)(int)(iItem), \
                ((prc) ? ((((LPMSRECT)(prc))->top = iSubItem), (((LPMSRECT)(prc))->left = code), (LPARAM)(prc)) : (LPARAM)(LPMSRECT)NULL))

#define LVM_SUBITEMHITTEST      (LVM_FIRST + 57)
#define MSListView_SubItemHitTest(hwnd, plvhti) \
        (int)SNDMSG((hwnd), LVM_SUBITEMHITTEST, 0, (LPARAM)(LPMSLVHITTESTINFO)(plvhti))

#define LVM_SETCOLUMNORDERARRAY (LVM_FIRST + 58)
#define MSListView_SetColumnOrderArray(hwnd, iCount, pi) \
        (BOOL)SNDMSG((hwnd), LVM_SETCOLUMNORDERARRAY, (WPARAM)(iCount), (LPARAM)(LPINT)(pi))

#define LVM_GETCOLUMNORDERARRAY (LVM_FIRST + 59)
#define MSListView_GetColumnOrderArray(hwnd, iCount, pi) \
        (BOOL)SNDMSG((hwnd), LVM_GETCOLUMNORDERARRAY, (WPARAM)(iCount), (LPARAM)(LPINT)(pi))

#define LVM_SETHOTITEM  (LVM_FIRST + 60)
#define MSListView_SetHotItem(hwnd, i) \
        (int)SNDMSG((hwnd), LVM_SETHOTITEM, (WPARAM)(i), 0)

#define LVM_GETHOTITEM  (LVM_FIRST + 61)
#define MSListView_GetHotItem(hwnd) \
        (int)SNDMSG((hwnd), LVM_GETHOTITEM, 0, 0)

#define LVM_SETHOTCURSOR  (LVM_FIRST + 62)
#define MSListView_SetHotCursor(hwnd, hcur) \
        (HCURSOR)SNDMSG((hwnd), LVM_SETHOTCURSOR, 0, (LPARAM)(hcur))

#define LVM_GETHOTCURSOR  (LVM_FIRST + 63)
#define MSListView_GetHotCursor(hwnd) \
        (HCURSOR)SNDMSG((hwnd), LVM_GETHOTCURSOR, 0, 0)

#define LVM_APPROXIMATEVIEWRECT (LVM_FIRST + 64)
#define MSListView_ApproximateViewRect(hwnd, iWidth, iHeight, iCount) \
        (DWORD)SNDMSG((hwnd), LVM_APPROXIMATEVIEWRECT, iCount, MAKELPARAM(iWidth, iHeight))
#endif      // _WIN32_IE >= 0x0300

#if (_WIN32_IE >= 0x0400)

#define LV_MAX_WORKAREAS         16
#define LVM_SETWORKAREAS         (LVM_FIRST + 65)
#define MSListView_SetWorkAreas(hwnd, nWorkAreas, prc) \
    (BOOL)SNDMSG((hwnd), LVM_SETWORKAREAS, (WPARAM)(int)(nWorkAreas), (LPARAM)(MSRECT *)(prc))

#define LVM_GETWORKAREAS        (LVM_FIRST + 70)
#define MSListView_GetWorkAreas(hwnd, nWorkAreas, prc) \
    (BOOL)SNDMSG((hwnd), LVM_GETWORKAREAS, (WPARAM)(int)(nWorkAreas), (LPARAM)(MSRECT *)(prc))


#define LVM_GETNUMBEROFWORKAREAS  (LVM_FIRST + 73)
#define MSListView_GetNumberOfWorkAreas(hwnd, pnWorkAreas) \
    (BOOL)SNDMSG((hwnd), LVM_GETNUMBEROFWORKAREAS, 0, (LPARAM)(UINT *)(pnWorkAreas))


#define LVM_GETSELECTIONMARK    (LVM_FIRST + 66)
#define MSListView_GetSelectionMark(hwnd) \
    (int)SNDMSG((hwnd), LVM_GETSELECTIONMARK, 0, 0)

#define LVM_SETSELECTIONMARK    (LVM_FIRST + 67)
#define MSListView_SetSelectionMark(hwnd, i) \
    (int)SNDMSG((hwnd), LVM_SETSELECTIONMARK, 0, (LPARAM)(i))

#define LVM_SETHOVERTIME        (LVM_FIRST + 71)
#define MSListView_SetHoverTime(hwndLV, dwHoverTimeMs)\
        (DWORD)SNDMSG((hwndLV), LVM_SETHOVERTIME, 0, (LPARAM)(dwHoverTimeMs))

#define LVM_GETHOVERTIME        (LVM_FIRST + 72)
#define MSListView_GetHoverTime(hwndLV)\
        (DWORD)SNDMSG((hwndLV), LVM_GETHOVERTIME, 0, 0)

#define LVM_SETTOOLTIPS       (LVM_FIRST + 74)
#define MSListView_SetToolTips(hwndLV, hwndNewHwnd)\
        (HMSWND)SNDMSG((hwndLV), LVM_SETTOOLTIPS, (WPARAM)(hwndNewHwnd), 0)

#define LVM_GETTOOLTIPS       (LVM_FIRST + 78)
#define MSListView_GetToolTips(hwndLV)\
        (HMSWND)SNDMSG((hwndLV), LVM_GETTOOLTIPS, 0, 0)


#define LVM_SORTITEMSEX          (LVM_FIRST + 81)
#define MSListView_SortItemsEx(hwndLV, _pfnCompare, _lPrm) \
  (BOOL)SNDMSG((hwndLV), LVM_SORTITEMSEX, (WPARAM)(LPARAM)(_lPrm), (LPARAM)(PFNLVCOMPARE)(_pfnCompare))

typedef struct tagMSLVBKIMAGEA
{
    ULONG ulFlags;              // LVBKIF_*
    HMSBITMAP hbm;
    LPSTR pszImage;
    UINT cchImageMax;
    int xOffsetPercent;
    int yOffsetPercent;
} MSLVBKIMAGEA, *LPMSLVBKIMAGEA;

#define LVBKIF_SOURCE_NONE      0x00000000
#define LVBKIF_SOURCE_HMSBITMAP   0x00000001
#define LVBKIF_SOURCE_URL       0x00000002
#define LVBKIF_SOURCE_MASK      0x00000003
#define LVBKIF_STYLE_NORMAL     0x00000000
#define LVBKIF_STYLE_TILE       0x00000010
#define LVBKIF_STYLE_MASK       0x00000010
#if (_WIN32_WINNT >= 0x501)
#define LVBKIF_FLAG_TILEOFFSET  0x00000100
#define LVBKIF_TYPE_WATERMARK   0x10000000
#endif

#define LVM_SETBKIMAGEA         (LVM_FIRST + 68)
#define LVM_GETBKIMAGEA         (LVM_FIRST + 69)

#if (_WIN32_WINNT >= 0x501)
#define LVM_SETSELECTEDCOLUMN         (LVM_FIRST + 140)
#define MSListView_SetSelectedColumn(hwnd, iCol) \
    SNDMSG((hwnd), LVM_SETSELECTEDCOLUMN, (WPARAM)iCol, 0)

#define LVM_SETTILEWIDTH         (LVM_FIRST + 141)
#define MSListView_SetTileWidth(hwnd, cpWidth) \
    SNDMSG((hwnd), LVM_SETTILEWIDTH, (WPARAM)cpWidth, 0)

#define LV_VIEW_ICON        0x0000
#define LV_VIEW_DETAILS     0x0001
#define LV_VIEW_SMALLICON   0x0002
#define LV_VIEW_LIST        0x0003
#define LV_VIEW_TILE        0x0004
#define LV_VIEW_MAX         0x0004

#define LVM_SETVIEW         (LVM_FIRST + 142)
#define MSListView_SetView(hwnd, iView) \
    (DWORD)SNDMSG((hwnd), LVM_SETVIEW, (WPARAM)(DWORD)iView, 0)

#define LVM_GETVIEW         (LVM_FIRST + 143)
#define MSListView_GetView(hwnd) \
    (DWORD)SNDMSG((hwnd), LVM_GETVIEW, 0, 0)


#define LVGF_NONE           0x00000000
#define LVGF_HEADER         0x00000001
#define LVGF_FOOTER         0x00000002
#define LVGF_STATE          0x00000004
#define LVGF_ALIGN          0x00000008
#define LVGF_GROUPID        0x00000010

#define LVGS_NORMAL         0x00000000
#define LVGS_COLLAPSED      0x00000001
#define LVGS_HIDDEN         0x00000002

#define LVGA_HEADER_LEFT    0x00000001
#define LVGA_HEADER_CENTER  0x00000002
#define LVGA_HEADER_RIGHT   0x00000004  // Don't forget to validate exclusivity
#define LVGA_FOOTER_LEFT    0x00000008
#define LVGA_FOOTER_CENTER  0x00000010
#define LVGA_FOOTER_RIGHT   0x00000020  // Don't forget to validate exclusivity

#if 0
typedef struct tagLVGROUP
{
    UINT    cbSize;
    UINT    mask;
    LPWSTR  pszHeader;
    int     cchHeader;

    LPWSTR  pszFooter;
    int     cchFooter;

    int     iGroupId;

    UINT    stateMask;
    UINT    state;
    UINT    uAlign;
} LVGROUP, *PLVGROUP;
#endif

#define LVM_INSERTGROUP         (LVM_FIRST + 145)
#define MSListView_InsertGroup(hwnd, index, pgrp) \
    SNDMSG((hwnd), LVM_INSERTGROUP, (WPARAM)index, (LPARAM)pgrp)


#define LVM_SETGROUPINFO         (LVM_FIRST + 147)
#define MSListView_SetGroupInfo(hwnd, iGroupId, pgrp) \
    SNDMSG((hwnd), LVM_SETGROUPINFO, (WPARAM)iGroupId, (LPARAM)pgrp)


#define LVM_GETGROUPINFO         (LVM_FIRST + 149)
#define MSListView_GetGroupInfo(hwnd, iGroupId, pgrp) \
    SNDMSG((hwnd), LVM_GETGROUPINFO, (WPARAM)iGroupId, (LPARAM)pgrp)


#define LVM_REMOVEGROUP         (LVM_FIRST + 150)
#define MSListView_RemoveGroup(hwnd, iGroupId) \
    SNDMSG((hwnd), LVM_REMOVEGROUP, (WPARAM)iGroupId, 0)

#define LVM_MOVEGROUP         (LVM_FIRST + 151)
#define MSListView_MoveGroup(hwnd, iGroupId, toIndex) \
    SNDMSG((hwnd), LVM_MOVEGROUP, (WPARAM)iGroupId, (LPARAM)toIndex)

#define LVM_MOVEITEMTOGROUP            (LVM_FIRST + 154)
#define MSListView_MoveItemToGroup(hwnd, idItemFrom, idGroupTo) \
    SNDMSG((hwnd), LVM_MOVEITEMTOGROUP, (WPARAM)idItemFrom, (LPARAM)idGroupTo)


#define LVGMF_NONE          0x00000000
#define LVGMF_BORDERSIZE    0x00000001
#define LVGMF_BORDERCOLOR   0x00000002
#define LVGMF_TEXTCOLOR     0x00000004

#if 0
typedef struct tagLVGROUPMETRICS
{
    UINT cbSize;
    UINT mask;
    UINT Left;
    UINT Top;
    UINT Right;
    UINT Bottom;
    COLORREF crLeft;
    COLORREF crTop;
    COLORREF crRight;
    COLORREF crBottom;
    COLORREF crHeader;
    COLORREF crFooter;
} LVGROUPMETRICS, *PLVGROUPMETRICS;
#endif
#define LVM_SETGROUPMETRICS         (LVM_FIRST + 155)
#define MSListView_SetGroupMetrics(hwnd, pGroupMetrics) \
    SNDMSG((hwnd), LVM_SETGROUPMETRICS, 0, (LPARAM)pGroupMetrics)

#define LVM_GETGROUPMETRICS         (LVM_FIRST + 156)
#define MSListView_GetGroupMetrics(hwnd, pGroupMetrics) \
    SNDMSG((hwnd), LVM_GETGROUPMETRICS, 0, (LPARAM)pGroupMetrics)

#define LVM_ENABLEGROUPVIEW         (LVM_FIRST + 157)
#define MSListView_EnableGroupView(hwnd, fEnable) \
    SNDMSG((hwnd), LVM_ENABLEGROUPVIEW, (WPARAM)fEnable, 0)

typedef int (CALLBACK *PFNLVGROUPCOMPARE)(int, int, void *);

#define LVM_SORTGROUPS         (LVM_FIRST + 158)
#define MSListView_SortGroups(hwnd, _pfnGroupCompate, _plv) \
    SNDMSG((hwnd), LVM_SORTGROUPS, (WPARAM)_pfnGroupCompate, (LPARAM)_plv)

#if 0
typedef struct tagLVINSERTGROUPSORTED
{
    PFNLVGROUPCOMPARE pfnGroupCompare;
    void *pvData;
    LVGROUP lvGroup;
}LVINSERTGROUPSORTED, *PLVINSERTGROUPSORTED;
#endif

#define LVM_INSERTGROUPSORTED           (LVM_FIRST + 159)
#define MSListView_InsertGroupSorted(hwnd, structInsert) \
    SNDMSG((hwnd), LVM_INSERTGROUPSORTED, (WPARAM)structInsert, 0)

#define LVM_REMOVEALLGROUPS             (LVM_FIRST + 160)
#define MSListView_RemoveAllGroups(hwnd) \
    SNDMSG((hwnd), LVM_REMOVEALLGROUPS, 0, 0)

#define LVM_HASGROUP                    (LVM_FIRST + 161)
#define MSListView_HasGroup(hwnd, dwGroupId) \
    SNDMSG((hwnd), LVM_HASGROUP, dwGroupId, 0)

#define LVTVIF_AUTOSIZE       0x00000000
#define LVTVIF_FIXEDWIDTH     0x00000001
#define LVTVIF_FIXEDHEIGHT    0x00000002
#define LVTVIF_FIXEDSIZE      0x00000003

#define LVTVIM_TILESIZE       0x00000001
#define LVTVIM_COLUMNS        0x00000002
#define LVTVIM_LABELMARGIN    0x00000004

#if 0
typedef struct tagLVTILEVIEWINFO
{
    UINT cbSize;
    DWORD dwMask;     //LVTVIM_*
    DWORD dwFlags;    //LVTVIF_*
    MSSIZE sizeTile;
    int cLines;
    MSRECT rcLabelMargin;
} LVTILEVIEWINFO, *PLVTILEVIEWINFO;

typedef struct tagLVTILEINFO
{
    UINT cbSize;
    int iItem;
    UINT cColumns;
    PUINT puColumns;
} LVTILEINFO, *PLVTILEINFO;
#endif

#define LVM_SETTILEVIEWINFO                 (LVM_FIRST + 162)
#define MSListView_SetTileViewInfo(hwnd, ptvi) \
    SNDMSG((hwnd), LVM_SETTILEVIEWINFO, 0, (LPARAM)ptvi)

#define LVM_GETTILEVIEWINFO                 (LVM_FIRST + 163)
#define MSListView_GetTileViewInfo(hwnd, ptvi) \
    SNDMSG((hwnd), LVM_GETTILEVIEWINFO, 0, (LPARAM)ptvi)

#define LVM_SETTILEINFO                     (LVM_FIRST + 164)
#define MSListView_SetTileInfo(hwnd, pti) \
    SNDMSG((hwnd), LVM_SETTILEINFO, 0, (LPARAM)pti)

#define LVM_GETTILEINFO                     (LVM_FIRST + 165)
#define MSListView_GetTileInfo(hwnd, pti) \
    SNDMSG((hwnd), LVM_GETTILEINFO, 0, (LPARAM)pti)

#if 0
typedef struct 
{
    UINT cbSize;
    DWORD dwFlags;
    int iItem;
    DWORD dwReserved;
} LVINSERTMARK, * LPLVINSERTMARK;
#endif

#define LVIM_AFTER      0x00000001 // TRUE = insert After iItem, otherwise before

#define LVM_SETINSERTMARK                   (LVM_FIRST + 166)
#define MSListView_SetInsertMark(hwnd, lvim) \
    (BOOL)SNDMSG((hwnd), LVM_SETINSERTMARK, (WPARAM) 0, (LPARAM) (lvim))

#define LVM_GETINSERTMARK                   (LVM_FIRST + 167)
#define MSListView_GetInsertMark(hwnd, lvim) \
    (BOOL)SNDMSG((hwnd), LVM_GETINSERTMARK, (WPARAM) 0, (LPARAM) (lvim))

#define LVM_INSERTMARKHITTEST               (LVM_FIRST + 168)
#define MSListView_InsertMarkHitTest(hwnd, point, lvim) \
    (int)SNDMSG((hwnd), LVM_INSERTMARKHITTEST, (WPARAM)(LPMSPOINT)(point), (LPARAM)(LPLVINSERTMARK)(lvim))

#define LVM_GETINSERTMARKRECT               (LVM_FIRST + 169)
#define MSListView_GetInsertMarkRect(hwnd, rc) \
    (int)SNDMSG((hwnd), LVM_GETINSERTMARKRECT, (WPARAM)0, (LPARAM)(LPMSRECT)(rc))

#define LVM_SETINSERTMARKCOLOR                 (LVM_FIRST + 170)
#define MSListView_SetInsertMarkColor(hwnd, color) \
    (COLORREF)SNDMSG((hwnd), LVM_SETINSERTMARKCOLOR, (WPARAM)0, (LPARAM)(COLORREF)(color))

#define LVM_GETINSERTMARKCOLOR                 (LVM_FIRST + 171)
#define MSListView_GetInsertMarkColor(hwnd) \
    (COLORREF)SNDMSG((hwnd), LVM_GETINSERTMARKCOLOR, (WPARAM)0, (LPARAM)0)

#if 0
typedef struct tagLVSETINFOTIP
{
    UINT cbSize;
    DWORD dwFlags;
    LPWSTR pszText;
    int iItem;
    int iSubItem;
} LVSETINFOTIP, *PLVSETINFOTIP;
#endif

#define  LVM_SETINFOTIP         (LVM_FIRST + 173)

#define MSListView_SetInfoTip(hwndLV, plvInfoTip)\
        (BOOL)SNDMSG((hwndLV), LVM_SETINFOTIP, (WPARAM)0, (LPARAM)plvInfoTip)

#define LVM_GETSELECTEDCOLUMN   (LVM_FIRST + 174)
#define MSListView_GetSelectedColumn(hwnd) \
    (UINT)SNDMSG((hwnd), LVM_GETSELECTEDCOLUMN, 0, 0)


#define LVM_ISGROUPVIEWENABLED  (LVM_FIRST + 175)
#define MSListView_IsGroupViewEnabled(hwnd) \
    (BOOL)SNDMSG((hwnd), LVM_ISGROUPVIEWENABLED, 0, 0)

#define LVM_GETOUTLINECOLOR     (LVM_FIRST + 176)
#define MSListView_GetOutlineColor(hwnd) \
    (COLORREF)SNDMSG((hwnd), LVM_GETOUTLINECOLOR, 0, 0)

#define LVM_SETOUTLINECOLOR     (LVM_FIRST + 177)
#define MSListView_SetOutlineColor(hwnd, color) \
    (COLORREF)SNDMSG((hwnd), LVM_SETOUTLINECOLOR, (WPARAM)0, (LPARAM)(COLORREF)(color))


#define LVM_CANCELEDITLABEL     (LVM_FIRST + 179)
#define MSListView_CancelEditLabel(hwnd) \
    (VOID)SNDMSG((hwnd), LVM_CANCELEDITLABEL, (WPARAM)0, (LPARAM)0)


// These next to methods make it easy to identify an item that can be repositioned
// within listview. For example: Many developers use the lParam to store an identifier that is
// unique. Unfortunatly, in order to find this item, they have to iterate through all of the items
// in the listview. Listview will maintain a unique identifier.  The upper bound is the size of a DWORD.
#define LVM_MAPINDEXTOID     (LVM_FIRST + 180)
#define MSListView_MapIndexToID(hwnd, index) \
    (UINT)SNDMSG((hwnd), LVM_MAPINDEXTOID, (WPARAM)index, (LPARAM)0)

#define LVM_MAPIDTOINDEX     (LVM_FIRST + 181)
#define MSListView_MapIDToIndex(hwnd, id) \
    (UINT)SNDMSG((hwnd), LVM_MAPIDTOINDEX, (WPARAM)id, (LPARAM)0)



#endif

#define MSLVBKIMAGE               MSLVBKIMAGEA
#define LPMSLVBKIMAGE             LPMSLVBKIMAGEA
#define LVM_SETBKIMAGE          LVM_SETBKIMAGEA
#define LVM_GETBKIMAGE          LVM_GETBKIMAGEA


#define MSListView_SetBkImage(hwnd, plvbki) \
    (BOOL)SNDMSG((hwnd), LVM_SETBKIMAGE, 0, (LPARAM)(plvbki))

#define MSListView_GetBkImage(hwnd, plvbki) \
    (BOOL)SNDMSG((hwnd), LVM_GETBKIMAGE, 0, (LPARAM)(plvbki))

#endif      // _WIN32_IE >= 0x0400

#if (_WIN32_IE >= 0x0300)
#define LPCSNM_LISTVIEW   LPMSNMLISTVIEW
#define CSNM_LISTVIEW     MSNMLISTVIEW
#else
#define tagMSNMLISTVIEW   _NM_LISTVIEW
#define    MSNMLISTVIEW    NM_LISTVIEW
#define  LPMSNMLISTVIEW  LPCSNM_LISTVIEW
#endif

typedef struct tagMSNMLISTVIEW
{
    MSNMHDR   hdr;
    int     iItem;
    int     iSubItem;
    UINT    uNewState;
    UINT    uOldState;
    UINT    uChanged;
    MSPOINT   ptAction;
    LPARAM  lParam;
} MSNMLISTVIEW, *LPMSNMLISTVIEW;


#if (_WIN32_IE >= 0x400)
// MSNMITEMACTIVATE is used instead of MSNMLISTVIEW in IE >= 0x400
// therefore all the fields are the same except for extra uKeyFlags
// they are used to store key flags at the time of the single click with
// delayed activation - because by the time the timer goes off a user may
// not hold the keys (shift, ctrl) any more
typedef struct tagMSNMITEMACTIVATE
{
    MSNMHDR   hdr;
    int     iItem;
    int     iSubItem;
    UINT    uNewState;
    UINT    uOldState;
    UINT    uChanged;
    MSPOINT   ptAction;
    LPARAM  lParam;
    UINT    uKeyFlags;
} MSNMITEMACTIVATE, *LPMSNMITEMACTIVATE;

// key flags stored in uKeyFlags
#define LVKF_ALT       0x0001
#define LVKF_CONTROL   0x0002
#define LVKF_SHIFT     0x0004
#endif //(_WIN32_IE >= 0x0400)


#if (_WIN32_IE >= 0x0300)
#define MSNMLVCUSTOMDRAW_V3_SIZE CCSIZEOF_STRUCT(NMLVCUSTOMDRW, clrTextBk)

typedef struct tagMSNMLVCUSTOMDRAW
{
    MSNMCUSTOMDRAW nmcd;
    COLORREF clrText;
    COLORREF clrTextBk;
#if (_WIN32_IE >= 0x0400)
    int iSubItem;
#endif
#if (_WIN32_WINNT >= 0x501)
    DWORD dwItemType;

    // Item custom draw
    COLORREF clrFace;
    int iIconEffect;
    int iIconPhase;
    int iPartId;
    int iStateId;

    // Group Custom Draw
    MSRECT rcText;
    UINT uAlign;      // Alignment. Use LVGA_HEADER_CENTER, LVGA_HEADER_RIGHT, LVGA_HEADER_LEFT
#endif
} MSNMLVCUSTOMDRAW, *LPMSNMLVCUSTOMDRAW;

// dwItemType
#define LVCDI_ITEM      0x00000000
#define LVCDI_GROUP     0x00000001

// ListView custom draw return values
#define LVCDRF_NOSELECT             0x00010000
#define LVCDRF_NOGROUPFRAME         0x00020000  


typedef struct tagMSNMLVCACHEHINT
{
    MSNMHDR   hdr;
    int     iFrom;
    int     iTo;
} MSNMLVCACHEHINT, *LPMSNMLVCACHEHINT;

#define LPMSNM_CACHEHINT  LPMSNMLVCACHEHINT
#define PMSNM_CACHEHINT   LPMSNMLVCACHEHINT
#define MSNM_CACHEHINT    MSNMLVCACHEHINT

typedef struct tagMSNMLVFINDITEMA
{
    MSNMHDR   hdr;
    int     iStart;
    MSLVFINDINFOA lvfi;
} MSNMLVFINDITEMA, *LPMSNMLVFINDITEMA;

#define PMSNM_FINDITEMA   LPMSNMLVFINDITEMA
#define LPMSNM_FINDITEMA  LPMSNMLVFINDITEMA
#define MSNM_FINDITEMA    MSNMLVFINDITEMA


#define PMSNM_FINDITEM    PMSNM_FINDITEMA
#define LPMSNM_FINDITEM   LPMSNM_FINDITEMA
#define MSNM_FINDITEM     MSNM_FINDITEMA
#define MSNMLVFINDITEM    MSNMLVFINDITEMA
#define LPMSNMLVFINDITEM  LPMSNMLVFINDITEMA

typedef struct tagMSNMLVODSTATECHANGE
{
    MSNMHDR hdr;
    int iFrom;
    int iTo;
    UINT uNewState;
    UINT uOldState;
} MSNMLVODSTATECHANGE, *LPMSNMLVODSTATECHANGE;

#define PCSNM_ODSTATECHANGE   LPMSNMLVODSTATECHANGE
#define LPCSNM_ODSTATECHANGE  LPMSNMLVODSTATECHANGE
#define CSNM_ODSTATECHANGE    MSNMLVODSTATECHANGE
#endif      // _WIN32_IE >= 0x0300


#define LVN_ITEMCHANGING        (LVN_FIRST-0)
#define LVN_ITEMCHANGED         (LVN_FIRST-1)
#define LVN_INSERTITEM          (LVN_FIRST-2)
#define LVN_DELETEITEM          (LVN_FIRST-3)
#define LVN_DELETEALLITEMS      (LVN_FIRST-4)
#define LVN_BEGINLABELEDITA     (LVN_FIRST-5)
#define LVN_BEGINLABELEDITW     (LVN_FIRST-75)
#define LVN_ENDLABELEDITA       (LVN_FIRST-6)
#define LVN_ENDLABELEDITW       (LVN_FIRST-76)
#define LVN_COLUMNCLICK         (LVN_FIRST-8)
#define LVN_BEGINDRAG           (LVN_FIRST-9)
#define LVN_BEGINRDRAG          (LVN_FIRST-11)

#if (_WIN32_IE >= 0x0300)
#define LVN_ODCACHEHINT         (LVN_FIRST-13)
#define LVN_ODFINDITEMA         (LVN_FIRST-52)

#define LVN_ITEMACTIVATE        (LVN_FIRST-14)
#define LVN_ODSTATECHANGED      (LVN_FIRST-15)

#define LVN_ODFINDITEM          LVN_ODFINDITEMA
#endif      // _WIN32_IE >= 0x0300


#if (_WIN32_IE >= 0x0400)
#define LVN_HOTTRACK            (LVN_FIRST-21)
#endif

#define LVN_GETDISPINFOA        (LVN_FIRST-50)
#define LVN_SETDISPINFOA        (LVN_FIRST-51)

#define LVN_BEGINLABELEDIT      LVN_BEGINLABELEDITA
#define LVN_ENDLABELEDIT        LVN_ENDLABELEDITA
#define LVN_GETDISPINFO         LVN_GETDISPINFOA
#define LVN_SETDISPINFO         LVN_SETDISPINFOA


#define LVIF_DI_SETITEM         0x1000

#if (_WIN32_IE >= 0x0300)
#define MSLV_DISPINFOA    MSNMLVDISPINFOA
#else
#define tagMSLVDISPINFO   _MSLV_DISPINFO
#define MSNMLVDISPINFOA    MSLV_DISPINFOA
#endif

#define MSLV_DISPINFO     MSNMLVDISPINFO

typedef struct tagMSLVDISPINFO {
    MSNMHDR hdr;
    MSLVITEMA item;
} MSNMLVDISPINFOA, *LPMSNMLVDISPINFOA;

#define  MSNMLVDISPINFO           MSNMLVDISPINFOA

#define LVN_KEYDOWN             (LVN_FIRST-55)

#if (_WIN32_IE >= 0x0300)
#define MSLV_KEYDOWN              MSNMLVKEYDOWN
#else
#define tagMSLVKEYDOWN            _MSLV_KEYDOWN
#define MSNMLVKEYDOWN              MSLV_KEYDOWN
#endif

//#ifdef _WIN32
//#include <pshpack1.h>
//#endif

typedef struct tagMSLVKEYDOWN
{
    MSNMHDR hdr;
    WORD wVKey;
    UINT flags;
} MSNMLVKEYDOWN, *LPMSNMLVKEYDOWN;

//#ifdef _WIN32
//#include <poppack.h>
//#endif

#if (_WIN32_IE >= 0x0300)
#define LVN_MARQUEEBEGIN        (LVN_FIRST-56)
#endif

#if (_WIN32_IE >= 0x0400)
typedef struct tagMSNMLVGETINFOTIPA
{
    MSNMHDR hdr;
    DWORD dwFlags;
    LPSTR pszText;
    int cchTextMax;
    int iItem;
    int iSubItem;
    LPARAM lParam;
} MSNMLVGETINFOTIPA, *LPMSNMLVGETINFOTIPA;


// MSNMLVGETINFOTIPA.dwFlag values

#define LVGIT_UNFOLDED  0x0001

#define LVN_GETINFOTIPA          (LVN_FIRST-57)

#define LVN_GETINFOTIP          LVN_GETINFOTIPA
#define CSNMLVGETINFOTIP          MSNMLVGETINFOTIPA
#define LPCSNMLVGETINFOTIP        LPMSNMLVGETINFOTIPA


#endif      // _WIN32_IE >= 0x0400


#if (_WIN32_WINNT >= 0x501)
#if 0
typedef struct tagNMLVSCROLL
{
    MSNMHDR   hdr;
    int     dx;
    int     dy;
} NMLVSCROLL, *LPNMLVSCROLL;
#endif

#define LVN_BEGINSCROLL          (LVN_FIRST-80)          
#define LVN_ENDSCROLL            (LVN_FIRST-81)
#endif

#endif // NOLISTVIEW

//====== TREEVIEW CONTROL =====================================================

#ifndef NOTREEVIEW

#ifdef _WIN32
#define WC_TREEVIEWA            "SysTreeView32"

#define  WC_TREEVIEW            WC_TREEVIEWA

#else
#define WC_TREEVIEW             "SysTreeView"
#endif

// begin_r_commctrl

#define TVS_HASBUTTONS          0x0001
#define TVS_HASLINES            0x0002
#define TVS_LINESATROOT         0x0004
#define TVS_EDITLABELS          0x0008
#define TVS_DISABLEDRAGDROP     0x0010
#define TVS_SHOWSELALWAYS       0x0020
#if (_WIN32_IE >= 0x0300)
#define TVS_RTLREADING          0x0040

#define TVS_NOTOOLTIPS          0x0080
#define TVS_CHECKBOXES          0x0100
#define TVS_TRACKSELECT         0x0200
#if (_WIN32_IE >= 0x0400)
#define TVS_SINGLEEXPAND        0x0400
#define TVS_INFOTIP             0x0800
#define TVS_FULLROWSELECT       0x1000
#define TVS_NOSCROLL            0x2000
#define TVS_NONEVENHEIGHT       0x4000
#endif
#if (_WIN32_IE >= 0x500)
#define TVS_NOHSCROLL           0x8000  // TVS_NOSCROLL overrides this
#endif
#endif


// end_r_commctrl

typedef struct _AURATREEITEM *HAURATREEITEM;
struct _TREEVIEWSTYLE;
typedef struct _TREEVIEWSTYLE *HTREEVIEW;

#define TVIF_TEXT               0x0001
#define TVIF_IMAGE              0x0002
#define TVIF_PARAM              0x0004
#define TVIF_STATE              0x0008
#define TVIF_HANDLE             0x0010
#define TVIF_SELECTEDIMAGE      0x0020
#define TVIF_CHILDREN           0x0040
#if (_WIN32_IE >= 0x0400)
#define TVIF_INTEGRAL           0x0080
#endif
#define TVIS_SELECTED           0x0002
#define TVIS_CUT                0x0004
#define TVIS_DROPHILITED        0x0008
#define TVIS_BOLD               0x0010
#define TVIS_EXPANDED           0x0020
#define TVIS_EXPANDEDONCE       0x0040
#if (_WIN32_IE >= 0x0300)
#define TVIS_EXPANDPARTIAL      0x0080
#endif

#define TVIS_OVERLAYMASK        0x0F00
#define TVIS_STATEIMAGEMASK     0xF000
#define TVIS_USERMASK           0xF000

#define I_CHILDRENCALLBACK  (-1)

#if (_WIN32_IE >= 0x0300)
#define LPMSTV_ITEMA              LPMSTVITEMA
#define MSTV_ITEMA                MSTVITEMA
#else
#define tagMSTVITEMA             _MSTV_ITEMA
#define    MSTVITEMA              MSTV_ITEMA
#define  LPMSTVITEMA            LPMSTV_ITEMA
#endif

#define LPCSTV_ITEM               LPMSTVITEM
#define CSTV_ITEM                 MSTVITEM

typedef struct tagMSTVITEMA {
    UINT      mask;
    HAURATREEITEM hItem;
    UINT      state;
    UINT      stateMask;
    LPSTR     pszText;
    int       cchTextMax;
    int       iImage;
    int       iSelectedImage;
    int       cChildren;
    LPARAM    lParam;
} MSTVITEMA, *LPMSTVITEMA;


#if (_WIN32_IE >= 0x0400)
// only used for Get and Set messages.  no notifies
typedef struct tagMSTVITEMEXA {
    UINT      mask;
    HAURATREEITEM hItem;
    UINT      state;
    UINT      stateMask;
    LPSTR     pszText;
    int       cchTextMax;
    int       iImage;
    int       iSelectedImage;
    int       cChildren;
    LPARAM    lParam;
    int       iIntegral;
} MSTVITEMEXA, *LPMSTVITEMEXA;
// only used for Get and Set messages.  no notifies

typedef MSTVITEMEXA MSTVITEMEX;
typedef LPMSTVITEMEXA LPMSTVITEMEX;

#endif

#define  MSTVITEM                 MSTVITEMA
#define  LPMSTVITEM               LPMSTVITEMA

#undef TVI_ROOT
#define TVI_ROOT                ((HAURATREEITEM)(ULONG_PTR)-0x10000)
#undef TVI_FIRST
#define TVI_FIRST               ((HAURATREEITEM)(ULONG_PTR)-0x0FFFF)
#undef TVI_LAST
#define TVI_LAST                ((HAURATREEITEM)(ULONG_PTR)-0x0FFFE)
#undef TVI_SORT
#define TVI_SORT                ((HAURATREEITEM)(ULONG_PTR)-0x0FFFD)

#if (_WIN32_IE >= 0x0300)
#define LPMSTV_INSERTSTRUCTA      LPMSTVINSERTSTRUCTA
#define MSTV_INSERTSTRUCTA        MSTVINSERTSTRUCTA
#else
#define tagMSTVINSERTSTRUCTA     _MSTV_INSERTSTRUCTA
#define    MSTVINSERTSTRUCTA      MSTV_INSERTSTRUCTA
#define  LPMSTVINSERTSTRUCTA    LPMSTV_INSERTSTRUCTA
#endif

#define MSTV_INSERTSTRUCT         MSTVINSERTSTRUCT
#define LPMSTV_INSERTSTRUCT       LPMSTVINSERTSTRUCT


#define MSTVINSERTSTRUCTA_V1_SIZE CCSIZEOF_STRUCT(MSTVINSERTSTRUCTA, item)
#define MSTVINSERTSTRUCTW_V1_SIZE CCSIZEOF_STRUCT(MSTVINSERTSTRUCTW, item)

typedef struct tagMSTVINSERTSTRUCTA {
    HAURATREEITEM hParent;
    HAURATREEITEM hInsertAfter;
//#if (_WIN32_IE >= 0x0400) 
#if (_WIN32_IE >= 0x0600) 
    union
    {
        MSTVITEMEXA itemex;
        MSTV_ITEMA  item;
    } DUMMYUNIONNAME;
#else
    MSTV_ITEMA item;
#endif
} MSTVINSERTSTRUCTA, *LPMSTVINSERTSTRUCTA;


#define  MSTVINSERTSTRUCT         MSTVINSERTSTRUCTA
#define  LPMSTVINSERTSTRUCT       LPMSTVINSERTSTRUCTA
#define MSTVINSERTSTRUCT_V1_SIZE MSTVINSERTSTRUCTA_V1_SIZE

#define TVM_INSERTITEMA         (TV_FIRST + 0)
#define  TVM_INSERTITEM         TVM_INSERTITEMA

#define MSTreeView_InsertItem(hwnd, lpis) \
    (HAURATREEITEM)SNDMSG((hwnd), TVM_INSERTITEM, 0, (LPARAM)(LPMSTV_INSERTSTRUCT)(lpis))


#define TVM_DELETEITEM          (TV_FIRST + 1)
#define MSTreeView_DeleteItem(hwnd, hitem) \
    (BOOL)SNDMSG((hwnd), TVM_DELETEITEM, 0, (LPARAM)(HAURATREEITEM)(hitem))


#define MSTreeView_DeleteAllItems(hwnd) \
    (BOOL)SNDMSG((hwnd), TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT)


#define TVM_EXPAND              (TV_FIRST + 2)
#define MSTreeView_Expand(hwnd, hitem, code) \
    (BOOL)SNDMSG((hwnd), TVM_EXPAND, (WPARAM)(code), (LPARAM)(HAURATREEITEM)(hitem))


#define TVE_COLLAPSE            0x0001
#define TVE_EXPAND              0x0002
#define TVE_TOGGLE              0x0003
#if (_WIN32_IE >= 0x0300)
#define TVE_EXPANDPARTIAL       0x4000
#endif
#define TVE_COLLAPSERESET       0x8000


#define TVM_GETITEMRECT         (TV_FIRST + 4)
#define MSTreeView_GetItemRect(hwnd, hitem, prc, code) \
    (*(HAURATREEITEM *)prc = (hitem), (BOOL)SNDMSG((hwnd), TVM_GETITEMRECT, (WPARAM)(code), (LPARAM)(MSRECT *)(prc)))


#define TVM_GETCOUNT            (TV_FIRST + 5)
#define MSTreeView_GetCount(hwnd) \
    (UINT)SNDMSG((hwnd), TVM_GETCOUNT, 0, 0)


#define TVM_GETINDENT           (TV_FIRST + 6)
#define MSTreeView_GetIndent(hwnd) \
    (UINT)SNDMSG((hwnd), TVM_GETINDENT, 0, 0)


#define TVM_SETINDENT           (TV_FIRST + 7)
#define MSTreeView_SetIndent(hwnd, indent) \
    (BOOL)SNDMSG((hwnd), TVM_SETINDENT, (WPARAM)(indent), 0)


#define TVM_GETIMAGELIST        (TV_FIRST + 8)
#define MSTreeView_GetImageList(hwnd, iImage) \
    (HMSIMAGELIST)SNDMSG((hwnd), TVM_GETIMAGELIST, iImage, 0)


#define TVSIL_NORMAL            0
#define TVSIL_STATE             2


#define TVM_SETIMAGELIST        (TV_FIRST + 9)
#define MSTreeView_SetImageList(hwnd, himl, iImage) \
    (HMSIMAGELIST)SNDMSG((hwnd), TVM_SETIMAGELIST, iImage, (LPARAM)(HMSIMAGELIST)(himl))


#define TVM_GETNEXTITEM         (TV_FIRST + 10)
#define MSTreeView_GetNextItem(hwnd, hitem, code) \
    (HAURATREEITEM)SNDMSG((hwnd), TVM_GETNEXTITEM, (WPARAM)(code), (LPARAM)(HAURATREEITEM)(hitem))


#define TVGN_ROOT               0x0000
#define TVGN_NEXT               0x0001
#define TVGN_PREVIOUS           0x0002
#define TVGN_PARENT             0x0003
#define TVGN_CHILD              0x0004
#define TVGN_FIRSTVISIBLE       0x0005
#define TVGN_NEXTVISIBLE        0x0006
#define TVGN_PREVIOUSVISIBLE    0x0007
#define TVGN_DROPHILITE         0x0008
#define TVGN_CARET              0x0009
#if (_WIN32_IE >= 0x0400)
#define TVGN_LASTVISIBLE        0x000A
#endif      // _WIN32_IE >= 0x0400

#if (_WIN32_WINNT >= 0x501)
#define TVSI_NOSINGLEEXPAND    0x8000 // Should not conflict with TVGN flags.
#endif

#define MSTreeView_GetChild(hwnd, hitem)          TreeView_GetNextItem(hwnd, hitem, TVGN_CHILD)
#define MSTreeView_GetNextSibling(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_NEXT)
#define MSTreeView_GetPrevSibling(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_PREVIOUS)
#define MSTreeView_GetParent(hwnd, hitem)         TreeView_GetNextItem(hwnd, hitem, TVGN_PARENT)
#define MSTreeView_GetFirstVisible(hwnd)          TreeView_GetNextItem(hwnd, NULL,  TVGN_FIRSTVISIBLE)
#define MSTreeView_GetNextVisible(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_NEXTVISIBLE)
#define MSTreeView_GetPrevVisible(hwnd, hitem)    TreeView_GetNextItem(hwnd, hitem, TVGN_PREVIOUSVISIBLE)
#define MSTreeView_GetSelection(hwnd)             TreeView_GetNextItem(hwnd, NULL,  TVGN_CARET)
#define MSTreeView_GetDropHilight(hwnd)           TreeView_GetNextItem(hwnd, NULL,  TVGN_DROPHILITE)
#define MSTreeView_GetRoot(hwnd)                  TreeView_GetNextItem(hwnd, NULL,  TVGN_ROOT)
#if (_WIN32_IE >= 0x0400)
#define MSTreeView_GetLastVisible(hwnd)          TreeView_GetNextItem(hwnd, NULL,  TVGN_LASTVISIBLE)
#endif      // _WIN32_IE >= 0x0400


#define TVM_SELECTITEM          (TV_FIRST + 11)
#define MSTreeView_Select(hwnd, hitem, code) \
    (BOOL)SNDMSG((hwnd), TVM_SELECTITEM, (WPARAM)(code), (LPARAM)(HAURATREEITEM)(hitem))


#define MSTreeView_SelectItem(hwnd, hitem)            MSTreeView_Select(hwnd, hitem, TVGN_CARET)
#define MSTreeView_SelectDropTarget(hwnd, hitem)      MSTreeView_Select(hwnd, hitem, TVGN_DROPHILITE)
#define MSTreeView_SelectSetFirstVisible(hwnd, hitem) MSTreeView_Select(hwnd, hitem, TVGN_FIRSTVISIBLE)

#define TVM_GETITEMA            (TV_FIRST + 12)

#define  TVM_GETITEM            TVM_GETITEMA

#define MSTreeView_GetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), TVM_GETITEM, 0, (LPARAM)(TV_ITEM *)(pitem))


#define TVM_SETITEMA            (TV_FIRST + 13)

#define  TVM_SETITEM            TVM_SETITEMA

#define MSTreeView_SetItem(hwnd, pitem) \
    (BOOL)SNDMSG((hwnd), TVM_SETITEM, 0, (LPARAM)(const TV_ITEM *)(pitem))


#define TVM_EDITLABELA          (TV_FIRST + 14)
#define TVM_EDITLABEL           TVM_EDITLABELA

#define MSTreeView_EditLabel(hwnd, hitem) \
    (HMSWND)SNDMSG((hwnd), TVM_EDITLABEL, 0, (LPARAM)(HAURATREEITEM)(hitem))


#define TVM_GETEDITCONTROL      (TV_FIRST + 15)
#define MSTreeView_GetEditControl(hwnd) \
    (HMSWND)SNDMSG((hwnd), TVM_GETEDITCONTROL, 0, 0)


#define TVM_GETVISIBLECOUNT     (TV_FIRST + 16)
#define MSTreeView_GetVisibleCount(hwnd) \
    (UINT)SNDMSG((hwnd), TVM_GETVISIBLECOUNT, 0, 0)


#define TVM_HITTEST             (TV_FIRST + 17)
#define MSTreeView_HitTest(hwnd, lpht) \
    (HAURATREEITEM)SNDMSG((hwnd), TVM_HITTEST, 0, (LPARAM)(LPCSTV_HITTESTINFO)(lpht))


#if (_WIN32_IE >= 0x0300)
#define LPCSTV_HITTESTINFO   LPMSTVHITTESTINFO
#define   CSTV_HITTESTINFO     MSTVHITTESTINFO
#else
#define tagMSTVHITTESTINFO    _CSTV_HITTESTINFO
#define    MSTVHITTESTINFO     CSTV_HITTESTINFO
#define  LPMSTVHITTESTINFO   LPCSTV_HITTESTINFO
#endif

typedef struct tagMSTVHITTESTINFO {
    MSPOINT       pt;
    UINT        flags;
    HAURATREEITEM   hItem;
} MSTVHITTESTINFO, *LPMSTVHITTESTINFO;

#define TVHT_NOWHERE            0x0001
#define TVHT_ONITEMICON         0x0002
#define TVHT_ONITEMLABEL        0x0004
#define TVHT_ONITEM             (TVHT_ONITEMICON | TVHT_ONITEMLABEL | TVHT_ONITEMSTATEICON)
#define TVHT_ONITEMINDENT       0x0008
#define TVHT_ONITEMBUTTON       0x0010
#define TVHT_ONITEMRIGHT        0x0020
#define TVHT_ONITEMSTATEICON    0x0040

#define TVHT_ABOVE              0x0100
#define TVHT_BELOW              0x0200
#define TVHT_TORIGHT            0x0400
#define TVHT_TOLEFT             0x0800


#define TVM_CREATEDRAGIMAGE     (TV_FIRST + 18)
#define MSTreeView_CreateDragImage(hwnd, hitem) \
    (HMSIMAGELIST)SNDMSG((hwnd), TVM_CREATEDRAGIMAGE, 0, (LPARAM)(HAURATREEITEM)(hitem))


#define TVM_SORTCHILDREN        (TV_FIRST + 19)
#define MSTreeView_SortChildren(hwnd, hitem, recurse) \
    (BOOL)SNDMSG((hwnd), TVM_SORTCHILDREN, (WPARAM)(recurse), (LPARAM)(HAURATREEITEM)(hitem))


#define TVM_ENSUREVISIBLE       (TV_FIRST + 20)
#define MSTreeView_EnsureVisible(hwnd, hitem) \
    (BOOL)SNDMSG((hwnd), TVM_ENSUREVISIBLE, 0, (LPARAM)(HAURATREEITEM)(hitem))


#define TVM_SORTCHILDRENCB      (TV_FIRST + 21)
#define MSTreeView_SortChildrenCB(hwnd, psort, recurse) \
    (BOOL)SNDMSG((hwnd), TVM_SORTCHILDRENCB, (WPARAM)(recurse), \
    (LPARAM)(LPMSTV_SORTCB)(psort))


#define TVM_ENDEDITLABELNOW     (TV_FIRST + 22)
#define MSTreeView_EndEditLabelNow(hwnd, fCancel) \
    (BOOL)SNDMSG((hwnd), TVM_ENDEDITLABELNOW, (WPARAM)(fCancel), 0)


#define TVM_GETISEARCHSTRINGA   (TV_FIRST + 23)

#define TVM_GETISEARCHSTRING     TVM_GETISEARCHSTRINGA

#if (_WIN32_IE >= 0x0300)
#define TVM_SETTOOLTIPS         (TV_FIRST + 24)
#define MSTreeView_SetToolTips(hwnd,  hwndTT) \
    (HMSWND)SNDMSG((hwnd), TVM_SETTOOLTIPS, (WPARAM)(hwndTT), 0)
#define TVM_GETTOOLTIPS         (TV_FIRST + 25)
#define MSTreeView_GetToolTips(hwnd) \
    (HMSWND)SNDMSG((hwnd), TVM_GETTOOLTIPS, 0, 0)
#endif

#define MSTreeView_GetISearchString(hwndTV, lpsz) \
        (BOOL)SNDMSG((hwndTV), TVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)(lpsz))

#if (_WIN32_IE >= 0x0400)
#define TVM_SETINSERTMARK       (TV_FIRST + 26)
#define MSTreeView_SetInsertMark(hwnd, hItem, fAfter) \
        (BOOL)SNDMSG((hwnd), TVM_SETINSERTMARK, (WPARAM) (fAfter), (LPARAM) (hItem))

#define TVM_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define MSTreeView_SetUnicodeFormat(hwnd, fUnicode)  \
    (BOOL)SNDMSG((hwnd), TVM_SETUNICODEFORMAT, (WPARAM)(fUnicode), 0)

#define TVM_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT
#define MSTreeView_GetUnicodeFormat(hwnd)  \
    (BOOL)SNDMSG((hwnd), TVM_GETUNICODEFORMAT, 0, 0)

#endif

#if (_WIN32_IE >= 0x0400)
#define TVM_SETITEMHEIGHT         (TV_FIRST + 27)
#define MSTreeView_SetItemHeight(hwnd,  iHeight) \
    (int)SNDMSG((hwnd), TVM_SETITEMHEIGHT, (WPARAM)(iHeight), 0)
#define TVM_GETITEMHEIGHT         (TV_FIRST + 28)
#define MSTreeView_GetItemHeight(hwnd) \
    (int)SNDMSG((hwnd), TVM_GETITEMHEIGHT, 0, 0)

#define TVM_SETBKCOLOR              (TV_FIRST + 29)
#define MSTreeView_SetBkColor(hwnd, clr) \
    (COLORREF)SNDMSG((hwnd), TVM_SETBKCOLOR, 0, (LPARAM)(clr))

#define TVM_SETTEXTCOLOR              (TV_FIRST + 30)
#define MSTreeView_SetTextColor(hwnd, clr) \
    (COLORREF)SNDMSG((hwnd), TVM_SETTEXTCOLOR, 0, (LPARAM)(clr))

#define TVM_GETBKCOLOR              (TV_FIRST + 31)
#define MSTreeView_GetBkColor(hwnd) \
    (COLORREF)SNDMSG((hwnd), TVM_GETBKCOLOR, 0, 0)

#define TVM_GETTEXTCOLOR              (TV_FIRST + 32)
#define MSTreeView_GetTextColor(hwnd) \
    (COLORREF)SNDMSG((hwnd), TVM_GETTEXTCOLOR, 0, 0)

#define TVM_SETSCROLLTIME              (TV_FIRST + 33)
#define MSTreeView_SetScrollTime(hwnd, uTime) \
    (UINT)SNDMSG((hwnd), TVM_SETSCROLLTIME, uTime, 0)

#define TVM_GETSCROLLTIME              (TV_FIRST + 34)
#define MSTreeView_GetScrollTime(hwnd) \
    (UINT)SNDMSG((hwnd), TVM_GETSCROLLTIME, 0, 0)


#define TVM_SETINSERTMARKCOLOR              (TV_FIRST + 37)
#define MSTreeView_SetInsertMarkColor(hwnd, clr) \
    (COLORREF)SNDMSG((hwnd), TVM_SETINSERTMARKCOLOR, 0, (LPARAM)(clr))
#define TVM_GETINSERTMARKCOLOR              (TV_FIRST + 38)
#define MSTreeView_GetInsertMarkColor(hwnd) \
    (COLORREF)SNDMSG((hwnd), TVM_GETINSERTMARKCOLOR, 0, 0)

#endif  /* (_WIN32_IE >= 0x0400) */

#if (_WIN32_IE >= 0x0500)
// tvm_?etitemstate only uses mask, state and stateMask.
// so unicode or ansi is irrelevant.
#define MSTreeView_SetItemState(hwndTV, hti, data, _mask) \
{ MSTVITEM _ms_TVi;\
  _ms_TVi.mask = TVIF_STATE; \
  _ms_TVi.hItem = hti; \
  _ms_TVi.stateMask = _mask;\
  _ms_TVi.state = data;\
  SNDMSG((hwndTV), TVM_SETITEM, 0, (LPARAM)(TV_ITEM *)&_ms_TVi);\
}

#define MSTreeView_SetCheckState(hwndTV, hti, fCheck) \
  TreeView_SetItemState(hwndTV, hti, INDEXTOSTATEIMAGEMASK((fCheck)?2:1), TVIS_STATEIMAGEMASK)

#define TVM_GETITEMSTATE        (TV_FIRST + 39)
#define MSTreeView_GetItemState(hwndTV, hti, mask) \
   (UINT)SNDMSG((hwndTV), TVM_GETITEMSTATE, (WPARAM)(hti), (LPARAM)(mask))

#define MSTreeView_GetCheckState(hwndTV, hti) \
   ((((UINT)(SNDMSG((hwndTV), TVM_GETITEMSTATE, (WPARAM)(hti), TVIS_STATEIMAGEMASK))) >> 12) -1)


#define TVM_SETLINECOLOR            (TV_FIRST + 40)
#define MSTreeView_SetLineColor(hwnd, clr) \
    (COLORREF)SNDMSG((hwnd), TVM_SETLINECOLOR, 0, (LPARAM)(clr))

#define TVM_GETLINECOLOR            (TV_FIRST + 41)
#define MSTreeView_GetLineColor(hwnd) \
    (COLORREF)SNDMSG((hwnd), TVM_GETLINECOLOR, 0, 0)

#endif

#if (_WIN32_WINNT >= 0x0501)
#define TVM_MAPACCIDTOHAURATREEITEM     (TV_FIRST + 42)
#define MSTreeView_MapAccIDToHAURATREEITEM(hwnd, id) \
    (HAURATREEITEM)SNDMSG((hwnd), TVM_MAPACCIDTOHAURATREEITEM, id, 0)
    
#define TVM_MAPHAURATREEITEMTOACCID     (TV_FIRST + 43)
#define MSTreeView_MapHAURATREEITEMToAccID(hwnd, htreeitem) \
    (UINT)SNDMSG((hwnd), TVM_MAPHAURATREEITEMTOACCID, (WPARAM)htreeitem, 0)


#endif

typedef int (CALLBACK *PFNTVCOMPARE)(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

#if (_WIN32_IE >= 0x0300)
#define LPMSTV_SORTCB    LPMSTVSORTCB
#define   MSTV_SORTCB      MSTVSORTCB
#else
#define tagMSTVSORTCB    _MSTV_SORTCB
#define    MSTVSORTCB     MSTV_SORTCB
#define  LPMSTVSORTCB   LPMSTV_SORTCB
#endif

typedef struct tagMSTVSORTCB
{
        HAURATREEITEM       hParent;
        PFNTVCOMPARE    lpfnCompare;
        LPARAM          lParam;
} MSTVSORTCB, *LPMSTVSORTCB;


#if (_WIN32_IE >= 0x0300)
#define LPCSNM_TREEVIEWA          LPMSNMTREEVIEWA
#define CSNM_TREEVIEWA            MSNMTREEVIEWA
#else
#define tagMSNMTREEVIEWA          _NM_TREEVIEWA
#define MSNMTREEVIEWA             NM_TREEVIEWA
#define LPMSNMTREEVIEWA           LPCSNM_TREEVIEWA
#endif

#define LPNM_TREEVIEW           LPNMTREEVIEW
#define NM_TREEVIEW             NMTREEVIEW

typedef struct tagMSNMTREEVIEWA {
    MSNMHDR       hdr;
    UINT        action;
    MSTVITEMA    itemOld;
    MSTVITEMA    itemNew;
    MSPOINT       ptDrag;
} MSNMTREEVIEWA, *LPMSNMTREEVIEWA;



#define  CSNMTREEVIEW             MSNMTREEVIEWA
#define  LPCSNMTREEVIEW           LPMSNMTREEVIEWA


#define TVN_SELCHANGINGA        (TVN_FIRST-1)
#define TVN_SELCHANGEDA         (TVN_FIRST-2)

#define TVC_UNKNOWN             0x0000
#define TVC_BYMOUSE             0x0001
#define TVC_BYKEYBOARD          0x0002

#define TVN_GETDISPINFOA        (TVN_FIRST-3)
#define TVN_SETDISPINFOA        (TVN_FIRST-4)

#define TVIF_DI_SETITEM         0x1000

#if (_WIN32_IE >= 0x0300)
#define MSTV_DISPINFOA            MSNMTVDISPINFOA
#else
#define tagMSTVDISPINFOA  _MSTV_DISPINFOA
#define MSNMTVDISPINFOA    MSTV_DISPINFOA
#endif

#define TV_DISPINFO             NMTVDISPINFO

typedef struct tagMSTVDISPINFOA {
    MSNMHDR hdr;
    MSTVITEMA item;
} MSNMTVDISPINFOA, *LPMSNMTVDISPINFOA;


#define CSNMTVDISPINFO            MSNMTVDISPINFOA
#define LPCSNMTVDISPINFO          LPMSNMTVDISPINFOA

#define TVN_ITEMEXPANDINGA      (TVN_FIRST-5)
#define TVN_ITEMEXPANDEDA       (TVN_FIRST-6)
#define TVN_BEGINDRAGA          (TVN_FIRST-7)
#define TVN_BEGINRDRAGA         (TVN_FIRST-8)
#define TVN_DELETEITEMA         (TVN_FIRST-9)
#define TVN_BEGINLABELEDITA     (TVN_FIRST-10)
#define TVN_ENDLABELEDITA       (TVN_FIRST-11)
#define TVN_KEYDOWN             (TVN_FIRST-12)

#if (_WIN32_IE >= 0x0400)
#define TVN_GETINFOTIPA         (TVN_FIRST-13)
#define TVN_SINGLEEXPAND        (TVN_FIRST-15)

#define TVNRET_DEFAULT          0
#define TVNRET_SKIPOLD          1
#define TVNRET_SKIPNEW          2

#endif // 0x400


#if (_WIN32_IE >= 0x0300)
#define MSTV_KEYDOWN      MSNMTVKEYDOWN
#else
#define tagMSTVKEYDOWN    _MSTV_KEYDOWN
#define  MSNMTVKEYDOWN     MSTV_KEYDOWN
#endif

//#ifdef _WIN32
//#include <pshpack1.h>
//#endif

typedef struct tagMSTVKEYDOWN {
    MSNMHDR hdr;
    WORD wVKey;
    UINT flags;
} MSNMTVKEYDOWN, *LPMSNMTVKEYDOWN;

//#ifdef _WIN32
//#include <poppack.h>
//#endif



#define TVN_SELCHANGING         TVN_SELCHANGINGA
#define TVN_SELCHANGED          TVN_SELCHANGEDA
#define TVN_GETDISPINFO         TVN_GETDISPINFOA
#define TVN_SETDISPINFO         TVN_SETDISPINFOA
#define TVN_ITEMEXPANDING       TVN_ITEMEXPANDINGA
#define TVN_ITEMEXPANDED        TVN_ITEMEXPANDEDA
#define TVN_BEGINDRAG           TVN_BEGINDRAGA
#define TVN_BEGINRDRAG          TVN_BEGINRDRAGA
#define TVN_DELETEITEM          TVN_DELETEITEMA
#define TVN_BEGINLABELEDIT      TVN_BEGINLABELEDITA
#define TVN_ENDLABELEDIT        TVN_ENDLABELEDITA

#if (_WIN32_IE >= 0x0300)
#define MSNMTVCUSTOMDRAW_V3_SIZE CCSIZEOF_STRUCT(MSNMTVCUSTOMDRAW, clrTextBk)

typedef struct tagMSNMTVCUSTOMDRAW
{
    MSNMCUSTOMDRAW nmcd;
    COLORREF     clrText;
    COLORREF     clrTextBk;
#if (_WIN32_IE >= 0x0400)
    int iLevel;
#endif
} MSNMTVCUSTOMDRAW, *LPMSNMTVCUSTOMDRAW;
#endif


#if (_WIN32_IE >= 0x0400)

// for tooltips

typedef struct tagMSNMTVGETINFOTIPA
{
    MSNMHDR hdr;
    LPSTR pszText;
    int cchTextMax;
    HAURATREEITEM hItem;
    LPARAM lParam;
} MSNMTVGETINFOTIPA, *LPMSNMTVGETINFOTIPA;


#define TVN_GETINFOTIP          TVN_GETINFOTIPA
#define MSNMTVGETINFOTIP          MSNMTVGETINFOTIPA
#define LPMSNMTVGETINFOTIP        LPMSNMTVGETINFOTIPA

// treeview's customdraw return meaning don't draw images.  valid on CDRF_NOTIFYITEMPREPAINT
#define TVCDRF_NOIMAGES         0x00010000






#endif      // _WIN32_IE >= 0x0400

#endif      // NOTREEVIEW

#if (_WIN32_IE >= 0x0300)

#ifndef NOUSEREXCONTROLS

////////////////////  ComboBoxEx ////////////////////////////////

#define WC_COMBOBOXEXA         "ComboBoxEx32"

#define WC_COMBOBOXEX          WC_COMBOBOXEXA


#define CBEIF_TEXT              0x00000001
#define CBEIF_IMAGE             0x00000002
#define CBEIF_SELECTEDIMAGE     0x00000004
#define CBEIF_OVERLAY           0x00000008
#define CBEIF_INDENT            0x00000010
#define CBEIF_LPARAM            0x00000020

#define CBEIF_DI_SETITEM        0x10000000

typedef struct tagMSCOMBOBOXEXITEMA
{
    UINT mask;
    INT_PTR iItem;
    LPSTR pszText;
    int cchTextMax;
    int iImage;
    int iSelectedImage;
    int iOverlay;
    int iIndent;
    LPARAM lParam;
} MSCOMBOBOXEXITEMA, *PMSCOMBOBOXEXITEMA;
typedef MSCOMBOBOXEXITEMA CONST *PCCSCOMBOEXITEMA;



#define MSCOMBOBOXEXITEM            MSCOMBOBOXEXITEMA
#define PMSCOMBOBOXEXITEM           PMSCOMBOBOXEXITEMA
#define PCMSCOMBOBOXEXITEM          PCMSCOMBOBOXEXITEMA

#define CBEM_INSERTITEMA        (WM_USER + 1)
#define CBEM_SETIMAGELIST       (WM_USER + 2)
#define CBEM_GETIMAGELIST       (WM_USER + 3)
#define CBEM_GETITEMA           (WM_USER + 4)
#define CBEM_SETITEMA           (WM_USER + 5)
#define CBEM_DELETEITEM         CB_DELETESTRING
#define CBEM_GETCOMBOCONTROL    (WM_USER + 6)
#define CBEM_GETEDITCONTROL     (WM_USER + 7)
#if (_WIN32_IE >= 0x0400)
#define CBEM_SETEXSTYLE         (WM_USER + 8)  // use  SETEXTENDEDSTYLE instead
#define CBEM_SETEXTENDEDSTYLE   (WM_USER + 14)   // lparam == new style, wParam (optional) == mask
#define CBEM_GETEXSTYLE         (WM_USER + 9) // use GETEXTENDEDSTYLE instead
#define CBEM_GETEXTENDEDSTYLE   (WM_USER + 9)
#define CBEM_SETUNICODEFORMAT   CCM_SETUNICODEFORMAT
#define CBEM_GETUNICODEFORMAT   CCM_GETUNICODEFORMAT
#else
#define CBEM_SETEXSTYLE         (WM_USER + 8)
#define CBEM_GETEXSTYLE         (WM_USER + 9)
#endif
#define CBEM_HASEDITCHANGED     (WM_USER + 10)
#define CBEM_INSERTITEMW        (WM_USER + 11)
#define CBEM_SETITEMW           (WM_USER + 12)
#define CBEM_GETITEMW           (WM_USER + 13)

#define CBEM_INSERTITEM         CBEM_INSERTITEMA
#define CBEM_SETITEM            CBEM_SETITEMA
#define CBEM_GETITEM            CBEM_GETITEMA

#if (_WIN32_WINNT >= 0x501)
#define CBEM_SETWINDOWTHEME     CCM_SETWINDOWTHEME
#endif

#define CBES_EX_NOEDITIMAGE          0x00000001
#define CBES_EX_NOEDITIMAGEINDENT    0x00000002
#define CBES_EX_PATHWORDBREAKPROC    0x00000004
#if (_WIN32_IE >= 0x0400)
#define CBES_EX_NOSIZELIMIT          0x00000008
#define CBES_EX_CASESENSITIVE        0x00000010

typedef struct {
    MSNMHDR hdr;
    MSCOMBOBOXEXITEMA ceItem;
} MSNMCOMBOBOXEXA, *PMSNMCOMBOBOXEXA;

#define MSNMCOMBOBOXEX            MSNMCOMBOBOXEXA
#define PMSNMCOMBOBOXEX           PMSNMCOMBOBOXEXA
#define CBEN_GETDISPINFO        CBEN_GETDISPINFOA

#else
typedef struct {
    MSNMHDR hdr;
    MSCOMBOBOXEXITEM ceItem;
} MSNMCOMBOBOXEX, *PMSNMCOMBOBOXEX;

#define CBEN_GETDISPINFO         (CBEN_FIRST - 0)

#endif      // _WIN32_IE >= 0x0400

#if (_WIN32_IE >= 0x0400)
#define CBEN_GETDISPINFOA        (CBEN_FIRST - 0)
#endif
#define CBEN_INSERTITEM          (CBEN_FIRST - 1)
#define CBEN_DELETEITEM          (CBEN_FIRST - 2)
#define CBEN_BEGINEDIT           (CBEN_FIRST - 4)
#define CBEN_ENDEDITA            (CBEN_FIRST - 5)

#if (_WIN32_IE >= 0x0400)
#define CBEN_GETDISPINFOW        (CBEN_FIRST - 7)
#endif

#if (_WIN32_IE >= 0x0400)
#define CBEN_DRAGBEGINA                  (CBEN_FIRST - 8)

#define CBEN_DRAGBEGIN CBEN_DRAGBEGINA

#endif  //(_WIN32_IE >= 0x0400)

// lParam specifies why the endedit is happening
#define CBEN_ENDEDIT CBEN_ENDEDITA

#define CBENF_KILLFOCUS         1
#define CBENF_RETURN            2
#define CBENF_ESCAPE            3
#define CBENF_DROPDOWN          4

#define CBEMAXSTRLEN 260

#if (_WIN32_IE >= 0x0400)
// CBEN_DRAGBEGIN sends this information ...


typedef struct {
    MSNMHDR hdr;
    int   iItemid;
    char szText[CBEMAXSTRLEN];
}CSNMCBEDRAGBEGINA, *LPCSNMCBEDRAGBEGINA, *PCSNMCBEDRAGBEGINA;

#define  CSNMCBEDRAGBEGIN CSNMCBEDRAGBEGINA
#define  LPCSNMCBEDRAGBEGIN LPCSNMCBEDRAGBEGINA
#define  PCSNMCBEDRAGBEGIN PCSNMCBEDRAGBEGINA
#endif      // _WIN32_IE >= 0x0400

// CBEN_ENDEDIT sends this information...
// fChanged if the user actually did anything
// iNewSelection gives what would be the new selection unless the notify is failed
//                      iNewSelection may be CB_ERR if there's no match

typedef struct {
        MSNMHDR hdr;
        BOOL fChanged;
        int iNewSelection;
        char szText[CBEMAXSTRLEN];
        int iWhy;
} MSNMCBEENDEDITA, *LPMSNMCBEENDEDITA,*PMSNMCBEENDEDITA;

#define  CSNMCBEENDEDIT MSNMCBEENDEDITA
#define  LPCSNMCBEENDEDIT LPMSNMCBEENDEDITA
#define  PCSNMCBEENDEDIT PMSNMCBEENDEDITA

#endif

#endif      // _WIN32_IE >= 0x0300



//====== TAB CONTROL ==========================================================

#ifndef NOTABCONTROL
struct _TABCTRLSTYLE;
typedef struct _TABCTRLSTYLE* HTABCTRL;

#ifdef _WIN32

#define WC_TABCONTROLA          "SysTabControl32"

#define  WC_TABCONTROL          WC_TABCONTROLA

#else
#define WC_TABCONTROL           "SysTabControl"
#endif

// begin_r_commctrl

#if (_WIN32_IE >= 0x0300)
#define TCS_SCROLLOPPOSITE      0x0001   // assumes multiline tab
#define TCS_BOTTOM              0x0002
#define TCS_RIGHT               0x0002
#define TCS_MULTISELECT         0x0004  // allow multi-select in button mode
#endif
#if (_WIN32_IE >= 0x0400)
#define TCS_FLATBUTTONS         0x0008
#endif
#define TCS_FORCEICONLEFT       0x0010
#define TCS_FORCELABELLEFT      0x0020
#if (_WIN32_IE >= 0x0300)
#define TCS_HOTTRACK            0x0040
#define TCS_VERTICAL            0x0080
#endif
#define TCS_TABS                0x0000
#define TCS_BUTTONS             0x0100
#define TCS_SINGLELINE          0x0000
#define TCS_MULTILINE           0x0200
#define TCS_RIGHTJUSTIFY        0x0000
#define TCS_FIXEDWIDTH          0x0400
#define TCS_RAGGEDRIGHT         0x0800
#define TCS_FOCUSONBUTTONDOWN   0x1000
#define TCS_OWNERDRAWFIXED      0x2000
#define TCS_TOOLTIPS            0x4000
#define TCS_FOCUSNEVER          0x8000

// end_r_commctrl

#if (_WIN32_IE >= 0x0400)
// EX styles for use with TCM_SETEXTENDEDSTYLE
#define TCS_EX_FLATSEPARATORS   0x00000001
#define TCS_EX_REGISTERDROP     0x00000002
#endif


#define TCM_GETIMAGELIST        (TCM_FIRST + 2)
#define MSTabCtrl_GetImageList(hwnd) \
    (HMSIMAGELIST)SNDMSG((hwnd), TCM_GETIMAGELIST, 0, 0L)


#define TCM_SETIMAGELIST        (TCM_FIRST + 3)
#define MSTabCtrl_SetImageList(hwnd, himl) \
    (HMSIMAGELIST)SNDMSG((hwnd), TCM_SETIMAGELIST, 0, (LPARAM)(HMSIMAGELIST)(himl))


#define TCM_GETITEMCOUNT        (TCM_FIRST + 4)
#define MSTabCtrl_GetItemCount(hwnd) \
    (int)SNDMSG((hwnd), TCM_GETITEMCOUNT, 0, 0L)


#define TCIF_TEXT               0x0001
#define TCIF_IMAGE              0x0002
#define TCIF_RTLREADING         0x0004
#define TCIF_PARAM              0x0008
#if (_WIN32_IE >= 0x0300)
#define TCIF_STATE              0x0010


#define TCIS_BUTTONPRESSED      0x0001
#endif
#if (_WIN32_IE >= 0x0400)
#define TCIS_HIGHLIGHTED        0x0002
#endif

#if (_WIN32_IE >= 0x0300)
#define MSTC_ITEMHEADERA         MSTCITEMHEADERA
#else
#define tagMSTCITEMHEADERA       _MSTC_ITEMHEADERA
#define    MSTCITEMHEADERA        MSTC_ITEMHEADERA
#endif
#define MSTC_ITEMHEADER          MSTCITEMHEADER

typedef struct tagMSTCITEMHEADERA
{
    UINT mask;
    UINT lpReserved1;
    UINT lpReserved2;
    LPSTR pszText;
    int cchTextMax;
    int iImage;
} MSTCITEMHEADERA, *LPMSTCITEMHEADERA;


#define  MSTCITEMHEADER          MSTCITEMHEADERA
#define  LPMSTCITEMHEADER        LPMSTCITEMHEADERA


#if (_WIN32_IE >= 0x0300)
#define MSTC_ITEMA                MSTCITEMA
#else
#define tagMSTCITEMA              _MSTC_ITEMA
#define    MSTCITEMA               MSTC_ITEMA
#endif
#define MSTC_ITEM                 MSTCITEM

typedef struct tagMSTCITEMA
{
    UINT mask;
#if (_WIN32_IE >= 0x0300)
    DWORD dwState;
    DWORD dwStateMask;
#else
    UINT lpReserved1;
    UINT lpReserved2;
#endif
    LPSTR pszText;
    int cchTextMax;
    int iImage;

    LPARAM lParam;
} MSTCITEMA, *LPMSTCITEMA;


#define  MSTCITEM                 MSTCITEMA
#define  LPMSTCITEM               LPMSTCITEMA


#define TCM_GETITEMA            (TCM_FIRST + 5)

#define TCM_GETITEM             TCM_GETITEMA

#define MSTabCtrl_GetItem(hwnd, iItem, pitem) \
    (BOOL)SNDMSG((hwnd), TCM_GETITEM, (WPARAM)(int)(iItem), (LPARAM)(MSTC_ITEM *)(pitem))


#define TCM_SETITEMA            (TCM_FIRST + 6)
#define TCM_SETITEM             TCM_SETITEMA

#define MSTabCtrl_SetItem(hwnd, iItem, pitem) \
    (BOOL)SNDMSG((hwnd), TCM_SETITEM, (WPARAM)(int)(iItem), (LPARAM)(MSTC_ITEM *)(pitem))


#define TCM_INSERTITEMA         (TCM_FIRST + 7)
#define TCM_INSERTITEM          TCM_INSERTITEMA

#define MSTabCtrl_InsertItem(hwnd, iItem, pitem)   \
    (int)SNDMSG((hwnd), TCM_INSERTITEM, (WPARAM)(int)(iItem), (LPARAM)(const MSTC_ITEM *)(pitem))


#define TCM_DELETEITEM          (TCM_FIRST + 8)
#define MSTabCtrl_DeleteItem(hwnd, i) \
    (BOOL)SNDMSG((hwnd), TCM_DELETEITEM, (WPARAM)(int)(i), 0L)


#define TCM_DELETEALLITEMS      (TCM_FIRST + 9)
#define MSTabCtrl_DeleteAllItems(hwnd) \
    (BOOL)SNDMSG((hwnd), TCM_DELETEALLITEMS, 0, 0L)


#define TCM_GETITEMRECT         (TCM_FIRST + 10)
#define MSTabCtrl_GetItemRect(hwnd, i, prc) \
    (BOOL)SNDMSG((hwnd), TCM_GETITEMRECT, (WPARAM)(int)(i), (LPARAM)(MSRECT *)(prc))


#define TCM_GETCURSEL           (TCM_FIRST + 11)
#define MSTabCtrl_GetCurSel(hwnd) \
    (int)SNDMSG((hwnd), TCM_GETCURSEL, 0, 0)


#define TCM_SETCURSEL           (TCM_FIRST + 12)
#define MSTabCtrl_SetCurSel(hwnd, i) \
    (int)SNDMSG((hwnd), TCM_SETCURSEL, (WPARAM)(i), 0)


#define TCHT_NOWHERE            0x0001
#define TCHT_ONITEMICON         0x0002
#define TCHT_ONITEMLABEL        0x0004
#define TCHT_ONITEM             (TCHT_ONITEMICON | TCHT_ONITEMLABEL)

#if (_WIN32_IE >= 0x0300)
#define LPCSTC_HITTESTINFO        LPMSTCHITTESTINFO
#define CSTC_HITTESTINFO          MSTCHITTESTINFO
#else
#define tagMSTCHITTESTINFO        _CSTC_HITTESTINFO
#define    MSTCHITTESTINFO         CSTC_HITTESTINFO
#define  LPMSTCHITTESTINFO       LPCSTC_HITTESTINFO
#endif

typedef struct tagMSTCHITTESTINFO
{
    MSPOINT pt;
    UINT flags;
} MSTCHITTESTINFO, *LPMSTCHITTESTINFO;

#define TCM_HITTEST             (TCM_FIRST + 13)
#define MSTabCtrl_HitTest(hwndTC, pinfo) \
    (int)SNDMSG((hwndTC), TCM_HITTEST, 0, (LPARAM)(CSTC_HITTESTINFO *)(pinfo))


#define TCM_SETITEMEXTRA        (TCM_FIRST + 14)
#define MSTabCtrl_SetItemExtra(hwndTC, cb) \
    (BOOL)SNDMSG((hwndTC), TCM_SETITEMEXTRA, (WPARAM)(cb), 0L)


#define TCM_ADJUSTRECT          (TCM_FIRST + 40)
#define MSTabCtrl_AdjustRect(hwnd, bLarger, prc) \
    (int)SNDMSG(hwnd, TCM_ADJUSTRECT, (WPARAM)(BOOL)(bLarger), (LPARAM)(MSRECT *)prc)


#define TCM_SETITEMSIZE         (TCM_FIRST + 41)
#define MSTabCtrl_SetItemSize(hwnd, x, y) \
    (DWORD)SNDMSG((hwnd), TCM_SETITEMSIZE, 0, MAKELPARAM(x,y))


#define TCM_REMOVEIMAGE         (TCM_FIRST + 42)
#define MSTabCtrl_RemoveImage(hwnd, i) \
        (void)SNDMSG((hwnd), TCM_REMOVEIMAGE, i, 0L)


#define TCM_SETPADDING          (TCM_FIRST + 43)
#define MSTabCtrl_SetPadding(hwnd,  cx, cy) \
        (void)SNDMSG((hwnd), TCM_SETPADDING, 0, MAKELPARAM(cx, cy))


#define TCM_GETROWCOUNT         (TCM_FIRST + 44)
#define MSTabCtrl_GetRowCount(hwnd) \
        (int)SNDMSG((hwnd), TCM_GETROWCOUNT, 0, 0L)


#define TCM_GETTOOLTIPS         (TCM_FIRST + 45)
#define MSTabCtrl_GetToolTips(hwnd) \
        (HMSWND)SNDMSG((hwnd), TCM_GETTOOLTIPS, 0, 0L)


#define TCM_SETTOOLTIPS         (TCM_FIRST + 46)
#define MSTabCtrl_SetToolTips(hwnd, hwndTT) \
        (void)SNDMSG((hwnd), TCM_SETTOOLTIPS, (WPARAM)(hwndTT), 0L)


#define TCM_GETCURFOCUS         (TCM_FIRST + 47)
#define MSTabCtrl_GetCurFocus(hwnd) \
    (int)SNDMSG((hwnd), TCM_GETCURFOCUS, 0, 0)

#define TCM_SETCURFOCUS         (TCM_FIRST + 48)
#define MSTabCtrl_SetCurFocus(hwnd, i) \
    SNDMSG((hwnd),TCM_SETCURFOCUS, i, 0)

#if (_WIN32_IE >= 0x0300)
#define TCM_SETMINTABWIDTH      (TCM_FIRST + 49)
#define MSTabCtrl_SetMinTabWidth(hwnd, x) \
        (int)SNDMSG((hwnd), TCM_SETMINTABWIDTH, 0, x)


#define TCM_DESELECTALL         (TCM_FIRST + 50)
#define MSTabCtrl_DeselectAll(hwnd, fExcludeFocus)\
        (void)SNDMSG((hwnd), TCM_DESELECTALL, fExcludeFocus, 0)
#endif

#if (_WIN32_IE >= 0x0400)

#define TCM_HIGHLIGHTITEM       (TCM_FIRST + 51)
#define MSTabCtrl_HighlightItem(hwnd, i, fHighlight) \
    (BOOL)SNDMSG((hwnd), TCM_HIGHLIGHTITEM, (WPARAM)(i), (LPARAM)MAKELONG (fHighlight, 0))

#define TCM_SETEXTENDEDSTYLE    (TCM_FIRST + 52)  // optional wParam == mask
#define MSTabCtrl_SetExtendedStyle(hwnd, dw)\
        (DWORD)SNDMSG((hwnd), TCM_SETEXTENDEDSTYLE, 0, dw)

#define TCM_GETEXTENDEDSTYLE    (TCM_FIRST + 53)
#define MSTabCtrl_GetExtendedStyle(hwnd)\
        (DWORD)SNDMSG((hwnd), TCM_GETEXTENDEDSTYLE, 0, 0)

#define TCM_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define MSTabCtrl_SetUnicodeFormat(hwnd, fUnicode)  \
    (BOOL)SNDMSG((hwnd), TCM_SETUNICODEFORMAT, (WPARAM)(fUnicode), 0)

#define TCM_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT
#define MSTabCtrl_GetUnicodeFormat(hwnd)  \
    (BOOL)SNDMSG((hwnd), TCM_GETUNICODEFORMAT, 0, 0)

#endif      // _WIN32_IE >= 0x0400

#define TCN_KEYDOWN             (TCN_FIRST - 0)

#if (_WIN32_IE >= 0x0300)
#define MSTC_KEYDOWN              MSNMTCKEYDOWN
#else
#define tagMSTCKEYDOWN            _MSTC_KEYDOWN
#define  MSNMTCKEYDOWN             MSTC_KEYDOWN
#endif

//#ifdef _WIN32
//#include <pshpack1.h>
//#endif

typedef struct tagMSTCKEYDOWN
{
    MSNMHDR hdr;
    WORD wVKey;
    UINT flags;
} MSNMTCKEYDOWN;

//#ifdef _WIN32
//#include <poppack.h>
//#endif

#define TCN_SELCHANGE           (TCN_FIRST - 1)
#define TCN_SELCHANGING         (TCN_FIRST - 2)
#if (_WIN32_IE >= 0x0400)
#define TCN_GETOBJECT           (TCN_FIRST - 3)
#endif      // _WIN32_IE >= 0x0400
#if (_WIN32_IE >= 0x0500)
#define TCN_FOCUSCHANGE         (TCN_FIRST - 4)
#endif      // _WIN32_IE >= 0x0500
#endif      // NOTABCONTROL




//====== ANIMATE CONTROL ======================================================

#ifndef NOANIMATE

#ifdef _WIN32

#define ANIMATE_CLASSA          "SysAnimate32"

#define ANIMATE_CLASS           ANIMATE_CLASSA

// begin_r_commctrl

#define ACS_CENTER              0x0001
#define ACS_TRANSPARENT         0x0002
#define ACS_AUTOPLAY            0x0004
#if (_WIN32_IE >= 0x0300)
#define ACS_TIMER               0x0008  // don't use threads... use timers
#endif

// end_r_commctrl

#define ACM_OPENA               (WM_USER+100)

#define ACM_OPEN                ACM_OPENA

#define ACM_PLAY                (WM_USER+101)
#define ACM_STOP                (WM_USER+102)


#define ACN_START               1
#define ACN_STOP                2


#define MSAnimate_Create(hwndP, id, dwStyle, hInstance)   \
            MSCreateWindow(ANIMATE_CLASS, NULL,           \
                dwStyle, 0, 0, 0, 0, hwndP, (HMSMENU)(id), hInstance, NULL)

#define MSAnimate_Open(hwnd, szName)          (BOOL)SNDMSG(hwnd, ACM_OPEN, 0, (LPARAM)(LPTSTR)(szName))
#define MSAnimate_OpenEx(hwnd, hInst, szName) (BOOL)SNDMSG(hwnd, ACM_OPEN, (WPARAM)(hInst), (LPARAM)(LPTSTR)(szName))
#define MSAnimate_Play(hwnd, from, to, rep)   (BOOL)SNDMSG(hwnd, ACM_PLAY, (WPARAM)(rep), (LPARAM)MAKELONG(from, to))
#define MSAnimate_Stop(hwnd)                  (BOOL)SNDMSG(hwnd, ACM_STOP, 0, 0)
#define MSAnimate_Close(hwnd)                 Animate_Open(hwnd, NULL)
#define MSAnimate_Seek(hwnd, frame)           Animate_Play(hwnd, frame, frame, 1)
#endif

#endif      // NOANIMATE

#if (_WIN32_IE >= 0x0300)
//====== MONTHCAL CONTROL ======================================================

#ifndef NOMONTHCAL
#ifdef _WIN32

#define MONTHCAL_CLASSA          "SysMonthCal32"

#define MONTHCAL_CLASS           MONTHCAL_CLASSA

// bit-packed array of "bold" info for a month
// if a bit is on, that day is drawn bold
typedef DWORD MONTHDAYSTATE, *LPMONTHDAYSTATE;


#define MCM_FIRST           0x1000

// BOOL MonthCal_GetCurSel(HMSWND hmc, LPMSSYSTEMTIME pst)
//   returns FALSE if MCS_MULTISELECT
//   returns TRUE and sets *pst to the currently selected date otherwise
#define MCM_GETCURSEL       (MCM_FIRST + 1)
#define MSMonthCal_GetCurSel(hmc, pst)    (BOOL)SNDMSG(hmc, MCM_GETCURSEL, 0, (LPARAM)(pst))

// BOOL MonthCal_SetCurSel(HMSWND hmc, LPMSSYSTEMTIME pst)
//   returns FALSE if MCS_MULTISELECT
//   returns TURE and sets the currently selected date to *pst otherwise
#define MCM_SETCURSEL       (MCM_FIRST + 2)
#define MSMonthCal_SetCurSel(hmc, pst)    (BOOL)SNDMSG(hmc, MCM_SETCURSEL, 0, (LPARAM)(pst))

// DWORD MonthCal_GetMaxSelCount(HMSWND hmc)
//   returns the maximum number of selectable days allowed
#define MCM_GETMAXSELCOUNT  (MCM_FIRST + 3)
#define MSMonthCal_GetMaxSelCount(hmc)    (DWORD)SNDMSG(hmc, MCM_GETMAXSELCOUNT, 0, 0L)

// BOOL MonthCal_SetMaxSelCount(HMSWND hmc, UINT n)
//   sets the max number days that can be selected iff MCS_MULTISELECT
#define MCM_SETMAXSELCOUNT  (MCM_FIRST + 4)
#define MSMonthCal_SetMaxSelCount(hmc, n) (BOOL)SNDMSG(hmc, MCM_SETMAXSELCOUNT, (WPARAM)(n), 0L)

// BOOL MonthCal_GetSelRange(HMSWND hmc, LPMSSYSTEMTIME rgst)
//   sets rgst[0] to the first day of the selection range
//   sets rgst[1] to the last day of the selection range
#define MCM_GETSELRANGE     (MCM_FIRST + 5)
#define MSMonthCal_GetSelRange(hmc, rgst) SNDMSG(hmc, MCM_GETSELRANGE, 0, (LPARAM)(rgst))

// BOOL MonthCal_SetSelRange(HMSWND hmc, LPMSSYSTEMTIME rgst)
//   selects the range of days from rgst[0] to rgst[1]
#define MCM_SETSELRANGE     (MCM_FIRST + 6)
#define MSMonthCal_SetSelRange(hmc, rgst) SNDMSG(hmc, MCM_SETSELRANGE, 0, (LPARAM)(rgst))

// DWORD MonthCal_GetMonthRange(HMSWND hmc, DWORD gmr, LPMSSYSTEMTIME rgst)
//   if rgst specified, sets rgst[0] to the starting date and
//      and rgst[1] to the ending date of the the selectable (non-grayed)
//      days if GMR_VISIBLE or all the displayed days (including grayed)
//      if GMR_DAYSTATE.
//   returns the number of months spanned by the above range.
#define MCM_GETMONTHRANGE   (MCM_FIRST + 7)
#define MSMonthCal_GetMonthRange(hmc, gmr, rgst)  (DWORD)SNDMSG(hmc, MCM_GETMONTHRANGE, (WPARAM)(gmr), (LPARAM)(rgst))

// BOOL MonthCal_SetDayState(HMSWND hmc, int cbds, DAYSTATE *rgds)
//   cbds is the count of DAYSTATE items in rgds and it must be equal
//   to the value returned from MonthCal_GetMonthRange(hmc, GMR_DAYSTATE, NULL)
//   This sets the DAYSTATE bits for each month (grayed and non-grayed
//   days) displayed in the calendar. The first bit in a month's DAYSTATE
//   corresponts to bolding day 1, the second bit affects day 2, etc.
#define MCM_SETDAYSTATE     (MCM_FIRST + 8)
#define MSMonthCal_SetDayState(hmc, cbds, rgds)   SNDMSG(hmc, MCM_SETDAYSTATE, (WPARAM)(cbds), (LPARAM)(rgds))

// BOOL MonthCal_GetMinReqRect(HMSWND hmc, LPMSRECT prc)
//   sets *prc the minimal size needed to display one month
//   To display two months, undo the AdjustWindowRect calculation already done to
//   this rect, double the width, and redo the AdjustWindowRect calculation --
//   the monthcal control will display two calendars in this window (if you also
//   double the vertical size, you will get 4 calendars)
//   NOTE: if you want to gurantee that the "Today" string is not clipped,
//   get the MCM_GETMAXTODAYWIDTH and use the max of that width and this width
#define MCM_GETMINREQRECT   (MCM_FIRST + 9)
#define MSMonthCal_GetMinReqRect(hmc, prc)        SNDMSG(hmc, MCM_GETMINREQRECT, 0, (LPARAM)(prc))

// set colors to draw control with -- see MCSC_ bits below
#define MCM_SETCOLOR            (MCM_FIRST + 10)
#define MSMonthCal_SetColor(hmc, iColor, clr) SNDMSG(hmc, MCM_SETCOLOR, iColor, clr)

#define MCM_GETCOLOR            (MCM_FIRST + 11)
#define MSMonthCal_GetColor(hmc, iColor) SNDMSG(hmc, MCM_GETCOLOR, iColor, 0)

#define MCSC_BACKGROUND   0   // the background color (between months)
#define MCSC_TEXT         1   // the dates
#define MCSC_TITLEBK      2   // background of the title
#define MCSC_TITLETEXT    3
#define MCSC_MONTHBK      4   // background within the month cal
#define MCSC_TRAILINGTEXT 5   // the text color of header & trailing days

// set what day is "today"   send NULL to revert back to real date
#define MCM_SETTODAY    (MCM_FIRST + 12)
#define MSMonthCal_SetToday(hmc, pst)             SNDMSG(hmc, MCM_SETTODAY, 0, (LPARAM)(pst))

// get what day is "today"
// returns BOOL for success/failure
#define MCM_GETTODAY    (MCM_FIRST + 13)
#define MSMonthCal_GetToday(hmc, pst)             (BOOL)SNDMSG(hmc, MCM_GETTODAY, 0, (LPARAM)(pst))

// determine what pinfo->pt is over
#define MCM_HITTEST          (MCM_FIRST + 14)
#define MSMonthCal_HitTest(hmc, pinfo) \
        SNDMSG(hmc, MCM_HITTEST, 0, (LPARAM)(PCSMCHITTESTINFO)(pinfo))

typedef struct {
        UINT cbSize;
        MSPOINT pt;

        UINT uHit;   // out param
        MSSYSTEMTIME st;
} MSMCHITTESTINFO, *PMSMCHITTESTINFO;

#define MCHT_TITLE                      0x00010000
#define MCHT_CALENDAR                   0x00020000
#define MCHT_TODAYLINK                  0x00030000

#define MCHT_NEXT                       0x01000000   // these indicate that hitting
#define MCHT_PREV                       0x02000000  // here will go to the next/prev month

#define MCHT_NOWHERE                    0x00000000

#define MCHT_TITLEBK                    (MCHT_TITLE)
#define MCHT_TITLEMONTH                 (MCHT_TITLE | 0x0001)
#define MCHT_TITLEYEAR                  (MCHT_TITLE | 0x0002)
#define MCHT_TITLEBTNNEXT               (MCHT_TITLE | MCHT_NEXT | 0x0003)
#define MCHT_TITLEBTNPREV               (MCHT_TITLE | MCHT_PREV | 0x0003)

#define MCHT_CALENDARBK                 (MCHT_CALENDAR)
#define MCHT_CALENDARDATE               (MCHT_CALENDAR | 0x0001)
#define MCHT_CALENDARDATENEXT           (MCHT_CALENDARDATE | MCHT_NEXT)
#define MCHT_CALENDARDATEPREV           (MCHT_CALENDARDATE | MCHT_PREV)
#define MCHT_CALENDARDAY                (MCHT_CALENDAR | 0x0002)
#define MCHT_CALENDARWEEKNUM            (MCHT_CALENDAR | 0x0003)

// set first day of week to iDay:
// 0 for Monday, 1 for Tuesday, ..., 6 for Sunday
// -1 for means use locale info
#define MCM_SETFIRSTDAYOFWEEK (MCM_FIRST + 15)
#define MSMonthCal_SetFirstDayOfWeek(hmc, iDay) \
        SNDMSG(hmc, MCM_SETFIRSTDAYOFWEEK, 0, iDay)

// DWORD result...  low word has the day.  high word is bool if this is app set
// or not (FALSE == using locale info)
#define MCM_GETFIRSTDAYOFWEEK (MCM_FIRST + 16)
#define MSMonthCal_GetFirstDayOfWeek(hmc) \
        (DWORD)SNDMSG(hmc, MCM_GETFIRSTDAYOFWEEK, 0, 0)

// DWORD MonthCal_GetRange(HMSWND hmc, LPMSSYSTEMTIME rgst)
//   modifies rgst[0] to be the minimum ALLOWABLE systemtime (or 0 if no minimum)
//   modifies rgst[1] to be the maximum ALLOWABLE systemtime (or 0 if no maximum)
//   returns GDTR_MIN|GDTR_MAX if there is a minimum|maximum limit
#define MCM_GETRANGE (MCM_FIRST + 17)
#define MSMonthCal_GetRange(hmc, rgst) \
        (DWORD)SNDMSG(hmc, MCM_GETRANGE, 0, (LPARAM)(rgst))

// BOOL MonthCal_SetRange(HMSWND hmc, DWORD gdtr, LPMSSYSTEMTIME rgst)
//   if GDTR_MIN, sets the minimum ALLOWABLE systemtime to rgst[0], otherwise removes minimum
//   if GDTR_MAX, sets the maximum ALLOWABLE systemtime to rgst[1], otherwise removes maximum
//   returns TRUE on success, FALSE on error (such as invalid parameters)
#define MCM_SETRANGE (MCM_FIRST + 18)
#define MSMonthCal_SetRange(hmc, gd, rgst) \
        (BOOL)SNDMSG(hmc, MCM_SETRANGE, (WPARAM)(gd), (LPARAM)(rgst))

// int MonthCal_GetMonthDelta(HMSWND hmc)
//   returns the number of months one click on a next/prev button moves by
#define MCM_GETMONTHDELTA (MCM_FIRST + 19)
#define MSMonthCal_GetMonthDelta(hmc) \
        (int)SNDMSG(hmc, MCM_GETMONTHDELTA, 0, 0)

// int MonthCal_SetMonthDelta(HMSWND hmc, int n)
//   sets the month delta to n. n==0 reverts to moving by a page of months
//   returns the previous value of n.
#define MCM_SETMONTHDELTA (MCM_FIRST + 20)
#define MSMonthCal_SetMonthDelta(hmc, n) \
        (int)SNDMSG(hmc, MCM_SETMONTHDELTA, n, 0)

// DWORD MonthCal_GetMaxTodayWidth(HMSWND hmc, LPSIZE psz)
//   sets *psz to the maximum width/height of the "Today" string displayed
//   at the bottom of the calendar (as long as MCS_NOTODAY is not specified)
#define MCM_GETMAXTODAYWIDTH (MCM_FIRST + 21)
#define MSMonthCal_GetMaxTodayWidth(hmc) \
        (DWORD)SNDMSG(hmc, MCM_GETMAXTODAYWIDTH, 0, 0)

#if (_WIN32_IE >= 0x0400)
#define MCM_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define MSMonthCal_SetUnicodeFormat(hwnd, fUnicode)  \
    (BOOL)SNDMSG((hwnd), MCM_SETUNICODEFORMAT, (WPARAM)(fUnicode), 0)

#define MCM_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT
#define MSMonthCal_GetUnicodeFormat(hwnd)  \
    (BOOL)SNDMSG((hwnd), MCM_GETUNICODEFORMAT, 0, 0)
#endif

// MCN_SELCHANGE is sent whenever the currently displayed date changes
// via month change, year change, keyboard navigation, prev/next button
//
typedef struct tagMSNMSELCHANGE
{
    MSNMHDR           nmhdr;  // this must be first, so we don't break WM_NOTIFY

    MSSYSTEMTIME      stSelStart;
    MSSYSTEMTIME      stSelEnd;
} MSNMSELCHANGE, *LPMSNMSELCHANGE;

#define MCN_SELCHANGE       (MCN_FIRST + 1)

// MCN_GETDAYSTATE is sent for MCS_DAYSTATE controls whenever new daystate
// information is needed (month or year scroll) to draw bolding information.
// The app must fill in cDayState months worth of information starting from
// stStart date. The app may fill in the array at prgDayState or change
// prgDayState to point to a different array out of which the information
// will be copied. (similar to tooltips)
//
typedef struct tagCSNMDAYSTATE
{
    MSNMHDR           nmhdr;  // this must be first, so we don't break WM_NOTIFY

    MSSYSTEMTIME      stStart;
    int             cDayState;

    LPMONTHDAYSTATE prgDayState; // points to cDayState MONTHDAYSTATEs
} CSNMDAYSTATE, *LPCSNMDAYSTATE;

#define MCN_GETDAYSTATE     (MCN_FIRST + 3)

// MCN_SELECT is sent whenever a selection has occured (via mouse or keyboard)
//
typedef MSNMSELCHANGE MSNMSELECT, *LPMSNMSELECT;


#define MCN_SELECT          (MCN_FIRST + 4)


// begin_r_commctrl

#define MCS_DAYSTATE        0x0001
#define MCS_MULTISELECT     0x0002
#define MCS_WEEKNUMBERS     0x0004
#if (_WIN32_IE >= 0x0400)
#define MCS_NOTODAYCIRCLE   0x0008
#define MCS_NOTODAY         0x0010
#else
#define MCS_NOTODAY         0x0008
#endif


// end_r_commctrl

#define GMR_VISIBLE     0       // visible portion of display
#define GMR_DAYSTATE    1       // above plus the grayed out parts of
                                // partially displayed months


#endif // _WIN32
#endif // NOMONTHCAL


//====== DATETIMEPICK CONTROL ==================================================

#ifndef NODATETIMEPICK
#ifdef _WIN32

#define DATETIMEPICK_CLASSA          "SysDateTimePick32"

#define DATETIMEPICK_CLASS           DATETIMEPICK_CLASSA

#define DTM_FIRST        0x1000

// DWORD DateTimePick_GetSystemtime(HMSWND hdp, LPMSSYSTEMTIME pst)
//   returns GDT_NONE if "none" is selected (DTS_SHOWNONE only)
//   returns GDT_VALID and modifies *pst to be the currently selected value
#define DTM_GETSYSTEMTIME   (DTM_FIRST + 1)
#define MSDateTime_GetSystemtime(hdp, pst)    (DWORD)SNDMSG(hdp, DTM_GETSYSTEMTIME, 0, (LPARAM)(pst))

// BOOL DateTime_SetSystemtime(HMSWND hdp, DWORD gd, LPMSSYSTEMTIME pst)
//   if gd==GDT_NONE, sets datetimepick to None (DTS_SHOWNONE only)
//   if gd==GDT_VALID, sets datetimepick to *pst
//   returns TRUE on success, FALSE on error (such as bad params)
#define DTM_SETSYSTEMTIME   (DTM_FIRST + 2)
#define MSDateTime_SetSystemtime(hdp, gd, pst)    (BOOL)SNDMSG(hdp, DTM_SETSYSTEMTIME, (WPARAM)(gd), (LPARAM)(pst))

// DWORD DateTime_GetRange(HMSWND hdp, LPMSSYSTEMTIME rgst)
//   modifies rgst[0] to be the minimum ALLOWABLE systemtime (or 0 if no minimum)
//   modifies rgst[1] to be the maximum ALLOWABLE systemtime (or 0 if no maximum)
//   returns GDTR_MIN|GDTR_MAX if there is a minimum|maximum limit
#define DTM_GETRANGE (DTM_FIRST + 3)
#define MSDateTime_GetRange(hdp, rgst)  (DWORD)SNDMSG(hdp, DTM_GETRANGE, 0, (LPARAM)(rgst))

// BOOL DateTime_SetRange(HMSWND hdp, DWORD gdtr, LPMSSYSTEMTIME rgst)
//   if GDTR_MIN, sets the minimum ALLOWABLE systemtime to rgst[0], otherwise removes minimum
//   if GDTR_MAX, sets the maximum ALLOWABLE systemtime to rgst[1], otherwise removes maximum
//   returns TRUE on success, FALSE on error (such as invalid parameters)
#define DTM_SETRANGE (DTM_FIRST + 4)
#define MSDateTime_SetRange(hdp, gd, rgst)  (BOOL)SNDMSG(hdp, DTM_SETRANGE, (WPARAM)(gd), (LPARAM)(rgst))

// BOOL DateTime_SetFormat(HMSWND hdp, LPCTSTR sz)
//   sets the display formatting string to sz (see GetDateFormat and GetTimeFormat for valid formatting chars)
//   NOTE: 'X' is a valid formatting character which indicates that the application
//   will determine how to display information. Such apps must support DTN_WMKEYDOWN,
//   DTN_FORMAT, and DTN_FORMATQUERY.
#define DTM_SETFORMATA (DTM_FIRST + 5)

#define DTM_SETFORMAT       DTM_SETFORMATA

#define MSDateTime_SetFormat(hdp, sz)  (BOOL)SNDMSG(hdp, DTM_SETFORMAT, 0, (LPARAM)(sz))


#define DTM_SETMCCOLOR    (DTM_FIRST + 6)
#define MSDateTime_SetMonthCalColor(hdp, iColor, clr) SNDMSG(hdp, DTM_SETMCCOLOR, iColor, clr)

#define DTM_GETMCCOLOR    (DTM_FIRST + 7)
#define MSDateTime_GetMonthCalColor(hdp, iColor) SNDMSG(hdp, DTM_GETMCCOLOR, iColor, 0)

// HMSWND DateTime_GetMonthCal(HMSWND hdp)
//   returns the HMSWND of the MonthCal popup window. Only valid
// between DTN_DROPDOWN and DTN_CLOSEUP notifications.
#define DTM_GETMONTHCAL   (DTM_FIRST + 8)
#define MSDateTime_GetMonthCal(hdp) (HMSWND)SNDMSG(hdp, DTM_GETMONTHCAL, 0, 0)

#if (_WIN32_IE >= 0x0400)

#define DTM_SETMCFONT     (DTM_FIRST + 9)
#define MSDateTime_SetMonthCalFont(hdp, hfont, fRedraw) SNDMSG(hdp, DTM_SETMCFONT, (WPARAM)(hfont), (LPARAM)(fRedraw))

#define DTM_GETMCFONT     (DTM_FIRST + 10)
#define MSDateTime_GetMonthCalFont(hdp) SNDMSG(hdp, DTM_GETMCFONT, 0, 0)

#endif      // _WIN32_IE >= 0x0400

// begin_r_commctrl

#define DTS_UPDOWN          0x0001 // use UPDOWN instead of MONTHCAL
#define DTS_SHOWNONE        0x0002 // allow a NONE selection
#define DTS_SHORTDATEFORMAT 0x0000 // use the short date format (app must forward WM_WININICHANGE messages)
#define DTS_LONGDATEFORMAT  0x0004 // use the long date format (app must forward WM_WININICHANGE messages)
#if (_WIN32_IE >= 0x500)
#define DTS_SHORTDATECENTURYFORMAT 0x000C// short date format with century (app must forward WM_WININICHANGE messages)
#endif // (_WIN32_IE >= 0x500)
#define DTS_TIMEFORMAT      0x0009 // use the time format (app must forward WM_WININICHANGE messages)
#define DTS_APPCANPARSE     0x0010 // allow user entered strings (app MUST respond to DTN_USERSTRING)
#define DTS_RIGHTALIGN      0x0020 // right-align popup instead of left-align it

// end_r_commctrl

#define DTN_DATETIMECHANGE  (DTN_FIRST + 1) // the systemtime has changed
typedef struct tagMSNMDATETIMECHANGE
{
    MSNMHDR       nmhdr;
    DWORD       dwFlags;    // GDT_VALID or GDT_NONE
    MSSYSTEMTIME  st;         // valid iff dwFlags==GDT_VALID
} MSNMDATETIMECHANGE, *LPMSNMDATETIMECHANGE;

#define DTN_USERSTRINGA  (DTN_FIRST + 2) // the user has entered a string
#define DTN_USERSTRINGW  (DTN_FIRST + 15)
typedef struct tagMSNMDATETIMESTRINGA
{
    MSNMHDR      nmhdr;
    LPCSTR     pszUserString;  // string user entered
    MSSYSTEMTIME st;             // app fills this in
    DWORD      dwFlags;        // GDT_VALID or GDT_NONE
} MSNMDATETIMESTRINGA, *LPMSNMDATETIMESTRINGA;

#define DTN_USERSTRING          DTN_USERSTRINGA
#define MSNMDATETIMESTRING        MSNMDATETIMESTRINGA
#define LPMSNMDATETIMESTRING      LPMSNMDATETIMESTRINGA


#define DTN_WMKEYDOWNA  (DTN_FIRST + 3) // modify keydown on app format field (X)
typedef struct tagMSNMDATETIMEWMKEYDOWNA
{
    MSNMHDR      nmhdr;
    int        nVirtKey;  // virtual key code of WM_KEYDOWN which MODIFIES an X field
    LPCSTR     pszFormat; // format substring
    MSSYSTEMTIME st;        // current systemtime, app should modify based on key
} MSNMDATETIMEWMKEYDOWNA, *LPMSNMDATETIMEWMKEYDOWNA;


#define DTN_WMKEYDOWN           DTN_WMKEYDOWNA
#define MSNMDATETIMEWMKEYDOWN     MSNMDATETIMEWMKEYDOWNA
#define LPMSNMDATETIMEWMKEYDOWN   LPMSNMDATETIMEWMKEYDOWNA


#define DTN_FORMATA  (DTN_FIRST + 4) // query display for app format field (X)
typedef struct tagMSNMDATETIMEFORMATA
{
    MSNMHDR nmhdr;
    LPCSTR  pszFormat;   // format substring
    MSSYSTEMTIME st;       // current systemtime
    LPCSTR pszDisplay;   // string to display
    CHAR szDisplay[64];  // buffer pszDisplay originally points at
} MSNMDATETIMEFORMATA, *LPMSNMDATETIMEFORMATA;


#define DTN_FORMAT             DTN_FORMATA
#define MSNMDATETIMEFORMAT        MSNMDATETIMEFORMATA
#define LPMSNMDATETIMEFORMAT      LPMSNMDATETIMEFORMATA


#define DTN_FORMATQUERYA  (DTN_FIRST + 5) // query formatting info for app format field (X)
typedef struct tagMSNMDATETIMEFORMATQUERYA
{
    MSNMHDR nmhdr;
    LPCSTR pszFormat;  // format substring
    MSSIZE szMax;        // max bounding rectangle app will use for this format string
} MSNMDATETIMEFORMATQUERYA, *LPMSNMDATETIMEFORMATQUERYA;


#define DTN_FORMATQUERY         DTN_FORMATQUERYA
#define MSNMDATETIMEFORMATQUERY   MSNMDATETIMEFORMATQUERYA
#define LPMSNMDATETIMEFORMATQUERY LPMSNMDATETIMEFORMATQUERYA


#define DTN_DROPDOWN    (DTN_FIRST + 6) // MonthCal has dropped down
#define DTN_CLOSEUP     (DTN_FIRST + 7) // MonthCal is popping up


#define GDTR_MIN     0x0001
#define GDTR_MAX     0x0002

#define GDT_ERROR    -1
#define GDT_VALID    0
#define GDT_NONE     1


#endif // _WIN32
#endif // NODATETIMEPICK


#if (_WIN32_IE >= 0x0400)

#ifndef NOIPADDRESS

///////////////////////////////////////////////
///    IP Address edit control

// Messages sent to IPAddress controls

#define IPM_CLEARADDRESS (WM_USER+100) // no parameters
#define IPM_SETADDRESS   (WM_USER+101) // lparam = TCP/IP address
#define IPM_GETADDRESS   (WM_USER+102) // lresult = # of non black fields.  lparam = LPDWORD for TCP/IP address
#define IPM_SETRANGE (WM_USER+103) // wparam = field, lparam = range
#define IPM_SETFOCUS (WM_USER+104) // wparam = field
#define IPM_ISBLANK  (WM_USER+105) // no parameters

#define WC_IPADDRESSA           "SysIPAddress32"

#define WC_IPADDRESS          WC_IPADDRESSA

#define IPN_FIELDCHANGED                (IPN_FIRST - 0)
typedef struct tagMSNMIPADDRESS
{
        MSNMHDR hdr;
        int iField;
        int iValue;
} MSNMIPADDRESS, *LPMSNMIPADDRESS;

// The following is a useful macro for passing the range values in the
// IPM_SETRANGE message.

#define MAKEIPRANGE(low, high)    ((LPARAM)(WORD)(((BYTE)(high) << 8) + (BYTE)(low)))

// And this is a useful macro for making the IP Address to be passed
// as a LPARAM.

#define MAKEIPADDRESS(b1,b2,b3,b4)  ((LPARAM)(((DWORD)(b1)<<24)+((DWORD)(b2)<<16)+((DWORD)(b3)<<8)+((DWORD)(b4))))

// Get individual number
#define FIRST_IPADDRESS(x)  ((x>>24) & 0xff)
#define SECOND_IPADDRESS(x) ((x>>16) & 0xff)
#define THIRD_IPADDRESS(x)  ((x>>8) & 0xff)
#define FOURTH_IPADDRESS(x) (x & 0xff)


#endif // NOIPADDRESS


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
///  ====================== Pager Control =============================
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

#ifndef NOPAGESCROLLER

//Pager Class Name
#define WC_PAGESCROLLERA           "SysPager"

#define WC_PAGESCROLLER          WC_PAGESCROLLERA


//---------------------------------------------------------------------------------------
// Pager Control Styles
//---------------------------------------------------------------------------------------
// begin_r_commctrl

#define PGS_VERT                0x00000000
#define PGS_HORZ                0x00000001
#define PGS_AUTOSCROLL          0x00000002
#define PGS_DRAGNDROP           0x00000004

// end_r_commctrl


//---------------------------------------------------------------------------------------
// Pager Button State
//---------------------------------------------------------------------------------------
//The scroll can be in one of the following control State
#define  PGF_INVISIBLE   0      // Scroll button is not visible
#define  PGF_NORMAL      1      // Scroll button is in normal state
#define  PGF_GRAYED      2      // Scroll button is in grayed state
#define  PGF_DEPRESSED   4      // Scroll button is in depressed state
#define  PGF_HOT         8      // Scroll button is in hot state


// The following identifiers specifies the button control
#define PGB_TOPORLEFT       0
#define PGB_BOTTOMORRIGHT   1

//---------------------------------------------------------------------------------------
// Pager Control  Messages
//---------------------------------------------------------------------------------------
#define PGM_SETCHILD            (PGM_FIRST + 1)  // lParam == hwnd
#define MSPager_SetChild(hwnd, hwndChild) \
        (void)SNDMSG((hwnd), PGM_SETCHILD, 0, (LPARAM)(hwndChild))

#define PGM_RECALCSIZE          (PGM_FIRST + 2)
#define MSPager_RecalcSize(hwnd) \
        (void)SNDMSG((hwnd), PGM_RECALCSIZE, 0, 0)

#define PGM_FORWARDMOUSE        (PGM_FIRST + 3)
#define MSPager_ForwardMouse(hwnd, bForward) \
        (void)SNDMSG((hwnd), PGM_FORWARDMOUSE, (WPARAM)(bForward), 0)

#define PGM_SETBKCOLOR          (PGM_FIRST + 4)
#define MSPager_SetBkColor(hwnd, clr) \
        (COLORREF)SNDMSG((hwnd), PGM_SETBKCOLOR, 0, (LPARAM)(clr))

#define PGM_GETBKCOLOR          (PGM_FIRST + 5)
#define MSPager_GetBkColor(hwnd) \
        (COLORREF)SNDMSG((hwnd), PGM_GETBKCOLOR, 0, 0)

#define PGM_SETBORDER          (PGM_FIRST + 6)
#define MSPager_SetBorder(hwnd, iBorder) \
        (int)SNDMSG((hwnd), PGM_SETBORDER, 0, (LPARAM)(iBorder))

#define PGM_GETBORDER          (PGM_FIRST + 7)
#define MSPager_GetBorder(hwnd) \
        (int)SNDMSG((hwnd), PGM_GETBORDER, 0, 0)

#define PGM_SETPOS              (PGM_FIRST + 8)
#define MSPager_SetPos(hwnd, iPos) \
        (int)SNDMSG((hwnd), PGM_SETPOS, 0, (LPARAM)(iPos))

#define PGM_GETPOS              (PGM_FIRST + 9)
#define MSPager_GetPos(hwnd) \
        (int)SNDMSG((hwnd), PGM_GETPOS, 0, 0)

#define PGM_SETBUTTONSIZE       (PGM_FIRST + 10)
#define MSPager_SetButtonSize(hwnd, iSize) \
        (int)SNDMSG((hwnd), PGM_SETBUTTONSIZE, 0, (LPARAM)(iSize))

#define PGM_GETBUTTONSIZE       (PGM_FIRST + 11)
#define MSPager_GetButtonSize(hwnd) \
        (int)SNDMSG((hwnd), PGM_GETBUTTONSIZE, 0,0)

#define PGM_GETBUTTONSTATE      (PGM_FIRST + 12)
#define MSPager_GetButtonState(hwnd, iButton) \
        (DWORD)SNDMSG((hwnd), PGM_GETBUTTONSTATE, 0, (LPARAM)(iButton))

#define PGM_GETDROPTARGET       CCM_GETDROPTARGET
#define MSPager_GetDropTarget(hwnd, ppdt) \
        (void)SNDMSG((hwnd), PGM_GETDROPTARGET, 0, (LPARAM)(ppdt))
//---------------------------------------------------------------------------------------
//Pager Control Notification Messages
//---------------------------------------------------------------------------------------


// PGN_SCROLL Notification Message

#define PGN_SCROLL          (PGN_FIRST-1)

#define PGF_SCROLLUP        1
#define PGF_SCROLLDOWN      2
#define PGF_SCROLLLEFT      4
#define PGF_SCROLLRIGHT     8


//Keys down
#define PGK_SHIFT           1
#define PGK_CONTROL         2
#define PGK_MENU            4


//#ifdef _WIN32
//#include <pshpack1.h>
//#endif

// This structure is sent along with PGN_SCROLL notifications
typedef struct {
    MSNMHDR hdr;
    WORD fwKeys;            // Specifies which keys are down when this notification is send
    MSRECT rcParent;          // Contains Parent Window Rect
    int  iDir;              // Scrolling Direction
    int  iXpos;             // Horizontal scroll position
    int  iYpos;             // Vertical scroll position
    int  iScroll;           // [in/out] Amount to scroll
}MSNMPGSCROLL, *LPMSNMPGSCROLL;

//#ifdef _WIN32
//#include <poppack.h>
//#endif

// PGN_CALCSIZE Notification Message

#define PGN_CALCSIZE        (PGN_FIRST-2)

#define PGF_CALCWIDTH       1
#define PGF_CALCHEIGHT      2

typedef struct {
    MSNMHDR   hdr;
    DWORD   dwFlag;
    int     iWidth;
    int     iHeight;
}MSNMPGCALCSIZE, *LPMSNMPGCALCSIZE;


// PGN_HOTITEMCHANGE Notification Message

#define PGN_HOTITEMCHANGE   (PGN_FIRST-3)

/* 
The PGN_HOTITEMCHANGE notification uses these notification
flags defined in TOOLBAR:

#define HICF_ENTERING       0x00000010          // idOld is invalid
#define HICF_LEAVING        0x00000020          // idNew is invalid
*/

// Structure for PGN_HOTITEMCHANGE notification
//

typedef struct tagMSNMPGHOTITEM
{
    MSNMHDR   hdr;
    int     idOld;
    int     idNew;
    DWORD   dwFlags;           // HICF_*
} MSNMPGHOTITEM, * LPMSNMPGHOTITEM;

#endif // NOPAGESCROLLER

////======================  End Pager Control ==========================================

//
// === Native Font Control ===
//
#ifndef NONATIVEFONTCTL
//NativeFont Class Name
#define WC_NATIVEFONTCTLA           "NativeFontCtl"

#define WC_NATIVEFONTCTL          WC_NATIVEFONTCTLA

// begin_r_commctrl

// style definition
#define NFS_EDIT                0x0001
#define NFS_STATIC              0x0002
#define NFS_LISTCOMBO           0x0004
#define NFS_BUTTON              0x0008
#define NFS_ALL                 0x0010
#define NFS_USEFONTASSOC        0x0020

// end_r_commctrl

#endif // NONATIVEFONTCTL
// === End Native Font Control ===

/// ====================== Button Control =============================

#ifndef NOBUTTON

#ifdef _WIN32

// Button Class Name
#define WC_BUTTONA              "Button"
#define WC_BUTTON               WC_BUTTONA

#else
#define WC_BUTTON               "Button"
#endif


#define BUTTON_IMAGELIST_ALIGN_LEFT     0
#define BUTTON_IMAGELIST_ALIGN_RIGHT    1
#define BUTTON_IMAGELIST_ALIGN_TOP      2
#define BUTTON_IMAGELIST_ALIGN_BOTTOM   3
#define BUTTON_IMAGELIST_ALIGN_CENTER   4       // Doesn't draw text

typedef struct _MSBUTTON_IMAGELIST
{
    HMSIMAGELIST  himl;   // Index: Normal, hot pushed, disabled. If count is less than 4, we use index 1
    MSRECT        margin; // Margin around icon.
    UINT        uAlign;
} MSBUTTON_IMAGELIST, *PMSBUTTON_IMAGELIST;

#define BCM_GETIDEALSIZE        (BCM_FIRST + 0x0001)
#define MSButton_GetIdealSize(hwnd, psize)\
    (BOOL)SNDMSG((hwnd), BCM_GETIDEALSIZE, 0, (LPARAM)(psize))

#define BCM_SETIMAGELIST        (BCM_FIRST + 0x0002)

#define MSButton_SetImageList(hwnd, pbuttonImagelist)\
    (BOOL)SNDMSG((hwnd), BCM_SETIMAGELIST, 0, (LPARAM)(pbuttonImagelist))

#define BCM_GETIMAGELIST        (BCM_FIRST + 0x0003)
#define MSButton_GetImageList(hwnd, pbuttonImagelist)\
    (BOOL)SNDMSG((hwnd), BCM_GETIMAGELIST, 0, (LPARAM)(pbuttonImagelist))

#define BCM_SETTEXTMARGIN       (BCM_FIRST + 0x0004)
#define MSButton_SetTextMargin(hwnd, pmargin)\
    (BOOL)SNDMSG((hwnd), BCM_SETTEXTMARGIN, 0, (LPARAM)(pmargin))
#define BCM_GETTEXTMARGIN       (BCM_FIRST + 0x0005)
#define MSButton_GetTextMargin(hwnd, pmargin)\
    (BOOL)SNDMSG((hwnd), BCM_GETTEXTMARGIN, 0, (LPARAM)(pmargin))

typedef struct tagCSNMBCHOTITEM
{
    MSNMHDR   hdr;
    DWORD   dwFlags;           // HICF_*
} CSNMBCHOTITEM, * LPCSNMBCHOTITEM;

#define BCN_HOTITEMCHANGE       (BCN_FIRST + 0x0001)

#define BST_HOT            0x0200




#endif // NOBUTTON

/// =====================  End Button Control =========================

/// ====================== Static Control =============================

#ifndef NOSTATIC

#ifdef _WIN32

// Static Class Name
#define WC_STATICA              "Static"

#define WC_STATIC               WC_STATICA

#else
#define WC_STATIC               "Static"
#endif

#endif // NOSTATIC

/// =====================  End Static Control =========================

/// ====================== Edit Control =============================

#ifndef NOEDIT

#ifdef _WIN32

// Edit Class Name
#define WC_EDITA                "Edit"
#define WC_EDIT                 WC_EDITA

#else
#define WC_EDIT                 "Edit"
#endif

#if (_WIN32_WINNT >= 0x501)
#define	EM_SETCUEBANNER	    (ECM_FIRST + 1)		// Set the cue banner with the lParm = LPCWSTR
#define MSEdit_SetCueBannerText(hwnd, lpcwText) \
        (BOOL)SNDMSG((hwnd), EM_SETCUEBANNER, 0, (LPARAM)(lpcwText))
#define	EM_GETCUEBANNER	    (ECM_FIRST + 2)		// Set the cue banner with the lParm = LPCWSTR
#define MSEdit_GetCueBannerText(hwnd, lpwText, cchText) \
        (BOOL)SNDMSG((hwnd), EM_GETCUEBANNER, (WPARAM)(lpwText), (LPARAM)(cchText))

typedef struct _tagCSEDITBALLOONTIP
{
    DWORD   cbStruct;
    LPCWSTR pszTitle;
    LPCWSTR pszText;
    INT     ttiIcon; // From TTI_*
} CSEDITBALLOONTIP, *PCSEDITBALLOONTIP;
#define	EM_SHOWBALLOONTIP   (ECM_FIRST + 3)		// Show a balloon tip associated to the edit control
#define MSEdit_ShowBalloonTip(hwnd, peditballoontip) \
        (BOOL)SNDMSG((hwnd), EM_SHOWBALLOONTIP, 0, (LPARAM)(peditballoontip))
#define EM_HIDEBALLOONTIP   (ECM_FIRST + 4)     // Hide any balloon tip associated with the edit control
#define MSEdit_HideBalloonTip(hwnd) \
        (BOOL)SNDMSG((hwnd), EM_HIDEBALLOONTIP, 0, 0)
#endif

#endif // NOEDIT

/// =====================  End Edit Control =========================

/// ====================== Listbox Control =============================

#ifndef NOLISTBOX

#ifdef _WIN32

// Listbox Class Name
#define WC_LISTBOXA             "ListBox"

#define WC_LISTBOX              WC_LISTBOXA

#else
#define WC_LISTBOX              "ListBox"
#endif

#endif // NOLISTBOX


/// =====================  End Listbox Control =========================

/// ====================== Combobox Control =============================

#ifndef NOCOMBOBOX

struct _COMBOBOXSTYTLE;
typedef struct _COMBOBOXSTYTLE* HCOMBOBOX;


#ifdef _WIN32

// Combobox Class Name
#define WC_COMBOBOXA            "ComboBox"

#define WC_COMBOBOX             WC_COMBOBOXA

#else
#define WC_COMBOBOX             "ComboBox"
#endif

#endif // NOCOMBOBOX


#if (_WIN32_WINNT >= 0x501) 

// custom combobox control messages
#define	CB_SETMINVISIBLE        (CBM_FIRST + 1)
#define CB_GETMINVISIBLE        (CBM_FIRST + 2)

#define MSComboBox_SetMinVisible(hwnd, iMinVisible) \
            (BOOL)SNDMSG((hwnd), CB_SETMINVISIBLE, (WPARAM)iMinVisible, 0)

#define MSComboBox_GetMinVisible(hwnd) \
            (int)SNDMSG((hwnd), CB_GETMINVISIBLE, 0, 0)

#endif

/// =====================  End Combobox Control =========================

/// ====================== Scrollbar Control ============================

#ifndef NOSCROLLBAR

#ifdef _WIN32

// Scrollbar Class Name
#define WC_SCROLLBARA            "ScrollBar"

#define WC_SCROLLBAR             WC_SCROLLBARA

#else
#define WC_SCROLLBAR             "ScrollBar"
#endif
/**************************************************/
//
//      Here is the ScrollBar custom draw,just like
// the TrackBar,We split it to three part,dwDrawStage
// use CDDS_ITEM,please attion it;
//
/**************************************************/
#if (_WIN32_IE >= 0x0300)
// custom draw item specs
#define SBCD_THUMB			0x0001
#define SBCD_CHANNEL		0x0002
#define SBCD_BKGND			0x0003
#endif // Scrollbar

#endif // NOSCROLLBAR


/// ===================== End Scrollbar Control =========================


//====== SysLink control =========================================

#ifdef _WIN32
#if (_WIN32_WINNT >= 0x501)

#define INVALID_LINK_INDEX  (-1)
#define MAX_LINKID_TEXT     48
#define L_MAX_URL_LENGTH    (2048 + 32 + sizeof("://"))

#define WC_LINK         L"SysLink"

#define LWS_TRANSPARENT    0x0001
#define LWS_IGNORERETURN   0x0002

#define LIF_ITEMINDEX    0x00000001
#define LIF_STATE        0x00000002
#define LIF_ITEMID       0x00000004
#define LIF_URL          0x00000008

#define LIS_FOCUSED      0x00000001
#define LIS_ENABLED      0x00000002
#define LIS_VISITED      0x00000004

typedef struct tagMSLITEM
{
    UINT        mask ;
    int         iLink ;
    UINT        state ;
    UINT        stateMask ;
    WCHAR       szID[MAX_LINKID_TEXT] ;
    WCHAR       szUrl[L_MAX_URL_LENGTH] ;
} MSLITEM, * PMSLITEM ;

typedef struct tagMSLHITTESTINFO
{
    MSPOINT       pt ;
    MSLITEM     item ;
} MSLHITTESTINFO, *PMSLHITTESTINFO ;

typedef struct tagMSNMLINK
{
    MSNMHDR       hdr;
    MSLITEM     item ;
} MSNMLINK,  *PMSNMLINK;

//  SysLink notifications
//  NM_CLICK   // wParam: control ID, lParam: PNMLINK, ret: ignored.   

//  LinkWindow messages
#define LM_HITTEST         (WM_USER+0x300)  // wParam: n/a, lparam: PLHITTESTINFO, ret: BOOL
#define LM_GETIDEALHEIGHT  (WM_USER+0x301)  // wParam: n/a, lparam: n/a, ret: cy
#define LM_SETITEM         (WM_USER+0x302)  // wParam: n/a, lparam: LITEM*, ret: BOOL
#define LM_GETITEM         (WM_USER+0x303)  // wParam: n/a, lparam: LITEM*, ret: BOOL

#endif
#endif // _WIN32
//====== End SysLink control =========================================


//
// === MUI APIs ===
//
#ifndef NOMUI
void WINAPI CSInitMUILanguage(LANGID uiLang);


LANGID WINAPI CSGetMUILanguage(void);
#endif  // NOMUI

#endif      // _WIN32_IE >= 0x0400

#ifdef _WIN32
//====== TrackMouseEvent  =====================================================

#ifndef NOMSTRACKMOUSEEVENT

//
// If the messages for TrackMouseEvent have not been defined then define them
// now.
//
#ifndef WM_MOUSEHOVER
#define WM_MOUSEHOVER                   0x02A1
#define WM_MOUSELEAVE                   0x02A3
#endif

//
// If the MSTRACKMOUSEEVENT structure and associated flags havent been declared
// then declare them now.
//
#ifndef TME_HOVER

#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002
#if (WINVER >= 0x0500)
#define TME_NONCLIENT   0x00000010
#endif /* WINVER >= 0x0500 */
#define TME_QUERY       0x40000000
#define TME_CANCEL      0x80000000



#define HOVER_DEFAULT   0xFFFFFFFF

typedef struct tagMSTRACKMOUSEEVENT {
    DWORD cbSize;
    DWORD dwFlags;
    HMSWND  hwndTrack;
    DWORD dwHoverTime;
} MSTRACKMOUSEEVENT, *LPMSTRACKMOUSEEVENT;

#endif // !TME_HOVER



//
// Declare _TrackMouseEvent.  This API tries to use the window manager's
// implementation of TrackMouseEvent if it is present, otherwise it emulates.
//

BOOL
WINAPI
MSTrackMouseEvent(
    LPMSTRACKMOUSEEVENT lpEventTrack);

#endif // !NOMSTRACKMOUSEEVENT

#if (_WIN32_IE >= 0x0400)

//====== Flat Scrollbar APIs=========================================
#ifndef NOFLATSBAPIS

#define WSB_PROP_CYVSCROLL  0x00000001L
#define WSB_PROP_CXHSCROLL  0x00000002L
#define WSB_PROP_CYHSCROLL  0x00000004L
#define WSB_PROP_CXVSCROLL  0x00000008L
#define WSB_PROP_CXHTHUMB   0x00000010L
#define WSB_PROP_CYVTHUMB   0x00000020L
#define WSB_PROP_VBKGCOLOR  0x00000040L
#define WSB_PROP_HBKGCOLOR  0x00000080L
#define WSB_PROP_VSTYLE     0x00000100L
#define WSB_PROP_HSTYLE     0x00000200L
#define WSB_PROP_WINSTYLE   0x00000400L
#define WSB_PROP_PALETTE    0x00000800L
#define WSB_PROP_MASK       0x00000FFFL

#define FSB_FLAT_MODE           2
#define FSB_ENCARTA_MODE        1
#define FSB_REGULAR_MODE        0

BOOL WINAPI MSFlatSB_EnableScrollBar(HMSWND, int, UINT);
BOOL WINAPI MSFlatSB_ShowScrollBar(HMSWND, int code, BOOL);

BOOL WINAPI MSFlatSB_GetScrollRange(HMSWND, int code, LPINT, LPINT);
BOOL WINAPI MSFlatSB_GetScrollInfo(HMSWND, int code, LPMSSCROLLINFO);

int WINAPI MSFlatSB_GetScrollPos(HMSWND, int code);


BOOL WINAPI MSFlatSB_GetScrollProp(HMSWND, int propIndex, LPINT);
#ifdef _WIN64
BOOL WINAPI MSFlatSB_GetScrollPropPtr(HMSWND, int propIndex, PINT_PTR);
#else
#define MSFlatSB_GetScrollPropPtr  MSFlatSB_GetScrollProp
#endif


int WINAPI MSFlatSB_SetScrollPos(HMSWND, int code, int pos, BOOL fRedraw);

int WINAPI MSFlatSB_SetScrollInfo(HMSWND, int code, LPMSSCROLLINFO, BOOL fRedraw);


int WINAPI MSFlatSB_SetScrollRange(HMSWND, int code, int min, int max, BOOL fRedraw);
BOOL WINAPI MSFlatSB_SetScrollProp(HMSWND, UINT index, INT_PTR newValue, BOOL);
#define MSFlatSB_SetScrollPropPtr MSFlatSB_SetScrollProp

BOOL WINAPI MSInitializeFlatSB(HMSWND);
HRESULT WINAPI MSUninitializeFlatSB(HMSWND);

#endif  //  NOFLATSBAPIS

#endif      // _WIN32_IE >= 0x0400

#endif /* _WIN32 */

#endif      // _WIN32_IE >= 0x0300

#if (_WIN32_WINNT >= 0x501)
//
// subclassing stuff
//
#if 0
typedef LRESULT (CALLBACK *SUBCLASSPROC)(HMSWND hWnd, UINT uMsg, WPARAM wParam,
    LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);


BOOL WINAPI MSSetWindowSubclass(HMSWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uIdSubclass,
    DWORD_PTR dwRefData);
BOOL WINAPI MSGetWindowSubclass(HMSWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uIdSubclass,
    DWORD_PTR *pdwRefData);
BOOL WINAPI MSRemoveWindowSubclass(HMSWND hWnd, SUBCLASSPROC pfnSubclass,
    UINT_PTR uIdSubclass);
#endif
LRESULT WINAPI MSDefSubclassProc(HMSWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif


#if (_WIN32_WINNT >= 0x501)

int WINAPI MSDrawShadowText(HMSDC hdc, LPCWSTR pszText, UINT cch, MSRECT* prc, DWORD dwFlags, COLORREF crText, COLORREF crShadow,
    int ixOffset, int iyOffset);
#endif



#ifdef __cplusplus
}
#endif

#endif


#endif  // _MSCOMMCTRL_H

