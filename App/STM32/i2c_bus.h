#ifndef STM32_I2C_BUS_H_
#define STM32_I2C_BUS_H_

#include "requests.h"
#include <stm32f4xx_hal.h>

class I2cBus {
	using Callback = void(*)(void* context);

public:
	static void init(I2C_HandleTypeDef* hi2c);
	static I2cBus& instance() { return *m_instance; }
	void processRequest(I2cRequest& request);
	void handleDmaComplete();
	void registerCallbacks(Callback completeCb, void* context);

private:
	I2cBus() = default;
	~I2cBus() = default;
	I2cBus(const I2cBus&) = delete;
	I2cBus& operator=(const I2cBus&) = delete;

	Callback onDmaComplete = nullptr;
	void* callbackContext = nullptr;
	inline static I2cBus* m_instance = nullptr;
	I2C_HandleTypeDef*  m_hi2c = nullptr;
};

#endif /* STM32_I2C_BUS_H_ */
