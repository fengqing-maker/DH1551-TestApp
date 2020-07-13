

#ifndef ETHERNETNOTIFY_H_
#define ETHERNETNOTIFY_H_
#include "adi_fs.h"

class EthernetNotify
{
public:
	EthernetNotify();
	virtual ~EthernetNotify();

public:

	virtual void EthernetReadyNotify() = 0;
	virtual void EthernetNotReadyNotify() = 0;

};

#endif /* ETHERNETNOTIFY_H_ */


