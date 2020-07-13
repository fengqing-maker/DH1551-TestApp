/*
 * LanguageCode.h
 *
 *  Created on: 2015-9-19
 *      Author: timothy.liao
 */

#ifndef LANGUAGECODE_H_
#define LANGUAGECODE_H_

class LanguageCode
{
public:
	LanguageCode();
	virtual ~LanguageCode();

public:

	unsigned int GetLanguageIndex(char acLanguageCode[3], unsigned int &runIndex);
	unsigned int GetLanguage(char acLanguageCode[3], char* pcLanguage, unsigned int unLength);

};

#endif /* LANGUAGECODE_H_ */
