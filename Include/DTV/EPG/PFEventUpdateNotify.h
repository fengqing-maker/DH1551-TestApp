/*
 * PFEventUpdateNotify.h
 *
 *  Created on: 2015-5-4
 *      Author: linc
 */

#ifndef PFEVENTUPDATENOTIFY_H_
#define PFEVENTUPDATENOTIFY_H_

class PFEventUpdateNotify
{
public:
	PFEventUpdateNotify(unsigned short usServiceId);
	virtual ~PFEventUpdateNotify();

	virtual unsigned int PresentEventUpdateNotify() = 0;
	virtual unsigned int FollowEventUpdateNotify() = 0;

	unsigned int IsSimilarEvent(unsigned short usServiceId);

private:
	unsigned short m_usServiceId;
};

#endif /* PFEVENTUPDATENOTIFY_H_ */
