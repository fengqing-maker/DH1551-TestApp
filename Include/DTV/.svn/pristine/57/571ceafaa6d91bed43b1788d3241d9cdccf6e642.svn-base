/*
 * NVODReferenceServiceUpdateNotify.h
 *
 *  Created on: 2015-11-29
 *      Author: Demo
 */

#ifndef NVODREFERENCESERVICEUPDATENOTIFY_H_
#define NVODREFERENCESERVICEUPDATENOTIFY_H_

class NVODReferenceServiceUpdateNotify
{

public:	
	NVODReferenceServiceUpdateNotify( );
	virtual ~NVODReferenceServiceUpdateNotify( );

public:

	virtual void NVODReferenceServiceCountUpdateNotify ( ) = 0;
    virtual void NVODReferenceServiceContentUpdateNotify ( unsigned short usNVODReferenceServiceID ) = 0;

	virtual void NVODPlayerConflictNotify ( unsigned int unGroupIndex , unsigned int unServiceIndex ) = 0;

};

#endif /* NVODREFERENCESERVICEUPDATENOTIFY_H_ */
