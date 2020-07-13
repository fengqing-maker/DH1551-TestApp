/*
 * ChannelNumberServiceIDSpec.h
 *
 *  Created on: 2015-11-19
 *      Author: Timtohy.Liao
 */

#ifndef CHANNELNUMBERSERVICEIDSPEC_H
#define CHANNELNUMBERSERVICEIDSPEC_H

#include "ChannelNumberSpec.h"

class ChannelNumberServiceIDSpec : public ChannelNumberSpec
{

public:

	ChannelNumberServiceIDSpec();
	virtual ~ChannelNumberServiceIDSpec();

public:

	unsigned short GetChannelNumber(ServiceInterface * pServiceInterface);
	unsigned short GetChannelNumber(unsigned int unGlobalIndex);
	unsigned short GetChannelNumber(unsigned int unGroupIndex, unsigned int unServiceIndex);
	ChannelNumberSpec* ConstructSimilarChannelNumberSpec();
};

#endif /* CHANNELNUMBERSERVICEIDSPEC_H */
