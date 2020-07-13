#ifndef MKVFILEFILTERSPEC_H_
#define MKVFILEFILTERSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class MkvFileFilterSpec : public FileFilterSpecInterface
{
public:
	MkvFileFilterSpec ( );
	virtual ~MkvFileFilterSpec ( );

public:

	unsigned int IsBelongToThis ( FileManagementComponent * pFileManagementComponent );

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType ( void );

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );
private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );
};

#endif /* MKVFILEFILTERSPEC_H_ */