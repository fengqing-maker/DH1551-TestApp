#ifndef FILESORTCOMPARESPEC_H_
#define FILESORTCOMPARESPEC_H_

#include "FileManagementComponent.h"
#include "FileSortCompareSpecType.h"

class FileSortCompareSpec
{
public:
	FileSortCompareSpec();
	virtual ~FileSortCompareSpec();

public:
	virtual int CompareFile(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType) = 0;

	virtual FileCompareSpecType GetType(void) = 0;
};

#endif /* FILESORTCOMPARESPEC_H_ */

