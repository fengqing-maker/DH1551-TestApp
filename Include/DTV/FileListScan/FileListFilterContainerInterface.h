#ifndef FILELISTFILTERCONTAINERINTERFACE_H_
#define FILELISTFILTERCONTAINERINTERFACE_H_

#include "FileSortCompareSpec.h"
#include "FileFilterSpecInterface.h"

class FileListFilterContainerInterface
{
public:
	FileListFilterContainerInterface ( );
	virtual ~FileListFilterContainerInterface ( );

public:

	virtual unsigned int CreateFileManagementComponent ( FileFilterSpecInterface *pFileFilterSpecInterface, FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType ) = 0;

	virtual unsigned int DestoryFileManagementComponent ( void ) = 0;

	virtual unsigned int ClearFileManagementComponent ( FileManagementComponent *intputFileManagementComponent ) = 0;

	virtual unsigned int ClearFileManagementComponent ( void ) = 0;

	virtual unsigned int SetFileFilterSpec ( FileFilterSpecInterface *pFileFilterSpecInterface ) = 0;

	virtual unsigned int SetFileSortCompareSpec ( FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType ) = 0;

	virtual unsigned int ChanageFileSortByFileContainer ( void ) = 0;

	virtual FileManagementComponent *GetFileManagementComponentNode ( char inputcurrentNoteName [ ], int inputcurrentNoteNameLen ) = 0;

	virtual FileManagementComponent *GetFileManagementComponentByIndex ( int nComponentIndex ) = 0;

	virtual FileManagementComponent *GetFileManagementComponentByIndex ( FileManagementComponent * inputFileManagementComponentNode, int nComponentIndex ) = 0;

	virtual unsigned int GetCurChildCount ( unsigned int & unChildCount ) = 0;

	virtual unsigned int GetCurFileType ( int & nFileType ) = 0;

	virtual unsigned int GetFileType ( int & nFileType, int nIndex ) = 0;

	virtual unsigned int GetCurFileNodeName ( char aucFileNodeName [ ], unsigned int unFileNodeNameLength ) = 0;

	virtual unsigned int GetFileNodeName ( char aucFileNodeName [ ], unsigned int unFileNodeNameLength, int nIndex ) = 0;

	virtual unsigned int GetFileName ( char aucFileName [ ], unsigned int unFileNameLength, int nIndex ) = 0;

	virtual unsigned int GetADIFSFile ( ADIFSFileStat_S * ouputADIFSFile, int nIndex ) = 0;

	virtual unsigned int UpdateFileFileManagementComponent ( FileManagementComponent *intputFileManagementComponent ) = 0;

	virtual unsigned int updateNotify ( FileManagementComponent *intputFileManagementComponent ) = 0;

	virtual unsigned int updateNotify ( FileManagementComponent *intputFileManagementComponent, unsigned int unErgodicFlag ) = 0;

	virtual unsigned int SortFileManagementComponent ( void ) = 0;

	virtual FileSortCompareSpec *GetFileSortCompareSpec ( void ) = 0;

	virtual unsigned int GetFileSortType ( void ) = 0;

	virtual FileSortCompareSpec *newFileSortCompareSpec ( FileCompareSpecType sSpecType ) = 0;
};


#endif //FILELISTFILTERCONTAINERINTERFACE_H_
