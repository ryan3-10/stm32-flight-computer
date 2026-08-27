#ifndef STM32_I2C_BUS_H_
#define STM32_I2C_BUS_H_

#include "i_context.h"
#include "i_queue.h"
#include "requests.h"
#include <stm32f4xx_hal.h>

class I2cBus {

public:
	static I2cBus& instance() { return *s_instance; }
	void init(I2C_HandleTypeDef* hi2c, IContext* context, IQueue<I2cRequest>* queue);
	void processNextReq();
	void submitRequest(const I2cRequest req) { m_queue->push(req); }
	void handleDmaCompleteIsr();

private:
	I2cBus() = default;
	~I2cBus() = default;
	I2cBus(const I2cBus&) = delete;
	I2cBus& operator=(const I2cBus&) = delete;

	inline static I2cBus* s_instance = nullptr;
	I2C_HandleTypeDef*  m_hi2c = nullptr;
	IContext* m_context = nullptr;
	IQueue<I2cRequest>* m_queue = nullptr;
};

#endif /* STM32_I2C_BUS_H_ */
