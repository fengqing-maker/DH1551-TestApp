/*
 * ApplicationSubListInterface.h
 *
 *  Created on: 2015-11-9
 *      Author: timothy.liao
 */

#ifndef APPLICATIONSUBLISTINTERFACE_H_
#define APPLICATIONSUBLISTINTERFACE_H_
#include "ApplicationInterface.h"

class ApplicationSubListInterface
{
public:
	ApplicationSubListInterface();
	virtual ~ApplicationSubListInterface();

public:

	virtual unsigned short GetAppliationType() = 0;
	virtual unsigned short GetTestApplicationFlag() = 0;

	virtual unsigned int GetApplicationCount() = 0;
	virtual ApplicationInterface* GetApplicationInterface(unsigned int unIndex) = 0;

	virtual unsigned int GetExtAuthorizationCount() = 0;
	virtual unsigned int GetExtAuthorization(unsigned int unIndex, unsigned int &runOrganzationID, unsigned short &rusApplicationID, unsigned char &rucPriority) = 0;

};

#endif /* APPLICATIONSUBLISTINTERFACE_H_ */
