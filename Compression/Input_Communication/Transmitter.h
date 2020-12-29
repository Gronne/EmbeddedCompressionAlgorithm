#pragma once
#ifndef __TRANSMITTER_H_INCLUDED__   
#define __TRANSMITTER_H_INCLUDED__
#include "ITransmitter.h"
#include "Package.h"
#include "Communication.h"

template<class T>
class Transmitter : public ITransmitter, public sc_module {
public:
    Transmitter(sc_fifo<T>* transmitterPipe, sc_fifo<T>* internalPipe) :
        sc_module("Transmitter"),
        _transmitterPipe(transmitterPipe),
        _internalPipe(internalPipe) 
    {
        SC_THREAD(transmit);
    };
    SC_HAS_PROCESS(Transmitter);

protected:
    
    virtual void transmit() {
        while (true)
        {
            wait(_transmitterPipe->data_written_event());
            T data = _transmitterPipe->read();
            std::cout << "Write: " << data << std::endl;
            _internalPipe->write(data);
        }
    };

    sc_fifo<T> *_internalPipe;
    sc_fifo<T> *_transmitterPipe;
};



#endif

