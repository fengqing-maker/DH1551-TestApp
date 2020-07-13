/*
 * ChannelNumberSpec.h
 *
 *  Created on: 2015-11-19
 *      Author: Timothy.Liao
 */

#ifndef CHANNELNUMBERSPEC_H_
#define CHANNELNUMBERSPEC_H_

#include "ServiceInterface.h"

class ChannelNumberSpec
{

public:

	ChannelNumberSpec ( );
	virtual ~ChannelNumberSpec ( );

public:

    virtual unsigned short GetChannelNumber ( ServiceInterface * pServiceInterface ) = 0;
	virtual unsigned short GetChannelNumber ( unsigned int unGlobalIndex ) = 0;
	virtual unsigned short GetChannelNumber ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
	virtual ChannelNumberSpec* ConstructSimilarChannelNumberSpec ( ) = 0;
};

#endif /* CHANNELNUMBERSPEC_H_ */
