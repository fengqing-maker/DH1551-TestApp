#ifndef FILEMANAGEMENTCOMPONENT_H_
#define FILEMANAGEMENTCOMPONENT_H_

#include "adi_fs.h"

class FileManagementComponent
{
public:
	FileManagementComponent();
	virtual ~FileManagementComponent();

public:

	virtual unsigned int GetFileType(int & nFileType) = 0;

	virtual unsigned int GetChildCount(unsigned int & unChildCount) = 0;

	virtual unsigned int GetFileNodeName(char aucFileNodeName[], unsigned int unFileNodeNameLength) = 0;

	virtual unsigned int SetFileNodeName(char aucFileNodeName[], unsigned int unFileNodeNameLength) = 0;

	virtual unsigned int SetFileName(char aucFileName[], unsigned int nFileNameLength) = 0;

	virtual unsigned int GetFileName(char aucFileName[], unsigned int unFileNameLength) = 0;

	virtual unsigned int GetADIFSFileStat(ADIFSFileStat_S * ouputADIFSFileStat) = 0;

	virtual unsigned int SetADIFSFileStat(ADIFSFileStat_S inputADIFSFileStat) = 0;

	virtual unsigned int SaveFileInformation(FileManagementComponent *inputFileManagementComponent) = 0;

	virtual unsigned int IsSimilarFileNodeName(char aucFileNodeName[], unsigned int unFileNodeNameLength) = 0;

	virtual unsigned int IsSimilarFileName ( char aucFileName [ ] , unsigned int unFileNameLength ) = 0;

	virtual unsigned int IsSimilarFileNameInCurFileNodeName ( char aucFileName [ ] , unsigned int unFileNameLength ) = 0;

	virtual int StringCompare ( char acFirstFileName [ ], char acSecondFileName [ ] ) = 0;

	virtual unsigned int GetStringUnicodeFlag ( unsigned int & unStingUnicodeFlag ) = 0;

};

#endif /* FILEMANAGEMENTCOMPONENT_H_ */
