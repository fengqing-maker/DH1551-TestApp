#ifndef SWITCH_INTERFACE_MODE_H_
#define SWITCH_INTERFACE_MODE_H_

#include "adi_tuner.h"
#include "adi_scart.h"

class SwitchInterfaceMode
{
public:
	SwitchInterfaceMode();
	~SwitchInterfaceMode();
	
public:
	int Init(void);
	ADITunerSwitchStatus_E Get22KMode(void);
	ADITunerChannelPolar_E GetPolarMode(void);
	ADIScartColorMod_E GetColorMode(void);
	ADIScartDisplayMod_E GetDisplayMode(void);
	ADI_BOOL GetPowerEnable(void);
	int Switch22KMode(void);
	int SwitchPolarMode(void);
	int SwitchColorMode(void);
	int SwitchDisplayMode(void);
	int SwitchPowerEnable(void);
	int StartTuner(ADITunerSwitchStatus_E enTuner22k, ADITunerChannelPolar_E enPolar);

private:
	ADITunerSwitchStatus_E m_en22K;
	ADITunerChannelPolar_E m_enPolar;
	ADIScartColorMod_E m_enColor;
	ADIScartDisplayMod_E m_enDisplay;
	ADI_BOOL m_bPower;
};

#endif/*SWITCH_INTERFACE_MODE_H_*/
