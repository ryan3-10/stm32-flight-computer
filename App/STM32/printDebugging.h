#ifndef PRINTDEBUGGING_H_
#define PRINTDEBUGGING_H_

#include <stm32f4xx_hal.h>
#include <string.h>

extern UART_HandleTypeDef huart2;

void print(const char* text) {
	HAL_UART_Transmit(&huart2, (uint8_t*)text, strlen(text), HAL_MAX_DELAY);
}



#endif /* PRINTDEBUGGING_H_ */
