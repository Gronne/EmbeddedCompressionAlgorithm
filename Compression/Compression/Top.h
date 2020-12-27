#pragma once
#include <systemc.h>
class Top : public sc_module {
public:

    SC_HAS_PROCESS(Top);
    Top(sc_module_name name);
    ~Top();
private:
};

