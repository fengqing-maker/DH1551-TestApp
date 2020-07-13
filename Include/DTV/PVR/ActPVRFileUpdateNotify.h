/*
 * ActPVRFileUpdateNotify.h
 *
 *  Created on: 2015-6-23
 *      Author: cl
 */

#ifndef ACTPVRFILEUPDATENOTIFY_H_
#define ACTPVRFILEUPDATENOTIFY_H_

#include "adi_player.h"
#include "KeyInterface.h"
#include "ADI_CA_Comon.h"
#include "ADITime.h"
#include "PlayError.h"

class ActPVRFileUpdateNotify
{
public:
    ActPVRFileUpdateNotify ( );
    virtual ~ActPVRFileUpdateNotify ( );

    virtual unsigned int UnPlugNotify ( ADIPLAYERType_E enADIPLAYERType ) = 0;
    virtual unsigned int PFUpdateNotify ( ADIPLAYERType_E enADIPLAYERType ) = 0;
    virtual unsigned int EOFNotify ( ADIPLAYERType_E enADIPLAYERType ) = 0;
    virtual unsigned int BOFNotify ( ADIPLAYERType_E enADIPLAYERType ) = 0;
    virtual unsigned int LockNotify ( ADIPLAYERType_E enADIPLAYERType, KeyInterface * pKey, unsigned int unFileIndex ) = 0;
    virtual unsigned int PlayBackWorkingNotify ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int TimeShiftWorkingNotify ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int ShowOSDNotify ( ADIAttribCovert_S * pADIAttribCovert, ADITime * pTime ) = 0;
    virtual unsigned int ClearOSDNotify ( ) = 0;
    virtual unsigned int SpeedLimitNotify ( unsigned char ucMaxForwardSpeed ) = 0;
    virtual unsigned int SeekLimitNotify ( ) = 0;
    virtual void FileExpiredNotify ( ADIPLAYERType_E ePVRPlayerType, unsigned int unFileIndex ) = 0;
    virtual void NoAccessNotify(ADIPLAYERType_E enADIPLAYERType) = 0;
	virtual void ShowPlayBackResultNotify(ADIPLAYERType_E enADIPLAYERType, PlayError enPlayError) = 0;
};

#endif /* ACTPVRFILEUPDATENOTIFY_H_ */
