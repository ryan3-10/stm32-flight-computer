#include "app_init.h"
#include "dma_i2c_bus.h"
#include "free_rtos_context.h"
#include "free_rtos_mutex.h"
#include <FreeRTOS.h>
#include <task.h>
#include <task_functions.h>

namespace {
	FreeRtosContext i2cContext;
	FreeRtosMutex i2cMutex;
}

// Called from the default task in main.c
void appInit(I2C_HandleTypeDef* hi2c) {
	static DmaI2cBus i2cBus(hi2c, i2cContext, i2cMutex);
	TaskFunctions::initBusses(&i2cBus);
	TaskFunctions::initTasks();
}


