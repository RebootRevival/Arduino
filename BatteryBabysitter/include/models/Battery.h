#pragma once

#include <Current.h>
#include <Voltage.h>
#include <Capacity.h>
#include <Configuration.h>
#include <Health.h>
#include <Power.h>


class Battery
{
private:

public:	
	Capacity capacity;
	Configuration config;
	Current current;
	Health health;
	Power power;
	Voltage voltage;

	

	Battery();
	void init();	   	  
};

