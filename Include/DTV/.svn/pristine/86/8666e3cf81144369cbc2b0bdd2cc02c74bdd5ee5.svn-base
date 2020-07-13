/*
 * BouquetNameSpec.h
 *
 *  Created on: 2015-7-9
 *      Author: HXC
 */

#ifndef BOUQUETNAMESPEC_H_
#define BOUQUETNAMESPEC_H_

#include "BouquetMergeSpec.h"

class BouquetNameSpec : public BouquetMergeSpec
{

public:

    BouquetNameSpec ( char acBouquetName [ ], unsigned int unNameLen );
    virtual ~BouquetNameSpec ( );

public:

    unsigned int IsAcceptableBouquetInterface ( BouquetInterface * pBouquetInterface );
    BouquetMergeSpec* ConstructSimilarBouquetMergeSpec ( );

    void * operator new ( unsigned int unSize );
    void operator delete ( void * p );

private:

    unsigned int MatchWithAsterisk ( char acString [ ], unsigned int unStrlen, char acPattern [ ], unsigned int unPatternLen );

private:

    char m_acStr [ 64 ];

};

#endif /* BOUQUETNAMESPEC_H_ */
