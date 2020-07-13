#ifndef READ_STB_AND_CARDID_H_
#define READ_STB_AND_CARDID_H_

int ReadCardID(char *pBuffer, int nLen);

int ReadSTBID(char *pBuffer, int nLen);

int IsCaDataBurned(void);

int GetCardStatus(void);

#endif/*READ_STB_AND_CARDID_H_*/
