#include "i2c_bus.h"
#include "requests.h"
#include <cassert>
#include <stm32f4xx_hal.h>

void I2cBus::processNextReq() {
#ifdef DEBUG
	// Check that hi2c is not null
	assert(m_hi2c);
#endif


	auto req = m_queue.pop();

	if (req.mutex) {
		req.mutex->lock();
	}

	switch (req.type) {

	case RequestType::transmit:
		HAL_I2C_Master_Transmit_DMA(m_hi2c, req.address, req.data, req.dataLength);
		break;
	case RequestType::receive:
		HAL_I2C_Master_Receive_DMA(m_hi2c, req.address, req.data, req.dataLength);
		break;
	}

	m_context.sleep(); // Sleeps until DMA is complete

	if (req.mutex) {
		req.mutex->unlock();
	}
}

void I2cBus::handleDmaCompleteIsr() {
	m_context.awakeFromIsr();
}




