#pragma once
#ifndef __SINUSSESNSOR_H_INCLUDED__   
#define __SINUSSESNSOR_H_INCLUDED__   
#include "ISensor.h"
#include <math.h>

using SinusSensorT = double;

class SinusSensor :
    public sc_module, public ISensor<SinusSensorT>
{
public:

    SinusSensor(sc_module_name name, sc_fifo<SinusSensorT>* out, int measurementSpeed = 100) :
        sc_module(name),
        _measurementSpeed(measurementSpeed),
        _out(out)
    {
        SC_THREAD(Measure);
    };

    SC_HAS_PROCESS(SinusSensor);

private:
    virtual void Measure() {
        while (true) {
            int data = (SinusSensorT)(sin(double(_counter++))*100);
            _out->write(data);
            wait(_measurementSpeed, SC_NS);
        }
    }

    sc_fifo<SinusSensorT> *_out;
    sc_uint<32> _counter = 0;
    sc_uint<32> _measurementSpeed;

};

#endif