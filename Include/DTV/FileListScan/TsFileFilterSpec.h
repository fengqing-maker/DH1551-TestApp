#ifndef TSFILEFILTERSPEC_H_
#define TSFILEFILTERSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class TsFileFilterSpec : public FileFilterSpecInterface
{
public:
	TsFileFilterSpec ( );
	virtual ~TsFileFilterSpec ( );

public:

	unsigned int IsBelongToThis ( FileManagementComponent * pFileManagementComponent );

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType ( void );

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );
private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );
};

#endif /* TSFILEFILTERSPEC_H_ */