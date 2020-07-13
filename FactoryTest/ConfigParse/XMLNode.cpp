#include "XMLNode.h"

#define HEXSYSTEM (16)
#define DECSYSTEM (10)

XMLNode::XMLNode(char *pTag, int nTagLen, char *pValue, int nValLen)
{
	memset(m_acTag, 0, sizeof(m_acTag));

	memset(m_acValue, 0, sizeof(m_acValue));

	if (pTag != NULL && nTagLen > 0 && nTagLen < sizeof(m_acTag))
	{
		memcpy(m_acTag, pTag, nTagLen);
	}

	if (pValue != NULL && nValLen > 0 && nValLen < sizeof(m_acValue))
	{
		memcpy(m_acValue, pValue, nValLen);
	}
}

XMLNode::~XMLNode()
{
	DelAllNode();
}

int XMLNode::IsSameTag(char *pTag, int nTagLen)
{
	int nRet = 0;

	if (pTag != NULL && nTagLen == strlen(m_acTag))
	{
		if (memcmp(pTag, m_acTag, nTagLen) == 0)
		{
			nRet = 1;
		}
	}

	return nRet;
}

int XMLNode::GetValue(char *pValue, int nValLen)
{
	int nRet = 0;

	if (pValue != NULL && nValLen > strlen(m_acValue))
	{
		memcpy(pValue, m_acValue, strlen(m_acValue));

		nRet = 1;
	}

	return nRet;
}

int XMLNode::SetTag(char *pTag, int nTagLen)
{
	int nRet = 0;

	if (pTag != NULL && nTagLen < sizeof(m_acTag))
	{
		memcpy(m_acTag, pTag, nTagLen);

		nRet = 1;
	}

	return nRet;
}

int XMLNode::SetValue(char *pValue, int nValLen)
{
	int nRet = 0;

	if (pValue != NULL && nValLen < sizeof(m_acValue))
	{
		memcpy(m_acValue, pValue, nValLen);

		nRet = 1;
	}

	return nRet;
}

int XMLNode::AddNode(char *pTag, int nTagLen, char *pValue, int nValLen)
{
	int nRet = 0;
	XMLNode *pXMLNode = new XMLNode(pTag, nTagLen, pValue, nValLen);

	if (pXMLNode != NULL)
	{
		m_pNodelist.push_back(pXMLNode);

		nRet = 1;
	}

	return nRet;
}

int XMLNode::AddNode(XMLNode *pXMLNode)
{
	int nRet = 0;

	if (pXMLNode != NULL)
	{
		m_pNodelist.push_back(pXMLNode);

		nRet = 1;
	}

	return nRet;
}

int XMLNode::DelAllNode(void)
{
	list<XMLNode*>::iterator cur;
	int ii = 0;

	for (ii, cur = m_pNodelist.begin(); ii < m_pNodelist.size(); ii++, cur++)
	{
		if ((*cur) != NULL)
		{
			delete (*cur);
		}
	}

	m_pNodelist.clear();

	return 1;
}

void XMLNode::PrintAll(int nDeep)
{
	int ii = 0;

	/*for (ii; ii < nDeep; ii++)
	{
		//printf("\t");
	}*/

	printf("%s:%s\n", m_acTag, m_acValue);

	if (m_pNodelist.size() > 0)
	{
		list<XMLNode*>::iterator cur;

		for (ii=0, cur = m_pNodelist.begin(); ii < m_pNodelist.size(); ii++, cur++)
		{
			if ((*cur) != NULL)
			{
				(*cur)->PrintAll(nDeep + 1);
			}
		}
	}
}

int XMLNode::GetValue(char *pTag, int nTagLen, char *pValue, int nValLen)
{
	int nRet = 0;
	int ii = 0;
	list<XMLNode*>::iterator cur;

	for (ii, cur = m_pNodelist.begin(); ii < m_pNodelist.size(); ii++, cur++)
	{
		if ((*cur)->IsSameTag(pTag, nTagLen))
		{
			if ((*cur)->GetValue(pValue, nValLen))
			{
				nRet = 1;
			}
		}
	}

	return nRet;
}

XMLNode *XMLNode::GetXMLNode(char *pTag, int nTagLen)
{
	int ii = 0;
	XMLNode *pTempXMLNode = NULL;
	list<XMLNode*>::iterator cur;

	for (ii, cur = m_pNodelist.begin(); ii < m_pNodelist.size(); ii++, cur++)
	{
		if ((*cur)->IsSameTag(pTag, nTagLen))
		{
			pTempXMLNode = *cur;

			break;
		}
	}

	return pTempXMLNode;
}

int XMLNode::GetValue(int *pValue, char *pTag, int nTagLen)
{
	int nRet = 0;
	int ii = 0;
	char acValue[32] = { 0 };
	list<XMLNode*>::iterator cur;

	for (ii, cur = m_pNodelist.begin(); ii < m_pNodelist.size(); ii++, cur++)
	{
		if ((*cur)->IsSameTag(pTag, nTagLen))
		{
			if ((*cur)->GetValue(acValue, sizeof(acValue)))
			{
				if (memcmp(acValue, "Test", strlen("Test")) == 0)
				{
					*pValue = 1;
				}
				else
				{
					*pValue = 0;
				}
				nRet = 1;
			}
		}
	}

	return nRet;
}

int XMLNode::GetValue(char *pTag, int nTagLen, int *pValue)
{
	int nRet = 0;
	int ii = 0;
	char acValue[32] = { 0 };
	list<XMLNode*>::iterator cur;

	for (ii, cur = m_pNodelist.begin(); ii < m_pNodelist.size(); ii++, cur++)
	{
		if ((*cur)->IsSameTag(pTag, nTagLen))
		{
			if ((*cur)->GetValue(acValue, sizeof(acValue)))
			{
				if (StringToNum(acValue, strlen(acValue), *pValue))
				{
					nRet = 1;
				}
			}
		}
	}

	return nRet;
}

unsigned int XMLNode::StringToNum(char *pBuffer, int nLen, int & nTemp)
{
	int ii = 0;
	int nType = DECSYSTEM;
	int nTempNum = 0;
	int nRetNum = 0;
	unsigned int unRet = 0;

	if (pBuffer != NULL)
	{
		if (nLen > 2)
		{
			if (pBuffer[0] == '0' && pBuffer[1] == 'x')
			{
				nType = HEXSYSTEM;
				ii += 2;
			}
		}
		for (ii; ii < nLen; ii++)
		{
			nTempNum = CharToNum(pBuffer[ii], nType);
			if (nTempNum == nType)
			{
				break;
			}
			nRetNum = nTempNum + nRetNum * nType;
		}
		if (ii == nLen)
		{
			unRet = 1;
		}
	}
	nTemp = nRetNum;

	return unRet;
}

unsigned int XMLNode::CharToNum(char cTemp, int nType)
{
	unsigned int unNum = nType;

	if (cTemp >= '0' && cTemp <= '9')
	{
		unNum = cTemp - '0';
	}
	else if (nType == HEXSYSTEM)
	{
		if (cTemp >= 'a' && cTemp <= 'f')
		{
			unNum = cTemp - 'a' + 10;
		}
		else if (cTemp >= 'A' && cTemp <= 'F')
		{
			unNum = cTemp - 'A' + 10;
		}
	}

	return unNum;
}