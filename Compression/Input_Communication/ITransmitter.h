#pragma once

#ifndef __ITRANSMITTER_H_INCLUDED__   
#define __ITRANSMITTER_H_INCLUDED__   

#include "systemc.h"

class ITransmitter {
protected:
	virtual void transmit() = 0;
};

#endif