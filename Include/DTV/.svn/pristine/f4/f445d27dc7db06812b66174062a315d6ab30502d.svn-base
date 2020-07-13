/*
 * ArchiveInterface.h
 *
 *  Created on: 2015-5-6
 *      Author: Demo
 */

#ifndef ARCHIVEINTERFACE_H_
#define ARCHIVEINTERFACE_H_

//#include "Storage.h"

class ArchiveInterface
{

public:

	ArchiveInterface( );
	virtual ~ArchiveInterface( );

public:

    virtual unsigned int SeekPos ( unsigned int unPos ) = 0;

    virtual void ClearAll ( ) = 0;

	virtual unsigned int Save( char cValue ) = 0;
	virtual unsigned int Save( unsigned char ucValue ) = 0;
	virtual unsigned int Save( short sValue ) = 0;
	virtual unsigned int Save( unsigned short sValue ) = 0;
	virtual unsigned int Save( int nValue ) = 0;
	virtual unsigned int Save( unsigned int unValue ) = 0;
	virtual unsigned int Save( long long llValue ) = 0;
	virtual unsigned int Save( unsigned long long ullValue ) = 0;
	virtual unsigned int Save( unsigned char aucValue[ ], unsigned int unLen ) = 0;

	virtual unsigned int Load( char & cValue ) = 0;
	virtual unsigned int Load( unsigned char & unValue ) = 0;
	virtual unsigned int Load( short & sValue ) = 0;
	virtual unsigned int Load( unsigned short & sValue ) = 0;
	virtual unsigned int Load( int & nValue ) = 0;
	virtual unsigned int Load( unsigned int & unValue ) = 0;
	virtual unsigned int Load( long long & llValue ) = 0;
	virtual unsigned int Load( unsigned long long & ullValue ) = 0;
	virtual unsigned int Load( unsigned char aucValue[ ], unsigned int unLen ) = 0;

};

#endif /* ARCHIVEINTERFACE_H_ */
