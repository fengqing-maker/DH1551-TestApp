#ifndef TELETEXTRENDERINGINTERFACE_H_
#define TELETEXTRENDERINGINTERFACE_H_
#include "Aura.h"

class TeletextRenderingInterface
{
public:
	TeletextRenderingInterface( );
	virtual ~TeletextRenderingInterface( );

public:
	virtual unsigned int ShowPage( HMSDC hDC, MSRECT & tShowRect, unsigned char ucPageNum ) = 0;
	virtual unsigned int ShowNextPage( HMSDC hDC, MSRECT & tShowRect ) = 0;
	virtual unsigned int ShowPrePage(HMSDC hDC, MSRECT & tShowRect) = 0;
    virtual unsigned int ShowNextSubPage ( HMSDC hDC, MSRECT & tShowRect ) = 0;
    virtual unsigned int ShowPreSubPage ( HMSDC hDC, MSRECT & tShowRect ) = 0;
	virtual unsigned int Recall(HMSDC hDC, MSRECT & tShowRect) = 0;
	virtual unsigned int Reshow(HMSDC hDC, MSRECT & tShowRect, unsigned int bStepShow) = 0;
	virtual unsigned int ShowLinkPage(HMSDC hDC, MSRECT & tShowRect) = 0;
	virtual unsigned int GoNextLinkPage(void) = 0;
	virtual unsigned int GoPreLinkPage(void) = 0;
	virtual unsigned int ChangeLinkPage(HMSDC hDC, MSRECT & tShowRect) = 0;
	virtual unsigned int ChangeFlashPage(HMSDC hDC, MSRECT & tShowRect) = 0;
	virtual unsigned int ShowTime(HMSDC hDC, MSRECT & tShowRect, unsigned char * pucTime, int nTimeLen) = 0;
	virtual unsigned int ShowSearchTitle(HMSDC hDC, MSRECT & tShowRect) = 0;
	virtual unsigned int ClearTeleTitle(HMSDC hDC, MSRECT & tShowRect) = 0;
	virtual unsigned int JumpPage(HMSDC hDC, MSRECT & tShowRect, int nJumpNum) = 0;
	virtual unsigned int ShowFastextPage(HMSDC hDC, MSRECT & tShowRect, int nColorIndex) = 0;

	virtual unsigned int ShowCaption(HMSDC hDC, MSRECT & tShowRect) = 0;

	virtual unsigned int RegisterFont(HMSHANDLE * hFontArray, int nFontCount) = 0;
	virtual unsigned int SetHeight(unsigned int dwHeight) = 0;
	virtual unsigned int SetWidth(unsigned int dwWidth) = 0;
	virtual unsigned int SetDisplayPageHead(unsigned int unDisplayHead) = 0;
	virtual unsigned int SetStepShowFlag(unsigned int unFlag) = 0;
	virtual unsigned int SetShowEmptyPage(unsigned int unMode) = 0;
	virtual unsigned int SetFontType(int nFontType) = 0;
	virtual unsigned int SetLanguageCode(char acLanguageCode[], unsigned int unLength) = 0;
	virtual unsigned int SetString(char * pString1, int nString1Len, char * pString2, int nString2Len) = 0;
	virtual unsigned int SetBGColor(unsigned int unGBColor, unsigned int unTransparency) = 0;
	virtual unsigned int SetEmptyColorFlag(unsigned int unIsSetBColor) = 0;

	virtual unsigned int GetCurPage(unsigned int * punPageNum) = 0;

    virtual void ResetTilteNumber ( ) = 0;

    virtual unsigned int ConfigFlashPage ( unsigned int unEnable ) = 0;
    virtual unsigned int ConfigLinkPage ( unsigned int unEnable ) = 0;
    virtual unsigned int ConfigFastextPageHelpBar ( unsigned int unEnable ) = 0;
};
#endif /* TELETEXTRENDERING_H_ */
