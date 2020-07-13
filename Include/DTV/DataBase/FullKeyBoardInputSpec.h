/*
 * FullKeyBoardInputSpec.h
 *
 *  Created on: 2016-8-15
 *      Author: linc
 */

#ifndef FULLKEYBOARDINPUTSPEC_H_
#define FULLKEYBOARDINPUTSPEC_H_


#include "KeyBoardInputSpec.h"


class FullKeyBoardInputSpec : public KeyBoardInputSpec
{

public:

	FullKeyBoardInputSpec();
	virtual ~FullKeyBoardInputSpec();

public:

	unsigned int GetOutputStr(char acInputStr[], unsigned int unInputStrLen, vector< char * > & outputStrList);

};

#endif /* FULLKEYBOARDINPUTSPEC_H_ */
