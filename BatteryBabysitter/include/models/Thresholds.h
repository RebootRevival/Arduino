#pragma once
#include "SparkFunBQ27441/SparkFunBQ27441.h"

class Thresholds : private BQ27441
{
public:
	Thresholds();
	uint8_t clearSoCFinal();
	uint8_t clearSoCWarning();
	bool isSoCWarningSet();
	bool isSoCFinalSet(); 

	//SET VALUES

	bool setSoCWarningThreshold(uint8_t set, uint8_t clear);
	bool setSoCFinalThreshold(uint8_t set, uint8_t clear);

	//GET VALUES

	uint8_t getSoCWarningThreshold();
	uint8_t getSoCFinalThreshold();
};

