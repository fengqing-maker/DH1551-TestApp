/*
 * CompositeOrBouquetAddSpec.h
 *
 *  Created on: 2015-5-5
 *      Author: HXC
 */

#ifndef COMPOSITEORBOUQUETADDSPEC_H_
#define COMPOSITEORBOUQUETADDSPEC_H_

#include "CompositeBouquetAddSpec.h"

class CompositeOrBouquetAddSpec : public CompositeBouquetAddSpec
{

public:

    CompositeOrBouquetAddSpec ( );
    virtual ~CompositeOrBouquetAddSpec ( );

public:

    unsigned int IsAcceptableBouquetInterface ( BouquetInterface * pBouquetInterface );
    BouquetMergeSpec* ConstructSimilarBouquetMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

};

#endif /* COMPOSITEORBOUQUETADDSPEC_H_ */
