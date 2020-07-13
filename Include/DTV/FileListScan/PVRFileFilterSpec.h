#ifndef PVRFILEFILTERSPEC_H_
#define PVRFILEFILTERSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "RecInfoFileFilterSpec.h"

class PVRFileFilterSpec : public FileFilterSpecInterface
{
public:
	PVRFileFilterSpec(char aucFileDir[], int nFileDirLength);
	virtual ~PVRFileFilterSpec();

public:

	unsigned int IsBelongToThis(FileManagementComponent * pFileManagementComponent);

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType(void);

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );
private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );

private:

	char m_aucFileDir[MAX_FILE_NAME_LEN];
	int  m_nFileDirLength;

};

#endif /* PVRFILEFILTERSPEC_H_ */