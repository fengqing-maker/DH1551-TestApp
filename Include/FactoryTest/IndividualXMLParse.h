#ifndef INDIVIDUAL_XML_PARSE_H_
#define INDIVIDUAL_XML_PARSE_H_

#include "XMLNode.h"

class IndividualXMLParse
{
public:
	IndividualXMLParse();
	~IndividualXMLParse();

public:
	int ReadAndParseConfig(unsigned int unAddress, unsigned int unSize);
	int ReadAndParseConfig(char *pFileName, int nNameLen);
	int ConstructNodeList(char *pBuffer, int nBufLen, XMLNode *pXMLNode);
	int ConstructLeafNode(char *pBuffer, int nBufLen, XMLNode *pXMLNode);
	int ConstructFirstNode(char *pBuffer, int nBufLen);
	XMLNode *GetXMLNode(void);

private:
	int IsLeafNode(char *pBuffer, int nLen);
	int GetNodeName(char *pRes, int nResLen, char *pDest, int nDestLen);
	int GetNodeValue(char *pRes, int nResLen, char *pDest, int nDestLen);

private:
	XMLNode *m_pXMLNode;
	
	int m_ParentCount;
	int m_ChildCount;
};

#endif/*INDIVIDUAL_XML_PARSE_H_*/
