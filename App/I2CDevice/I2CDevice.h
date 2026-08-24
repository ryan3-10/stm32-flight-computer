#ifndef I2CDEVICE_I2CDEVICE_H_
#define I2CDEVICE_I2CDEVICE_H_

#include <stdint.h>

class I2CDevice {
public:
	virtual uint8_t address() = 0;
	virtual uint8_t txLength() = 0;
	virtual uint8_t* txBuffer() = 0;
	virtual uint8_t rxLength() = 0;
	virtual uint8_t* rxBuffer() = 0;
	virtual void onRequestComplete() = 0;
};



#endif /* I2CDEVICE_I2CDEVICE_H_ */
