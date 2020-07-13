
#ifndef _MSFONT_H
#define _MSFONT_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

	typedef BOOL ReadCharOutlineDataFUN( DWORD hFont, WORD wStrID, PBYTE pbData, DWORD dwDataLen, int nDataWidth, int nOff, int Bits, int nValue, int* pnActiveWidth, int* pnDataType );
	typedef BOOL ExchangeExternInfoFUN( DWORD hFont, int nX, int nY, int nDelta, int nShowBuffWidth, int nBits, COLORREF clrText, COLORREF clrBackGND, PBYTE pCorlor, PBYTE pLev, PBYTE pbData );

	typedef struct tagExternFontOption
	{
		DWORD hFont;
		int   m_nFontWidth;
		int   m_nFontHeight;
		char  m_pchFontName[ 32 ];
		BOOL( *ReadCharOutlineData )( DWORD hFont, WORD wStrID, PBYTE pbData, DWORD dwDataLen, int nDataWidth, int nOff, int Bits, int nValue, int* pnActiveWidth, int* pnDataType );
		BOOL( *ExchangeExternInfo )( DWORD hFont, int nX, int nY, int nDelta, int nShowBuffWidth, int nBits, COLORREF clrText, COLORREF clrBackGND, PBYTE pCorlor, PBYTE pLev, PBYTE pbData );

	}EXTERNFONTOPTION;

	BOOL SetDefaultSystemLargeFont( HMSFONT hCSFONT );
	BOOL SetDefaultSystemSmallFont( HMSFONT hCSFONT );
	BOOL MSCreateExternFont( EXTERNFONTOPTION *pEXTERNFONTOPTION );
	BOOL MSSetFontCharInterSpaceAndLineSpace( HMSFONT hFont, int nCharInterSpace, int nLineSpace );
	int GetFontModelDataFromAura( HMSFONT hFont, LPCTSTR pcInputStr, int nInputStrLen, PBYTE pbDataBuf, int nDataBufCount, int nOneLinesBytes, int Bits, int nValue );
	int GetMultiLineFontModelData( HMSFONT hFont, LPCTSTR pcInputStr, int nInputStrLen, PBYTE pbDataBuf, int nDataBufLen, DWORD dwFormat, int nLineSpace, int nInterCharSpace, int nOffSetX, int nOffSetY, MSSIZE* pMSSIZE );

#ifdef  __cplusplus
}
#endif

#endif
