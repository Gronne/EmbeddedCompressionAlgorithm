#pragma once
#ifndef __COMMUNICATION_H_INCLUDED__
#define __COMMUNICATION_H_INCLUDED__
#include "systemc.h"
#include "ITransmitter.h"
#include "IReceiver.h"
#include "Transmitter.h"
#include "Receiver.h"

template<class T>
class Communication : public sc_module
{
public:
	Communication(sc_fifo<T>* transmitterPipe, sc_fifo<T>* receiverPipe) :
		sc_module("Communication")
	{
		transmitter = new Transmitter<T>(transmitterPipe, &fifoCommunication);
		receiver = new Receiver<T>(receiverPipe, &fifoCommunication);
	}
	SC_HAS_PROCESS(Communication);

	~Communication() { 
		delete transmitter;
		delete receiver;
	};

	
protected:
	sc_fifo<T> fifoCommunication;
	ITransmitter *transmitter;
	IReceiver *receiver;	
};

#endif 