/*
 * KeyInterface.h
 *
 *  Created on: 2015-4-29
 *      Author: timothy.liao
 */

#ifndef KEYINTERFACE_H_
#define KEYINTERFACE_H_

class KeyInterface
{
public:
	KeyInterface();
	virtual ~KeyInterface();

public:

	virtual void OpenKey() = 0;
	virtual void CloseKey() = 0;
};

#endif /* KEYINTERFACE_H_ */
