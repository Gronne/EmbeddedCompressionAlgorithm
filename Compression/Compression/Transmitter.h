#pragma once
#include "Package.h"
class Transmitter : public sc_module {
public:
    sc_fifo_out<Package*> out;
    sc_fifo_in<Package*> in;

    Transmitter(sc_module_name name);
    SC_HAS_PROCESS(Transmitter);
private:
    void Transmit();
    sc_uint<32> sequenceNumber;
};

