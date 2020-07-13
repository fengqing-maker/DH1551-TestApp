/* TestAppNotify.h
 *
 *  Created on: 2015-7-15
 *      Author: gongjinjun
 */
 
#ifndef TESTAPPNOTIFY_H_
#define TESTAPPNOTIFY_H_

#include "FactoryTestNotify.h"

class TestAppNotify : public FactoryTestNotify
{

public:	
	TestAppNotify();
	~TestAppNotify();

public:
	void LivePlayNotify(unsigned int unSuccess);
	void FrontPanelTestNotify(unsigned int unSuccess);
	void SmartCardTestNotify(unsigned int unSuccess);
	void USBTestNotify(unsigned int unSuccess);
	void EthernetTestNotify(unsigned int unSuccess);
};

#endif //TESTAPPNOTIFY_H_

