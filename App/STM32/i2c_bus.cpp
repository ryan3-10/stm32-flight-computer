#include "i2c_bus.h"
#include "requests.h"
#include <stm32f4xx_hal.h>

void I2cBus::init(I2C_HandleTypeDef* hi2c) {
	static I2cBus instance;
	m_instance = &instance;
	instance.m_hi2c = hi2c;
}

void I2cBus::processRequest(I2cRequest& req) {
	switch (req.type) {

	case RequestType::transmit:
		HAL_I2C_Master_Transmit_DMA(m_hi2c, req.address, req.data, req.dataLength);
		break;
	case RequestType::receive:
		HAL_I2C_Master_Receive_DMA(m_hi2c, req.address, req.data, req.dataLength);
		break;
	}
}

void I2cBus::handleDmaComplete() {
	if (onDmaComplete)
		onDmaComplete(callbackContext);
}

void I2cBus::registerCallbacks(Callback completeCb, void* context) {
	onDmaComplete = completeCb;
	callbackContext = context;
}

extern "C" {
    void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    	I2cBus::instance().handleDmaComplete();
    }

    void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    	I2cBus::instance().handleDmaComplete();
    }
}


