#ifndef SMC_CONFIG_H_
#define SMC_CONFIG_H_

typedef enum
{
	CLOAKED_CARD,
	CIPLUS_CARD,
	IRDETO_B_CARD,
	IRDETO_S_CARD,
	ALI_CARD,
	TONGFANG_CARD,
	INVALID_CARD
} CARD_TYPE;

class SMCConfig
{
public:
	void SetDefaultConfig(void);
	
public:
	int m_nCAType;
};

#endif/*SMC_CONFIG_H_*/