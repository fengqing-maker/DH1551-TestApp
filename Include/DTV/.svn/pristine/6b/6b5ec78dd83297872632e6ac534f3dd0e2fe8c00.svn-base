/*
 * TunerServicesSearcherInterface.h
 *
 *  Created on: 2015-5-11
 *      Author: timothy.liao
 */

#ifndef TUNERSERVICESSEARCHERINTERFACE_H_
#define TUNERSERVICESSEARCHERINTERFACE_H_
#include "Delivery.h"
#include "ServiceInterface.h"
#include "LegalNetworkSpec.h"
#include "TunerServicesSearchMode.h"
#include "TunerServicesSearcherNotify.h"
#include "SatelliteInterface.h"
#include "ServiceMergeSpec.h"

class TunerServicesSearcherInterface
{
public:
    TunerServicesSearcherInterface ( );
    virtual ~TunerServicesSearcherInterface ( );

public:

    virtual unsigned int AddSearchDelivery ( SatelliteInterface* pSatellite, Delivery* apDeliveryList [ ], unsigned int unDeliveryCount ) = 0;
    virtual unsigned int AddSearchDelivery ( Delivery* apDeliveryList [ ], unsigned int unDeliveryCount ) = 0;

    virtual unsigned int StartSearching ( TunerServicesSearchMode eSearchMode ) = 0;
    virtual unsigned int StartSearching ( TunerServicesSearchMode eSearchMode, ServiceMergeSpec* pServiceMergeSpec ) = 0;
    virtual unsigned int StartSearching ( TunerServicesSearchMode eSearchMode, LegalNetworkSpec* pLegalNetworkSpec ) = 0;
    virtual unsigned int StartSearching ( Delivery* apDeliveryList [ ], unsigned int unDeliveryCount, TunerServicesSearchMode eSearchMode ) = 0;
    virtual unsigned int StartSearching ( Delivery* apDeliveryList [ ], unsigned int unDeliveryCount, TunerServicesSearchMode eSearchMode, ServiceMergeSpec* pServiceMergeSpec ) = 0;
    virtual unsigned int StartSearching ( Delivery* apDeliveryList [ ], unsigned int unDeliveryCount, TunerServicesSearchMode eSearchMode, LegalNetworkSpec* pLegalNetworkSpec ) = 0;
    virtual unsigned int StartSearching ( SatelliteInterface* pSatellite, Delivery* apDeliveryList [ ], unsigned int unDeliveryCount, TunerServicesSearchMode eSearchMode ) = 0;
    virtual unsigned int StartSearching ( SatelliteInterface* pSatellite, Delivery* apDeliveryList [ ], unsigned int unDeliveryCount, TunerServicesSearchMode eSearchMode, ServiceMergeSpec* pServiceMergeSpec ) = 0;
    virtual unsigned int StartSearching ( SatelliteInterface* pSatellite, Delivery* apDeliveryList [ ], unsigned int unDeliveryCount, TunerServicesSearchMode eSearchMode, LegalNetworkSpec* pLegalNetworkSpec ) = 0;

    virtual unsigned int M7FSTFNTStartSearching ( SatelliteInterface* pSatellite, Delivery* apDeliveryList [ ], unsigned int unDeliveryCount, unsigned short usOperatorID, unsigned short usFSTPID, unsigned int unOTABATBouquetID ) = 0;
    virtual unsigned int M7FSTFNTStartSearching ( unsigned short usOperatorID, unsigned short usFSTPID, unsigned int unOTABATBouquetID ) = 0;
    virtual unsigned int M7FSTFNTStartUpdating ( SatelliteInterface* pSatellite, Delivery* apDeliveryList[], unsigned int unDeliveryCount, unsigned short usOperatorID, unsigned short usFSTPID, unsigned int unCareTableVersion, unsigned int unOTABATBouquetID ) = 0;
    virtual unsigned int M7FSTFNTStartUpdating ( unsigned short usOperatorID, unsigned short usFSTPID, unsigned int unCareTableVersion, unsigned int unOTABATBouquetID ) = 0;
    virtual unsigned int M7FSTFNTTerminateUpdating ( ) = 0;

    virtual unsigned int StartBlindScan ( SatelliteInterface* pSatellite, unsigned int unPolarization, unsigned int unStartFrequency, unsigned int unEndFrequency, unsigned int unStartSymbolRate, unsigned int unEndSymbolRate, unsigned int unFastMode, ServiceMergeSpec* pServiceMergeSpec ) = 0;
    virtual unsigned int StartBlindScan ( SatelliteInterface* pSatellite, unsigned int unStartFrequency, unsigned int unEndFrequency, unsigned int unStartSymbolRate, unsigned int unEndSymbolRate, unsigned int unFastMode, ServiceMergeSpec* pServiceMergeSpec ) = 0;
    virtual unsigned int StartBlindScan ( SatelliteInterface* pSatellite, unsigned int unPolarization, unsigned int unFastMode, ServiceMergeSpec* pServiceMergeSpec ) = 0;
    virtual unsigned int StartBlindScan ( SatelliteInterface* pSatellite, unsigned int unFastMode, ServiceMergeSpec* pServiceMergeSpec ) = 0;

    virtual unsigned int EndSearch ( unsigned int unUpdateDataBase ) = 0;

    virtual unsigned int StartLNBPortDetecting ( Delivery* pDelivery, SatelliteInterface* pSatellite, unsigned short usOriNetworkID, unsigned short usTSID ) = 0;
    virtual unsigned int StopLNBPortDetecing ( ) = 0;

    virtual unsigned int SetServiceMergeSpec ( ServiceMergeSpec *pServiceMergeSpec ) = 0;
    virtual unsigned int GetServiceCount ( unsigned int unTVRadio ) = 0;
    virtual unsigned int GetServices ( ServiceInterface* apService [ ], unsigned int unCount, unsigned int unTVRadio ) = 0;

    virtual unsigned int RegisterServicesSearcherNotify ( TunerServicesSearcherNotify* pNotify ) = 0;
    virtual unsigned int UnregisterServicesSearcherNotify ( TunerServicesSearcherNotify* pNotify ) = 0;

    virtual float GetSignalStrength ( ) = 0;
    virtual float GetSignalQuality ( ) = 0;
    virtual float GetSignalBER ( ) = 0;

    virtual void ConfigMergeNetworkDataRecoverHideService ( unsigned int unRecoverHideService ) = 0;
};

#endif /* TUNERSERVICESSEARCHERINTERFACE_H_ */
