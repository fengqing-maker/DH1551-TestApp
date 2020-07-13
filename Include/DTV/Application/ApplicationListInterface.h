/*
 * ApplicationListInterface.h
 *
 *  Created on: 2015-11-8
 *      Author: timothy.liao
 */

#ifndef APPLICATIONLISTINTERFACE_H_
#define APPLICATIONLISTINTERFACE_H_
#include "ApplicationSubListInterface.h"

class ApplicationListInterface
{
public:
	ApplicationListInterface();
	virtual ~ApplicationListInterface();

public:

	virtual unsigned int GetSubListCount() = 0;
	virtual ApplicationSubListInterface* GetSubList(unsigned int unIndex) = 0;
	virtual ApplicationSubListInterface* GetSubList(unsigned short usApplicationType, unsigned short usTestApplicationFlag) = 0;

};

#endif /* APPLICATIONLISTINTERFACE_H_ */
