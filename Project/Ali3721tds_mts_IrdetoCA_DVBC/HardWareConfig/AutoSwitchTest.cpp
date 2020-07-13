#include "AutoSwitchTest.h"
#include <string.h>

static SwitchInterfaceMode *g_sSwitchInterfaceMode = NULL;

SwitchInterfaceMode *GetSwitchInterfaceMode()
{
	if(g_sSwitchInterfaceMode == NULL)
	{
		g_sSwitchInterfaceMode = new SwitchInterfaceMode();

		g_sSwitchInterfaceMode->Init();
	}

	return g_sSwitchInterfaceMode;
}

int Dealwith22kMode(void)
{
	return GetSwitchInterfaceMode()->Switch22KMode();
}

ADITunerSwitchStatus_E Get22KMode(void)
{
	return GetSwitchInterfaceMode()->Get22KMode();
}

int DealwithTunerPolar(void)
{
	return GetSwitchInterfaceMode()->SwitchPolarMode();
}

ADITunerChannelPolar_E GetPolarMode(void)
{
	return GetSwitchInterfaceMode()->GetPolarMode();
}

int DealwithColorMode(void)
{
	return GetSwitchInterfaceMode()->SwitchColorMode();
}

ADIScartColorMod_E GetColorMode(void)
{
	return GetSwitchInterfaceMode()->GetColorMode();
}

int DealwithAspectRatio(void)
{
	return GetSwitchInterfaceMode()->SwitchDisplayMode();
}

ADIScartDisplayMod_E GetDisplayMode(void)
{
	return GetSwitchInterfaceMode()->GetDisplayMode();
}

int DealwithTunerPower(void)
{
	return GetSwitchInterfaceMode()->SwitchPowerEnable();
}

ADI_BOOL GetPowerEnable(void)
{
	return GetSwitchInterfaceMode()->GetPowerEnable();
}

