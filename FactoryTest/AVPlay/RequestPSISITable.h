#ifndef REQUEST_PSI_SI_TABLE_H_
#define REQUEST_PSI_SI_TABLE_H_

#include "APSafeThread.h"
#include "adi_tuner.h"
#include "RequestTableNotify.h"
#include "APLock.h"

class RequestPSISITable : public APSafeThread
{
public:
	RequestPSISITable(unsigned int unPID, unsigned int unTunerID, RequestTableNotify *pRequestTableNotify);
	~RequestPSISITable();

public:
	void OnceProcess();
	unsigned int StartLock(ADITunerSRCDeliver_U* pDelivery);
	unsigned int SectionReceive(unsigned int nPid, unsigned int unBufSize);
	unsigned int ListenSectionData(ADI_HANDLE hFilterSignal);
	unsigned int StopListen(void);
	unsigned int StartFilter(void);

private:
	unsigned int m_unPID;
	unsigned int m_unTunerID;
	ADI_HANDLE m_hFilterSignal;
	RequestTableNotify *m_pRequestTableNotify;
	unsigned int m_unLockStatus;
	APLock m_APLock;
	ADI_HANDLE m_hFilterHandle;
	ADITunerSRCDeliver_U m_curLockDelivery;
};

#endif/*REQUEST_PSI_SI_TABLE_H_*/
