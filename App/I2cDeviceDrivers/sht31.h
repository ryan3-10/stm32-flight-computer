#ifndef I2CDEVICEDRIVERS_SHT31_H_
#define I2CDEVICEDRIVERS_SHT31_H_

#include "i_i2c_bus.h"
#include "i2c_device.h"
#include <stdint.h>

constexpr uint8_t TX_LENGTH = 2;
constexpr uint8_t RX_LENGTH = 2;

class Sht31 : public I2cDevice<TX_LENGTH, RX_LENGTH> {
public:
	Sht31(II2cBus& i2cBus)
		: I2cDevice(
			0x44 << 1, 		// 7-bit address
			{0x2c, 0x06}, 	// tx data, high repeat, clock stretch enabled
			i2cBus,
			0				// no delay needed
		 )
	{}


	float lastTempF() const {
		return m_lastTempF;
	}

	float lastTempC() const {
		return m_lastTempC;
	}

private:
	void processData(bool result) override {
		// Only process results if transmission was successful
		if (result) {
			m_lastTempF = -49 + (315.0f * rawTemp() / 65535.0f);
			m_lastTempC = -45 + (175.0f * rawTemp() / 65535.0f);
		}
	}

	uint16_t rawTemp() const {
			return (m_masterRx[0] << 8) | m_masterRx[1];
	}

	float m_lastTempF;
	float m_lastTempC;
};

#endif /* I2CDEVICEDRIVERS_SHT31_H_ */
