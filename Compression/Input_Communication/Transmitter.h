#pragma once
#ifndef __TRANSMITTER_H_INCLUDED__   
#define __TRANSMITTER_H_INCLUDED__
#include "ITransmitter.h"
#include "Package.h"
class Transmitter : public ITransmitter<Package*>, public sc_module {
public:
    Transmitter(sc_module_name name);
    SC_HAS_PROCESS(Transmitter);
private:
    Package* _data;
    virtual void Transmit();
    virtual void ReadData();
};



#endif

