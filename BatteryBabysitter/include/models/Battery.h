#pragma once

#include "SparkfunBQ27441/SparkFunBQ27441.h"
#include <cstdint>

class Battery
{
private:
	uint16_t maxCapacity;
public:
	BQ27441 babysitter;
	Battery();
	void init();

//region -- Set Values
	bool setCapacity(uint16_t mAH);

//region -- Get Values	
	uint16_t getCapacity();
	uint16_t getVoltage();
	uint16_t getMaxCurrent();
	uint16_t getStandbyCurrent();
	uint16_t getAverageCurrent();

};

