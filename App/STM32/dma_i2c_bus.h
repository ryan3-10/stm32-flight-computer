#ifndef STM32_DMA_I2C_BUS_H_
#define STM32_DMA_I2C_BUS_H_

#include "i_context.h"
#include "i_i2c_bus.h"
#include "i_mutex.h"
#include <array>
#include <cassert>
#include <stm32f4xx_hal.h>

class DmaI2cBus : public II2cBus {

public:
	DmaI2cBus(I2C_HandleTypeDef* hi2c, IContext& context, IMutex& mutex)
		: m_hi2c(hi2c)
		, m_context(context)
		, m_mutex(mutex)
	{
		#ifdef DEBUG
		assert(s_linkIndex < s_hi2cLinks.size());
		#endif
		// This allows the i2c callback to find out which i2cBus needs to be notified
		s_hi2cLinks[s_linkIndex++] = {m_hi2c, this};
	}

	~DmaI2cBus() = default;
	DmaI2cBus(const DmaI2cBus&) = delete;
	DmaI2cBus& operator=(const DmaI2cBus&) = delete;

	bool masterTransmit(uint16_t address, uint8_t* data, uint16_t length) override;
	bool masterReceive(uint16_t address, uint8_t* data, uint16_t length) override;
	void handleDmaCompleteIsr();
	static DmaI2cBus& getLinkedBus(I2C_HandleTypeDef* hi2c);

private:
	I2C_HandleTypeDef* m_hi2c;
	IContext& m_context;
	IMutex& m_mutex;

	static inline std::array<std::pair<I2C_HandleTypeDef*, DmaI2cBus*>, 1> s_hi2cLinks;
	static inline uint8_t s_linkIndex = 0;
};

#endif /* STM32_DMA_I2C_BUS_H_ */
