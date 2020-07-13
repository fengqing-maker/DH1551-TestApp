/*
 * TunerLockingNotify.h
 *
 *  Created on: 2015-5-11
 *      Author: HXC
 */

#ifndef TUNERLOCKINGNOTIFY_H_
#define TUNERLOCKINGNOTIFY_H_

#include "Delivery.h"
#include "adi_tuner.h"

class TunerLockingNotify
{

public:

    TunerLockingNotify ( );
    virtual ~TunerLockingNotify ( );

public:

    virtual void LockingNotify ( Delivery  *pDelivery ) = 0;
    virtual void LockedNotify ( Delivery  *pDelivery ) = 0;

    virtual void BlindScanningNotify ( unsigned int unCurrentFreq );
    virtual void BlindScannSuccessNotify ( ADITunerBlindScanTPInfo_S asBlindScanTPInfo [ ], unsigned int unCount );
};

#endif /* TUNERLOCKINGNOTIFY_H_ */
