/*
 * PacketListener.h
 *
 *  Created on: 2015-3-22
 *      Author: Demo
 */

#ifndef PACKETLISTENER_H_
#define PACKETLISTENER_H_

#include "APSemaphore.h"

class PacketListener
{

public:
	
	PacketListener( );
	virtual ~PacketListener( );

public:

	virtual void SendData( unsigned char aucPacketData[ ], unsigned int unPacketDataLen ) = 0;

};

#endif /* PACKETLISTENER_H_ */
