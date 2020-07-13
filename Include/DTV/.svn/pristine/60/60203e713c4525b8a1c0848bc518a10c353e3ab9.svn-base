/*
 * UserDefineLCNFollowHeadendDefine.h
 *
 *  Created on: 2017-4-6
 *      Author: Timothy.Liao
 */

#ifndef USERDEFINELCNFOLLOWHEADENDDEFINE_H_
#define USERDEFINELCNFOLLOWHEADENDDEFINE_H_
#include "UserDefineLCNSpec.h"
#include "ServicesCompareSpec.h"

class UserDefineLCNFollowHeadendDefine : public UserDefineLCNSpec
{

public:

    UserDefineLCNFollowHeadendDefine ( unsigned short usLCNStart, ServicesCompareSpec * pServicesCompareSpec, unsigned int unAscending );
    virtual ~UserDefineLCNFollowHeadendDefine ( );

public:

    unsigned int SetUserLCN ( ServicesDataBaseInterface * pServicesDataBaseInterface );

private:

    unsigned short m_usLCNStart;

    ServicesCompareSpec * m_pServicesCompareSpec;
    unsigned int m_unAscending;
};

#endif /* USERDEFINELCNFOLLOWHEADENDDEFINE_H_ */
