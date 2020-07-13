/*
 * ApplicationInterface.h
 *
 *  Created on: 2015-11-8
 *      Author: timothy.liao
 */

#ifndef APPLICATIONINTERFACE_H_
#define APPLICATIONINTERFACE_H_

class ApplicationInterface
{
public:
	ApplicationInterface();
	virtual ~ApplicationInterface();

public:

	virtual unsigned int GetIdentifier(unsigned int &runOrganizationID, unsigned short &rusApplicationID) = 0;
	virtual unsigned char GetControlCode() = 0;
	virtual unsigned int GetProfileCount() = 0;
	virtual unsigned int GetProfile(unsigned int unProfileIndex, unsigned short &rusProfile, unsigned char &rucVerMajor, unsigned char &rucVerMinor, unsigned char &rucVerMicro) = 0;
	virtual unsigned char GetServiceBoundFlag() = 0;
	virtual unsigned char GetVisibility() = 0;
	virtual unsigned char GetPriority() = 0;
	virtual unsigned char GetUsageType() = 0;
	
	virtual unsigned int GetTransportProtocolLabelCount() = 0;
	virtual unsigned char GetTransportProtocolLabel(unsigned int unIndex) = 0;
	
	virtual unsigned int GetBoundaryExtensionCount() = 0;
	virtual unsigned int GetBoundaryExtensionBytes(unsigned int unIndex, char acBoundaryExtBytes[], unsigned int unSize) = 0;
	
	virtual unsigned int GetApplicationName(char acName[], unsigned int unSize) = 0;
	virtual unsigned int GetApplicationLanguageCode(char LanguageCode[], unsigned int unSize) = 0;
	
	virtual unsigned int GetTransportProtocolCount() = 0;
	virtual unsigned short GetTransportProtocolID(unsigned int unIndex) = 0;
	virtual unsigned int GetTransportProtocolICURLCount(unsigned int unIndex) = 0;
	virtual unsigned int GetTransportProtocolICURL(unsigned int unProtocolIndex, unsigned int unURLIndex, char acURL[], unsigned int unSize) = 0;
	virtual unsigned int GetTransportProtocolOCComponent(unsigned int unIndex, unsigned short &rusOriNetworkID, unsigned short &rusTSID, unsigned short &rusServiceID, unsigned char &rucComponentTag) = 0;
	virtual unsigned int GetTransportProtocolOCRCFlag(unsigned int unIndex) = 0;

	virtual unsigned int GetApplicationInitialPath(char acInitialPath[], unsigned int unSize) = 0;

};

#endif /* APPLICATIONPROFILE_H_ */
