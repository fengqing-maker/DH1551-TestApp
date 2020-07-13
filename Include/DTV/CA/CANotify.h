/*
 * CANotify.h
 *
 *  Created on: 2015-10-17
 *      Author: timothy.liao
 */

#ifndef CANOTIFY_H_
#define CANOTIFY_H_
#include "ServiceInterface.h"
#include "CAPipeType.h"

class CANotify
{
public:
    CANotify ( );
    virtual ~CANotify ( );

public:

    virtual void StartCANotify ( CAPipeType ePipeType, ServiceInterface* pService ) = 0;
    virtual void StopCANotify ( CAPipeType ePipeType, ServiceInterface* pService ) = 0;
    virtual void AddComponentNotify ( CAPipeType ePipeType, ServiceInterface* pService, unsigned short usPid ) = 0;
    virtual void RemoveComponentNotify ( CAPipeType ePipeType, ServiceInterface* pService, unsigned short usPid ) = 0;

    virtual void InjectPMTSectionsNotify ( CAPipeType ePipeType, ServiceInterface* pServiceInterface, unsigned char aucData [ ], unsigned int unLength ) = 0;
    virtual void InjectSDTSectionsNotify ( CAPipeType ePipeType, unsigned char aucData [ ], unsigned int unLength ) = 0;
    virtual void InjectNITSectionsNotify ( CAPipeType ePipeType, unsigned char aucData [ ], unsigned int unLength ) = 0;
    virtual void InjectCATSectionsNotify ( CAPipeType ePipeType, unsigned char aucData [ ], unsigned int unLength ) = 0;
    virtual void InjectBATSectionsNotify ( CAPipeType ePipeType, unsigned char aucData [ ], unsigned int unLength ) = 0;

    virtual unsigned int CheckMasterPinCodeNotify ( CAPipeType ePipeType, unsigned int unMasterPinCode, void* pvParam1, void* pvParam2 ) = 0;

    virtual void InjectECMDataNotify ( CAPipeType ePipeType, unsigned short usECMPid, unsigned char aucData [ ], unsigned int unLength ) = 0;
};

#endif /* CANOTIFY_H_ */
