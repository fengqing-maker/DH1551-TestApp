/*
 * TunerServicesSearcherNotify.h
 *
 *  Created on: 2015-5-12
 *      Author: timothy.liao
 */

#ifndef TUNERSERVICESSEARCHERNOTIFY_H_
#define TUNERSERVICESSEARCHERNOTIFY_H_
#include "Delivery.h"
#include "SatelliteInterface.h"

class TunerServicesSearcherNotify
{
public:
    TunerServicesSearcherNotify ( );
    virtual ~TunerServicesSearcherNotify ( );

public:
    virtual void TunerServicesSearchProgressNotify ( unsigned int unSearchProgress ) = 0;
    virtual void TunerServicesSearchDeliveryStart ( Delivery* pDelivery, SatelliteInterface *pSatelliteInterface ) = 0;
    virtual void TunerServicesSearchDeliveryEnd ( Delivery* pDelivery ) = 0;
    virtual void TunerServicesSearchAllFinished ( ) = 0;

    virtual void TunerSearvicesSearchLNBPortDetectingFinish ( SatelliteInterface* pSatellite ) = 0;

    virtual void M7FSTUpdatingNotify ( unsigned int unIndex ) = 0;
    virtual void M7FindingHomeTPNotify ( unsigned int unIndex ) = 0;
    virtual void M7FindingRefTPNotify ( unsigned int unIndex ) = 0;

    virtual void TunerServicesSearchNITVersion ( unsigned short usNetworkID, unsigned char ucNITVersion ) = 0;
};

#endif /* TUNERSERVICESSEARCHERNOTIFY_H_ */
