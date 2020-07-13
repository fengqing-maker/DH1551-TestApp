#include "TransportProtocol.h"
#include "string.h"

#define FACTORY_HEAD (0xEF)
#define FACTORY_TAIL (0xFE)
#define IGNORE_COMMAND (0xFFFF)

#define CRC_FLAG 0xEDB88320


TransportProtocol::TransportProtocol()
{
}

TransportProtocol::~TransportProtocol()
{
}

//data struct:head(1B)+command(1B)+len(2B)+data(nB)+tail(1B)+CRC(4B)=(9+n)B (n>=0)
int TransportProtocol::ConstructData(unsigned char *pResData, unsigned int unResLen, unsigned int unCommand, unsigned char *pDestData, unsigned int unDestLen)
{
	int unRet = 0;
	int unIndex = 0;
	unsigned int unCrc = 0;

	if (unResLen + MIN_FACTORY_LEN <= unDestLen)
	{
		pDestData[unIndex++] = FACTORY_HEAD;
		pDestData[unIndex++] = (unsigned char)(unCommand & 0xff);
		pDestData[unIndex++] = (unsigned char)((unResLen >> 8) & 0xff);
		pDestData[unIndex++] = (unsigned char)(unResLen & 0xff);

		if (unResLen > 0 && pResData != NULL)
		{
			memcpy(&pDestData[unIndex], pResData, unResLen);

			unIndex += unResLen;
		}

		pDestData[unIndex++] = FACTORY_TAIL;
		unCrc = CalculateCRC32(pDestData, unIndex);
		pDestData[unIndex++] = (unsigned char)((unCrc >> 24) & 0xff);
		pDestData[unIndex++] = (unsigned char)((unCrc >> 16) & 0xff);
		pDestData[unIndex++] = (unsigned char)((unCrc >> 8) & 0xff);
		pDestData[unIndex++] = (unsigned char)(unCrc & 0xff);

		unRet = unIndex;
	}

	return unRet;
}

int TransportProtocol::PraseData(unsigned char *pResData, unsigned int unResLen, unsigned int unCommand)
{
	int nRet = -1;
	unsigned int unIndex = 0;
	unsigned int unDataLen = 0;
	unsigned int unOrgCrc = 0;
	unsigned int unCrc = 0;

	while (unResLen >= MIN_FACTORY_LEN + unIndex)
	{
		if (pResData[unIndex] == FACTORY_HEAD)
		{
			if (pResData[unIndex + 1] == unCommand || IGNORE_COMMAND == unCommand)
			{
				unDataLen = (unsigned int)((pResData[unIndex + 2] << 8) | pResData[unIndex + 3]);
				if (unDataLen + MIN_FACTORY_LEN + unIndex <= unResLen)
				{
					if (pResData[unIndex + unDataLen + 4] == FACTORY_TAIL)
					{
						unCrc = CalculateCRC32(&pResData[unIndex], unDataLen + MIN_HEAD_LEN);

						unOrgCrc |= (unsigned int)(pResData[unIndex + unDataLen + MIN_HEAD_LEN] << 24);
						unOrgCrc |= (unsigned int)(pResData[unIndex + unDataLen + MIN_HEAD_LEN + 1] << 16);
						unOrgCrc |= (unsigned int)(pResData[unIndex + unDataLen + MIN_HEAD_LEN + 2] << 8);
						unOrgCrc |= (unsigned int)(pResData[unIndex + unDataLen + MIN_HEAD_LEN + 3]);

						if (unOrgCrc == unCrc)
						{
							nRet = unIndex;
							break;
						}
						else
						{
							unOrgCrc = 0;
							unCrc = 0;
						}
					}
				}
			}
		}
		unIndex++;
	}

	return nRet;
}

int TransportProtocol::PraseData(unsigned char *pResData, unsigned int unResLen)
{
	return PraseData(pResData, unResLen, IGNORE_COMMAND);
}

unsigned int TransportProtocol::CalculateCRC32(BYTE * pbData, unsigned int unLength)
{
	unsigned int ii = 0;
	unsigned int jj = 0;
	unsigned int dwCRC = 0;
	unsigned int dwCrc32 = 0xffffffff;

	for ( ii = 0; ii < unLength; ii++ )
	{
		for ( jj = 0; jj < 8; jj++ )
		{
			if (((pbData[ii] >> (7 - jj)) & 0x01))
				dwCrc32 ^= 1;

			if (dwCrc32 & 1)
				dwCrc32 = ((dwCrc32 >> 1) ^ CRC_FLAG);
			else
				dwCrc32 >>= 1;
		}
	}

	for (ii = 0; ii<32; ii++)
	{
		if ((dwCrc32 >> ii) & 1)
		{
			dwCRC <<= 1;
			dwCRC |= 1;
		}
		else
		{
			dwCRC <<= 1;
		}
	}

	return dwCRC;
}