#pragma once
#ifndef __TEXTFILESESNSOR_H_INCLUDED__   
#define __TEXTFILESESNSOR_H_INCLUDED__   
#include "ISensor.h"
#include "Package.h"
#include <string>
class TextFileSensor :
    public ISensor<Package*>, public sc_module
{
public:

    TextFileSensor(sc_module_name name, char* filename);
    SC_HAS_PROCESS(TextFileSensor);
private:
    virtual void Measure();
    sc_uint<32> size;
    char* _filename;
};

#endif