/*
 * MosaicComponetInterface.h
 *
 *  Created on: 2016-4-26
 *      Author: HXC
 */

#ifndef MOSAICCOMPONETINTERFACE_H_
#define MOSAICCOMPONETINTERFACE_H_

#include "LogicalCellInterface.h"

class MosaicComponetInterface
{

public:

	MosaicComponetInterface( );
	virtual ~MosaicComponetInterface( );

public:

    virtual void GetServiceID ( unsigned short & unOriNetworkID, unsigned short & usTSID, unsigned short & usServiceID ) = 0;

    virtual unsigned int GetNumberOfHorizontalElementaryCellsCount ( ) = 0;
    virtual unsigned int GetNumberOfVerticalElementaryCellsCount ( ) = 0;

    virtual unsigned int GetLogicalCellCount ( ) = 0;
    virtual LogicalCellInterface * GetLogicalCell ( unsigned int unIndex ) = 0;
    virtual LogicalCellInterface * GetLogicalCell ( unsigned int unHIndex, unsigned int unVIndex ) = 0;

};

#endif /* MOSAICCOMPONETINTERFACE_H_ */
