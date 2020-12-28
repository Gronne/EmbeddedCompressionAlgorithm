#pragma once
#ifndef __IRECEIVER_H_INCLUDED__   
#define __IRECEIVER_H_INCLUDED__
#include "systemc.h"
template <class T> class IReceiver {
public:
	sc_fifo_out<T> out;
	sc_fifo_in<T> in;
protected:
	virtual void Receive() = 0;
	virtual void WriteData() = 0;
};
#endif