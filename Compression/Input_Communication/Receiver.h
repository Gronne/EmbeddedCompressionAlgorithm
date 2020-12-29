#pragma once
#ifndef __RECEIVER_H_INCLUDED__   
#define __RECEIVER_H_INCLUDED__   
#include "IReceiver.h"
#include "Package.h"

template<class T>
class Receiver : public IReceiver, public sc_module
{
public:
	Receiver(sc_fifo<T> *receiverPipe, sc_fifo<T> *internalPipe) : 
		sc_module("Receiver"),
		_receiverPipe(receiverPipe),
		_internalPipe(internalPipe)
	{
		SC_THREAD(receive);
	}
	SC_HAS_PROCESS(Receiver);

	

protected:
	void receive() {
		while (true)
		{
			wait(_internalPipe->data_written_event());
			T data = _internalPipe->read();
			_receiverPipe->write(data);
		}
	}


	sc_fifo<T> *_internalPipe;
	sc_fifo<T> *_receiverPipe;
};

#endif