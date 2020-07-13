/*
 * SignalIndicatorInterface.h
 *
 *  Created on: 2015-7-15
 *      Author: HXC
 */

#ifndef SIGNALINDICATORINTERFACE_H_
#define SIGNALINDICATORINTERFACE_H_

class SignalIndicatorInterface
{

public:

	SignalIndicatorInterface( );
	virtual ~SignalIndicatorInterface( );

public:

    virtual void InputKeyGrow ( unsigned int unKeyCode ) = 0;

    virtual void MailLedOn ( ) = 0;
    virtual void MailLedOff ( ) = 0;

    virtual void StandbyLedOn ( ) = 0;
    virtual void StandbyLedOff ( ) = 0;

    virtual void SingalLedOn ( ) = 0;
    virtual void SingalLedOff ( ) = 0;

    virtual void RadioLedOn ( ) = 0;
    virtual void RadioLedOff ( ) = 0;

    virtual void Quar7SDD ( unsigned char aucData[], unsigned int unDataLen ) = 0;

	virtual void Standby ( unsigned int unIsShowTime ) = 0;
	virtual void Active ( ) = 0;

    virtual void LightRedGreenLed ( unsigned int unRedLedStatus, unsigned int unGreenLedStatus ) = 0; // 0, off; 1, on; 2, blink.

    virtual void PVRPlayOn ( ) = 0;
    virtual void PVRPlayOff ( ) = 0;
    
    virtual void RecordOn ( ) = 0;
    virtual void RecrodOff ( ) = 0;

    virtual void MediaOn ( unsigned int unPlayMusic ) = 0;
    virtual void MediaOff ( ) = 0;
};

#endif /* SIGNALINDICATORINTERFACE_H_ */
