#ifndef PVRFILENAMECOMPARESPEC_H_
#define PVRFILENAMECOMPARESPEC_H_

#include "FileSortCompareSpec.h"
#include "FileManagementComponent.h"
#include "FileSortCompareSpecType.h"

class PVRFileNameCompareSpec : public FileSortCompareSpec
{
public:
	PVRFileNameCompareSpec();
	virtual ~PVRFileNameCompareSpec();

public:
	int CompareFile(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType);

	FileCompareSpecType GetType(void);

private:

	unsigned int CheckingRecordFilePath(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType,int & nComppareResult);

};

#endif /* PVRFILENAMECOMPARESPEC_H_ */