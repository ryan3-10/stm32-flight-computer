#ifndef I2CDEVICEDRIVERS_I2CDEVICE_H_
#define I2CDEVICEDRIVERS_I2CDEVICE_H_

#include "requests.h"
#include <array>

template <uint8_t TxLength, uint8_t RxLength>
class I2cDevice {
public:
	virtual ~I2cDevice() = default;

	I2cRequest createI2cTxReq() {
		return {m_address, m_tx.data(), TxLength, RequestType::transmit, m_context};
	}

	I2cRequest createI2cRxReq() {
		return {m_address, m_rx.data(), RxLength, RequestType::receive, m_context};
	}

protected:
	I2cDevice<TxLength, RxLength>(void* context) : m_context(context) {} // Base class only

	uint8_t m_address;
	std::array<uint8_t, TxLength> m_tx;
	std::array<uint8_t, RxLength> m_rx;
	void* m_context;
};

#endif
