#pragma once
#include "systemc.h"
template <class T> class IReceiver {
public:
	sc_fifo_out<T*> out;
	sc_fifo_in<T*> in;
private:
	virtual void Receive() = 0;
	virtual void WriteData() = 0;
};