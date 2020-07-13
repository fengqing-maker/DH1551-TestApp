/*
 * DTVInterface.h
 *
 *  Created on: 2015-5-26
 *      Author: linc
 */

#ifndef DTVINTERFACE_H_
#define DTVINTERFACE_H_
#include "ServicesDataBaseInterface.h"
#include "TunerServicesSearcherInterface.h"
#include "DataBaseContainerPlayerInterface.h"
#include "DVBType.h"
#include "NetworkDeliveryInterface.h"
#include "ServicesGroupContainerInterface.h"
#include "ServicesDataBasePlayerInterface.h"
#include "NetworkDataMergeInterface.h"
#include "UpdateLiveServiceInfoInterface.h"
#include "NetworkTime/NetworkTimeInterface.h"
#include "TunerInterface.h"
#include "DemultiplexerInterface.h"
#include "SignalIndicatorInterface.h"
#include "HDMIConnection/HDMIConnectionInterface.h"
#include "Timer/TimerContainerInterface.h"
#include "PVRFileListScanInterface.h"
#include "MediaFileListScanInterface.h"
#include "PVR/PVRInitInterface.h"
#include "PVR/FilePlayerInterface.h"
#include "CompositeNetworkEventInterface.h"
#include "adi_panel.h"
#include "StorageDeviceManagementInterface.h"
#include "FileListScanNotifyManagementInterface.h"
#include "Nvod/NVODPlayInterface.h"
#include "Media/Movie/MoviePlayerInterface.h"
#include "Media/Mp3/Mp3PlayerInterface.h"
#include "LCNDescriptorSpec.h"
#include "UserDefineLCNSpec.h"
#include "Mosaic/MosaicPlayInterface.h"
#include "CheckSimilarTransponderSpec.h"
#include "CustomDescriptor/CustomDescriptorParserInterface.h"
#include "ServiceExpDataSerializationNotify.h"
#include "FileSystemCharacterType.h"

typedef struct
{
    DVBType m_eDVBType;

    void * m_pvDBFlashStartAddr;
    unsigned int m_unDBFlashSize;
    unsigned char m_aucDBVerID [ 8 ];
    ServiceExpDataSerializationNotify * m_pServiceExpDataSerializationNotify;
   
    ServiceMergeSpec * m_pServiceMergeSpec;
    BouquetMergeSpec * m_pBouquetMergeSpec;
    ServicesCompareSpec * m_pDefaultServicesCompareSpec;
    unsigned int m_unDefaultSortType;
    unsigned int m_unInclueServicesGroup;
    unsigned int m_unHideBouquetWithoutServices;
    unsigned int m_unHandleSameLCN;
    CheckServiceSpec * m_pCheckServiceAllowToBeDel;

    unsigned int m_unEventMemoryPoolSize;
   
    PVRSolutionType m_ePVRSolution;
    unsigned int m_unTShiftBufSize; //unTShiftBufSize:µ¥Î»ÎªM
    FileSystemCharacterType m_eFSCharacterType;
    unsigned int m_unMp3SoftDecorder;

    ADIPANELType_E m_ePanelType;
    TimeZone m_eDefaultTimeZone;

    LCNDescriptorSpec * m_pLCNDescriptorSpec;
    UserDefineLCNSpec * m_pUserDefineLCNSpec;
    
    CheckSimilarTransponderSpec * m_pCheckSimilarTSSpec;
    CustomDescriptorParserInterface * m_pCustomDescriptorParserInterface;

    unsigned int m_unDefaultVolume;

    unsigned int m_unSectionReceiveCheckCRC;

}DTVInitParams;


unsigned int InitDTV ( DTVInitParams & inputInitParams );

TunerServicesSearcherInterface * GetTunerServicesSearcher ( );

ServicesDataBaseInterface * GetServicesDataBaseInterface ( );
NetworkDeliveryInterface * GetNetworkDeliveryInterface ( );
ServicesGroupContainerInterface * GetServicesGroupContainerInterface ( );
NetworkDataMergeInterface * GetNetworkDataMergeInterface ( );

ServicesDataBasePlayerInterface * GetServicesDataBasePlayerInterface ( );
DataBaseContainerPlayerInterface * GetDataBaseContainerPlayer ( );
UpdateLiveServiceInfoInterface * GetUpdateLiveServiceInfoInterface ( );

NetworkTimeInterface* GetNetworkTimeInterface ( );

TunerInterface* GetPreemptiveTunerInterface ( );
unsigned int ReleasePreemptiveTunerInterface ( TunerInterface* pPreemptiveTunerInterface );

DemultiplexerInterface* GetDemultiplexerInterface ( );

SignalIndicatorInterface* GetSignalIndicatorInterface ( );
TimerContainerInterface * GetTimerContainerInterface ( );

PVRFileListScanInterface *GetPVRFileListScanInterface ( );

MediaFileListScanInterface *GetMediaFileListScanInterface ( );

StorageDeviceManagementInterface *GetStorageDeviceManagementInterface ( );

FileScanNotifyManagementInterface *GetFileScanNotifyManagementInterface ( );

PVRInitInterface * GetPVRInit ( );
FilePlayerInterface * GetFilePlayerInterface ( );

CompositeNetworkEventInterface * GetCompositeNetworkEvent ( );

ServicesFindInterface *GetServicesFindInterfaceByIndex ( unsigned int unGroupIndex );

unsigned int ReleaseServicesGroupFindInterface ( );

HDMIConnectionInterface* GetHDMIConnectionInterface ( );

unsigned int InitTimer ( TimerHelperNotify pTimerHelperNotify, unsigned int unContinueAfterReboot, unsigned int unForceAskPermission );

NVODPlayInterface *GetNVODPlayInterface ( );

MoviePlayerInterface *GetMoviePlayerInterface ( );

Mp3PlayerInterface *GetMp3PlayerInterface ( );

MosaicPlayInterface *CreateMosaicPlayInterface ( MosaicComponetInfoUpdateNotify * pMosaicComponetInfoUpdateNotify );

CustomDescriptorParserInterface * GetCustomDescriptorParserInterface ( );

CheckSimilarTransponderSpec * GetCheckSimilarTransponderSpec ( );

unsigned int IsCheckingSectionCRCChangeEnabled ( );

#endif /* DTVINTERFACE_H_ */
