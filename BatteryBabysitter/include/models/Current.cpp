#include "Current.h"

Current::Current()
{
}

uint16_t Current::getMaxCurrent()
{
	return current(MAX);
}

uint16_t Current::getStandbyCurrent()
{
	return current(STBY);
}

uint16_t Current::getAverageCurrent()
{
	return current(AVG);
}
