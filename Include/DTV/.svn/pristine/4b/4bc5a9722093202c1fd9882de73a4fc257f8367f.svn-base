/*
 * BouquetInterface.h
 *
 *  Created on: 2015-4-16
 *      Author: timothy.liao
 */

#ifndef BOUQUETINTERFACE_H_
#define BOUQUETINTERFACE_H_

#include "string.h"

class BouquetInterface
{

public:

    BouquetInterface ( );
    virtual ~BouquetInterface ( );

public:

    virtual unsigned short GetBouquetID ( ) = 0;
    virtual unsigned int GetBouquetName ( char acName [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetServiceCount ( ) = 0;
    virtual unsigned int GetService ( unsigned int unIndex, unsigned short &usOriginalNetworkID, unsigned short &usTSID, unsigned short &usServiceID ) = 0;
    virtual unsigned int GetService ( unsigned int unIndex, unsigned short &usOriginalNetworkID, unsigned short &usTSID, unsigned short &usServiceID, unsigned short & usAttribute ) = 0;
    virtual unsigned int GetServiceAttribute ( unsigned short usOriginalNetworkID, unsigned short usTSID, unsigned short usServiceID, unsigned short & usAttribute ) = 0;

    virtual unsigned int GetSubBouquetCount ( ) = 0;
    virtual BouquetInterface * GetSubBouquet ( unsigned int unIndex ) = 0;
    virtual BouquetInterface * GetSubBouquet ( unsigned short usBouquetID ) = 0;

    virtual unsigned int IsServiceInBouquet ( unsigned short usOriginalNetworkID, unsigned short usTSID, unsigned short usServiceID ) = 0;

};

#endif /* BOUQUETINTERFACE_H_ */
