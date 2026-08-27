#include "app_init.h"
#include "free_rtos_context.h"
#include "free_rtos_lock.h"
#include "free_rtos_queue.h"
#include "i2c_bus.h"
#include "requests.h"
#include "task_codes.h"
#include <FreeRTOS.h>
#include <task.h>

namespace {
	constexpr uint8_t QUEUE_SIZE = 10;
	TaskHandle_t i2cTask;
	FreeRtosContext i2cContext(i2cTask);
	FreeRtosQueue<I2cRequest, QUEUE_SIZE> i2cRequests;
}

// Called from the default task in main.c
void appInit(I2C_HandleTypeDef* hi2c) {
	I2cBus::instance().init(hi2c, &i2cContext, &i2cRequests);
	xTaskCreate(workI2cQueue, "workI2cQueue", 256, &I2cBus::instance(), 1, &i2cTask);
}



