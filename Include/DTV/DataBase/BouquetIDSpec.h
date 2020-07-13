/*
 * BouquetIDSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef BOUQUETIDSPEC_H_
#define BOUQUETIDSPEC_H_

#include "BouquetMergeSpec.h"

class BouquetIDSpec : public BouquetMergeSpec
{

public:

    BouquetIDSpec ( unsigned short usBouquetID );
    virtual ~BouquetIDSpec ( );

public:

    unsigned int IsAcceptableBouquetInterface ( BouquetInterface * pBouquetInterface );
    BouquetMergeSpec* ConstructSimilarBouquetMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned short m_usBouquetID;

};

#endif /* BOUQUETIDSPEC_H_ */
