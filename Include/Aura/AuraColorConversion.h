
#ifndef _AURACOLORCONVERSION_H
#define _AURACOLORCONVERSION_H

#ifdef  __cplusplus
extern "C" {
#endif

#define RGBA(r,g,b,a)       ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|((DWORD)((BYTE)(a))<<24))
#define RGB( r,g,b )        RGBA(r,g,b,0xff)

#define GetRValue(rgb)      ((BYTE)(rgb))
#define GetGValue(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      ((BYTE)((rgb)>>16))
#define GetAValue(rgb)      ((BYTE)((rgb)>>24))

COLORREF GetCOLORREF ( int nRed, int nGreen, int nBlue, int nAlpha );

#ifdef  __cplusplus
}
#endif

#endif

