/*
 * ChannelNumberLCNSpec.h
 *
 *  Created on: 2015-11-19
 *      Author: Timtohy.Liao
 */

#ifndef CHANNELNUMBERLCNSPEC_H
#define CHANNELNUMBERLCNSPEC_H

#include "ChannelNumberSpec.h"

class ChannelNumberLCNSpec : public ChannelNumberSpec
{

public:

	ChannelNumberLCNSpec();
	virtual ~ChannelNumberLCNSpec();

public:

	unsigned short GetChannelNumber(ServiceInterface * pServiceInterface);
	unsigned short GetChannelNumber(unsigned int unGlobalIndex);
	unsigned short GetChannelNumber(unsigned int unGroupIndex, unsigned int unServiceIndex);
	ChannelNumberSpec* ConstructSimilarChannelNumberSpec();
};

#endif /* CHANNELNUMBERLCNSPEC_H */
