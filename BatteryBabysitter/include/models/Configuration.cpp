#include "Configuration.h"

Configuration::Configuration()
{
}

bool Configuration::setPinState(bool pinState)
{
	return BQ27441::setGPOUTPolarity(pinState);
}

bool Configuration::getPinState()
{
	return BQ27441::GPOUTPolarity();
}

bool Configuration::setMonitoringProtocol(protocol type)
{
	return BQ27441::setGPOUTFunction(mapProtocol.find(type)->second);
}

uint8_t Configuration::getSoCInterval(void)
{
	return uint8_t();
}

bool Configuration::setSoCInterval(uint8_t delta)
{
	return false;
}

bool Configuration::pulsePin()
{
	return false;
}

bool Configuration::getMonitoringProtocol()
{
	return BQ27441::GPOUTFunction();
}