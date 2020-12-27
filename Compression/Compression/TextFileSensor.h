#pragma once
#include "ISensor.h"
#include "Package.h"
#include <string>
class TextFileSensor :
    public ISensor<Package*>, public sc_module
{
public:
    sc_fifo_out<Package*> out; //pipe

    TextFileSensor(sc_module_name name, char* filename);
    SC_HAS_PROCESS(TextFileSensor);
private:
    virtual void Measure();
    sc_uint<32> size;
    char* _filename;
};

