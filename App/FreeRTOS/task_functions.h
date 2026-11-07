#include <i_i2c_bus.h>

#ifndef FREERTOS_TASK_FUNCTIONS_H_
#define FREERTOS_TASK_FUNCTIONS_H_

namespace TaskFunctions {
	void initBusses(II2cBus* i2cBus);
	void initTasks();
}

#endif /* FREERTOS_TASK_FUNCTIONS_H_ */
