/*
 * CableDelivery.h
 *
 *  Created on: 2015-3-15
 *      Author: Demo
 */

#ifndef CABLEDELIVERY_H_
#define CABLEDELIVERY_H_

#include "Delivery.h"
#include "CableModulationType.h"

class CableDelivery : public Delivery
{

public:

    CableDelivery ( );
    virtual ~CableDelivery ( );

public:

    unsigned int IsSimilarDelivery ( Delivery * pDelivery );
    Delivery * ConstructSimilarDelivery ( );
    int CompareFrequency ( Delivery * pDelivery );
    int CompareFrequency ( unsigned int unFrequency );

    static void * operator new ( unsigned int size );
    static void  operator delete ( void * p );

    void DebugPrint ( );

protected:

    DeliveryType GetDeliveryType ( );

public:

    unsigned int m_unFrequency;
    unsigned int m_unSymbolRate;
    CableModulationType m_eCableModulationType;

};

#endif /* CABLEDELIVERY_H_ */
