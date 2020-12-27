#pragma once
#include "systemc.h"
template <class T> class ITransmitter {
public:
	sc_fifo_out<T*> out;
	sc_fifo_in<T*> in;
private:
	virtual void Transmit() = 0;
	virtual void ReadData() = 0;
};