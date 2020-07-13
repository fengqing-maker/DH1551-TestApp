/*
 * FrontPanelNotify.h
 *
 *  Created on: 2015-8-15
 *      Author: timothy.liao
 */

#ifndef FRONTPANELNOTIFY_H_
#define FRONTPANELNOTIFY_H_

class FrontPanelNotify
{
public:
	FrontPanelNotify();
	virtual ~FrontPanelNotify();

public:

	virtual void FrontPanelTestFinish(unsigned int unSuccess) = 0;

};

#endif /* FRONTPANELNOTIFY_H_ */
