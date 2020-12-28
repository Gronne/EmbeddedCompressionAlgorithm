#pragma once
#ifndef __TOP_H_INCLUDED__   
#define __TOP_H_INCLUDED__  
#include <systemc.h>
#include "Package.h"
#include "ISensor.h"
#include "Communication.h"

class Top : public sc_module {
public:
    sc_fifo<Package*> *fifoInputData;
    sc_fifo<Package*> *fifoOutputData;

    ISensor<Package*>* sensor;
    Communication* communication;
    
    Top(sc_module_name name);
    SC_HAS_PROCESS(Top);
    ~Top();
private:
};

#endif

