#pragma once
#include "systemc.h"
#include "Package.h"
template <class T> class ISensor {
public:
	sc_fifo_out<T> out;
protected:
	virtual void Measure() = 0;
	
};
