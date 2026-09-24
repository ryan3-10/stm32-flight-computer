#ifndef I2CDEVICEDRIVERS_I2CDEVICE_H_
#define I2CDEVICEDRIVERS_I2CDEVICE_H_

#include "i_allocator.h"
#include "i_lock.h"
#include "requests.h"
#include <array>
#include <initializer_list>
#include <stdint.h>

class I2cDevice {
	using List = std::initializer_list<uint8_t>;
	using Pool = MemoryPool<uint8_t>;

public:
	virtual ~I2cDevice() = default;
	I2cRequest txReq() const { return m_txReq; }
	I2cRequest rxReq() const { return m_rxReq; }
	static void registerAllocator(MemoryPool<uint8_t>* pool) { s_pool = pool; }

protected:
	// Base class only
	I2cDevice(
		uint8_t add,
		const List txDat,
		uint8_t rxLen,
		ILock* rxMutex,
		IAllocator<uint8_t>& allocator
	)
		: m_txReq({
			.address 	= add,
			.data 		= allocator.allocate(txDat),
			.dataLength	= static_cast<uint8_t>(txDat.size()),
			.type 		= RequestType::transmit
		})
		, m_rxReq({
			.address 	= add,
			.data		= allocator.allocate(rxLen),
			.dataLength	= rxLen,
			.type		= RequestType::receive,
			.mutex		= rxMutex
		})
	{}

private:
	I2cRequest m_txReq;
	I2cRequest m_rxReq;
};

#endif
