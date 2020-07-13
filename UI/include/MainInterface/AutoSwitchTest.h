#ifndef AUTO_SWITCH_TEST_H_
#define AUTO_SWITCH_TEST_H_

#include "SwitchInterfaceMode.h"

int Dealwith22kMode(void);
ADITunerSwitchStatus_E Get22KMode(void);

int DealwithTunerPolar(void);
ADITunerChannelPolar_E GetPolarMode(void);

int DealwithColorMode(void);
ADIScartColorMod_E GetColorMode(void);

int DealwithAspectRatio(void);
ADIScartDisplayMod_E GetDisplayMode(void);

int DealwithTunerPower(void);
ADI_BOOL GetPowerEnable(void);

#endif/*AUTO_SWITCH_TEST_H_*/
