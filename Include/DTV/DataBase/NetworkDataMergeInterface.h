/*
 * NetworkDataMergeInterface.h
 *
 *  Created on: 2015-5-4
 *      Author: Demo
 */

#ifndef NETWORKDATAMERGEINTERFACE_H_
#define NETWORKDATAMERGEINTERFACE_H_

#include "SatelliteInterface.h"
#include "ServiceMergeSpec.h"
#include "BouquetMergeSpec.h"
#include "NetworkInterface.h"
#include "TransponderInterface.h"
#include "Delivery.h"
#include "ArchiveInterface.h"
#include "ArchiveReloadNotify.h"
#include "ServicesDeletedNotify.h"
#include "ServiceInterface.h"
#include <list>

using namespace std;
using std::list;

class NetworkDataMergeInterface
{

public:
	
	NetworkDataMergeInterface( );
	virtual ~NetworkDataMergeInterface( );

public:

    virtual unsigned int SetServiceMergeSpec ( ServiceMergeSpec * pServiceMergeSpec ) = 0;
    virtual unsigned int SetBouquetMergeSpec ( BouquetMergeSpec * pBouquetMergeSpec ) = 0;

    virtual unsigned int MergeNetworkData ( Delivery * pActualDelivery, NetworkInterface * pNetworkInterface ) = 0;
    
