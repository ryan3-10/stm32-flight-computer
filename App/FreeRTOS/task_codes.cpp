#include "i2c_bus.h"
#include "task_codes.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

void i2cTask(void* i2cBus) {
	auto bus = static_cast<I2cBus*>(i2cBus);

	while (true) {
		bus->processNextReq();
	}
}




