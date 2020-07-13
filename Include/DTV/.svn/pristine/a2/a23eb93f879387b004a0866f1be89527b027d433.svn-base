/*
 * TunerInterface.h
 *
 *  Created on: 2015-5-11
 *      Author: HXC
 */

#ifndef TUNERINTERFACE_H_
#define TUNERINTERFACE_H_

#include "TunerLockingNotify.h"
#include "AntennaInterface.h"
#include "Delivery.h"
#include "adi_diseqc.h"


class TunerInterface
{

public:

    TunerInterface ( );
    virtual ~TunerInterface ( );

public:

    virtual unsigned int LockingDelivery ( Delivery * pDelivery, AntennaInterface * pAntennaInterface ) = 0;

    virtual float GetSignalStrength ( ) = 0;
    virtual float GetSignalQuality ( ) = 0;
    virtual float GetSignalBER ( ) = 0;
    virtual float GetSignalMER ( ) = 0;

    virtual unsigned int AddTunerLockingNotify ( TunerLockingNotify * pTunerLockingNotify ) = 0;
    virtual unsigned int RemoveTunerLockingNotify ( TunerLockingNotify * pTunerLockingNotify ) = 0;

    virtual unsigned int SetDiSEqC12RotateTimes ( ADIRotateDirection_E eDirection, unsigned char ucTime ) = 0;
    virtual unsigned int SetDiSEqC12RotateCycles ( ADIRotateDirection_E eDirection, unsigned char ucCycles ) = 0;
    virtual unsigned int DiSEqC12StorePosition ( unsigned char ucPosition ) = 0;
    virtual unsigned int DiSEqC12GotoPosition ( unsigned char ucPosition ) = 0;
    virtual unsigned int DiSEqC12ResetPosition ( ) = 0;
    virtual unsigned int DiSEqC12RotateWithoutStop ( unsigned char ucDirection ) = 0;
    virtual unsigned int DiSEqC12RotateStop ( ) = 0;
    virtual unsigned int DiSEqC12DisableLimit ( ) = 0;
    virtual unsigned int DiSEqC12SetLimit ( unsigned char ucDirection ) = 0;
    virtual unsigned int DiSEqC12AdjustTAB ( unsigned char ucPosition ) = 0;
    virtual unsigned int DiSEqC12GotoSTABPosition ( double dlAngle ) = 0;
    virtual unsigned int DiSEqC12GetAntennaAngle ( double dlSatLongitude, double dlMyLongitude, double dlMyLatitude, double *pdlAngle ) = 0;
    virtual unsigned int DiSEqC12TurnSateWithUsals ( const ADISatLocationInfo_S *psSatLocationInfo ) = 0;

    virtual unsigned int SetLocalLongituedLatitude ( double ldLongitude, double ldLatitude ) = 0;

    virtual void SetSCRUserBand ( unsigned int m_unUserBandNumber, unsigned int m_unUserBandCenterFreq ) = 0;

    virtual unsigned int GetPLPInfo ( unsigned char aucPLPInfo [ 256 ], unsigned int & unAvailableSize ) = 0;
};

#endif /* TUNERINTERFACE_H_ */
