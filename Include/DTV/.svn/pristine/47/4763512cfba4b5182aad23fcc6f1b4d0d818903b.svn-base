/*
 * EPGSearchInterface.h
 *
 *  Created on: 2016-7-5
 *      Author: linc
 */

#ifndef EPGSEARCHINTERFACE_H_
#define EPGSEARCHINTERFACE_H_

#include "KeyBoradType.h"
#include "EPGSearchType.h"
#include "EPGSearchNotify.h"
#include "EventInfoInterface.h"

#define MAX_T9_INPUT_COUNT 5
#define MAX_FULL_INPUT_COUNT 64

class EPGSearchInterface
{

public:

	EPGSearchInterface( );
	virtual ~EPGSearchInterface( );

public:

	//StartSearch前必须先调用InitEventList
	virtual unsigned int InitEventList ( unsigned short usNetworkID ) = 0;
	
	virtual unsigned int SearchEPGByName(char acStr[], unsigned int unStrLen, KeyBoradType eKeyBoradType, unsigned int unCaseSensitive, unsigned int unFindExacty) = 0;
	virtual unsigned int SearchEPGByContentType(unsigned char ucContentLevel1, unsigned char ucContentLevel2, unsigned int unLevel2Enable) = 0;
	virtual unsigned int StopSearch ( ) = 0;
	
	virtual unsigned int GetSearchEventCount ( ) = 0;
    virtual EventInfoInterface * GetSearchEvent ( unsigned int unIndex ) = 0;

	virtual unsigned int AddEPGSearchNotify ( EPGSearchNotify * pEPGSearchNotify ) = 0;
	virtual unsigned int RemoveEPGSearchNotify ( EPGSearchNotify * pEPGSearchNotify ) = 0;
};

#endif /* EPGSEARCHINTERFACE_H_ */
