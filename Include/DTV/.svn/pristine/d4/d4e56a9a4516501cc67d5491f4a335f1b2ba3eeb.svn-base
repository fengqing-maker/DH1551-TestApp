#ifndef FILEFILTEGLOBALRSPEC_H_
#define FILEFILTEGLOBALRSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class FileFilterGlobalSpec : public FileFilterSpecInterface
{
public:
	FileFilterGlobalSpec();
	virtual ~FileFilterGlobalSpec();

public:

	unsigned int IsBelongToThis(FileManagementComponent * pFileManagementComponent);

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType(void);

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );

private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );
};

#endif /* PVRFILEFILTEGLOBALRSPEC_H_ */