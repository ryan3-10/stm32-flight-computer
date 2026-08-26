#ifndef FREERTOS_APP_INIT_H_
#define FREERTOS_APP_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f4xx_hal.h>

// Called from the default task in main.c
void appInit(I2C_HandleTypeDef* hi2c);

#ifdef __cplusplus
}
#endif



#endif /* FREERTOS_APP_INIT_H_ */
