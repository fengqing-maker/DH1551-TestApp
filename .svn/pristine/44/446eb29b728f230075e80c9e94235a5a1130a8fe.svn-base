/*
 * SmartCardNotify.h
 *
 *  Created on: 2015-8-15
 *      Author: timothy.liao
 */

#ifndef SMARTCARDNOTIFY_H_
#define SMARTCARDNOTIFY_H_

class SmartCardNotify
{
public:
	SmartCardNotify();
	virtual ~SmartCardNotify();

public:

	virtual void SmartCardInNotify(unsigned int unIndex) = 0;
	virtual void SmartCardOutNotify(unsigned int unIndex) = 0;
	virtual void SmartCardResetNotify(unsigned int unIndex, unsigned int unSuccess) = 0;
	virtual void NoSmartCardNotify() = 0;
};

#endif /* SMARTCARDNOTIFY_H_ */
