
#ifndef FILELISTFILTERCONTAINER_H_
#define FILELISTFILTERCONTAINER_H_

#include "APLock.h"
#include "FileListFilterContainerInterface.h"


class FileListFilterContainer :public FileListFilterContainerInterface
{
public:
	FileListFilterContainer ( unsigned int unIsUnicodeFlag );
	virtual ~FileListFilterContainer();

public:

	unsigned int CreateFileManagementComponent(FileFilterSpecInterface *pFileFilterSpecInterface, FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType);

	unsigned int DestoryFileManagementComponent(void);

	unsigned int ClearFileManagementComponent(FileManagementComponent *intputFileManagementComponent);

	unsigned int ClearFileManagementComponent(void);

	unsigned int SetFileFilterSpec ( FileFilterSpecInterface *pFileFilterSpecInterface );

	unsigned int SetFileSortCompareSpec(FileSortCompareSpec *pFileSortCompareSpec, unsigned int unSortType);

	unsigned int ChanageFileSortByFileContainer(void);

	FileManagementComponent *GetFileManagementComponentNode(char inputcurrentNoteName[], int inputcurrentNoteNameLen);

	FileManagementComponent *GetFileManagementComponentByIndex(int nComponentIndex);

	FileManagementComponent *GetFileManagementComponentByIndex(FileManagementComponent * inputFileManagementComponentNode, int nComponentIndex);

	unsigned int SortFileManagementComponent( void );

	unsigned int UpdateFileFileManagementComponent ( FileManagementComponent *intputFileManagementComponent );

	unsigned int updateNotify(FileManagementComponent *intputFileManagementComponent);

	unsigned int updateNotify(FileManagementComponent *intputFileManagementComponent, unsigned int unErgodicFlag);

	void SetDeviceId(int  nDeviceId);

	int  GetDeviceId(void);

	void SetAlreadyMountStutas(bool bAlreadyMount);

	bool GetAlreadyMountStutas(void);

	FileSortCompareSpec *GetFileSortCompareSpec(void);

	unsigned int GetFileSortType(void);

	unsigned int GetCurChildCount(unsigned int & unChildCount);

	unsigned int GetCurFileType(int & nFileType);

	unsigned int GetFileType(int & nFileType, int nIndex);

	unsigned int GetCurFileNodeName(char aucFileNodeName[], unsigned int unFileNodeNameLength);

	unsigned int GetFileNodeName(char aucFileNodeName[], unsigned int unFileNodeNameLength, int nIndex);

	unsigned int GetFileName(char aucFileName[], unsigned int unFileNameLength, int nIndex);

	unsigned int GetADIFSFile(ADIFSFileStat_S * ouputADIFSFile, int nIndex);

	FileSortCompareSpec *newFileSortCompareSpec(FileCompareSpecType sSpecType);

private:

	int  m_nDeviceId;

	bool m_bAlreadyMount;

	APLock m_APLock;

	unsigned int m_unIsUnicodeFlag;

	FileFilterSpecInterface *m_pFileFilterSpecInterface;

	FileSortCompareSpec *m_pFileSortCompareSpec;

	unsigned int m_unSortType;

	FileManagementComponent * m_pFileManagementComponentList;
};

#endif