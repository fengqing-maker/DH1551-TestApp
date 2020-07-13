#ifndef BOUQUETIDCOMPARESPEC_H_
#define BOUQUETIDCOMPARESPEC_H_

#include "BouquetInterface.h"
#include "ArchiveInterface.h"
#include "BouquetCompareSpec.h"
#include "BouquetCompareSpecType.h"

class BouquetIDCompareSpec : public BouquetCompareSpec
{

public:

	BouquetIDCompareSpec();
	virtual ~BouquetIDCompareSpec();

public:

	int CompareServices( BouquetInterface * pFirstBouquetInterface, BouquetInterface * pSecondBouquetInterface );

	BouquetCompareSpecType GetType( void );

	unsigned int GetSortName( char acNameBuf[ ], unsigned int unBufLen );

	unsigned int Save( ArchiveInterface & inputArchiveInterface );

	BouquetCompareSpec * CopyConstructBouquetCompareSpec( void );

};

#endif /* BOUQUETIDCOMPARESPEC_H_ */