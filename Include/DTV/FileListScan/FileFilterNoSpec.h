#ifndef FILEFILTERNOSPEC_H_
#define FILEFILTERNOSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class FileFilterNoSpec : public FileFilterSpecInterface
{
public:
	FileFilterNoSpec();
	virtual ~FileFilterNoSpec();

public:

	unsigned int IsBelongToThis(FileManagementComponent * pFileManagementComponent);

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType(void);

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );

};

#endif /* FILEFILTERNOSPEC_H_ */