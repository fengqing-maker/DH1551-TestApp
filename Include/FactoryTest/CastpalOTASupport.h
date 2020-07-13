/* IrdetoOTASupport.h
 *
 */
 
#ifndef CASTPALOTASUPPORT_H_
#define CASTPALOTASUPPORT_H_

#include "OTASupport.h"

class CastpalOTASupport : public OTASupport
{

public:
	
	CastpalOTASupport();
	~CastpalOTASupport();
	
public:

	unsigned int OpenHLType(int nBoot, int nCW, int nJtag);

};

#endif //CASTPALOTASUPPORT_H_

