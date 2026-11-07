#include "i_i2c_bus.h"
#include <array>
#include <stdint.h>

#ifndef I2CDEVICEDRIVERS_I2C_DEVICE_H_
#define I2CDEVICEDRIVERS_I2C_DEVICE_H_

template <std::size_t masterTxSize, std::size_t masterRxSize>
class I2cDevice {
	using MasterTx = std::array<uint8_t, masterTxSize>;
	using MasterRx = std::array<uint8_t, masterRxSize>;

public:
	bool masterTransmit() {
		return m_i2cBus.masterTransmit(m_address, m_masterTx.data(), masterTxSize);
	}

	uint32_t msDelayAfterTransmmit() { return m_msDelayAfterTransmit; }

	bool masterReceive() {
		auto result = m_i2cBus.masterReceive(m_address, m_masterRx.data(), masterRxSize);
		processData(result);
		return result;
	}

protected:
	I2cDevice(uint8_t address, const MasterTx& masterTx, II2cBus& i2cBus, uint32_t delay)
		: m_address(address)
		, m_masterTx(masterTx)
		, m_i2cBus(i2cBus)
		, m_msDelayAfterTransmit(delay)
	{}

	virtual ~I2cDevice() = default;

	MasterRx m_masterRx{};

private:
	virtual void processData(bool result) = 0;

	const uint8_t m_address;
	MasterTx m_masterTx;
	II2cBus& m_i2cBus;
	uint32_t m_msDelayAfterTransmit;
};



#endif /* I2CDEVICEDRIVERS_I2C_DEVICE_H_ */
