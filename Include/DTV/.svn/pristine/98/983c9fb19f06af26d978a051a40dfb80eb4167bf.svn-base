

#ifndef FILEFILTERSPECINTERFACE_H_
#define FILEFILTERSPECINTERFACE_H_

#include <string.h>
#include "FileManagementComponent.h"
#include "FileListFilterSpecType.h"


class FileFilterSpecInterface
{
public:
	FileFilterSpecInterface();
	virtual ~FileFilterSpecInterface();

public:
	virtual unsigned int IsBelongToThis(FileManagementComponent * pFileManagementComponent) = 0;

	virtual FileType GetFileType ( FileManagementComponent * pFileManagementComponent ) = 0;
	
	virtual FileListFilterSpecType GetFileFilterSpecType(void) = 0;

	virtual FileFilterSpecInterface * ConstructFileFilterSpec ( void ) = 0;

	
};

#endif /* FILEFILTERSPECINTERFACE_H_ */
