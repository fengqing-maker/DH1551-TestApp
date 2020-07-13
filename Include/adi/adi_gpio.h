#ifndef _ADI_GPIO_H_
#define _ADI_GPIO_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum
{
    EM_ADIGPIO_LEVEL_HIGH = 0,          //LEVEL on is equal to level high if not invert, but equal to level low if invert
    EM_ADIGPIO_LEVEL_LOW,             //LEVEL off iis equal to level low if not invert, but equal to level high if invert
} ADIGPIOLevel_E;

typedef enum
{
    EM_ADIGPIO_DIRECTION_OUTPUT = 0,
    EM_ADIGPIO_DIRECTION_INPUT,
} ADIGPIODirection_E;


ADI_Error_Code ADIGPIOSetLevel(int nGpio, ADIGPIOLevel_E eGpioLevel);


ADI_Error_Code ADIGPIOSetDirection(int nGpio, ADIGPIODirection_E eGpioDirection);


ADI_Error_Code ADIGPIOGetLevel(int nGpio, ADIGPIOLevel_E *eGpioLevel);


ADI_Error_Code ADIGPIOGetDirection(int nGpio, ADIGPIODirection_E *eGpioDirection);

#ifdef  __cplusplus
}
#endif

#endif

