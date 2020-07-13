#ifndef PVRFILESIZECOMPARESPEC_H_
#define PVRFILESIZECOMPARESPEC_H_

#include "FileSortCompareSpec.h"
#include "FileManagementComponent.h"
#include "FileSortCompareSpecType.h"

class PVRFileSizeCompareSpec : public FileSortCompareSpec
{
public:
	PVRFileSizeCompareSpec();
	virtual ~PVRFileSizeCompareSpec();

public:
	int CompareFile(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType);

	FileCompareSpecType GetType(void);
private:

	unsigned int CheckingRecordFilePath(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType, int & nComppareResult);

};

#endif /* PVRFILESIZECOMPARESPEC_H_ */