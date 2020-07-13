#include "IndividualXMLParse.h"
#include "adi_os.h"
#include "adi_flash.h"
#include "adi_fs.h"


IndividualXMLParse::IndividualXMLParse()
{
	m_ParentCount = 0;

	m_ChildCount = 0;

	m_pXMLNode = NULL;
}

IndividualXMLParse::~IndividualXMLParse()
{
	if (m_pXMLNode != NULL)
	{
		delete m_pXMLNode;

		m_pXMLNode = NULL;
	}
}

int IndividualXMLParse::ReadAndParseConfig(unsigned int unAddress, unsigned int unSize)
{
	int nRet = 0;
	char *pucTempBuf = NULL;
	int nLen = 0;

	do
	{
		pucTempBuf = (char*)ADIOSMalloc(unSize);
		if(pucTempBuf == NULL)
		{
			printf("***Malloc Memery Fail***\n");
			break;
		}
		
		if(ADIFlashRead(unAddress, (unsigned char *)pucTempBuf, unSize) != ADI_SUCCESS)
		{
			printf("***ADIFlashRead Fail***\n");
			break;
		}

		nLen = ConstructFirstNode(pucTempBuf, unSize);
		if(nLen == 0)
		{
			printf("***ConstructFirstNode Fail***\n");
			break;
		}

		if(ConstructNodeList(&pucTempBuf[nLen], unSize - nLen, m_pXMLNode) == 0)
		{
			printf("***ConstructNodeList Fail***\n");
			break;
		}

		//m_pXMLNode->PrintAll(0);

		nRet = 1;
		
	}while(0);

	if(pucTempBuf != NULL)
	{
		ADIOSFree(pucTempBuf);
	}

	return nRet;
}

int IndividualXMLParse::ReadAndParseConfig(char *pFileName, int nNameLen)
{
	int nRet = 0;
	char *pcTempBuf = NULL;
	int nLen = 0;
	ADI_HANDLE TsFile = NULL;
	unsigned int nSize = 0;

	do
	{
		if (pFileName == NULL || nNameLen <= 0)
		{
			printf("file name can not be null\n");
			break;
		}
		
		TsFile = ADIFSOpen( pFileName,"rb" );
		if ( NULL == TsFile )
		{
			printf("***Fail to Open File:%s***\n", pFileName);
			break;
		}

		ADIFSSeek( TsFile, 0, ADIFS_SEEK_END );
		nSize = (int)ADIFSTell( TsFile );
		if(nSize <= 0)
		{
			printf("***File:%s Data Len is 0***\n", pFileName);
			break;
		}
		ADIFSSeek( TsFile, 0, ADIFS_SEEK_SET );
		
		pcTempBuf = (char*)ADIOSMalloc(nSize);
		if(pcTempBuf == NULL)
		{
			printf("***Malloc Memery Fail***\n");
			break;
		}
		
		if(ADIFSRead(TsFile, pcTempBuf, nSize) <= 0)
		{
			printf("***ADIFSRead Fail***\n");
			break;
		}

		nLen = ConstructFirstNode(pcTempBuf, nSize);
		if(nLen == 0)
		{
			printf("***ConstructFirstNode Fail***\n");
			break;
		}

		if(ConstructNodeList(&pcTempBuf[nLen], nSize - nLen, m_pXMLNode) == 0)
		{
			printf("***ConstructNodeList Fail***\n");
			break;
		}

		//m_pXMLNode->PrintAll(0);

		nRet = 1;
		
	}while(0);

	if(pcTempBuf != NULL)
	{
		ADIOSFree(pcTempBuf);
	}

	if ( TsFile != NULL )
	{
		ADIFSClose( TsFile );
	}

	return nRet;

}

int IndividualXMLParse::ConstructFirstNode(char *pBuffer, int nBufLen)
{
	int nRet = 0;
	int nNodeType = 0;
	char acNodeName[32] = { 0 };
	char acValue[32] = { 0 };

	if (pBuffer != 0 && nBufLen > 0)
	{
		for (int ii = 0; ii < nBufLen - 1; ii++)
		{
			if (pBuffer[ii] == '<' && pBuffer[ii + 1] != '/')
			{
				ii++;
				nNodeType = IsLeafNode(&pBuffer[ii], nBufLen - ii); 
				if (nNodeType == 0)
				{
					break;
				}
				nRet = GetNodeName(&pBuffer[ii], nBufLen - ii, acNodeName, sizeof(acNodeName));
				if(nRet == 0)
				{
					break;
				}
				
				ii += ( nRet + 1 );
				if(nNodeType == 1)
				{
					nRet = GetNodeValue(&pBuffer[ii], nBufLen - ii, acValue, sizeof(acValue));
					ii += ( nRet + strlen(acNodeName) + 3 );
				}
				
				m_pXMLNode = new XMLNode(acNodeName, strlen(acNodeName), acValue, strlen(acValue));
				nRet = ii;
				break;
			}
		}
	}

	return nRet;
}

