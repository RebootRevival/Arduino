#pragma once

#include "SparkFunBQ27441/SparkFunBQ27441.h"
#include <cstdint>

class Voltage :	private BQ27441
{
private:

public:
	Voltage();

	uint16_t getVoltage();
};

