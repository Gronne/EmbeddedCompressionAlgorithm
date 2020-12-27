#pragma once
#include "ISensor.h"
#include "Package.h"
#include "Datatypes.h"

template <class T>
class SensorFactory : public sc_module
{
public:
	ISensor<T>* CreateTextFileSensor(sc_fifo<T*> fifo);
private:

};

