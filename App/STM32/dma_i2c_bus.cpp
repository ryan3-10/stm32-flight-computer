#include <dma_i2c_bus.h>
#include <algorithm>
#include <cassert>
#include <stm32f4xx_hal.h>


bool DmaI2cBus::masterTransmit(uint16_t address, uint8_t* data, uint16_t length) {
	m_mutex.lock();
	m_context.setToCurrentContext();
	bool result = HAL_I2C_Master_Transmit_DMA(m_hi2c, address, data, length) == HAL_OK;
	m_context.sleep(); // sleep until DMA is complete
	m_mutex.unlock();
	return result;
}

bool DmaI2cBus::masterReceive(uint16_t address, uint8_t* data, uint16_t length) {
	m_mutex.lock();
	m_context.setToCurrentContext();
	bool result =  HAL_I2C_Master_Receive_DMA(m_hi2c, address, data, length) == HAL_OK;
	m_context.sleep(); // sleep until DMA is complete
	m_mutex.unlock();
	return result;
}

void DmaI2cBus::handleDmaCompleteIsr() {
	m_context.awakeFromIsr();
}

DmaI2cBus& DmaI2cBus::getLinkedBus(I2C_HandleTypeDef* hi2c) {
	auto endIt = s_hi2cLinks.end() + s_linkIndex;

	auto it = std::find_if(s_hi2cLinks.begin(), endIt, [hi2c](auto pair) {
		return pair.first == hi2c;
	});

	#ifdef DEBUG
		assert(it != endIt);
	#endif

	return *(it->second);
}

extern "C" {
    void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef* hi2c) {
    	DmaI2cBus::getLinkedBus(hi2c).handleDmaCompleteIsr();
    }

    void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c) {
    	DmaI2cBus::getLinkedBus(hi2c).handleDmaCompleteIsr();
    }
}




