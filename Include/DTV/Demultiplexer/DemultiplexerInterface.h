/*
 * DemultiplexerInterface.h
 *
 *  Created on: 2015-3-24
 *      Author: Demo
 */

#ifndef DEMULTIPLEXERINTERFACE_H_
#define DEMULTIPLEXERINTERFACE_H_

#include "PacketFilterInterface.h"
#include "PacketListener.h"
#include "PacketListenerDestructInterface.h"

class DemultiplexerInterface
{

public:
	
	DemultiplexerInterface( );
	virtual ~DemultiplexerInterface( );

public:

	virtual unsigned int GetSlotCount( ) = 0;
	virtual unsigned int GetFreeSlotCount( ) = 0;
	virtual unsigned int GetFilterCount( ) = 0;
	virtual unsigned int GetFreeFilterCount( ) = 0;
	virtual unsigned int GetBufferSingalCount( ) = 0;
	virtual unsigned int GetFreeBufferSingalCount( ) = 0;

    virtual PacketFilterInterface * MallocSectionPacketListenerFilter ( char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;
    virtual PacketFilterInterface * MallocSectionPacketListenerFilter ( char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, unsigned int unCRCCheck, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;
    virtual PacketFilterInterface * MallocPESPacketListenerFilter ( char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;
    virtual PacketFilterInterface * MallocTSRawSlot ( char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;

    virtual PacketFilterInterface * MallocSectionPacketListenerFilter ( unsigned int unDemuxID, char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;
    virtual PacketFilterInterface * MallocSectionPacketListenerFilter ( unsigned int unDemuxID, char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, unsigned int unCRCCheck, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;
    virtual PacketFilterInterface * MallocPESPacketListenerFilter ( unsigned int unDemuxID, char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;
    virtual PacketFilterInterface * MallocTSRawSlot ( unsigned int unDemuxID, char acDispatcherName [ ], unsigned int unPID, unsigned int unBufferSize, PacketListener * pPacketListener, PacketListenerDestructInterface & inputPacketListenerDestruct ) = 0;
	
	virtual unsigned int FreePacketFilterInterface( PacketFilterInterface * pPacketFilterInterface ) = 0;

    virtual PacketListenerDestructInterface * MallocPacketListenerDestruct ( ) = 0;

};

#endif /* DEMULTIPLEXERINTERFACE_H_ */
