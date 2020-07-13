/*
 * TerrestrialDelivery.h
 *
 *  Created on: 2015-3-15
 *      Author: Demo
 */

#ifndef TERRESTRIALDELIVERY_H_
#define TERRESTRIALDELIVERY_H_

#include "Delivery.h"
#include "TerrestrialModulationMode.h"

class TerrestrialDelivery : public Delivery
{

public:

    TerrestrialDelivery ( );
    virtual ~TerrestrialDelivery ( );

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
    unsigned int m_unBandwidth;
    unsigned short m_unT2Flag; // 0:T, 1:T2
    unsigned short m_usPLD;
    TerrestrialModulationMode m_eTerrestrialModulationMode;

};

#endif /* TERRESTRIALDELIVERY_H_ */
