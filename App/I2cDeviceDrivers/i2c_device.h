#ifndef I2CDEVICEDRIVERS_I2CDEVICE_H_
#define I2CDEVICEDRIVERS_I2CDEVICE_H_

#include "requests.h"
#include <array>

template <uint8_t RxLength, uint8_t TxLength>
class I2cDevice {
public:
	I2cDevice() = default;
	virtual ~I2cDevice() = default;

	I2cRequest createI2cReadReq() {
		return {address, rx.data(), rx.size(), RequestType::read};
	}

	I2cRequest createI2cWriteReq() {
		return {address, tx.data(), tx.size(), RequestType::write};
	}

protected:
	uint8_t address;
	std::array<uint8_t, RxLength> rx;
	std::array<uint8_t, TxLength> tx;
};

#endif
