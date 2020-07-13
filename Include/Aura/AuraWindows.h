
#ifndef _AURAWINDOWS_H
#define _AURAWINDOWS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

void * AuraGetDefaultAuraLayer ( );
void * AuraCreateAuraLayer ( unsigned int unWidth, unsigned int unHeight );
unsigned int AuraDeleteAuraLayer ( void * hAuraLayer );

HMSWND AuraCreateWindow ( DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HMSWND hWndParent, HMSMENU hMenu, HMSINSTANCE hInstance, LPVOID lpParam, void * hAuraLayer );
HMSWND AuraCreateDialog( HMSINSTANCE hInstance, LPCTSTR lpTemplate, HMSWND hWndParent, MSDLGPROC lpDialogFunc, void * hAuraLayer );
HMSWND AuraCreateDialogIndirect( HMSINSTANCE hInstance, LPCMSDLGTEMPLATE lpTemplate, HMSWND hWndParent, MSDLGPROC lpDialogFunc, void * hAuraLayer );
HMSWND AuraCreateDialogIndirectParam( HMSINSTANCE hInstance, LPCMSDLGTEMPLATEA lpTemplate, HMSWND hWndParent, MSDLGPROC lpDialogFunc, LPARAM lParamInit, void * hAuraLayer );
HMSWND AuraCreateDialogParam( HMSINSTANCE hInstance, LPCTSTR lpTemplateName, HMSWND hWndParent, MSDLGPROC lpDialogFunc, LPARAM dwInitParam, void * hAuraLayer );
int AuraDialogBox( HMSINSTANCE hInstance, LPCTSTR lpTemplate, HMSWND hWndParent, MSDLGPROC lpDialogFunc, void * hAuraLayer );
int AuraDialogBoxIndirect( HMSINSTANCE hInstance, LPMSDLGTEMPLATE lpTemplate, HMSWND hWndParent, MSDLGPROC lpDialogFunc, void * hAuraLayer );
int AuraDialogBoxIndirectParam( HMSINSTANCE hInstance, LPCMSDLGTEMPLATEA hDialogTemplate, HMSWND hWndParent, MSDLGPROC lpDialogFunc, LPARAM dwInitParam, void * hAuraLayer );
int AuraDialogBoxParam( HMSINSTANCE hInstance, LPCTSTR lpTemplateName, HMSWND hWndParent, MSDLGPROC lpDialogFunc, LPARAM dwInitParam, void * hAuraLayer );
int AuraMessageBox( HMSWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, void * hAuraLayer );

HMSBITMAP AuraLoadPNG( HMSINSTANCE hInstance, LPCTSTR lpBitmapName );

HMSBITMAP AuraLoadPNGOnlyBuf ( HMSINSTANCE hInstance, unsigned char ucDataBuf [ ], unsigned int unDataLen );

#ifdef __cplusplus
}
#endif

#endif

