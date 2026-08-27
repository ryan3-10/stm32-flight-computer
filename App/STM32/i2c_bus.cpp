#include "i2c_bus.h"
#include "requests.h"
#include <cassert>
#include <stm32f4xx_hal.h>

void I2cBus::init(I2C_HandleTypeDef* hi2c, IContext* context, IQueue<I2cRequest>* queue) {
	static I2cBus instance;
	instance.m_hi2c = hi2c;
	instance.m_context = context;
	instance.m_queue = queue;
	s_instance = &instance;
}

void I2cBus::processNextReq() {
#ifdef DEBUG
	// Check that no member variables are null
	assert(m_hi2c);
	assert(m_context);
	assert(m_queue);
#endif


	auto req = m_queue->pop();

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

	m_context->sleep(); // Sleeps until DMA is complete

	if (req.mutex) {
		req.mutex->unlock();
	}
}

void I2cBus::handleDmaCompleteIsr() {
	m_context->awakeFromIsr();
}

extern "C" {
    void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    	I2cBus::instance().handleDmaCompleteIsr();
    }

    void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    	I2cBus::instance().handleDmaCompleteIsr();
    }
}


