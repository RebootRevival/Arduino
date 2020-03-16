#pragma once

#include "SparkFunBQ27441/SparkFunBQ27441.h"
#include <cstdint>

class Health :	private BQ27441
{
public:
	Health();

	//GET VALUES

	uint16_t getFilteredStateOfCharge();
	uint16_t getUnfilteredStateOfCharge();
	uint16_t getStatusStateOfHealth();
	uint16_t getPercentStateOfHealth();
	uint16_t getBatteryTemperature();
	uint16_t getInternalTemperature();
};

