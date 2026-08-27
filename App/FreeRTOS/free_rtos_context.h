#ifndef FREERTOS_FREE_RTOS_CONTEXT_H_
#define FREERTOS_FREE_RTOS_CONTEXT_H_

#include "i_context.h"
#include <FreeRTOS.h>
#include <task.h>

class FreeRtosContext : public IContext {
public:
	FreeRtosContext(TaskHandle_t task) : m_task(task) {}

	void sleep() override {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}

	void awakeFromIsr() override {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(m_task, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}

private:
	TaskHandle_t m_task;
};



#endif /* FREERTOS_FREE_RTOS_CONTEXT_H_ */
