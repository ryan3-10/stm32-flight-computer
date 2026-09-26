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
	TaskHandle_t i2cTaskHandle;
	FreeRtosContext i2cContext(i2cTaskHandle);
	FreeRtosQueue<I2cRequest, QUEUE_SIZE> i2cRequests;
	MemoryPool<uint8_t, 32> memPool;
	FreeRtosLock sht31Lock;
	Sht31 sht31(&sht31Lock, memPool);
}

// Called from the default task in main.c
void appInit(I2C_HandleTypeDef* hi2c) {
	I2cBus::instance().init(hi2c, &i2cContext, &i2cRequests);
	I2cBus::instance().submitRequest(sht31.txReq());
	I2cBus::instance().submitRequest(sht31.rxReq());

	xTaskCreate(i2cTask, "I2C Task", 256, &I2cBus::instance(), 1, &i2cTaskHandle);
}


