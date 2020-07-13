#ifndef M2TSFILEFILTERSPEC_H_
#define M2TSFILEFILTERSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class M2tsFileFilterSpec : public FileFilterSpecInterface
{
public:
	M2tsFileFilterSpec ( );
	virtual ~M2tsFileFilterSpec ( );

public:

	unsigned int IsBelongToThis ( FileManagementComponent * pFileManagementComponent );

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType ( void );

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );
private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );
};

#endif /* AACFILEFILTERSPEC_H_ */