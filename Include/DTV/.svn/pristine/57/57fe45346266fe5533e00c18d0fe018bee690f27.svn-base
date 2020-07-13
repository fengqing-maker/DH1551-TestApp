/*
 * DataBaseContainerPlayerNotify.h
 *
 *  Created on: 2015-5-7
 *      Author: timothy.liao
 */

#ifndef DATABASECONTAINERPLAYERNOTIFY_H_
#define DATABASECONTAINERPLAYERNOTIFY_H_
#include "ServiceInterface.h"
#include "Delivery.h"

class DataBaseContainerPlayerNotify
{
public:

    DataBaseContainerPlayerNotify ( );
    virtual ~DataBaseContainerPlayerNotify ( );

public:

    virtual void DeliveryLockingNotify ( Delivery * pDelivery ) = 0;
    virtual void DeliveryLockedNotify ( Delivery * pDelivery ) = 0;
    virtual void TunerUnavailableNotify ( ) = 0;
    virtual void TunerAvailableNotify ( ) = 0;
    virtual void ServiceStartPlayingNotify ( ServiceInterface* pService ) = 0;
    virtual void ServiceStartSections ( ServiceInterface* pService ) = 0;
    virtual void ServiceStopNotify ( ) = 0;
    virtual void ServiceStartFinishedNotify ( ) = 0;
    virtual void ServiceStopFinishedNotify ( ) = 0;
    virtual void IncompatibleServicePlayFailed ( ) = 0;
    virtual void PESScramblingControlNotify ( unsigned int unPESScramblingControl ) = 0;
    virtual void PlayingServiceIndexChangedNotify ( int nServiceIndex ) = 0;
	virtual void PlayingServiceVideoSourceChangedNotify ( ) = 0;
	virtual void PlayingServiceScrambledNotify ( unsigned int unScrambled ) = 0;
};

#endif /* DATABASECONTAINERPLAYERNOTIFY_H_ */
