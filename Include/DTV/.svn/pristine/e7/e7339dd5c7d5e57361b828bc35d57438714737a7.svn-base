#ifndef PVRFILETIMECOMPARESPEC_H_
#define PVRFILETIMECOMPARESPEC_H_

#include "FileSortCompareSpec.h"
#include "FileManagementComponent.h"
#include "FileSortCompareSpecType.h"

class PVRFileTimeCompareSpec : public FileSortCompareSpec
{
public:
	PVRFileTimeCompareSpec();
	virtual ~PVRFileTimeCompareSpec();

public:
	int CompareFile(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType);

	FileCompareSpecType GetType(void);
private:

	unsigned int CheckingRecordFilePath(FileManagementComponent * pFirstFileManagementComponent, FileManagementComponent * pSecondFileManagementComponent, unsigned int unSortType, int & nComppareResult);

};

#endif /* PVRFILETIMECOMPARESPEC_H_ */