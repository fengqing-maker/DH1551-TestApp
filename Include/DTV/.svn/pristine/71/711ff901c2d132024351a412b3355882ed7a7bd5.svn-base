
#ifndef _COMPOSITEANDFILEFILTERSPEC000_H
#define _COMPOSITEANDFILEFILTERSPEC000_H

#include "CompositeFileFilterSpec.h"


class CompositeAndFileFilterSpec : public CompositeFileFilterSpec
{
public:
	CompositeAndFileFilterSpec ( );

	virtual ~CompositeAndFileFilterSpec ( );

public:
	unsigned int IsBelongToThis ( FileManagementComponent * pFileManagementComponent );

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType ( void );

	FileFilterSpecInterface * ConstructFileFilterSpec ( void );


};

#endif