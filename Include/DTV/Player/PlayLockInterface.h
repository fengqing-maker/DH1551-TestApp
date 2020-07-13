/*
 * PlayLockInterface.h
 *
 *  Created on: 2015-7-2
 *      Author: timothy.liao
 */

#ifndef PLAYLOCKINTERFACE_H_
#define PLAYLOCKINTERFACE_H_
#include "PlayLockingNotify.h"

class PlayLockInterface
{
public:
	PlayLockInterface();
	virtual ~PlayLockInterface();

public:

	virtual unsigned int AdddPlayLockingNotify(PlayLockingNotify* pNotify) = 0;
	virtual unsigned int RemovePlayLcokingNotify(PlayLockingNotify* pNotify) = 0;
};

#endif /* PLAYLOCKINTERFACE_H_ */
