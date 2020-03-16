#pragma once

#include "SparkfunBQ27441/SparkFunBQ27441.h"
#include <cstdint>

class Current :	private BQ27441
{
private:
	

public:
	Current();
	uint16_t getMaxCurrent();
	uint16_t getStandbyCurrent();
	uint16_t getAverageCurrent();
};

