#pragma once
#ifndef __TOP_H_INCLUDED__   
#define __TOP_H_INCLUDED__  
#include <systemc.h>
#include "Package.h"
#include "ISensor.h"
#include "ITransmitter.h"
#include "IReceiver.h"
class Top : public sc_module {
public:
    sc_fifo<Package*> *fifoInputData;
    sc_fifo<Package*> *fifoCommunication;
    sc_fifo<Package*> *fifoOutputData;

    ISensor<Package*>* sensor;
    ITransmitter<Package*>* transmitter;
    IReceiver<Package*>* receiver;
    SC_HAS_PROCESS(Top);
    Top(sc_module_name name);
    ~Top();
private:
};

#endif

