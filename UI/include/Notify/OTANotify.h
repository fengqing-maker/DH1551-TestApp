#ifndef _OTANOTIFY_H
#define _OTANOTIFY_H

class OTANotify
{
public:
	OTANotify();
	virtual ~OTANotify();
	
	void OTAStart(int nResult);
	void StartWriteCore(int nResult);
	void StartWriteRC(int nResult);
	void StartWriteApp(int nResult);
	void StartOpenHL(int nResult);
};

#endif