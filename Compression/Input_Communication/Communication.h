#pragma once
#ifndef __COMMUNICATION_H_INCLUDED__
#define __COMMUNICATION_H_INCLUDED__
#include "systemc.h"
#include "Package.h"
#include "ITransmitter.h"
#include "IReceiver.h"
class Communication : public sc_module
{
public:
	sc_fifo<Package*>* fifoCommunication;
	ITransmitter<Package*>* transmitter;
	IReceiver<Package*>* receiver;

	Communication(sc_module_name name, sc_fifo<Package*>* fifoInputData, sc_fifo<Package*>* fifoOutputData);
	SC_HAS_PROCESS(Communication);
	~Communication();
private:
	
};

#endif 