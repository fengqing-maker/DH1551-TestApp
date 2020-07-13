/*
 * OTASupport.cpp
 *
 *  Created on: 2015-8-20
 *      Author: Timothy
 */

#include "adi_secure.h"
#include "VMXOTASupport.h"

VMXOTASupport::VMXOTASupport()
{
}

VMXOTASupport ::~VMXOTASupport()
{
}

unsigned int VMXOTASupport::OpenHLType(int nBoot, int nCW, int nJtag)
{
	unsigned int unRet = 0;

	if (ADISecureVMXEnableFuses() == ADI_SUCCESS)
	{
		if(ADISecureVMXCheckFusesStatus() == ADI_SUCCESS)
		{
			unRet = 1;
		}
	}

	return unRet;
}

