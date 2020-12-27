#pragma once
#include "ITransmitter.h"
template <class T>
class Transmitter : public ITransmitter<T>, public sc_module {
public:
    sc_fifo_out<T*> out;
    sc_fifo_in<T*> in;
    Transmitter(sc_module_name name);
    SC_HAS_PROCESS(Transmitter);
private:
    virtual void Transmit();
    virtual void ReadData();
};

