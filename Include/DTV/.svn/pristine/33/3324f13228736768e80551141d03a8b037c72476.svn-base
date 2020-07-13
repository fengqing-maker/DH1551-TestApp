/*
 * NVODPlayInterface.h
 *
 *  Created on: 2015-11-29
 *      Author: Demo
 */

#ifndef NVODPLAYINTERFACE_H_
#define NVODPLAYINTERFACE_H_
#include "NVODReferenceServiceContainerInterface.h"
#include "NVODReferenceServiceUpdateNotify.h"
#include "Delivery.h"
#include "ServicesGroupFilterSpec.h"
#include "CheckServiceNameSpec.h"

class NVODPlayInterface
{

public:
	
	NVODPlayInterface( );
	virtual ~NVODPlayInterface( );

public:

	virtual unsigned int StartSearch ( Delivery ** appDelivery, unsigned int unDeliveryCount ) = 0;
	virtual void StopSearch ( ) = 0;

    virtual Delivery * GetMainDelivery ( ) = 0;

    virtual NVODReferenceServiceContainerInterface * GetNVODReferenceServiceContainerInterface ( ) = 0;

    virtual unsigned int Play ( unsigned int unReferenceServiceIndex, unsigned int unTimeShiftEventIndex ) = 0;
    virtual unsigned int PlayPreReferenceService ( ) = 0;
    virtual unsigned int PlayNextReferenceService ( ) = 0;

    virtual unsigned int GetCurrentNVODPlayIndex ( int & nReferenceServiceIndex, int & nTimeShiftEventIndex ) = 0;

    virtual unsigned int AddNVODReferenceServiceUpdateNotify ( NVODReferenceServiceUpdateNotify * pNVODReferenceServiceUpdateNotify ) = 0;
    virtual unsigned int RemoveNVODReferenceServiceUpdateNotify ( NVODReferenceServiceUpdateNotify * pNVODReferenceServiceUpdateNotify ) = 0;
    virtual void SetNVODReferenceServiceContentUpdatedNotify ( unsigned int unReferenceServiceIndex ) = 0;
	
    virtual void SetNVODReferenceServicesGroupFilterSpec ( ServicesGroupFilterSpec * pServicesGroupFilterSpec ) = 0;
	virtual void SetNVODReferenceServiceNameFilterSpec(CheckServiceNameSpec * pCheckServiceNameSpec) = 0;

	virtual unsigned int IsNVODWorking() = 0;
	virtual void DoNVODPlayConflict(unsigned int unGroupIndex , unsigned int unServiceIndex) = 0;

};

#endif /* NVODPLAYINTERFACE_H_ */
