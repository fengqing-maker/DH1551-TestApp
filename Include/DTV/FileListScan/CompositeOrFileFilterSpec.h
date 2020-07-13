#ifndef _COMPOSITEORFILEFILTERSPEC000_H
#define _COMPOSITEORFILEFILTERSPEC000_H

#include "CompositeFileFilterSpec.h"


class CompositeOrFileFilterSpec : public CompositeFileFilterSpec
{
public:
	CompositeOrFileFilterSpec ( );

	virtual ~CompositeOrFileFilterSpec ( );

public:
	unsigned int IsBelongToThis ( FileManagementComponent * pFileManagementComponent );

	FileType GetFileType ( FileManagementComponent * pFileManagementComponent );

	FileListFilterSpecType GetFileFilterSpecType ( void );

	FileFilterSpecInterface * ConstructFileFilterSpec ( void );


};

#endif