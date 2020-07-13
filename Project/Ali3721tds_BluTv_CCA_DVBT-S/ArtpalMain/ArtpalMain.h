
#ifndef _Artpal_main_
#define _Artpal_main_


#include <stdio.h>
#include "adi_typedef.h"
#include "adi_os.h"
#include "adi_tuner.h"
#include "MSWinDef.h"

#ifdef  __cplusplus
extern "C" {
#endif


extern unsigned char g_aucRC[];

extern "C"  int AuraApp( HMSINSTANCE hInstance, HMSINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow );
extern void SectionInit(void);
extern void PlayerInterfaceInit();
extern void PvrInterfaceInit();

void artpal_main(void) ;
void AuraMain(void);

#ifdef  __cplusplus
}
#endif

#endif


