/*
* ServicesDataBaseInterface.h
*
*  Created on: 2015-5-4
*      Author: Demo
*/

#ifndef SERVICESDATABASEINTERFACE_H_
#define SERVICESDATABASEINTERFACE_H_

#include "ServicesGroupInterface.h"
#include "ServiceInterface.h"
#include "TransponderInterface.h"
#include "NetworkInterface.h"
#include "SatelliteInterface.h"
#include "ServicesCompareSpec.h"
#include "ServicesFindInterface.h"
#include "CheckServiceSpec.h"
#include "ServiceIndexUpdatedNotify.h"
#include "ServiceDataBaseFindNotify.h"

class ServicesDataBaseInterface
{

public:

    ServicesDataBaseInterface ( );
    virtual ~ServicesDataBaseInterface ( );

public:

    virtual unsigned int GetGlobalServicesCount ( ) = 0;
    virtual ServiceInterface * GetServiceInterface ( unsigned int unGlobalServiceIndex ) = 0;
    virtual ServiceInterface * GetServiceInterface ( unsigned short usOriNetwork, unsigned short usTSID, unsigned short usServiceID ) = 0;

    virtual unsigned int LockedService ( unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int UnLockService ( unsigned int unGlobalServiceIndex ) = 0;

    virtual unsigned int LockedService ( ServiceInterface *pServiceInterface ) = 0;
    virtual unsigned int UnLockService ( ServiceInterface *pServiceInterface ) = 0;
    virtual unsigned int IsHideService ( ServiceInterface *pServiceInterface ) = 0;
    virtual unsigned int IsHideService ( unsigned int unGlobalServiceIndex ) = 0;

    virtual unsigned int HidedService ( unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int UnhideService ( unsigned int unGlobalServiceIndex ) = 0;

    virtual unsigned int HidedService ( ServiceInterface *pServiceInterface ) = 0;
    virtual unsigned int UnhideService ( ServiceInterface *pServiceInterface ) = 0;

    virtual unsigned int SelectService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int UnSelectService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int UnSelectAllService ( unsigned int unGroupIndex ) = 0;
    virtual unsigned int IsSelectService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int GetSelectedServiceCount ( unsigned int unGroupIndex ) = 0;
    virtual ServiceInterface * GetSelectedServiceInterface ( unsigned int unGroupIndex, unsigned int unSelectServiceIndex ) = 0;

    virtual unsigned int GetBATGroupCount ( ) = 0;
    virtual ServicesGroupInterface * GetBATServicesGroupInterface ( unsigned int unIndex ) = 0;
    virtual BouquetInterface * GetBouquetInterface ( unsigned int unIndex ) = 0;
    virtual unsigned int IsBATServicesGroup ( char acGroupName [ ], unsigned int unNameLen ) = 0;

    virtual unsigned int GetSubBATGroupCount ( unsigned int unBATIndex ) = 0;
    virtual ServicesGroupInterface * GetSubBATServicesGroupInterface ( unsigned int unBATIndex, unsigned int unSubBATIndex ) = 0;
    virtual BouquetInterface * GetBouquetInterface ( unsigned int unBATIndex, unsigned int unSubIndex ) = 0;

    virtual unsigned int GetGroupCount ( ) = 0;
    virtual ServicesGroupInterface * GetServicesGroupInterface ( unsigned int unGroupIndex ) = 0;
    virtual ServicesGroupInterface * GetServicesGroupInterface ( char acGroupName [ ], unsigned int unNameLen ) = 0;

    virtual unsigned int GetFAVServicesGroupCount ( ) = 0;
    virtual ServicesGroupInterface * GetFAVServicesGroupInterface ( unsigned int unGroupIndex ) = 0;
    virtual unsigned int IsFAVServicesGroup ( char acGroupName [ ], unsigned int unNameLen ) = 0;

    virtual ServicesFindInterface * CreateServicesFindInterface ( unsigned int unGroupIndex ) = 0;
    virtual unsigned int DeleteServicesFindInterface ( ServicesFindInterface * pServicesFindInterface ) = 0;

    virtual unsigned int GetServicesCount ( unsigned int unGroupIndex ) = 0;
    virtual ServiceInterface * GetServiceInterface ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int LockedService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int UnLockService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int LockedSelectedService ( unsigned int unGroupIndex ) = 0;

    virtual unsigned int HidedService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int UnhideService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int HidedSelectedService ( unsigned int unGroupIndex ) = 0;
    virtual unsigned int IsHideService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int SkipPlayService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int UnskipPlayService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int SkipPlaySelectedService ( unsigned int unGroupIndex ) = 0;
    virtual unsigned int UnskipPlayService ( ServiceInterface * pServiceInterface ) = 0;
    virtual unsigned int IsSkipPlayService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int IsLockedService ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int IsLockedService ( ServiceInterface * pServiceInterface ) = 0;
    virtual unsigned int GetLockedServiceCount ( ) = 0;
    virtual ServiceInterface *GetLockedServiceByIndex ( unsigned int unLockServiceIndex ) = 0;

    virtual unsigned int GetHidedServiceCount ( ) = 0;
    virtual ServiceInterface *GetHidedServiceByIndex ( unsigned int unSkipServiceIndex ) = 0;

    virtual unsigned int GetSkipPlayServiceCount ( ) = 0;
    virtual ServiceInterface *GetSkipPlayServiceByIndex ( unsigned int unSkipServiceIndex ) = 0;

	virtual unsigned int EditServiceName(ServiceInterface *pServiceInterface, char acNewName[], unsigned int unNameLength) = 0;
	virtual unsigned int UndoEditServiceName(ServiceInterface *pServiceInterface) = 0;

    virtual unsigned int MovedService ( unsigned int unGroupIndex, unsigned int unServiceIndex, int nMovedPos ) = 0;
    virtual unsigned int MovedService ( unsigned int unServiceIndex, int nMovedPos ) = 0;
    virtual unsigned int MovedFAVService ( unsigned int unFAVGroupIndex, unsigned int unServiceIndex, int nMovePos ) = 0;
    virtual unsigned int MoveSelectedServices ( unsigned int unGroupIndex, unsigned int unMoveToNewPos ) = 0;

    virtual unsigned int ChangeDefaultServicesGroupSortType ( ServicesCompareSpec * pServicesCompareSpec, unsigned int unSortType ) = 0;
    virtual ServicesCompareSpec * GetDefaultServicesCompareSpec ( ) = 0;

    virtual unsigned int SetServiceAudioVolume ( ServiceInterface * pServiceInterface, unsigned int unAudioVolume ) = 0;
    virtual unsigned int SetServiceAudioVolume ( unsigned int unGlobalServiceIndex, unsigned int unAudioVolume ) = 0;
    virtual unsigned int SetServiceAudioVolume ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned int unAudioVolume ) = 0;
    virtual unsigned int GetServiceAudioVolume ( ServiceInterface * pServiceInterface ) = 0;
    virtual unsigned int GetServiceAudioVolume ( unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int GetServiceAudioVolume ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int SetServiceAudioChannel ( ServiceInterface * pServiceInterface, unsigned int unAudioChannel ) = 0;
    virtual unsigned int SetServiceAudioChannel ( unsigned int unGlobalServiceIndex, unsigned int unAudioChannel ) = 0;
    virtual unsigned int SetServiceAudioChannel ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned int unAudioChannel ) = 0;
    virtual unsigned int GetServiceAudioChannel ( ServiceInterface * pServiceInterface ) = 0;
    virtual unsigned int GetServiceAudioChannel ( unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int GetServiceAudioChannel ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;

    virtual unsigned int SetSubTitleISO639LanguageCode ( ServiceInterface * pServiceInterface, unsigned char aucSubTitleISO639LanguageCode [ 3 ] ) = 0;
    virtual unsigned int SetSubTitleISO639LanguageCode ( unsigned int unGlobalServiceIndex, unsigned char aucSubTitleISO639LanguageCode [ 3 ] ) = 0;
    virtual unsigned int SetSubTitleISO639LanguageCode ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned char aucSubTitleISO639LanguageCode [ 3 ] ) = 0;
    virtual unsigned int GetSubTitleISO639LanguageCode ( ServiceInterface * pServiceInterface, unsigned char * pucSubTitleISO639LanguageCode, unsigned int unLen ) = 0;
    virtual unsigned int GetSubTitleISO639LanguageCode ( unsigned int unGlobalServiceIndex, unsigned char * pucSubTitleISO639LanguageCode, unsigned int unLen ) = 0;
    virtual unsigned int GetSubTitleISO639LanguageCode ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned char * pucSubTitleISO639LanguageCode, unsigned int unLen ) = 0;

