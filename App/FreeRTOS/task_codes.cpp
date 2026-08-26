#include "i2c_bus.h"
#include "requests.h"
#include "task_codes.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

void workI2cQueue(void* queue) {
	auto i2cQueue = static_cast<QueueHandle_t>(queue);
	I2cRequest* req;

	while (true) {
		xQueueReceive(i2cQueue, &req, portMAX_DELAY);
		I2cBus::instance().processRequest(*req);
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Sleep until DMA complete
	}
}




