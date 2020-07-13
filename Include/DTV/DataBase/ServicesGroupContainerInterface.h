/*
 * ServicesGroupContainerInterface.h
 *
 *  Created on: 2015-5-4
 *      Author: Demo
 */

#ifndef SERVICESGROUPCONTAINERINTERFACE_H_
#define SERVICESGROUPCONTAINERINTERFACE_H_

#include "ServicesGroupFilterSpec.h"
#include "ServicesCompareSpec.h"
#include "ServicesGroupInterface.h"
#include "BouquetCompareSpec.h"

class ServicesGroupContainerInterface
{

public:

    ServicesGroupContainerInterface ( );
    virtual ~ServicesGroupContainerInterface ( );

public:

	virtual ServicesGroupInterface * CreateServicesGroup ( ServicesGroupFilterSpec * pServicesGroupFilterSpec, ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending ) = 0;
    virtual ServicesGroupInterface * CreateFAVServicesGroup ( ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending ) = 0;
    virtual ServicesGroupInterface * CreateFAVServicesGroupByServicesName ( ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending ) = 0;
    virtual ServicesGroupInterface * CreateFAVServicesGroupByServicesNameORID ( ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending ) = 0;
    virtual unsigned int CreateBATServicesGroup ( BouquetCompareSpec *pBouquetCompareSpec, unsigned int unSortType, ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending ) = 0;
	
    virtual unsigned int CreateAllSatelliteServicesGroup ( ) = 0;

	virtual unsigned int FindServicesGroup( char acGroupName[ ], unsigned int unNameLen ) = 0;
	virtual unsigned int DeleteServicesGroup( char acGroupName[ ], unsigned int unNameLen ) = 0;

    virtual unsigned int ChangeServicesGroupSortType ( char acGroupName [ ], unsigned int unNameLen, ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending ) = 0;
	virtual unsigned int ChangeServicesGroupSortType ( unsigned int unIndex, ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending ) = 0;

    virtual unsigned int GetServicesGroupSortType ( unsigned int unIndex, ServicesCompareSpec *& pServicesCompareSpec, unsigned int & unAscending ) = 0;

};

#endif /* SERVICESGROUPCONTAINERINTERFACE_H_ */
