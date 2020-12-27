#pragma once
#include "Package.h"
class Input : public sc_module {
public:
    sc_fifo_out<Package*> out;

    Input(sc_module_name name);
    SC_HAS_PROCESS(Input);
private:
    void measure();
    sc_uint<32> inputvalue;
    sc_uint<32> size;
};

