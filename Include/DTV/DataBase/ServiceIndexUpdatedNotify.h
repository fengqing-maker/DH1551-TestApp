/*
 * ServiceIndexUpdatedNotify.h
 *
 *  Created on: 2015-11-20
 *      Author: HXC
 */

#ifndef SERVICEINDEXUPDATEDNOTIFY_H_
#define SERVICEINDEXUPDATEDNOTIFY_H_

class ServiceIndexUpdatedNotify
{

public:

	ServiceIndexUpdatedNotify( );
	virtual ~ServiceIndexUpdatedNotify( );

public:

    virtual void ServiceIndexUpdated ( unsigned short usOriNetowrkID, unsigned short usTSID, unsigned short usServiceID, unsigned int unOriIndex, int nNewIndex ) = 0;

};

#endif /* SERVICEINDEXUPDATEDNOTIFY_H_ */
