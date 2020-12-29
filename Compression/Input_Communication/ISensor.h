#pragma once
#ifndef __ISENSOR_H_INCLUDED__   
#define __ISENSOR_H_INCLUDED__   
#include "systemc.h"
template <class T> class ISensor {
public:

protected:
	virtual void Measure() = 0;
	
};
#endif