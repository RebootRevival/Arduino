#include "Capacity.h"

Capacity::Capacity()
{
}

bool Capacity::setCapacity(uint16_t mAH)
{
	return false;
}

uint16_t Capacity::getCapacity()
{
	return this->maxCapacity;
}

uint16_t Capacity::getRemainingCapacity()
{
	return uint16_t();
}

uint16_t Capacity::getFullCapacity()
{
	return uint16_t();
}

uint16_t Capacity::getAvailableCapacity()
{
	return uint16_t();
}

uint16_t Capacity::getFullAvailableCapacity()
{
	return uint16_t();
}

uint16_t Capacity::getRemainingCapacityFiltered()
{
	return uint16_t();
}

uint16_t Capacity::getRemainingCapacityUnfiltered()
{
	return uint16_t();
}

uint16_t Capacity::getFullCapacityFiltered()
{
	return uint16_t();
}

uint16_t Capacity::getFullCapacityUnfiltered()
{
	return uint16_t();
}

uint16_t Capacity::getDesignCapacity()
{
	return uint16_t();
}
