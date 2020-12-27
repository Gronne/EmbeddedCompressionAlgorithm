#pragma once
#include "Package.h"
class Input : public sc_module {
public:
    sc_fifo_out<Package*> out;

    Input(sc_module_name name);
    SC_HAS_PROCESS(Input);
private:
    void sensor();
    sc_uint<32> inputvalue;
    sc_uint<32> size;
};

