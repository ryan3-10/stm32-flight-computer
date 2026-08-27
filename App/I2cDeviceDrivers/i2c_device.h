#ifndef I2CDEVICEDRIVERS_I2CDEVICE_H_
#define I2CDEVICEDRIVERS_I2CDEVICE_H_

#include "i_lock.h"
#include "memory_pool.h"
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
	I2cDevice(uint8_t add, List txDat, uint8_t rxLen, ILock* rxMutex) : // Base class only
		m_txReq({
			.address 	= add,
			.data 		= s_pool->allocate(txDat),
			.dataLength	= static_cast<uint8_t>(txDat.size()),
			.type 		= RequestType::transmit
		}),

		m_rxReq({
			.address 	= add,
			.data		= s_pool->allocate(rxLen),
			.dataLength	= rxLen,
			.type		= RequestType::receive,
			.mutex		= rxMutex
		})
	{}

private:
	static inline MemoryPool<uint8_t>* s_pool = nullptr;
	I2cRequest m_txReq;
	I2cRequest m_rxReq;
};

#endif
