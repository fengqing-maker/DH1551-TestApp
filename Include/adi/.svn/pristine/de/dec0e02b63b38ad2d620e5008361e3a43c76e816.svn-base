

#ifndef _ADI_HDMI_CEC_H_
#define _ADI_HDMI_CEC_H_
#include "adi_error.h"
#ifdef __cplusplus
extern "C" {
#endif

#define ADIHDMI_CEC_PHA_LEN (2)
#define ADIHDMI_CEC_MSGLEN (14)

typedef enum
{
    E_ADI_CEC_FEATURE_ABORT = 0x00,  //CEC ERROR CODE FEATURE ABORT
    E_ADI_CEC_RX_SUCCESS    = 0x01,  //CEC Receive Success
    E_ADI_CEC_TX_SUCCESS    = 0x02,  //CEC Transfer Success
    E_ADI_CEC_RF            = 0x04,  //CEC ERROR CODE RF
    E_ADI_CEC_LOST_ABT      = 0x08,  //CEC ERROR CODE Lost ABT
    E_ADI_CEC_BIT_SHORT     = 0x10,  //CEC ERROR CODE Bit short
    E_ADI_CEC_BIT_LONG      = 0x20,  //CEC ERROR CODE Bit long
    E_ADI_CEC_NACK          = 0x40,  //CEC ERROR CODE none-Ack
    E_ADI_CEC_SYSTEM_BUSY   = 0x80,  //CEC ERROR CODE System busy
}ADIHDMICECErrorCode_E;

//LOGICAL_ADDRESS
typedef enum
{
	E_ADI_CEC_LA_DEFAULT         =-1,
    E_ADI_CEC_LA_TV              =0,     //CEC device TV
    E_ADI_CEC_LA_RECORDER1       =1,     //CEC device RECORDER1
    E_ADI_CEC_LA_RECORDER2       =2,     //CEC device RECORDER2
    E_ADI_CEC_LA_TUNER1          =3,     //CEC device TUNER1
    E_ADI_CEC_LA_PLAYBACK1       =4,     //CEC device PLAYBACK1
    E_ADI_CEC_LA_AUDIO_SYS       =5,     //CEC device AUDIO SYSTEM
    E_ADI_CEC_LA_TUNER2          =6,     //CEC device TUNER2
    E_ADI_CEC_LA_TUNER3          =7,     //CEC device TUNER3
    E_ADI_CEC_LA_PLAYBACK2       =8,     //CEC device PLAYBACK2
    E_ADI_CEC_LA_RECORER3        =9,     //CEC device RECORDER3
    E_ADI_CEC_LA_TUNER4          =10,    //CEC device TUNER4
    E_ADI_CEC_LA_PLAYBACK3       =11,    //CEC device PLAYBACK3
    E_ADI_CEC_LA_RESERVED1       =12,    //Reserved use for CEC device
    E_ADI_CEC_LA_RESERVED2       =13,    //Reserved use for CEC device
    E_ADI_CEC_LA_FREE_USE        =14,    //Free use for CEC device
    E_ADI_CEC_LA_UNREGISTERED    =15,    //Unregistered
    E_ADI_CEC_LA_BROADCAST       =15,    //BROADCAST to all CEC devices
    E_ADI_CEC_LA_MAX,                     //MAX Logical Addr num
}ADIHDMICECDeviceLa_E;

typedef enum
{
    E_ADI_CEC_DEVICE_TYPE_TV              = 0,   //Device Type TV
    E_ADI_CEC_DEVICE_TYPE_RECORDER,              //Device Type Recorder
    E_ADI_CEC_DEVICE_TYPE_RESERVED,              //Reserved
    E_ADI_CEC_DEVICE_TYPE_TUNER,                 //Device Type Tuner
    E_ADI_CEC_DEVICE_TYPE_PLAYBACK,              //Device Type Playback
    E_ADI_CEC_DEVICE_TYPE_AUDIO_SYSTEM,          //Device Type Audio System
    E_ADI_CEC_DEVICE_TYPE_PURE_CEC_SWITCH,       //Device Type CEC Switch
    E_ADI_CEC_DEVICE_TYPE_VIDEO_PROCESSOR,       //Device Type Video Processor
    E_ADI_CEC_DEVICE_TYPE_MAX,
}ADIHDMICECDeviceType_E;

typedef enum
{
	EM_ADI_CEC_DEVICE_POWER_ON,
	EM_ADI_CEC_DEVICE_POWER_STANDBY,
	EM_ADI_CEC_DEVICE_POWER_STANDBY_TO_ON,
	EM_ADI_CEC_DEVICE_POWER_ON_TO_STANDBY
}ADIHDMICecDevicePowerStatus_E;


//Cec°æ±¾ºÅ
typedef enum
{
	EM_ADI_CEC_VERSION_11,		//CEC1.1
	EM_ADI_CEC_VERSION_12,		//CEC1.2
	EM_ADI_CEC_VERSION_12a,		//CEC1.2a
	EM_ADI_CEC_VERSION_13,		//CEC1.3
	EM_ADI_CEC_VERSION_13a,		//CEC1.3a
	EM_ADI_CEC_VERSION_14		//CEC1.4
}ADIHDMICecVersion_E;



typedef struct
{
    ADIHDMICECDeviceType_E m_eCecDevType;  //CEC Device Type
	ADIHDMICECDeviceLa_E   m_eCecDevLa;    //Logical Address
    unsigned char          m_ucPha[ADIHDMI_CEC_PHA_LEN];     //Physical Address
}ADIHDMICECDeviceInfo_S;

typedef enum
{
	E_ADI_CEC_ON,      //ADIHDMICECDeviceInfo_S *
	E_ADI_CEC_OFF,     //No Param
	E_ADI_CEC_OPCODE,  //ADIHDMICECMsgInfo_S *
}ADIHDMICECEventType_E;

typedef enum
{
//----- One Touch Play ----------------------------
    E_ADI_CEC_OP_ACTIVE_SOURCE                         = 0x82,  //Used by a new source to indicate that it has started to transADIt a stream or used in response to E_ADI_CEC_OP_RC_REQ_ACTIVE_SOURCE
    E_ADI_CEC_OP_OTP_IMAGE_VIEW_ON                     = 0x04,  //Sent by a source device to the TV whenever it enters the active state
    E_ADI_CEC_OP_OTP_TEXT_VIEW_ON                      = 0x0D,  //As E_ADI_CEC_OP_OTP_IMAGE_VIEW_ON, but should also remove any text, menus and PIP window from the TV's display

//----- Routing Control ---------------------------
    E_ADI_CEC_OP_RC_INACTIVE_SOURCE                    = 0x9D,  //Used by the currently active source to inform the TV that it has no video to be presented to the user, or is going into the standby state as the result of a local user command on the device.
    E_ADI_CEC_OP_RC_REQ_ACTIVE_SOURCE                  = 0x85,  //Used by a new device to discover the status of the system.
    E_ADI_CEC_OP_RC_ROUTING_CHANGE                     = 0x80,  //Sent by a CEC Switch when it is manually switched to inform all other devices on the network that the active route below the switch has changed.
    E_ADI_CEC_OP_RC_ROUTING_INFO                       = 0x81,  //Sent by a CEC Switch to indicate the active route below the switch.
    E_ADI_CEC_OP_RC_SET_STREAM_PATH                    = 0x86,  //Used by the TV to request a streaADIng path from the specified physical address.
//----- Standby Command ---------------------------
    E_ADI_CEC_OP_STANDBY                               = 0x36,  //Switches one or all devices into the standby state. Can be used as a broadcast message or be addressed to a specific device.
//----- One Touch Record---------------------------
    E_ADI_CEC_OP_OTR_RECORD_ON                         = 0x09,  //Requests a device to stop a recording.
    E_ADI_CEC_OP_OTR_RECORD_OFF                        = 0x0B,  //Attempt to record the specified source.
    E_ADI_CEC_OP_OTR_RECORD_STATUS                     = 0x0A,  //Used by a recording Device to inform the initiator of the message E_ADI_CEC_OP_OTR_RECORD_ON about its status.
    E_ADI_CEC_OP_OTR_RECORD_TV_SCREEN                  = 0x0F,  //Request by the recording device to record the presently displayed source.
//----- Timer programmer -------------------------- CEC1.3a
    E_ADI_CEC_OP_TP_CLEAR_ANALOG_TIMER                 = 0x33,  //Used to clear an Analogue timer block of a device.
    E_ADI_CEC_OP_TP_CLEAR_DIGITAL_TIMER                = 0x99,  //Used to clear a digital timer block of a device.
    E_ADI_CEC_OP_TP_CLEAR_EXT_TIMER                    = 0xA1,  //Used to clear an external timer block of a device.
    E_ADI_CEC_OP_TP_SET_ANALOG_TIMER                   = 0x34,  //Used to set a single timer block on an analogue recording device.
    E_ADI_CEC_OP_TP_SET_DIGITAL_TIMER                  = 0x97,  //Used to set a single timer block on a digital recording device.
    E_ADI_CEC_OP_TP_SET_EXT_TIMER                      = 0xA2,  //Used to set a single timer block to record from an external device.
    E_ADI_CEC_OP_TP_SET_TIMER_PROGRAM_TITLE            = 0x67,  //Used to set the name of a program associated with a timer block. Sent directly after sending a E_ADI_CEC_OP_TP_SET_ANALOG_TIMER or E_ADI_CEC_OP_TP_SET_DIGITAL_TIMER message. The name if then associated with that timer block.
    E_ADI_CEC_OP_TP_TIMER_CLEARED_STATUS               = 0x43,  //Used to give the status of a E_ADI_CEC_OP_TP_CLEAR_ANALOG_TIMER/E_ADI_CEC_OP_TP_CLEAR_DIGITAL_TIMER/E_ADI_CEC_OP_TP_CLEAR_EXT_TIMER message.
    E_ADI_CEC_OP_TP_TIMER_STATUS                       = 0x35,  //Used to send timer status to the initiator of a set timer message.
//----- System Information ------------------------
    E_ADI_CEC_OP_SI_CEC_VERSION                        = 0x9E,  //Used to indicate the version number of the CEC Specification which was used to design the device, in response to a E_ADI_CEC_OP_SI_GET_CEC_VERSION message.
    E_ADI_CEC_OP_SI_GET_CEC_VERSION                    = 0x9F,  //Used by a device to enquire which version number of the CEC Specification was used to design the follower device.
    E_ADI_CEC_OP_SI_GIVE_PHY_ADDR                      = 0x83,  //A request to a device to return its physical address.
    E_ADI_CEC_OP_SI_REPORT_PHY_ADDR                    = 0x84,  //Used to inform all other devices of the mapping between physical and logical address of the initiator.
    E_ADI_CEC_OP_SI_GET_MENU_LANGUAGE                  = 0x91,  //Set by a device capable of character generation(for OSD and Menus) to a TV in the order to discover the currently selected menu language on the TV.
    E_ADI_CEC_OP_SI_SET_MENU_LANGUAGE                  = 0x32,  //Used by a TV to indicate its currently selected menu language.
//----- Deck Control Feature-----------------------
    E_ADI_CEC_OP_DC_DECK_CTRL                          = 0x42,  //Used to control a device's media functions.
    E_ADI_CEC_OP_DC_DECK_STATUS                        = 0x1B,  //Used to provide a deck's status to the initiator of the E_ADI_CEC_OP_DC_GIVE_DECK_STATUS message.
    E_ADI_CEC_OP_DC_GIVE_DECK_STATUS                   = 0x1A,  //Used to request the status of a device, regardless of whether or not it is the current active source.
    E_ADI_CEC_OP_DC_PLAY                               = 0x41,  //Used to control the playback behavior of a source device.
//----- Tuner Control ------------------------------
    E_ADI_CEC_OP_TC_GIVE_TUNER_STATUS                  = 0x08,  //Used to request the status of a tuner device.
    E_ADI_CEC_OP_TC_SEL_ANALOG_SERVICE                 = 0x92,  //Directly selects an analogue TV service.
    E_ADI_CEC_OP_TC_SEL_DIGITAL_SERVICE                = 0x93,  //Directly selects a Ditial TV, Radio or Data Broadcast Service.
    E_ADI_CEC_OP_TC_TUNER_DEVICE_STATUS                = 0x07,  //Used by a tuner device to provide its status to the initiator of the E_ADI_CEC_OP_TC_GIVE_TUNER_STATUS message.
    E_ADI_CEC_OP_TC_TUNER_STEP_DEC                     = 0x06,  //Used to tune to next lowest service in a tuner's service list. Can be used for PIP.
    E_ADI_CEC_OP_TC_TUNER_STEP_INC                     = 0x05,  //Used to tune to next highest service in a tuner's service list. Can be used for PIP.
//---------Vendor Specific -------------------------
    E_ADI_CEC_OP_VS_DEVICE_VENDOR_ID                   = 0x87,  //Reports the vendor ID of this device.
    E_ADI_CEC_OP_VS_GIVE_VENDOR_ID                     = 0x8C,  //Requests the vendor ID from a device.
    E_ADI_CEC_OP_VS_VENDOR_COMMAND                     = 0x89,  //Allows vendor specific commands to be sent between two devices.
    E_ADI_CEC_OP_VS_VENDOR_COMMAND_WITH_ID             = 0xA0,  //Allows vendor specific commands to be sent between two devices or broadcast.
    E_ADI_CEC_OP_VS_VENDOR_RC_BUT_DOWN                 = 0x8A,  //Indicates that a remote control button has been depressed.
    E_ADI_CEC_OP_VS_VENDOR_RC_BUT_UP                   = 0x8B,  //Indicates that a remote control button(the last button pressed indicated by the E_ADI_CEC_OP_VS_VENDOR_RC_BUT_DOWN message) has been released.
//----- OSD Display --------------------------------
    E_ADI_CEC_OP_SET_OSD_STRING                        = 0x64,  //Used to send a text message to output on a TV.
//----- Device OSD Name Transfer  ------------------
    E_ADI_CEC_OP_OSDNT_GIVE_OSD_NAME                   = 0x46,  //Used to request the preferred OSD name of a device for use in menus associated with that device.
    E_ADI_CEC_OP_OSDNT_SET_OSD_NAME                    = 0x47,  //Used to set the preferred OSD name of a device for use in menus associated with that device.
//----- Device Menu Control ------------------------
    E_ADI_CEC_OP_DMC_MENU_REQUEST                      = 0x8D,  //A requeste from the TV for a device to show/remove a menu or to query if a device is currently showing a menu.
    E_ADI_CEC_OP_DMC_MENU_STATUS                       = 0x8E,  //Used to indicate to the TV that the device is showing/has removed a menu and requests the remote control keys to be passed through.
    E_ADI_CEC_OP_UI_PRESS                              = 0x44,  //Used to indicate that the user pressed a remote control button or switched from one remote control button to another. Can also be used as a command that is not directly initiated by the user.
    E_ADI_CEC_OP_UI_RELEASE                            = 0x45,  //Indicates that user released a remote control button (the last one indicated by the E_ADI_CEC_OP_UI_PRESS message). Also used after a command that is not directly initiated by the user.
//----- Power Status  ------------------------------
    E_ADI_CEC_OP_PS_GIVE_POWER_STATUS                  = 0x8F,  //Used to deterADIne the current power status of a target device.
    E_ADI_CEC_OP_PS_REPORT_POWER_STATUS                = 0x90,  //Used to inform a requesting device of the current power status.
//----- General Protocal Message -------------------
    //----- Abort Message --------------------------
    E_ADI_CEC_OP_ABORT_MESSAGE                         = 0xFF,  //This message is reserved for testing purposes.
    //----- Feature Abort --------------------------
    E_ADI_CEC_OP_FEATURE_ABORT                         = 0x00,  //Used as a response to indicate that the device does not support the requested message type, or that it cannot execute it at the present time.
//----- System Audio Control -----------------------
    E_ADI_CEC_OP_SAC_GIVE_AUDIO_STATUS                 = 0x71,  //Requests an Amplifier to send its volume and mute status.
    E_ADI_CEC_OP_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS     = 0x7D,  //Requests the status of the system audio mode.
    E_ADI_CEC_OP_SAC_REPORT_AUDIO_STATUS               = 0x7A,  //Reports an Amplifier's volume and mute status.
    E_ADI_CEC_OP_SAC_SET_SYSTEM_AUDIO_MODE             = 0x72,  //Turns the System Audio Mode On of Off.
    E_ADI_CEC_OP_SAC_SYSTEM_AUDIO_MODE_REQUEST         = 0x70,  //A device implementing System Audio Control and which has volume control RC buttons requests to use System Audio Mode to the Amplifier.
    E_ADI_CEC_OP_SAC_SYSTEM_AUDIO_MODE_STATUS          = 0x7E,  //Reports the current status of the system audio mode.
    E_ADI_CEC_OP_SAC_REPORT_SHORT_AUDIO_DESCRIPTOR     = 0xA3,  //Report Audio Capability.
    E_ADI_CEC_OP_SAC_REQUEST_SHORT_AUDIO_DESCRIPTOR    = 0xA4,  //Request Audio Capability.
//----- System Audio Rate Control ------------------
    E_ADI_CEC_OP_SAC_SET_AUDIO_RATE                    = 0x9A,  //Used to control audio rate from Source Device.
//----- Audio Return Channel  Control --------------
    E_ADI_CEC_OP_ARC_INITIATE_ARC                      = 0xC0,  //Used by an ARC RX device to activate the ARC functionality in an ARC TX device.
    E_ADI_CEC_OP_ARC_REPORT_ARC_INITIATED              = 0xC1,  //Used by an ARC TX device to inidicate that its ARC functionality has been activated.
    E_ADI_CEC_OP_ARC_REPORT_ARC_TERADINATED            = 0xC2,  //Used by an ARC TX device to indicate that its ARC functionality has been deactivated.
    E_ADI_CEC_OP_ARC_REQUEST_ARC_INITIATION            = 0xC3,  //Used by an ARC TX device to request an ARC RX device to activate the ARC functionality in the ARC TX device.
    E_ADI_CEC_OP_ARC_REQUEST_ARC_TERADINATION          = 0xC4,  //Used by an ARC TX device to request an ARC RX device to deactivate the ARC functionality in the ARC TX device.
    E_ADI_CEC_OP_ARC_TERADINATED_ARC                   = 0xC5,  //Used by an ARC RX device to deactivate the ARC functionality in an ARC TX device.

} ADIHDMICECOpCode_E;




typedef struct
{
    /// CEC message Source Logical address
    ADIHDMICECDeviceLa_E m_eSrcLa;
    /// CEC message Destination Logical address
    ADIHDMICECDeviceLa_E m_eDstLa;
    /// CEC message opcode
    ADIHDMICECOpCode_E m_eOpCode;
    /// CEC message parameter
    unsigned char m_au8Param[ADIHDMI_CEC_MSGLEN];
    /// CEC message length
    unsigned char m_u8MsgLen;//len = parameter len
}ADIHDMICECMsgInfo_S;




typedef void (*ADIHDMICECCmdCallback_F)(int nHdmiIndex, ADIHDMICECEventType_E eEventType,void *pEventData, void *pUsrParam);//CEC command callback


ADI_Error_Code ADIHDMICECEnable(int nHdmiIndex);


ADI_Error_Code ADIHDMICECDisable(int nHdmiIndex);


ADI_Error_Code ADIHDMICECAddCallback(int nHdmiIndex,  ADIHDMICECCmdCallback_F fnHdmiCallback,void * pUsrParam );


ADI_Error_Code ADIHDMICECSendTxMsg(int nHdmiIndex, ADIHDMICECMsgInfo_S *pstTxMsgInfo, ADIHDMICECErrorCode_E* peResErrCode);


ADI_Error_Code ADIHDMICECSendTxPolling(int nHdmiIndex, ADIHDMICECDeviceLa_E eDevLa, ADIHDMICECErrorCode_E* peResErrCode);




#ifdef __cplusplus
}
#endif

#endif///_ADI_HDMI_CEC_H_

