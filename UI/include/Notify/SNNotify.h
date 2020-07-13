/*
 * SNNotify.h
 *
 *  Created on: 2015-8-17
 *      Author: linc
 */

#ifndef SNNOTIFY_H_
#define SNNOTIFY_H_

#include "UpgradeNotify.h"

class SNNotify : public UpgradeNotify
{
public:
	SNNotify();
	virtual ~SNNotify();

	void UpgradeStarted();
	void UpgradeSuccess();	
	void UpgradeFail();
	void UpgradeTimeOut();
	void UpgradeEraseSuccess();
};

#endif /* SNNOTIFY_H_ */
