
#ifndef _COMPOSITEFILEFILTERSPEC_H
#define _COMPOSITEFILEFILTERSPEC_H

#include <vector>
using std::vector;

#include "FileFilterSpecInterface.h"

class CompositeFileFilterSpec : public FileFilterSpecInterface
{
public:
	CompositeFileFilterSpec ( );
	virtual ~CompositeFileFilterSpec ( );

public:

	unsigned int AddFileFilterMergeSpec ( FileFilterSpecInterface * pFileFilterMergeSpec );
	unsigned int RemoveFileFilterMergeSpec ( FileFilterSpecInterface * pFileFilterMergeSpec );

	

protected:
	unsigned int GetFileFilterMergeSpecCount ( );
	FileFilterSpecInterface * GetFileFilterMergeSpec ( unsigned int unIndex );

private:

	void DeleteFileFilterMergeSpecList ( vector < FileFilterSpecInterface * > & inputFileFilterMergeSpecList );

private:

	vector < FileFilterSpecInterface * > m_FileFilterSpecList;

};

#endif