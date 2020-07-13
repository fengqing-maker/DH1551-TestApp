/*
 * SatelliteInterface.h
 *
 *  Created on: 2015-5-10
 *      Author: Demo
 */

#ifndef SATELLITEINTERFACE_H_
#define SATELLITEINTERFACE_H_

#include "AntennaInterface.h"

class SatelliteInterface
{

public:

	SatelliteInterface( );
	virtual ~SatelliteInterface( );

public:

    virtual unsigned short GetID ( ) = 0;
    virtual unsigned int GetName ( char acStrName [ ], unsigned int unLen ) = 0;
	virtual unsigned int SetName ( char acStrName [ ], unsigned int unLen ) = 0;
    virtual AntennaInterface * GetAntennaInterface ( ) = 0;

};

#endif /* SATELLITEINTERFACE_H_ */