    virtual unsigned int SetServiceUserDataReserved ( ServiceInterface * pServiceInterface, unsigned char aucReserved [ ], unsigned int unLength ) = 0;
    virtual unsigned int SetServiceUserDataReserved ( unsigned int unGlobalServiceIndex, unsigned char aucReserved [ ], unsigned int unLength ) = 0;
    virtual unsigned int SetServiceUserDataReserved ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned char aucReserved [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetServiceUserDataReserved ( ServiceInterface * pServiceInterface, unsigned char aucReserved [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetServiceUserDataReserved ( unsigned int unGlobalServiceIndex, unsigned char aucReserved [ ], unsigned int unLength ) = 0;
    virtual unsigned int GetServiceUserDataReserved ( unsigned int unGroupIndex, unsigned int unServiceIndex, unsigned char aucReserved [ ], unsigned int unLength ) = 0;

    virtual unsigned int AddFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int AddFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int AddFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int RemoveFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int RemoveFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int RemoveFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int IsBelongFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int IsBelongFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int IsBelongFAVGroupService ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int AddFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int AddFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int AddFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int RemoveFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int RemoveFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int RemoveFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int IsBelongFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int IsBelongFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int IsBelongFAVGroupServiceName ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int AddFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int AddFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int AddFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int RemoveFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int RemoveFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int RemoveFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int IsBelongFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unGlobalServiceIndex ) = 0;
    virtual unsigned int IsBelongFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int IsBelongFAVGroupServiceNameORID ( char acFAVName [ ], unsigned int unFAVNameLen, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int IsFAVService ( unsigned int unSrcGroupIndex, unsigned int unSrcServiceIndex ) = 0;
    virtual unsigned int IsFAVService ( ServiceInterface * pServiceInterface ) = 0;
    virtual unsigned int IsFAVService ( unsigned int unGlobalServiceIndex ) = 0;

    virtual TransponderInterface * GetServiceTransponder ( unsigned int unGlobalServiceIndex ) = 0;
    virtual TransponderInterface * GetServiceTransponder ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual TransponderInterface * GetServiceTransponder ( ServiceInterface * pServiceInterface ) = 0;

    virtual NetworkInterface * GetServiceNetwork ( unsigned int unGlobalServiceIndex ) = 0;
    virtual NetworkInterface * GetServiceNetwork ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual NetworkInterface * GetServiceNetwork ( ServiceInterface * pServiceInterface ) = 0;

    virtual SatelliteInterface * GetServiceSatellite ( unsigned int unGlobalServiceIndex ) = 0;
    virtual SatelliteInterface * GetServiceSatellite ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual SatelliteInterface * GetServiceSatellite ( ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int GetServiceLCN ( unsigned int unGroupIndex, unsigned int unServiceIndex ) = 0;
    virtual unsigned int GetServiceLCN ( unsigned int unServiceIndex ) = 0;
    virtual unsigned int GetServiceAttributeInBATGroup ( ServicesGroupInterface * pServicesGroupInterface, ServiceInterface * pServiceInterface ) = 0;

    virtual unsigned int CheckService ( unsigned int unGlobalServiceIndex, CheckServiceSpec * pCheckServiceSpec ) = 0;
    virtual unsigned int CheckService ( unsigned int unGroupIndex, unsigned int unServiceIndex, CheckServiceSpec * pCheckServiceSpec ) = 0;
    virtual unsigned int CheckService ( ServiceInterface * pServiceInterface, CheckServiceSpec * pCheckServiceSpec ) = 0;

    virtual unsigned int AddServiceIndexUpdatedNotify ( unsigned int unGroupIndex, unsigned int unServiceIndex, ServiceIndexUpdatedNotify * pServiceIndexUpdatedNotify ) = 0;
    virtual unsigned int RemoveServiceIndexUpdatedNotify ( unsigned int unGroupIndex, unsigned int unServiceIndex, ServiceIndexUpdatedNotify * pServiceIndexUpdatedNotify ) = 0;

    virtual unsigned int GetCableNetworkCount ( ) = 0;
    virtual NetworkInterface* GetCableNetwork ( unsigned int unIndex ) = 0;
    virtual NetworkInterface* GetCableNetwork ( unsigned short usNetowrkID ) = 0;

    virtual unsigned int GetTerrestrialNetworkCount ( ) = 0;
    virtual NetworkInterface* GetTerrestrialNetwork ( unsigned int unIndex ) = 0;
    virtual NetworkInterface* GetTerrestrialNetwork ( unsigned short usNetowrkID ) = 0;

    virtual unsigned int GetSatelliteNetworkCount ( ) = 0;
    virtual NetworkInterface* GetSatelliteNetwork ( unsigned int unIndex ) = 0;
    virtual NetworkInterface* GetSatelliteNetwork ( unsigned short usNetowrkID ) = 0;

    virtual void CreateLockUndoPoint ( ) = 0;
    virtual void DeleteLockUndoPoint ( ) = 0;
    virtual void UndoLockUndoPoint ( ) = 0;

    virtual void CreateHideUndoPoint ( ) = 0;
    virtual void DeleteHideUndoPoint ( ) = 0;
    virtual void UndoHideUndoPoint ( ) = 0;

    virtual void CreatePlaySkipUndoPoint ( ) = 0;
    virtual void DeletePlaySkipUndoPoint ( ) = 0;
    virtual void UndoPlaySkipUndoPoint ( ) = 0;

    virtual void CreateMoveUndoPoint ( ) = 0;
    virtual void DeleteMoveUndoPoint ( ) = 0;
    virtual void UndoMoveUndoPoint ( ) = 0;

    virtual void CreateFavUndoPoint ( ) = 0;
    virtual void DeleteFavUndoPoint ( ) = 0;
    virtual void UndoFavUndoPoint ( ) = 0;

    virtual void SafeMergeLocked ( ) = 0;
    virtual void SafeMergeUnlocked ( ) = 0;

    virtual void AllServicesReSort ( ) = 0;

    virtual ServiceInterface * FindService ( ServiceDataBaseFindNotify & inputServiceDataBaseFindNotify ) = 0;

};

#endif /* SERVICESDATABASEINTERFACE_H_ */
