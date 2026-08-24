#include "app_tasks.h"
#include "I2CDevice.h"
#include "printDebugging.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <stm32f4xx_hal.h>

namespace {
	QueueHandle_t i2cQueue;
}

void workI2cQueue(void* i2cHandle) {
	I2CDevice* device;
	auto hi2c = static_cast<I2C_HandleTypeDef*>(i2cHandle);

	while (true) {
		xQueueReceive(i2cQueue, &device, portMAX_DELAY);
		// transmit DMA
		HAL_I2C_Master_Transmit_DMA(hi2c, device->address(), device->txBuffer(), device->txLength());
		// sleep
		// receive DMA
		// sleep
	}
}

// Called from the default task in main.c
void appInit(I2C_HandleTypeDef* hi2c) {
	print("test test 123");
	i2cQueue = xQueueCreate(10, sizeof(I2CDevice*));

	xTaskCreate(workI2cQueue, "workI2cQueue", 256, hi2c, 1, nullptr);
}



