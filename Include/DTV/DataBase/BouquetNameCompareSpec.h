#ifndef BOUQUETNAMECOMPARESPEC_H_
#define BOUQUETNAMECOMPARESPEC_H_

#include "BouquetInterface.h"
#include "ArchiveInterface.h"
#include "BouquetCompareSpec.h"
#include "BouquetCompareSpecType.h"

class BouquetNameCompareSpec : public BouquetCompareSpec
{

public:

	BouquetNameCompareSpec();
	virtual ~BouquetNameCompareSpec();

public:

	int CompareServices( BouquetInterface * pFirstBouquetInterface, BouquetInterface * pSecondBouquetInterface );

	BouquetCompareSpecType GetType( void );

	unsigned int GetSortName( char acNameBuf[ ], unsigned int unBufLen );

	unsigned int Save( ArchiveInterface & inputArchiveInterface );

	BouquetCompareSpec * CopyConstructBouquetCompareSpec( void );

};

#endif /* BouquetNameCompareSpec */