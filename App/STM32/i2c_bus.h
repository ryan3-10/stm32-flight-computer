#ifndef STM32_I2C_BUS_H_
#define STM32_I2C_BUS_H_

#include "i_context.h"
#include "i_queue.h"
#include "requests.h"
#include <stm32f4xx_hal.h>

class I2cBus {

public:
	I2cBus(IQueue<I2cRequest>& queue, IContext& context) : m_queue(queue), m_context(context)
	{}

	~I2cBus() = default;
	I2cBus(const I2cBus&) = delete;
	I2cBus& operator=(const I2cBus&) = delete;

	void bindHi2c(I2C_HandleTypeDef* hi2c) { m_hi2c = hi2c; }
	void processNextReq();
	void submitRequest(const I2cRequest req) { m_queue.push(req); }
	void handleDmaCompleteIsr();

private:
	IQueue<I2cRequest>& m_queue;
	IContext& m_context;
	I2C_HandleTypeDef*  m_hi2c = nullptr;
};

#endif /* STM32_I2C_BUS_H_ */