XMLNode *IndividualXMLParse::GetXMLNode(void)
{
	return m_pXMLNode;
}

int IndividualXMLParse::ConstructNodeList(char *pBuffer, int nBufLen, XMLNode *pXMLNode)
{
	int nRet = 0;
	int nNodeType = 0;
	int ii = 0;

	if (pBuffer != 0 && nBufLen > 0)
	{
		for (ii = 0; ii < nBufLen - 1; ii++)
		{
			if (pBuffer[ii] == '<' && pBuffer[ii + 1] != '/')
			{
				nNodeType = IsLeafNode(&pBuffer[ii + 1], nBufLen - ii - 1); 
				if (nNodeType == 0)
				{
					break;
				}
				else if (nNodeType == 1)
				{
					m_ChildCount++;
					nRet = ConstructLeafNode(&pBuffer[ii + 1], nBufLen - ii - 1, pXMLNode);
					if (nRet == 0)
					{
						break;
					}
					ii += (nRet + 1);
				}
				else if (nNodeType == 2)
				{
					m_ParentCount++;
					char acTag[32] = { 0 };
					XMLNode *pTemp = NULL;
					nRet = GetNodeName(&pBuffer[ii + 1], nBufLen - ii - 1, acTag, sizeof(acTag));
					
					pTemp = new XMLNode(acTag, strlen(acTag), NULL, 0);
					pXMLNode->AddNode(pTemp);

					nRet = ConstructNodeList(&pBuffer[ii + 1], nBufLen - ii - 1, pTemp);
					if (nRet == 0)
					{
						break;
					}
					ii += nRet;
				}
			}
			else if (pBuffer[ii] == '<' && pBuffer[ii + 1] == '/')
			{
				char acTag[32] = { 0 };
				nRet = GetNodeName(&pBuffer[ii + 2], nBufLen - ii - 2, acTag, sizeof(acTag));

				if (nRet == 0)
				{
					break;
				}

				if (pXMLNode->IsSameTag(acTag, strlen(acTag)))
				{
					nRet = (ii + 2 + strlen(acTag) + 1);
					break;
				}
			}
		}
	}

	return nRet;
}

int IndividualXMLParse::ConstructLeafNode(char *pBuffer, int nBufLen, XMLNode *pXMLNode)//leaf
{
	char acNodeName[32] = { 0 };
	char acValue[32] = { 0 };
	int nLen = 0;
	int nRet = 0;

	do
	{
		nRet = GetNodeName(pBuffer, nBufLen, acNodeName, sizeof(acNodeName));
		if (nRet == 0)
		{
			break;
		}
		nLen += (nRet + 1);

		nRet = GetNodeValue(&pBuffer[nLen], nBufLen - nLen, acValue, sizeof(acValue));
		if (nRet == 0)
		{
			//break;
		}
		nLen += nRet;

		pXMLNode->AddNode(acNodeName, strlen(acNodeName), acValue, strlen(acValue));

		nRet = nLen;
	} while (0);

	return nRet;
}

int IndividualXMLParse::IsLeafNode(char *pBuffer, int nLen)
{
	int nRet = 0;

	if (pBuffer != NULL && nLen > 0)
	{
		int ii = 0;
		while (ii < nLen-1)
		{
			if (pBuffer[ii] == '<')
			{
				if (pBuffer[ii + 1] == '/')
				{
					nRet = 1;
				}
				else
				{
					nRet = 2;
				}
				break;
			}
			ii++;
		}
	}

	return nRet;
}

int IndividualXMLParse::GetNodeName(char *pRes, int nResLen, char *pDest, int nDestLen)
{
	int ii = 0;

	while (pRes[ii] != '>')
	{
		if (ii > nDestLen)
		{
			ii = 0;
			break;
		}

		pDest[ii] = pRes[ii];
		ii++;
	}

	return ii;
}

int IndividualXMLParse::GetNodeValue(char *pRes, int nResLen, char *pDest, int nDestLen)
{
	int ii = 0;

	while (pRes[ii] != '<')
	{
		if (ii > nDestLen)
		{
			ii = 0;
			break;
		}

		pDest[ii] = pRes[ii];
		ii++;
	}

	return ii;
}
