/*
 * NetworkDeliveryInterface.h
 *
 *  Created on: 2015-5-10
 *      Author: Demo
 */

#ifndef NETWORKDELIVERYINTERFACE_H_
#define NETWORKDELIVERYINTERFACE_H_

#include "SatelliteInterface.h"
#include "AntennaInterface.h"
#include "CableDelivery.h"
#include "TerrestrialDelivery.h"
#include "SatelliteDelivery.h"

class NetworkDeliveryInterface
{

public:
	
	NetworkDeliveryInterface( );
	virtual ~NetworkDeliveryInterface( );

public:

	virtual unsigned int GetCableDeliveryCount( ) = 0;
	virtual CableDelivery * GetCableDelivery( unsigned int unIndex ) = 0;

	virtual unsigned int GetTerrestrialDeliveryCount( ) = 0;
	virtual TerrestrialDelivery * GetTerrestrialDelivery( unsigned int unIndex ) = 0;

	virtual unsigned int GetSatelliteCount( ) = 0;
	virtual SatelliteInterface * GetSatellite( unsigned int unIndex ) = 0;

	virtual unsigned int GetSatelliteDeliveryCount( SatelliteInterface * pSatelliteInterface ) = 0;
	virtual SatelliteDelivery * GetSatelliteDelivery( SatelliteInterface * pSatelliteInterface, unsigned int unIndex ) = 0;

	virtual unsigned int AddCableDelivery( CableDelivery * pCableDelivery ) = 0;
	virtual unsigned int AddTerrestrialDelivery( TerrestrialDelivery * pTerrestrialDelivery ) = 0;
    virtual SatelliteInterface * CreateAndAddSatellite ( char acName [ ], unsigned int unNameLen ) = 0;
	virtual unsigned int DeleteSatellite(char acName[], unsigned int unNameLen) = 0;
	virtual unsigned int EditSatelliteName(char acSrcName[], unsigned int unSrcNameLen, char acNewName[], unsigned int unNewNameLen) = 0;
	virtual unsigned int AddSatelliteDelivery(SatelliteInterface * pSatelliteInterface, SatelliteDelivery * pSatelliteDelivery) = 0;
	virtual unsigned int RemoveSatelliteDelivery(SatelliteInterface * pSatelliteInterface, SatelliteDelivery * pSatelliteDelivery) = 0;
	virtual unsigned int DeleteSatelliteDelivery(SatelliteInterface * pSatelliteInterface, unsigned int unDeliveryIndex) = 0;
};

#endif /* NETWORKDELIVERYINTERFACE_H_ */
