#include "i2c_bus.h"
#include "task_codes.h"
#include <FreeRTOS.h>
#include <print_debugging.h>
#include <queue.h>
#include <task.h>

namespace {
	I2cBus* g_i2cBus = nullptr;
}

void i2cTask(void* i2cBus) {
	g_i2cBus = static_cast<I2cBus*>(i2cBus);

	while (true) {
		g_i2cBus->processNextReq();
	}
}


extern "C" {
    void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef*) {
    	if (g_i2cBus)
    		g_i2cBus->handleDmaCompleteIsr();
    }

    void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef*) {
    	if (g_i2cBus)
    		g_i2cBus->handleDmaCompleteIsr();
    }
}

