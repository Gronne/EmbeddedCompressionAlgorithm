#pragma once
#ifndef __IRECEIVER_H_INCLUDED__   
#define __IRECEIVER_H_INCLUDED__
#include "systemc.h"

class IReceiver {
public:
	virtual void receive() = 0;
};
#endif