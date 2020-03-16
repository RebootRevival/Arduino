#pragma once
#include "SparkFunBQ27441/SparkFunBQ27441.h"
#include <cstdint>
class Capacity : private BQ27441
{
private:
	uint16_t maxCapacity;

public:
	Capacity();

	//SET VALUES

	bool setCapacity(uint16_t mAH);

	//GET VALUES

	uint16_t getCapacity();
	uint16_t getRemainingCapacity();
	uint16_t getFullCapacity();
	uint16_t getAvailableCapacity();
	uint16_t getFullAvailableCapacity();
	uint16_t getRemainingCapacityFiltered();
	uint16_t getRemainingCapacityUnfiltered();
	uint16_t getFullCapacityFiltered();
	uint16_t getFullCapacityUnfiltered();
	uint16_t getDesignCapacity();

};

