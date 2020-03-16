#pragma once

#include "SparkFunBQ27441/SparkFunBQ27441.h"
#include "Thresholds.h"
#include <map>

typedef enum {
	STATE_OF_CHARGE_INTERVAL,
	BATTERY_LOW	
} protocol;

class Configuration : private BQ27441, Thresholds
{
private:

	typedef std::map<protocol, gpout_function> protocolMapping;
	
protected:

	protocolMapping mapProtocol = {
		{BATTERY_LOW, BAT_LOW},
		{STATE_OF_CHARGE_INTERVAL, SOC_INT}
	};

public:	

	Configuration();
	bool pulsePin();
	
	//SET VALUES

	bool setPinState(bool pinState);
	bool setMonitoringProtocol(protocol type);
	bool setSoCInterval(uint8_t delta);

	//GET VALUES

	bool getPinState();
	bool getMonitoringProtocol();
	uint8_t getSoCInterval(void);
};

