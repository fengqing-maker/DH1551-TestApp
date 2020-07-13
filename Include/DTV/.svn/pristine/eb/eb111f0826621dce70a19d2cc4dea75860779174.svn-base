/*
 * LogicalCellInterface.h
 *
 *  Created on: 2016-4-26
 *      Author: HXC
 */

#ifndef LOGICALCELLINTERFACE_H_
#define LOGICALCELLINTERFACE_H_

#include "ElementaryCellInterface.h"

class LogicalCellInterface
{

public:

	LogicalCellInterface( );
	virtual ~LogicalCellInterface( );

public:

    virtual unsigned char GetLogicalCellID ( ) = 0;
    virtual unsigned int GetElementaryCellCount ( ) = 0;
    virtual ElementaryCellInterface * GetElementaryCell ( unsigned int unIndex ) = 0;

    virtual void GetRECT ( unsigned int & unLeft, unsigned int & unTop, unsigned int & unRight, unsigned int & unBottom ) = 0;

};

#endif /* LOGICALCELLINTERFACE_H_ */
