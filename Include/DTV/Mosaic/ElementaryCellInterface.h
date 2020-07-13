/*
 * ElementaryCellInterface.h
 *
 *  Created on: 2016-4-26
 *      Author: HXC
 */

#ifndef ELEMENTARYCELLINTERFACE_H_
#define ELEMENTARYCELLINTERFACE_H_

class ElementaryCellInterface
{

public:

	ElementaryCellInterface( );
	virtual ~ElementaryCellInterface( );

public:

    virtual unsigned int GetElementaryCellID ( ) = 0;

};

#endif /* ELEMENTARYCELLINTERFACE_H_ */
