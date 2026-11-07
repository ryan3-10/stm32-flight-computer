#ifndef INTERFACES_I_I2C_BUS_H_
#define INTERFACES_I_I2C_BUS_H_

#include <stdint.h>

class II2cBus {
public:
	virtual ~II2cBus() = default;
	virtual bool masterTransmit(uint16_t address, uint8_t* data, uint16_t length) = 0;
	virtual bool masterReceive(uint16_t address, uint8_t* data, uint16_t length) = 0;
};


#endif /* INTERFACES_I_I2C_BUS_H_ */
