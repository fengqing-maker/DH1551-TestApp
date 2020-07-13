#ifndef COMMAND_DATA_H_
#define COMMAND_DATA_H_

#define MAX_DATA_LEN (16*1024)

class CommandData
{
public:
	int m_nCommand;
	int m_nDataLen;
	unsigned char m_aucData[MAX_DATA_LEN];
};

#endif/*COMMAND_DATA_H_*/

