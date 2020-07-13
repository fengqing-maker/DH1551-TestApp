#ifndef FILEFILTEINCLUDEFILESPEC_H_
#define FILEFILTEINCLUDEFILESPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class FileFilterIncludePhotoSpec : public FileFilterSpecInterface
{
public:
	FileFilterIncludePhotoSpec ( );
	virtual ~FileFilterIncludePhotoSpec ( );

public:

	unsigned int IsBelongToThis(FileManagementComponent * pFileManagementComponent);

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType(void);

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );

};

#endif /* PVRFILEFILTEGLOBALRSPEC_H_ */