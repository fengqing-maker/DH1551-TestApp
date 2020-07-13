/*
 * Delivery.h
 *
 *  Created on: 2015-3-15
 *      Author: Demo
 */

#ifndef DELIVERY_H_
#define DELIVERY_H_

#include "DeliveryType.h"

class Delivery
{

public:

    Delivery ( );
    virtual ~Delivery ( );

public:

    virtual unsigned int IsSimilarDelivery ( Delivery * pDelivery );
    virtual Delivery * ConstructSimilarDelivery ( ) = 0;
    virtual DeliveryType GetDeliveryType ( ) = 0;
    virtual int CompareFrequency ( Delivery * pDelivery ) = 0;
    virtual int CompareFrequency ( unsigned int unFrequency ) = 0;

    virtual void DebugPrint ( ) = 0;
};

#endif /* DELIVERY_H_ */
