
#ifndef _AURA_H
#define _AURA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"

typedef int ( * AURAMAIN )( HMSINSTANCE, HMSINSTANCE, char*, int );

void AuraVersion ( char acVersion [ ], unsigned int unVerLen );

unsigned int AuraInit2 ( unsigned char * pucAuraBuf, unsigned int unAuraBufLen, unsigned char * apucRCData [ ], unsigned int aunRCDataLen [ ], unsigned int aunDataType [ ], unsigned int unDataCount, void * hUIADISurface );
unsigned int AuraInit ( unsigned char * pucAuraBuf, unsigned int unAuraBufLen, unsigned char * apucRCData [ ], unsigned int aunRCDataLen [ ], unsigned int aunDataType [ ], unsigned int unDataCount );
unsigned int AuraBoot ( AURAMAIN AuraMain, unsigned int unPriority, unsigned int unStackSize );

unsigned int AuraInputKeyMsg ( MSMSG * pMSMSG );
unsigned int AuraInputKeyEvent ( unsigned int unKeyCode );

unsigned int AuraSetReplaceCode ( unsigned int unReplace );

unsigned int AuraAddShortcutKey ( HMSWND hParentCSWND, unsigned int unVCode, HMSWND hMSWND );
unsigned int AuraDeleteShortcutKey ( HMSWND hMSWND, unsigned int unVCode );
unsigned int AuraAddGlobalKey ( unsigned int unKeyCode );
unsigned int AuraDeleteGlobalKey ( unsigned int unKeyCode );

void EnableGlobalKey ( );
void DisableGlobalKey ( );

unsigned int AuraSetDLGParse ( HMSWND hMSWND, int nVCode, unsigned int unActive );

unsigned int AuraGetMutiLanguageCount ( );
unsigned int AuraSetCurLanguageCode ( char acLanguageName[ ], unsigned int unNameLen );
unsigned int AuraGetCurLanguageCode ( char acLanguageNameBuf [ ], unsigned int unNameBufLen );
unsigned int AuraGetLanguageCodeByIndex ( unsigned int nIndex, char acLanguageNameBuf [ ], unsigned int unNameBufLen );

void AuraSetDefaultLanguageCodePage ( unsigned int unLanguageCodePage );

void AuraPrintfAuraMemoryStatus ( );

/*version (0,MQRSPEC_VERSION_MAX)*/
unsigned int AuraQRcode_encodeString(const char *string, int version, unsigned int & unWidth);
unsigned int AuraQRcode_getcolor(unsigned int nX, unsigned int nY, unsigned int & unBlack);
void AuraQRcode_free();

#ifdef __cplusplus
}
#endif

#endif

