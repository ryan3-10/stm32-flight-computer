#ifndef I2CDEVICEDRIVERS_SHT31_H_
#define I2CDEVICEDRIVERS_SHT31_H_

#include "i_allocator.h"
#include "i2c_device.h"
#include "i_lock.h"
#include <stdint.h>

constexpr uint8_t TX_LENGTH = 2;
constexpr uint8_t RX_LENGTH = 2;

class Sht31 : public I2cDevice {
public:
	Sht31(ILock* rxMutex, IAllocator<uint8_t>& allocator) :
		I2cDevice(
			0x44 << 1, 		// 7-bit address
			{0x2c, 0x06}, 	// tx data, high repeat, clock stretch enabled
			2,				// need to allocate 2 bytes for rx
			rxMutex,		// for synchronizing read and writes to rx
			allocator 		// for allocating memory for rx and tx
		)
	{}

	float lastProcessedTempF() const {
		rxReq().mutex->lock();
		float result = -49 + (315.0f * rawTemp() / 65535.0f);
		rxReq().mutex->unlock();

		return result;
	}

	float lastProcessedTempC() const {
		rxReq().mutex->lock();
		float result = -45 + (175.0f * rawTemp() / 65535.0f);
		rxReq().mutex->unlock();

		return result;
	}

private:
	uint16_t rawTemp() {
		return (rxReq().data[0] << 8) | rxReq().data[1];
	}
};

#endif /* I2CDEVICEDRIVERS_SHT31_H_ */
