#ifndef COMPOSITEFILESORTCOMPARESPEC_H_
#define COMPOSITEFILESORTCOMPARESPEC_H_

#include "FileSortCompareSpec.h"
#include <vector>
using std::vector;

class CompositeFileSortCompareSpec : public FileSortCompareSpec
{

public:

	CompositeFileSortCompareSpec();
	virtual ~CompositeFileSortCompareSpec();

public:

	unsigned int AddFileSortCompareSpec( FileSortCompareSpec * pFileSortCompareSpec );
	unsigned int RemoveFileSortCompareSpec( FileSortCompareSpec * pFileSortCompareSpec );
    unsigned int GetFileSortCompareSpecCount ( );
    FileSortCompareSpec* GetFileSortCompareSpec ( unsigned int unIndex );
	
	int CompareFile(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType);
	FileCompareSpecType GetType(void);

private:

	void DeleteFileSortCompareSpecList(vector< FileSortCompareSpec * > & inputFileSortCompareSpecList);

private:
	vector < FileSortCompareSpec * > m_FileSortCompareSpecList;

};

#endif /* COMPOSITEFILESORTCOMPARESPEC_H_ */