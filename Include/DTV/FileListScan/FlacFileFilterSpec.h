#ifndef FLACFILEFILTERSPEC_H_
#define FLACFILEFILTERSPEC_H_

#include "FileManagementComponent.h"
#include "FileFilterSpecInterface.h"
#include "FileListFilterSpecType.h"

class FlacFileFilterSpec : public FileFilterSpecInterface
{
public:
	FlacFileFilterSpec ( );
	virtual ~FlacFileFilterSpec ( );

public:

	unsigned int IsBelongToThis ( FileManagementComponent * pFileManagementComponent );
	
	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType ( void );

	FileFilterSpecInterface *ConstructFileFilterSpec ( void );
private:

	unsigned int IsBelongToThisA ( FileManagementComponent * pFileManagementComponent );

	unsigned int IsBelongToThisW ( FileManagementComponent * pFileManagementComponent );
};

#endif /* FLACFILEFILTERSPEC_H_ */