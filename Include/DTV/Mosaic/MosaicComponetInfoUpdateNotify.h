/*
 * MosaicComponetInfoUpdateNotify.h
 *
 *  Created on: 2016-4-26
 *      Author: HXC
 */

#ifndef MOSAICCOMPONETINFOUPDATENOTIFY_H_
#define MOSAICCOMPONETINFOUPDATENOTIFY_H_

#include "Delivery.h"
#include "MosaicComponetInterface.h"
#include "LogicalCellInterface.h"

class MosaicComponetInfoUpdateNotify
{

public:

	MosaicComponetInfoUpdateNotify( );
	virtual ~MosaicComponetInfoUpdateNotify( );

public:

    virtual void StartSearcheDelivery ( Delivery * pDelivery ) = 0;
    virtual void FindedMainDelivery ( Delivery * pDelivery ) = 0;
	virtual void SearchingDeliveryFinished() = 0;
    virtual void MosaicComponetLocking ( Delivery * pDelivery ) = 0;
    virtual void MosaicComponetPlayNotify ( MosaicComponetInterface * pMosaicComponetInterface ) = 0;
    virtual void MosaicComponentLogiciCellChangeNotify ( LogicalCellInterface * pLogicalCellInterface ) = 0;
    
};

#endif /* MOSAICCOMPONETINFOUPDATENOTIFY_H_ */
