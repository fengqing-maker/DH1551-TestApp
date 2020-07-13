/*
 * OTASupport.cpp
 *
 *  Created on: 2015-8-20
 *      Author: Timothy
 */


#include "adi_secure.h"
#include "IrdetoOTASupport.h"

IrdetoOTASupport::IrdetoOTASupport()
{
}
 
IrdetoOTASupport ::~IrdetoOTASupport()
{
}

unsigned int IrdetoOTASupport::OpenHLType(int nBoot, int nCW, int nJtag)
{
	unsigned int unRet = 0;

	do
	{
		if(nBoot == 1)
		{
			if (ADISecureBootEnable() != ADI_SUCCESS)
			{
				break;
			}
		}

		if(nCW == 1)
		{
			if (ADISecureCWEnable() != ADI_SUCCESS)
			{
				break;
			}
		}

		if(nJtag == 1)
		{
			if (ADISecureSetJtagEnable() != ADI_SUCCESS)
			{
				break;
			}
		}

		unRet = 1;
	} while (0);

	return unRet;
}
