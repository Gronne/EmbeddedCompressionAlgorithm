#pragma once
#include <systemc.h>
#include "Package.h"
#include "Input.h"
class Top : public sc_module {
public:
    sc_fifo<Package*> fifo;
    Input* input;

    SC_HAS_PROCESS(Top);
    Top(sc_module_name name);
    ~Top();
private:
};

