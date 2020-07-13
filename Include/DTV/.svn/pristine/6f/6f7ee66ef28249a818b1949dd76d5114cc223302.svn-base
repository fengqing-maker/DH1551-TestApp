/*
 * PlayLockingNotify.h
 *
 *  Created on: 2015-7-2
 *      Author: timothy.liao
 */

#ifndef PLAYLOCKINGNOTIFY_H_
#define PLAYLOCKINGNOTIFY_H_
#include "KeyInterface.h"
#include "PlayLockType.h"

class PlayLockingNotify
{
public:
	PlayLockingNotify();
	virtual ~PlayLockingNotify();

public:

	virtual void PlayLockedNotify(PlayLockType eLockType, KeyInterface* pKeyInterface) = 0;
	virtual void PlayUnlockedNotify(PlayLockType eLockType, KeyInterface* pKeyInterface) = 0;
};

#endif /* PLAYLOCKINGNOTIFY_H_ */
