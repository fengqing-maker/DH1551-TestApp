/*
*  MS_DrawListPubType.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/
#ifndef	_MS_DRAWLISTPUBTYPE_H_
#define	_MS_DRAWLISTPUBTYPE_H_

#include "MSWindows.h"

#ifdef __cplusplus
extern "C" {
#endif



#define	MS_CELLBORDER_DEFAULT    (0x00000000)  
#define MS_CELLBORDER_LEFT		 (0x00000001)  
#define	MS_CELLBORDER_RIGHT		 (0x00000002) 
#define	MS_CELLBORDER_UP	     (0x00000004)  
#define	MS_CELLBORDER_DOWN		 (0x00000008)

#define MS_DLI_DODEFAULT		 (0)
#define	MS_DLI_SKIPDEFAULT		 (1)
#define	MS_DLI_BACKGROUND		 (2)

typedef int (* MS_DrawListItemProc)(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW);

typedef void (* MS_DrawListPubliMSetHelpInfo)(UINT uItemHelpState);

typedef int (* MS_DrawListPublicGetIndexProc)(int nIndexType);

typedef enum
{
	MS_LIFS_NOFOCUS,
	MS_LIFS_FOCUS,
	MS_LIFS_LOSTFOCUS
}EMMSLISTITEMFOCUSSTATE;

typedef enum
{
	MS_CONTENTTYPE_STRING,			
	MS_CONTENTTYPET_HMSBITMAP
}EMMSCONTENTTYE;     

typedef enum
{
	MS_CELLTYPE_DEFAULT	

}EMMSCELLTYPE;		

typedef enum
{
	MS_MOVETYPE_STATIC,  
	MS_MOVETYPE_AUTO,    
	MS_MOVETYPE_MOVE	

}EMMSMOVETYPE;			

typedef enum
{
	MSPV_DS_COLOR,
	MSPV_DS_BITMAPID,
	MSPV_DS_HMSBITMAP,
    MSPV_DS_CNT

}EMMSDRAWLISTDRAWSTYLE;

typedef struct _MSDRAWLISTPUB_INITPARAM
{
	EMMSDRAWLISTDRAWSTYLE m_emFocusDrawStyle; 
    
	//focus
	DWORD m_dwFocusLeft;		
	DWORD m_dwFocusMid;
	DWORD m_dwFocusRight;

	EMMSDRAWLISTDRAWSTYLE m_emNoFocusDrawStyle; 
	//no focus
	DWORD m_dwNoFocusLeft;
	DWORD m_dwNoFocusMid;
	DWORD m_dwNoFocusRight;

	EMMSDRAWLISTDRAWSTYLE m_emLostFocusDrawStyle; 	
	//lost focus
	DWORD m_dwLostLeft;
	DWORD m_dwLostMid;
	DWORD m_dwLostRight;

	//text color
	DWORD m_dwFocusTextColor;						
	DWORD m_dwNoFocusTextColor;						
	DWORD m_dwLostFocusTextColor;						

	DWORD	m_dwFocusOutLineColor;								
	DWORD	m_dwNoFocusOutLineColor;								
	DWORD	m_dwLostFocusOutLineColor;								
	int		m_nOutLineWidth	;						

	MS_DrawListItemProc m_pDrawListItemProc;
}MSDRAWLISTPUB_INITPARAM, *LPMSDRAWLISTPUB_INITPARAM;


typedef struct 
{
	LPMSNMLVCUSTOMDRAW m_lpMSNMLVCUSTOMDRAW;	
	int m_nCellIndex;	
	MSRECT m_rcCell;

	EMMSCELLTYPE m_emCellType;		
	
	EMMSCONTENTTYE m_emContentType;			
	DWORD m_dwParam1;			
	DWORD m_dwParam2;
	UINT m_uContentFormate;		

	BOOL m_bCustomTxtColor;		
	DWORD m_dwFocusTxtColor;
	DWORD m_dwNoFocusTxtColor;
	DWORD m_dwLostTxtColor;	

	// 绘制Cell的背景画刷
	HMSBRUSH m_hbrFocusBackground;	 
	HMSBRUSH m_hbrNoFocusBackground;
	HMSBRUSH m_hbrLostBackground;	

	// 绘制边框	
	HMSPEN   m_hpenFocusBorder;		
	HMSPEN   m_hpenNoFocusBorder;	
	HMSPEN   m_hpenLostBorder;		
	UINT     m_uBorderFormate;		
	LPMSDRAWLISTPUB_INITPARAM m_pItemCustomPar;
}MSNMLVCELLCUSTOMDRAW, *LPMSNMLVCELLCUSTOMDRAW;


typedef int (* MS_DrawListCellProc)(MSNMLVCELLCUSTOMDRAW* lpMSNMLVCELLCUSTOMDRAW);

typedef struct
{	
	int m_nCellPos;				
	int m_nCellWidth;			
	HMSFONT m_hFont;
	EMMSCELLTYPE m_emCellType;			
	UINT m_uCellFormate;		

	EMMSCONTENTTYE m_emContentType;			
	DWORD m_dwParam1;			// m_nCellType: 为MS_CONTENTTYPE_STRING, m_dwParam1为String的首地址, 其他为0	
	DWORD m_dwParam2;
	UINT m_uContentFormate;		// 绘制字符串时见MSDrawText中的uFormate格式, 绘制位图时用到uFormate DT_TOP DT_LEFT DT_CENTER DT_RIGHT DT_VCENTER DT_BOTTOM

	BOOL m_bCustomTxtColor;				
	DWORD m_dwFocusTxtColor;	
	DWORD m_dwNoFocusTxtColor;
	DWORD m_dwLostTxtColor;

	// 绘制Cell的背景画刷 
	HMSBRUSH m_hbrFocusBackground;	
	HMSBRUSH m_hbrNoFocusBackground;
	HMSBRUSH m_hbrLostBackground;	

	// 绘制边框	
	HMSPEN   m_hpenFocusBorder;		
	HMSPEN   m_hpenNoFocusBorder;		
	HMSPEN   m_hpenLostBorder;			
	UINT     m_uBorderFormate;		// 边框的类型	

	int m_nMoveType;	
	UINT  m_uMoveInterval;   // 滚动间隔 

	LPMSDRAWLISTPUB_INITPARAM  m_pItemCustomPar;
	MS_DrawListCellProc m_pDrawListCellProc;

    BOOL m_bFoucus;//默认的focus状态
    MSDRAWLISTPUB_INITPARAM  m_pCellCustomPar;//绘制cell的自定义结构
    
}MSLISTCELL, *LPMSLISTCELL; 


int MSDrawListPublicOneItemByCell(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW, MSLISTCELL* lpMSListCell, int nCellCount);

#ifdef __cplusplus
}
#endif

#endif

