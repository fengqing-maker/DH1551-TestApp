/*
 * UpgradeNotify.h
 *
 *  Created on: 2015-8-17
 *      Author: linc
 */

#ifndef UPGRADENOTIFY_H_
#define UPGRADENOTIFY_H_



class UpgradeNotify
{
public:
	UpgradeNotify();
	virtual ~UpgradeNotify();

	virtual void UpgradeStarted() = 0;
	virtual void UpgradeSuccess() = 0;
	virtual void UpgradeFail() = 0;
	virtual void UpgradeTimeOut() = 0;
	virtual void UpgradeEraseSuccess() = 0;
};

#endif /* UPGRADENOTIFY_H_ */
