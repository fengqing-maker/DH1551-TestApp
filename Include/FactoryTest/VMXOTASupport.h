/* VMXOTASupport.h
 *
 *  Created on: 2015-7-15
 *      Author: gongjinjun
 */
 
#ifndef VMXOTASUPPORT_H_
#define VMXOTASUPPORT_H_

#include "OTASupport.h"

class VMXOTASupport : public OTASupport
{

public:
	
	VMXOTASupport();
	~VMXOTASupport();
	
public:

	unsigned int OpenHLType(int nBoot, int nCW, int nJtag);

};

#endif //VMXOTASUPPORT_H_

