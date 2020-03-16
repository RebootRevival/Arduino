#pragma once

#include "SparkFunBQ27441/SparkFunBQ27441.h"
#include <cstdint>

class Power : private BQ27441
{
public:
	Power();

	//GET VALUES
	
	uint16_t getAveragePower();
};

