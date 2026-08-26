#ifndef MODELS_REQUESTS_H_
#define MODELS_REQUESTS_H_

#include <stdint.h>

enum class RequestType : uint8_t {
	read = 0,
	write
};

struct I2cRequest {
	uint8_t address;
	uint8_t* data;
	uint8_t dataLength;
	RequestType type;
	bool errorFlag = false;
	void* context = nullptr;
};



#endif /* MODELS_REQUESTS_H_ */
