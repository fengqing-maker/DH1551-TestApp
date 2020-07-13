/*
 * TransponderInterface.h
 *
 *  Created on: 2015-4-9
 *      Author: timothy.liao
 */

#ifndef TRANSPONDERINTERFACE_H_
#define TRANSPONDERINTERFACE_H_

#include "Delivery.h"
#include "ServiceInterface.h"

class TransponderInterface
{

public:

    TransponderInterface ( );
    virtual ~TransponderInterface ( );

public:

    virtual unsigned short GetOriginalNetworkID ( ) = 0;
    virtual unsigned short GetTSID ( ) = 0;
	virtual unsigned short GetPHYNetworkID ( ) = 0;
    virtual Delivery* GetDelivery ( ) = 0;

    virtual unsigned int GetServiceCount ( ) = 0;
    virtual ServiceInterface* GetServiceByIndex ( unsigned int unIndex ) = 0;
    virtual ServiceInterface* GetServiceByID ( unsigned short usOriginalNetworkID, unsigned short usTSID, unsigned short usServiceID ) = 0;

	virtual unsigned int GetServiceCount ( ServiceType eServiceType ) = 0;
    virtual ServiceInterface* GetServiceByIndex ( unsigned int unIndex , ServiceType eServiceType ) = 0;

};

#endif /* TRANSPONDERINTERFACE_H_ */
