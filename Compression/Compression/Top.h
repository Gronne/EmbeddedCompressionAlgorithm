#pragma once
#include <systemc.h>
#include "Package.h"
#include "ISensor.h"
class Top : public sc_module {
public:
    sc_fifo<Package*>* fifo;
    ISensor<Package*>* sensor;

    SC_HAS_PROCESS(Top);
    Top(sc_module_name name);
    ~Top();
private:
};

