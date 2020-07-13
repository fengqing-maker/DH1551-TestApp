/*
 * AuraCompositorInterface.h
 *
 *  Created on: 2015-7-19
 *      Author: Demo
 */

#ifndef AURACOMPOSITORINTERFACE_H_
#define AURACOMPOSITORINTERFACE_H_

#include "adi_osg.h"
#include "MSWindows.h"

#ifdef __cplusplus
extern "C" {
#endif

	void DrawExpAndUISurface ( MSRECT & dstRect, MSRECT & srcRect );
    void DisableExpAndUISurface ( );

	ADI_HANDLE GetUIADISurface ( );
	ADI_HANDLE GetExpADISurface ( );
	ADI_HANDLE GetExpOSDADISurface ( );
    ADI_HANDLE CreateWaterPintADISurface ( MSSIZE inputSIZE, MSPOINT inputPOINT );

#ifdef __cplusplus
}
#endif

#endif /* AURACOMPOSITORINTERFACE_H_ */
