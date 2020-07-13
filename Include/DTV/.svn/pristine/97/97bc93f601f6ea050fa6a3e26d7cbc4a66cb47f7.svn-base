/*
 * MosaicPlayInterface.h
 *
 *  Created on: 2016-4-26
 *      Author: HXC
 */

#ifndef MOSAICPLAYINTERFACE_H_
#define MOSAICPLAYINTERFACE_H_

#include "Delivery.h"
#include "MosaicComponetInfoUpdateNotify.h"
#include "MosaicComponetInterface.h"
#include "LogicalCellInterface.h"

class MosaicPlayInterface
{

public:

	MosaicPlayInterface( );
	virtual ~MosaicPlayInterface( );

public:

    virtual void SetScreenPosition ( unsigned int unLeft, unsigned int unTop, unsigned int unRight, unsigned int unBottom ) = 0;

    virtual unsigned int Start ( Delivery ** appDelivery, unsigned int unDeliveryCount ) = 0;
    virtual void Stop ( ) = 0;

    virtual unsigned int GetMosaicComponetCount ( ) = 0;
    virtual MosaicComponetInterface * GetMosaicComponet ( unsigned int unIndex ) = 0;
    virtual MosaicComponetInterface * GetCurMosaicComponet ( ) = 0;

    virtual MosaicComponetInterface * ChangeUpMosaicComponet ( ) = 0;
    virtual MosaicComponetInterface * ChangeDownMosaicComponet ( ) = 0;
    virtual MosaicComponetInterface * ChangeDefaultComponet ( ) = 0;

    virtual LogicalCellInterface * DefaultLogicalCellAudio ( ) = 0;
    virtual LogicalCellInterface * ChangeLeftLogicalCellAudio ( ) = 0;
    virtual LogicalCellInterface * ChangeRightLogicalCellAudio ( ) = 0;
    virtual LogicalCellInterface * ChangeUpLogicalCellAudio ( ) = 0;
    virtual LogicalCellInterface * ChangeDownLogicalCellAudio ( ) = 0;

    virtual unsigned int PlayCurLogicalCellService ( ) = 0;

	virtual unsigned int GetMosaicServiceName(MosaicComponetInterface * pMosaicComponet, char aucName[], unsigned int unLength) = 0;

};

#endif /* MOSAICPLAYINTERFACE_H_ */
