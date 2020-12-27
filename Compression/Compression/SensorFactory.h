#pragma once
#include "ISensor.h"
#include "Package.h"
#include "Datatypes.h"

class SensorFactory : public sc_module
{
public:
	static ISensor<Package*>* CreateTextFileSensor(sc_fifo<Package*>* fifo);
private:

};

