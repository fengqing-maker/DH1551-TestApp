/*
 * NetworkInterface.h
 *
 *  Created on: 2015-4-9
 *      Author: timothy.liao
 */

#ifndef NETWORKINTERFACE_H_
#define NETWORKINTERFACE_H_

#include "TransponderInterface.h"
#include "BouquetInterface.h"

class NetworkInterface
{

public:

    NetworkInterface ( );
    virtual ~NetworkInterface ( );

public:
    virtual unsigned short GetNetworkID ( ) = 0;
    virtual unsigned int GetNetworkName ( char acNetworkName [ ], unsigned int unNetworkNameLength ) = 0;

    virtual unsigned int GetTransponderCount ( ) = 0;
    virtual TransponderInterface * GetTransponderByIndex ( unsigned int unIndex ) = 0;
    virtual TransponderInterface * GetTransponderByID ( unsigned short usOriginalNetworkID, unsigned short usTSID ) = 0;

    virtual unsigned int GetBouquetCount ( ) = 0;
    virtual BouquetInterface* GetBouquetByIndex ( unsigned int unIndex ) = 0;
    virtual BouquetInterface* GetBouquetByID ( unsigned short usBouquetID ) = 0;

    virtual unsigned int GetAllServicesCount ( ) = 0;
    virtual void DebugPrint ( ) = 0;
};

#endif /* NETWORKINTERFACE_H_ */
