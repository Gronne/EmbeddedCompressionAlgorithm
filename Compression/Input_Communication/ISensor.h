#pragma once
#ifndef __ISENSOR_H_INCLUDED__   
#define __ISENSOR_H_INCLUDED__   
#include "systemc.h"
template <class T> class ISensor {
public:
	sc_fifo_out<T> out;
protected:
	virtual void Measure() = 0;
	
};
#endif