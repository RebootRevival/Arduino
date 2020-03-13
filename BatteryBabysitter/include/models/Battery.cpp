#include "Battery.h"

Battery::Battery()
{
	babysitter = BQ27441::BQ27441();
}

void Battery::init()
{
	babysitter.begin();
}

bool Battery::setCapacity(uint16_t mAH)
{
	return babysitter.setCapacity(mAH);
}

uint16_t Battery::getCapacity()
{
	return this->maxCapacity;
}

uint16_t Battery::getVoltage()
{
	return babysitter.voltage();
}

uint16_t Battery::getMaxCurrent()
{
	return babysitter.current(MAX);
}

uint16_t Battery::getStandbyCurrent()
{
	return babysitter.current(STBY);
}

uint16_t Battery::getAverageCurrent()
{
	return babysitter.current(AVG);
}
