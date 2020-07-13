/*
 * ServicesDataBasePlayerNotify.h
 *
 *  Created on: 2015-5-4
 *      Author: Demo
 */

#ifndef SERVICESDATABASEPLAYERNOTIFY_H_
#define SERVICESDATABASEPLAYERNOTIFY_H_

class ServicesDataBasePlayerNotify
{

public:

    ServicesDataBasePlayerNotify ( );
    virtual ~ServicesDataBasePlayerNotify ( );

public:

    virtual void DeliveryLockingNotify ( ) = 0;
    virtual void DeliveryLockedNotify ( ) = 0;
    virtual void TunerUnavailableNotify ( ) = 0;
    virtual void TunerAvailableNotify ( ) = 0;

    virtual void PMTServiceInfoComplete ( ) = 0;
    virtual void GettingPMTServiceInfoTimeout ( ) = 0;
    virtual void ApplicationInfoComplete ( ) = 0;

    virtual void IncompatibleServicePlayFailed ( ) = 0;
    virtual void ServicePlaySucceed ( ) = 0;

    virtual void NITVersionChanged ( unsigned short usNetworkID, unsigned char ucVersion ) = 0;
    virtual void ServicesAttributesChanged ( ) = 0;

    virtual void PlayerSettingCorrupted ( ) = 0;

    virtual void NetworkDataUpdated ( ) = 0;
    virtual void NetworkNameUpdated ( char acNetworkName [ ], unsigned int unLength ) = 0;
    virtual void PlayingServiceIndexChangedNotify ( int nServiceIndex ) = 0;
    virtual void PlayingServiceWasDeleted ( ) = 0;

    virtual void PlayingServiceAvailableNotify ( ) = 0;
    virtual void PlayingServiceUnavailableNotify ( ) = 0; //Ç°¶ËÍ£²¥
	virtual void PlayingServiceVideoSourceChangedNotify ( ) = 0;
	virtual void PlayingServiceScrambledNotify ( unsigned int unScrambled ) = 0;
};

#endif /* SERVICESDATABASEPLAYERINTERFACE_H_ */
