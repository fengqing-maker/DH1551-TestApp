/*
 * ServicePlayNotify.h
 *
 *  Created on: 2015-8-15
 *      Author: timothy.liao
 */

#ifndef SERVICEPLAYNOTIFY_H_
#define SERVICEPLAYNOTIFY_H_

class ServicePlayNotify
{
public:
	ServicePlayNotify();
	virtual ~ServicePlayNotify();

public:

	virtual void ServicePlaySuccessNotify() = 0;
	virtual void ServicePlayTimeoutNotify(unsigned int unStatus) = 0;
	virtual void ServicePlayLockErrorNotify(unsigned int unStatus) = 0;
};

#endif /* SERVICEPLAYNOTIFY_H_ */
