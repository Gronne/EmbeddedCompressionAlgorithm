#pragma once
#include <systemc.h>
#include "Package.h"
#include "ISensor.h"
class Top : public sc_module {
public:
<<<<<<< HEAD
    sc_fifo<Package*> fifo;
    ISensor<Package>* sensor;
=======
    sc_fifo<Package*>* fifo;
    ISensor<Package*>* sensor;
>>>>>>> 1dc35a4c060c20f2f8396256c23d77ef9bfb31a5

    SC_HAS_PROCESS(Top);
    Top(sc_module_name name);
    ~Top();
private:
};

