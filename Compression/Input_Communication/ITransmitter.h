#pragma once

#ifndef __ITRANSMITTER_H_INCLUDED__   
#define __ITRANSMITTER_H_INCLUDED__   

#include "systemc.h"
template <class T> class ITransmitter {
public:
	sc_fifo_out<T> out;
	sc_fifo_in<T> in;
protected:
	virtual void Transmit() = 0;
	virtual void ReadData() = 0;
};

#endif