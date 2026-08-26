#ifndef FREERTOS_CALLBACKS_H_
#define FREERTOS_CALLBACKS_H_

#include <FreeRTOS.h>
#include <task.h>

inline void notifyTaskFromISR(void* task) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	TaskHandle_t taskToNotify = static_cast<TaskHandle_t>(task);

	if (taskToNotify != nullptr) {
		// Notify the waiting task from the ISR context
		vTaskNotifyGiveFromISR(taskToNotify, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

#endif /* FREERTOS_CALLBACKS_H_ */
