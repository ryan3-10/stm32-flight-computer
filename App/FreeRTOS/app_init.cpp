#include "app_init.h"
#include "callbacks.h"
#include "i2c_bus.h"
#include "i2c_device.h"
#include "requests.h"
#include "task_codes.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

namespace {
	constexpr uint8_t QUEUE_SIZE = 10;
	TaskHandle_t i2cTask;
	QueueHandle_t i2cQueue;
}

// Called from the default task in main.c
void appInit(I2C_HandleTypeDef* hi2c) {
	I2cBus::init(hi2c);
	I2cBus::instance().registerCallbacks(notifyTaskFromISR, i2cTask);

	i2cQueue = xQueueCreate(QUEUE_SIZE, sizeof(I2cRequest*));
	xTaskCreate(workI2cQueue, "workI2cQueue", 256, &i2cQueue, 1, &i2cTask);
}



