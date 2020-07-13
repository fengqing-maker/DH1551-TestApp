#ifndef AC3FILEFILTERSPEC_H_
#define AC3FILEFILTERSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class Ac3FileFilterSpec : public FileFilterSpecInterface
{
public:
	Ac3FileFilterSpec ( );
	virtual ~Ac3FileFilterSpec ( );

public:

	unsigned int IsBelongToThis ( FileManagementComponent * pFileManagementComponent );

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType ( void );

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );
private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );
};

#endif /* AC3FILEFILTERSPEC_H_ */