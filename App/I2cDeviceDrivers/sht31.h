#ifndef I2CDEVICEDRIVERS_SHT31_H_
#define I2CDEVICEDRIVERS_SHT31_H_

#include "i2c_device.h"
#include <stdint.h>

constexpr uint8_t TX_LENGTH = 2;
constexpr uint8_t RX_LENGTH = 2;

class Sht31 : public I2cDevice<TX_LENGTH, RX_LENGTH> {
public:
	Sht31(void* context) : I2cDevice<TX_LENGTH, RX_LENGTH>(context) {
		m_address = 0x44 << 1;
		m_tx = {0x2C, 0x06};
		m_rx = {0};
	}

	float lastProcessedTempF() {
		uint16_t rawTemp = (m_rx.at(0) << 8) | m_rx.at(1);
		return  -49 + (315.0f * rawTemp / 65535.0f);
	}

	float lastProcessedTempC() {
			uint16_t rawTemp = (m_rx.at(0) << 8) | m_rx.at(1);
			return  -45 + (175.0f * rawTemp / 65535.0f);
		}
};

#endif /* I2CDEVICEDRIVERS_SHT31_H_ */
