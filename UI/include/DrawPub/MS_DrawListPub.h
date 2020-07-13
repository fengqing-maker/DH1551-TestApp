/*
*  MS_DrawListPubFun.h
*
*  Created on: 2015-5-21
*      Author: Burt.Li
*/

#ifndef	_MS_DRAWLISTPUBFUN_H_
#define	_MS_DRAWLISTPUBFUN_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "MSWindows.h"
#include "MSCommCtrl.h"
#include "MS_DrawListPubType.h"


int MSDrawListPublicOneItemByCell(MSNMLVCUSTOMDRAW* pMSNMLVCUSTOMDRAW,	MSLISTCELL* lpMSListCell,int nCellCount);


#ifdef __cplusplus
}
#endif

#endif