    virtual unsigned int MergeCableNetworkData ( NetworkInterface * pNetworkInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeTerrestrialNetworkData ( NetworkInterface * pNetworkInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeSatelliteNetworkData ( NetworkInterface * pNetworkInterface, SatelliteInterface * pSatelliteInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;

    virtual unsigned int MergeCableNetworkOnlyServiceData ( NetworkInterface * pNetworkInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeTerrestrialNetworkOnlyServiceData ( NetworkInterface * pNetworkInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeSatelliteNetworkOnlyServiceData ( NetworkInterface * pNetworkInterface, SatelliteInterface * pSatelliteInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;

    virtual unsigned int MergeCableNetworkOnlyBouquetData ( NetworkInterface * pNetworkInterface ) = 0;
    virtual unsigned int MergeTerrestrialNetworkOnlyBouquetData ( NetworkInterface * pNetworkInterface ) = 0;
    virtual unsigned int MergeSatelliteNetworkOnlyBouquetData ( NetworkInterface * pNetworkInterface, SatelliteInterface * pSatelliteInterface ) = 0;

    virtual unsigned int MergeCableNetworkOnlyServiceLCN ( NetworkInterface * pNetworkInterface ) = 0;
    virtual unsigned int MergeTerrestrialNetworkOnlyServiceLCN ( NetworkInterface * pNetworkInterface ) = 0;
    virtual unsigned int MergeSatelliteNetworkOnlyServiceLCN ( NetworkInterface * pNetworkInterface, SatelliteInterface * pSatelliteInterface ) = 0;

    virtual unsigned int MergeCableNetworkData ( TransponderInterface * pTransponderInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeTerrestrialNetworkData ( TransponderInterface * pTransponderInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeSatelliteNetworkData ( TransponderInterface * pTransponderInterface, SatelliteInterface * pSatelliteInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;

    virtual unsigned int MergeCableNetworkData ( unsigned short usNetworkID, TransponderInterface * pTransponderInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeTerrestrialNetworkData ( unsigned short usNetworkID, TransponderInterface * pTransponderInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeSatelliteNetworkData ( unsigned short usNetworkID, TransponderInterface * pTransponderInterface, SatelliteInterface * pSatelliteInterface, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;

    virtual unsigned int MergeCableNetworkData ( list <TransponderInterface *> & InputTransponderList, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeTerrestrialNetworkData ( list <TransponderInterface *> & InputTransponderList, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeSatelliteNetworkData ( list <TransponderInterface *> & InputTransponderList, list <SatelliteInterface *> & InputSatelliteInterfaceList, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;

    virtual unsigned int MergeCableNetworkData ( list <unsigned short> & InputNetworkIDList, list <TransponderInterface *> & InputTransponderList, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeTerrestrialNetworkData ( list <unsigned short> & InputNetworkIDList, list <TransponderInterface *> & InputTransponderList, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;
    virtual unsigned int MergeSatelliteNetworkData ( list <unsigned short> & InputNetworkIDList, list <TransponderInterface *> & InputTransponderList, list <SatelliteInterface *> & InputSatelliteInterfaceList, unsigned int unRemoveNotExist, unsigned int unForceUpdateLCN, unsigned int unUpdateFreeCAMode, unsigned int unAllowDeletedTS, unsigned int unAllowAddTS ) = 0;

    virtual unsigned int AddCableNetworkService ( unsigned short usOriNetworkID, unsigned short usTSID, unsigned short usServiceID, unsigned short usLCN, char acServiceName [ ], unsigned int unNameLength, ServiceType eServiceType, FreeCAMode eFreeCAMode, unsigned short usPMTPID ) = 0;
    virtual unsigned int AddTerrestrialNetworkService ( unsigned short usOriNetworkID, unsigned short usTSID, unsigned short usServiceID, unsigned short usLCN, char acServiceName [ ], unsigned int unNameLength, ServiceType eServiceType, FreeCAMode eFreeCAMode, unsigned short usPMTPID ) = 0;
    virtual unsigned int AddSatelliteNetworkService ( SatelliteInterface * pSatelliteInterface, unsigned short usOriNetworkID, unsigned short usTSID, unsigned short usServiceID, unsigned short usLCN, char acServiceName [ ], unsigned int unNameLength, ServiceType eServiceType, FreeCAMode eFreeCAMode, unsigned short usPMTPID ) = 0;

	virtual ArchiveInterface * CreateArchive(unsigned int unSize) = 0;
    virtual ArchiveInterface * CreateArchive ( unsigned int unSize, ArchiveReloadNotify * pArchiveReloadNotify ) = 0;

    virtual void LoadDefaultDataBase ( ) = 0;
    virtual void SaveCurDataBaseToDefauleDataBase ( ) = 0;

    virtual void Clear ( ) = 0; //Clear whole DataBase completely
    virtual void ClearUserData ( ) = 0; //Clear service related user settings ( FAV, LOCK, SKIP, HIDE, VOLUME, SUBTITLE LANGUAGE...)
    virtual void ClearServiceData ( ) = 0; //Clear all services
    virtual void ClearNetworkDelivery ( ) = 0; //Clear all service and delivery

    virtual void Save ( ) = 0;
    virtual void SaveDefaultNetworkDelivery ( ) = 0;
    virtual void SaveServicesDataBase ( ) = 0;
    virtual void SaveUserData ( ) = 0;

	virtual void SyncSave ( ) = 0;
	virtual void SyncSaveDefaultNetworkDelivery ( ) = 0;
	virtual void SyncSaveServicesDataBase ( ) = 0;
	virtual void SyncSaveUserData ( ) = 0;

    virtual unsigned int Backup ( ) = 0;
    virtual unsigned int LoadNetworkDeliveryFromBackup ( ) = 0;

    virtual unsigned int UpdateServiceFlashData ( ServiceInterface * pServiceInterface ) = 0;
    virtual unsigned int UpdateTransponderFlashData ( TransponderInterface * pTransponderInterface ) = 0;
    virtual unsigned int UpdateTransponderDeliveryData ( TransponderInterface * pTransponderInterface, Delivery * pDelivery ) = 0;
    virtual unsigned int UpdateSatelliteFlashData ( SatelliteInterface * pSatelliteInterface ) = 0;

    virtual void Flush ( ) = 0;

    virtual unsigned int AddServicesDeletedNotify ( ServicesDeletedNotify * pServicesDeletedNotify ) = 0;
    virtual unsigned int RemoveServicesDeletedNotify ( ServicesDeletedNotify * pServicesDeletedNotify ) = 0;

};

#endif /* NETWORKDATAMERGEINTERFACE_H_ */
