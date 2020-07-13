/*
 * AuraSurfaceCompositorInterface.h
 *
 *  Created on: 2015-7-19
 *      Author: Demo
 */

#ifndef AURASURFACECOMPOSITORINTERFACE_H_
#define AURASURFACECOMPOSITORINTERFACE_H_

#include "adi_osg.h"
#include "MSWindows.h"

#ifdef __cplusplus
extern "C" {
#endif

	void * CreateAuraSurfaceInterface ( char acName [ ], unsigned int unNameLen, MSSIZE inputSIZE );
    void * CreateAuraSurfaceInterfaceWithPosition ( char acName [ ], unsigned int unNameLen, MSSIZE inputSIZE, MSPOINT inputPOINT );
    void * CreateAuraSurfaceInterfaceWithPositionAndFormat ( char acName [ ], unsigned int unNameLen, MSSIZE inputSIZE, MSPOINT inputPOINT, ADIOSGPixelFormat_E eFormat );
    void * FindAuraSurfaceInterface ( char acName [ ], unsigned int unNameLen );
	unsigned int DeleteAuraSurfaceInterface ( char acName [ ], unsigned int unNameLen );

	void * CreateAuraSurfaceLayerInterface ( char acName [ ], unsigned int unNameLen, void * pMainAuraSurface, unsigned int unROP, unsigned int unAlphaValue );
	void * FindAuraSurfaceLayerInterface ( char acName [ ], unsigned int unNameLen );
	unsigned int DeleteAuraSurfaceLayerInterface ( char acName [ ], unsigned int unNameLen );

	void UpdateAuraSurfaceLayerList ( MSRECT updateRECT );

	void EnableAuraSurfaceLayer ( void * pAuraSurfaceLayerInterface );
	void DisableAuraSurfaceLayer ( void * pAuraSurfaceLayerInterface );
	unsigned int IsEnableAuraSurfaceLayer ( void * pAuraSurfaceLayerInterface );

	unsigned int SetSurfaceLayerAlphaValue ( void * pAuraSurfaceLayerInterface, unsigned int unAlphaValue );

    unsigned int AddAuraSurface ( void * pAuraSurfaceLayerInterface, void * pAuraSurface, unsigned int unROP, unsigned int unAlphaValue );
    unsigned int RemoveAuraSurface ( void * pAuraSurfaceLayerInterface, void * pAuraSurface );
    unsigned int MoveUpAuraSurface ( void * pAuraSurfaceLayerInterface, void * pAuraSurface );
    unsigned int MoveDownAuraSurface ( void * pAuraSurfaceLayerInterface, void * pAuraSurface );

    void * GetPICAuraSurfaceInterface ( );
    void * GetUIAuraSurfaceInterface ( );
    void * GetFingerPrintAuraSurfaceInterface ( );
    void * GetOSDPrintAuraSurfaceInterface ( );
	void * GetWaterPrintAuraSurfaceInterface ( MSSIZE inputSIZE, MSPOINT inputPOINT, unsigned int unROP, unsigned int unAlphaValue );

    void * GetPICADISurfaceInterface ( );
    void * GetUIADISurfaceInterface ( );
    void * GetFingerPrintADISurfaceInterface ( );
	void * GetOSDADISurfaceInterface ( );
	void * GetWaterPrintADISurfaceInterface ( MSSIZE inputSIZE, MSPOINT inputPOINT, unsigned int unROP, unsigned int unAlphaValue );

#ifdef __cplusplus
}
#endif


#endif /* AURASURFACECOMPOSITORINTERFACE_H_ */
