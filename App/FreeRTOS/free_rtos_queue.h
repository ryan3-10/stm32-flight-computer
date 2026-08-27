#ifndef FREERTOS_FREE_RTOS_QUEUE_H_
#define FREERTOS_FREE_RTOS_QUEUE_H_

#include "i_queue.h"
#include <cstddef>
#include <FreeRTOS.h>
#include <queue.h>
#include <utility>

template <typename T, size_t Size>
class FreeRtosQueue : public IQueue<T> {
public:
	FreeRtosQueue<T, Size>() : m_queue(xQueueCreate(Size, sizeof(T))) {
		configASSERT(m_queue != nullptr);
	}

	~FreeRtosQueue<T, Size>() {
		vQueueDelete(m_queue);
	}

	void push(T item) override {
		xQueueSend(m_queue, &item, portMAX_DELAY);
	}

	T pop() override {
	    // Allocate raw uninitialized memory with correct alignment for T
	    alignas(T) unsigned char buffer[sizeof(T)];

	    // Copy raw bytes into our uninitialized buffer
	    xQueueReceive(m_queue, buffer, portMAX_DELAY);

	    // Move/Copy construct the object into the return value slot
	    T* itemPtr = reinterpret_cast<T*>(buffer);
	    T item(std::move(*itemPtr));

	    // Destroy the temporary object inside the buffer
	    itemPtr->~T();

	    return item;
	}
private:
	QueueHandle_t m_queue = nullptr;
};

#endif /* FREERTOS_FREE_RTOS_QUEUE_H_ */
