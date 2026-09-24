#ifndef MODELS_REQUESTS_H_
#define MODELS_REQUESTS_H_

#include "i_lock.h"
#include <stdint.h>

enum class RequestType : uint8_t {
	transmit = 0,
	receive
};

struct I2cRequest {
	uint8_t address;
	uint8_t* data;
	uint8_t dataLength;
	RequestType type;
	ILock* mutex = nullptr;
	bool errorFlag = false;
};


#endif /* MODELS_REQUESTS_H_ */
