#include "USBBackDoor.h"

static USBBackDoor *g_USBBackDoor = NULL;

void InitUSBBackDoor(unsigned int unByteFlag, unsigned int unFlashSize, char *pBacDoorFile)
{
	if( g_USBBackDoor == NULL )
	{
		g_USBBackDoor = new USBBackDoor(unByteFlag, unFlashSize, pBacDoorFile);
	}
}

void START_UPGRADE_8M(void)
{
}
