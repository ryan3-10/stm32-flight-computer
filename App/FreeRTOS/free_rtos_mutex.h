#include <FreeRTOS.h>
#include <i_mutex.h>
#include <semphr.h>

#ifndef FREERTOS_FREE_RTOS_LOCK_H_
#define FREERTOS_FREE_RTOS_LOCK_H_

class FreeRtosMutex : public IMutex {
public:
	FreeRtosMutex() : m_mutex(xSemaphoreCreateMutex()) {
		configASSERT(m_mutex != NULL);
	}

	~FreeRtosMutex() {
		vSemaphoreDelete(m_mutex);
	}

	FreeRtosMutex(const FreeRtosMutex&) = delete;
	FreeRtosMutex& operator=(const FreeRtosMutex&) = delete;

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
