/*
 * SerialUpgrade.h
 *
 *  Created on: 2015-8-17
 *      Author: linc
 */

#ifndef SERIALUPGRADE_H_
#define SERIALUPGRADE_H_

#include "adi_uart.h"
#include "APSafeThread.h"
#include "SerialBuf.h"
#include "UpgradeMode.h"
#include "UpgradeCommand.h"
#include "UpgradeNotify.h"
#include "adi_toolset.h"
#include "FactoryTestInit.h"
#include "SNConfig.h"
#include "ListenConn.h"
#include "IFCP.h"

typedef enum
{
	E_ABV_WRITE=0x0,
	E_SN_WRITE=0x1,
	E_HDCP_WRITE=0x2,
	E_MAC_WRITE=0x4,
	E_PEF_WRITE=0x8,
	E_CONAX_PERSONALIZE=0x10,
	E_IFCP_WRITE=0x20
};

class SerialUpgrade : public APSafeThread
{
public:
	SerialUpgrade(UpgradeNotify * pNotify);
	virtual ~SerialUpgrade();

public:
	void Init(SNConfig csSNConfig);
	unsigned int GetChipID(ADICHIPID_S * pADICHIPID);
	void PrintAllLogInfo(void);
	unsigned int CheckChipID(void);
	
private:
	void OnceProcess(void);
	void StartWriteFlash(void);
	void WriteIrdetoIFCP(void);
	void ConaxPersonalize(void);
	void SendReturnFile(void);
	void InsertDataIntoDB(void);
	void StartVerify(void);
	void StartErase(void);
	void UpgradeFinish(void);
	void Stop(void);
	void SaveUpgradeStatus(void);
	int RepairStep(UPGRADE_COMMAND enCOMMAND);
	void RemindChipIDError(void);
	void SendUpgradeStatus(void);

	unsigned int SendAndReceiveUartData(UPGRADE_COMMAND enSendCOMMAND, UPGRADE_COMMAND enWantReceiveCOMMAND, unsigned char aucStr[], unsigned int unLen, unsigned int unTimeOut);
	
	unsigned int ConstructAllData(unsigned char aucStr[], unsigned int unLen);
	unsigned int WriteChipIDToFlash(void);
	unsigned int EraseAllData(void);
	unsigned int CanStartUpgradeSN(void);
	
private:
	int m_nStatus;
	
	unsigned int m_WriteType;
	SerialBuf m_SerialBuf;
	UpgradeNotify * m_pUpgradeNotify;

	ListenConn m_ListenConn;

	SNConfig m_SNConfig;
	CommandData m_CommandData;
	IFCP m_IFCP;
};

#endif /* SERIALUPGRADE_H_ */
