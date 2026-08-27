#include "i_lock.h"
#include <FreeRTOS.h>
#include <semphr.h>

#ifndef FREERTOS_FREE_RTOS_LOCK_H_
#define FREERTOS_FREE_RTOS_LOCK_H_

class FreeRtosLock : public ILock {
public:
	FreeRtosLock() : m_mutex(xSemaphoreCreateMutex()) {
		configASSERT(m_mutex != NULL);
	}

	~FreeRtosLock() {
		vSemaphoreDelete(m_mutex);
	}

	FreeRtosLock(const FreeRtosLock&) = delete;
	FreeRtosLock& operator=(const FreeRtosLock&) = delete;

	void lock() override {
		if (m_mutex != nullptr) {
			xSemaphoreTake(m_mutex, portMAX_DELAY);
		}
	}

	void unlock() override {
		if (m_mutex != nullptr) {
			xSemaphoreGive(m_mutex);
		}
	}

private:
	SemaphoreHandle_t m_mutex = nullptr;
};



#endif /* FREERTOS_FREE_RTOS_LOCK_H_ */
