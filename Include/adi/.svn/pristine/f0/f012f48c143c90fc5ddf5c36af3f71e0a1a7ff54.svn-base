#ifndef _ADI_IFRAME_H_
#define _ADI_IFRAME_H_

#include "adi_typedef.h"
#include "adi_osg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	ADIIFAME_LAYER_VIDEO,
	ADIIFAME_LAYER_OSG
}ADIIFrameLayerType_E;

typedef struct _ADIIFrame_t
{
    void*                 UserData;   //iframe buffer
	int 			      nBufSize;    //iframe length
    ADIIFrameLayerType_E  eLayer;	//display on video layer or osg layer
}ADIIFrame_t;

ADI_Error_Code ADIIFrameOpen(int nIndex, ADIIFrame_t stIFrameParams);

ADI_Error_Code ADIIFrameClose(int nIndex);

ADI_Error_Code ADIIFrameShow(int nIndex, ADI_BOOL bIsShow);

ADI_Error_Code ADIIFrameShow2Surface(int nIndex,ADI_HANDLE phSurface);/*add bcm7362 iframeshow to surface*/

#ifdef __cplusplus
}
#endif


#endif

