#pragma once
#include "IReceiver.h"
template <class T>
class Receiver : public IReceiver<T>, public sc_module
{
public:
	sc_fifo_out<T*> out;
	sc_fifo_in<T*> in;
	Receiver(sc_module_name name);
	SC_HAS_PROCESS(Receiver);
private:
	virtual void Receive();
	virtual void WriteData();
};

