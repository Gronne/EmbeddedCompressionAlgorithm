#pragma once
#ifndef __SENSORFACTORY_H_INCLUDED__   
#define __SENSORFACTORY_H_INCLUDED__   
#include "ISensor.h"
#include "Package.h"
#include "Datatypes.h"

class SensorFactory : public sc_module
{
public:
	static ISensor<Package*>* CreateTextFileSensor(sc_fifo<Package*>* fifo);
private:

};
#endif
