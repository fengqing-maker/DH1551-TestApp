/*
 * PacketFilterInterface.h
 *
 *  Created on: 2015-3-24
 *      Author: Demo
 */

#ifndef PACKEFILTERINTERFACE_H_
#define PACKEFILTERINTERFACE_H_

#include "FilterParameter.h"

class PacketFilterInterface
{

public:
	
	PacketFilterInterface( );
	virtual ~PacketFilterInterface( );

public:

	virtual void Start( ) = 0;
	virtual void Stop( ) = 0;

	virtual unsigned int SetFilter( FilterParameter & inputFilterParameter ) = 0;

};

#endif /* PACKEFILTERINTERFACE_H_ */
