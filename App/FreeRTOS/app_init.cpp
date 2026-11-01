#include "app_init.h"
#include "free_rtos_context.h"
#include "free_rtos_lock.h"
#include "free_rtos_queue.h"
#include "i2c_bus.h"
#include "memory_pool.h"
#include "requests.h"
#include "sht31.h"
#include "task_codes.h"
#include <FreeRTOS.h>
#include <task.h>

namespace {
	constexpr uint8_t QUEUE_SIZE = 10;
	FreeRtosQueue<I2cRequest, QUEUE_SIZE> i2cRequests;
	TaskHandle_t i2cTaskHandle;
	FreeRtosContext i2cContext(i2cTaskHandle);
	I2cBus i2cBus(i2cRequests, i2cContext);

	MemoryPool<uint8_t, 32> memPool;
	FreeRtosLock sht31Lock;
	Sht31 sht31(&sht31Lock, memPool);
}

// Called from the default task in main.c
void appInit(I2C_HandleTypeDef* hi2c) {
	i2cBus.bindHi2c(hi2c);
	i2cBus.submitRequest(sht31.txReq());
	i2cBus.submitRequest(sht31.rxReq());

	xTaskCreate(i2cTask, "I2C Task", 256, &i2cBus, 1, &i2cTaskHandle);
}


