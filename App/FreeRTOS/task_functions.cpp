#include "free_rtos_queue.h"
#include "i_i2c_bus.h"
#include "print_debugging.h"
#include "sht31.h"
#include "task_functions.h"
#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>


namespace {
	II2cBus* g_i2cBus = nullptr;
	FreeRtosQueue<float, 20> g_queue;
}

void Sht31Task(void*) {
	Sht31 sht31(*g_i2cBus);

	while (true) {
		sht31.masterTransmit();
		vTaskDelay(pdMS_TO_TICKS(sht31.msDelayAfterTransmmit()));
		sht31.masterReceive();
		g_queue.push(sht31.lastTempF());

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void TelemetryTask(void*) {
	char buf[32];

	while (true) {
		auto temp = g_queue.pop();
		snprintf(buf, sizeof(buf), "%.2f F\n\r", temp);
		print(buf);
	}
}

void TaskFunctions::initBusses(II2cBus* i2cBus) {
	g_i2cBus = i2cBus;
}

void TaskFunctions::initTasks() {
	xTaskCreate(Sht31Task, "Sht31 Task", 256, nullptr, 1, nullptr);
	xTaskCreate(TelemetryTask, "Telemetry Task", 256, nullptr, 1, nullptr);
}
