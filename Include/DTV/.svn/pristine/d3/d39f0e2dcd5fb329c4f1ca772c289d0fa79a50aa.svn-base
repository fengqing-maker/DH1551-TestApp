/*
 * LCNDescriptorSpec.h
 *
 *  Created on: 2016-2-27
 *      Author: Timothy.Liao
 */

#ifndef LCNDESCRIPTORSPEC_H_
#define LCNDESCRIPTORSPEC_H_

class LCNDescriptorSpec
{

public:

    LCNDescriptorSpec ( );
    virtual ~LCNDescriptorSpec ( );

public:

    virtual unsigned int ParseDescriptor ( unsigned char ucDesData [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetServiceCount ( ) = 0;
    virtual unsigned int GetService ( unsigned int unIndex, unsigned short &usServiceID, unsigned short &usLCN, unsigned char &ucVisible ) = 0;

};

#endif /* LCNDESCRIPTORSPEC_H_ */
