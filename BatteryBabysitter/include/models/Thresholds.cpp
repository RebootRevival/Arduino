#include "Thresholds.h"

Thresholds::Thresholds()
{
}

uint8_t Thresholds::clearSoCFinal()
{
	return uint8_t();
}

uint8_t Thresholds::clearSoCWarning()
{
	return uint8_t();
}

bool Thresholds::isSoCWarningSet()
{
	return false;
}

bool Thresholds::isSoCFinalSet()
{
	return false;
}

bool Thresholds::setSoCWarningThreshold(uint8_t set, uint8_t clear)
{
	return false;
}

bool Thresholds::setSoCFinalThreshold(uint8_t set, uint8_t clear)
{
	return false;
}

uint8_t Thresholds::getSoCWarningThreshold()
{
	return uint8_t();
}

uint8_t Thresholds::getSoCFinalThreshold()
{
	return uint8_t();
}
