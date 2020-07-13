/*
 * SatelliteDelivery.h
 *
 *  Created on: 2015-3-15
 *      Author: Demo
 */

#ifndef SATELLITEDELIVERY_H_
#define SATELLITEDELIVERY_H_

#include "Delivery.h"
#include "SatelliteModulationMode.h"

class SatelliteDelivery : public Delivery
{

public:

    SatelliteDelivery ( );
    virtual ~SatelliteDelivery ( );

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
    unsigned int m_unPolarization;
    unsigned short m_usOrbitalPosition;
    unsigned char m_ucWestEastFlag;
    SatelliteModulationMode m_eSatelliteModulationMode;

};

#endif /* SATELLITEDELIVERY_H_ */
