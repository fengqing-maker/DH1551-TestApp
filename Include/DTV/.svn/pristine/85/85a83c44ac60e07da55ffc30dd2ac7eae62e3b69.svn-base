#ifndef	RECINFOFILEFILTERSPEC_H_
#define RECINFOFILEFILTERSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListScanPublicType.h"

class RecInfoFileFilterSpec : public FileFilterSpecInterface
{
public:
	RecInfoFileFilterSpec(char aucFileDir[], int nFileDirLength);
	RecInfoFileFilterSpec(char aucFileDir[], int nFileDirLength, unsigned int unExcludeRecordingFile);
	virtual ~RecInfoFileFilterSpec();

public:

	unsigned int IsBelongToThis(FileManagementComponent * pFileManagementComponent);

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType(void);

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );
private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );

	unsigned int IncludeRecordingFile ( FileManagementComponent * pFileManagementComponent );
private:
	char m_aucFileDir[MAX_FILE_NAME_LEN];
	int  m_nFileDirLength;
	unsigned int m_unExcludeRecordingFile;
};

#endif /* RECINFOFILEFILTERSPEC_H_ */