/*
 * FactoryTestNotify.h
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#ifndef FACTORYTESTNOTIFY_H_
#define FACTORYTESTNOTIFY_H_


class FactoryTestNotify
{
public:
	FactoryTestNotify();
	virtual ~FactoryTestNotify();

public:

	virtual void LivePlayNotify(unsigned int unSuccess) = 0;
	virtual void FrontPanelTestNotify(unsigned int unSuccess) = 0;
	virtual void SmartCardTestNotify(unsigned int unSuccess) = 0;
	virtual void USBTestNotify(unsigned int unSuccess) = 0;
	virtual void EthernetTestNotify(unsigned int unSuccess) = 0;

};

#endif /* FACTORYTESTNOTIFY_H_ */
