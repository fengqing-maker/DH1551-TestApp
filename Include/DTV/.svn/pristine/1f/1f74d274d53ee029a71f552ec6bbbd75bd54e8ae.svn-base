/*
 * ChannelNumberIndexSpec.h
 *
 *  Created on: 2015-11-19
 *      Author: Timtohy.Liao
 */

#ifndef CHANNELNUMBERINDEXSPEC_H
#define CHANNELNUMBERINDEXSPEC_H

#include "ChannelNumberSpec.h"

class ChannelNumberIndexSpec : public ChannelNumberSpec
{

public:

	ChannelNumberIndexSpec();
	virtual ~ChannelNumberIndexSpec();

public:

	unsigned short GetChannelNumber(ServiceInterface * pServiceInterface);
	unsigned short GetChannelNumber(unsigned int unGlobalIndex);
	unsigned short GetChannelNumber(unsigned int unGroupIndex, unsigned int unServiceIndex);
	ChannelNumberSpec* ConstructSimilarChannelNumberSpec();
};

#endif /* CHANNELNUMBERINDEXSPEC_H */
