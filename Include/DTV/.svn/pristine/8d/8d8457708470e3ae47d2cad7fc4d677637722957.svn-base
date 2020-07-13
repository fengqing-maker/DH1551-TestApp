/*
 * ServicesDataBaseInterface.h
 *
 *  Created on: 2015-5-4
 *      Author: Demo
 */

#ifndef SERVICESDATABASEPLAYERINTERFACE_H_
#define SERVICESDATABASEPLAYERINTERFACE_H_

#include "DataBaseContainerPlayerInterface.h"
#include "ServiceComponentsSelectInterface.h"
#include "UpdateLiveServiceInfoInterface.h"
#include "UpdateLiveEventInfoInterface.h"
#include "../Application/UpdateLiveApplicationInfoInterface.h"
#include "ServicesDataBasePlayerNotify.h"
#include "ServicesDataBasePlayerServiceUpdateNotify.h"
#include "../PVR/DataBaseContainerRecorderInterface.h"
#include "CA/CAGlueInterface.h"
#include "AutoServiceUpdateMode.h"

class ServicesDataBasePlayerInterface
{

public:

    ServicesDataBasePlayerInterface ( );
    virtual ~ServicesDataBasePlayerInterface ( );

public:

    virtual DataBaseContainerPlayerInterface* GetDataBaseContainerPlayerInterface ( ) = 0;
    virtual UpdateLiveEventInfoInterface * GetUpdateLiveEventInfoInterface ( ) = 0;
    virtual ServiceComponentsSelectInterface* GetServiceComponentsSelectInterface ( ) = 0;
    virtual UpdateLiveServiceInfoInterface* GetUpdateLiveServiceInfoInterface ( ) = 0;
    virtual DataBaseContainerRecorderInterface* GetDataBaseContainerRecorderInterface ( ) = 0;
    virtual UpdateLiveApplicationInfoInterface* GetUpdateLiveApplicationInfoInterface ( ) = 0;
    virtual CAGlueInterface* GetCAGlueInterface ( CAPipeType eCAPipeType ) = 0;
    virtual unsigned int SetSmartCardMasterPinCode ( unsigned int unMasterPinCode ) = 0;

    virtual float GetSignalStrength ( ) = 0;
    virtual float GetSignalQuality ( ) = 0;
    virtual float GetSignalBER ( ) = 0;
    virtual float GetSignalMER ( ) = 0;

    virtual void ConfigNetworkServiceAutoUpdate ( unsigned int unEnableSAU, unsigned int unRequestSDTOther, unsigned int unRequestBAT ) = 0;
    virtual void ConfigNetworkServiceAutoUpdate ( unsigned int unEnableSAU, unsigned int unRequestSDTOther, unsigned int unRequestBAT, unsigned int unTimeoutInSecond ) = 0;
    virtual void ConfigNetworkServiceAutoUpdate ( unsigned int unEnableSAU, unsigned int unRequestSDTOther, unsigned int unRequestBAT, unsigned int unTimeoutInSecond, unsigned int unRecoverHideService ) = 0;
    virtual void ConfigNetworkServiceAutoUpdate ( unsigned int unEnableSAU, unsigned int unRequestSDTOther, unsigned int unRequestBAT, unsigned int unTimeoutInSecond, unsigned int unRecoverHideService, unsigned int unCheckPATPMT ) = 0;
    virtual void ConfigNetworkServiceAutoUpdate ( unsigned int unEnableSAU, unsigned int unRequestSDTOther, unsigned int unRequestBAT, unsigned int unTimeoutInSecond, unsigned int unRecoverHideService, unsigned int unCheckPATPMT, unsigned int unUpdateFreeCAMode ) = 0;
    virtual void ConfigNetworkServiceAutoUpdate ( AutoServiceUpdateMode eSAUMode ) = 0;
    virtual void ConfigNetworkServiceAutoUpdate ( AutoServiceUpdateMode eSAUMode, unsigned int unTimeoutInSecond ) = 0;
    virtual void ConfigNetworkServiceAutoUpdateAllowDeleteTS ( unsigned int unAllowDeleteTS ) = 0;
    virtual void ConfigApplicationInformationMonitor ( unsigned int unMonitorAIT ) = 0;

    virtual unsigned int AddServicesDataBasePlayerNotify ( ServicesDataBasePlayerNotify* pNotify ) = 0;
    virtual unsigned int RemoveServicesDataBasePlayerNotify ( ServicesDataBasePlayerNotify* pNotify ) = 0;

    virtual unsigned int AddServicesDataBasePlayerServiceUpdateMonitor ( ServiceInterface* pService, ServicesDataBasePlayerServiceUpdateNotify* pNotify ) = 0;
    virtual unsigned int RemoveServicesDataBasePlayerServiceUpdateMonitor ( ServiceInterface* pService, ServicesDataBasePlayerServiceUpdateNotify* pNotify ) = 0;
};

#endif /* SERVICESDATABASEPLAYERINTERFACE_H_ */
