#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <systemc.h>
#include <iostream>
#include "ICompressionSetup.h"
#include "ICompressionCompress.h"
#include "ICompressionDecompress.h"
#include "../Input_Communication/Package.h"

template<class T>
class Compression :
    public sc_module
{
public:
    Compression(sc_module_name name, sc_fifo<T>* in, sc_fifo<T>* out, ICompressionSetup<T>* setup, ICompressionCompress<T>* compressor, ICompressionDecompress<T>* decompressor) :
        sc_module(name),
        _datalinkIn(in),
        _datalinkOut(out),
        _setup(setup),
        _compressor(compressor),
        _decompressor(decompressor)
    {
        SC_THREAD(run);
    };
    SC_HAS_PROCESS(Compression);


private:
    void run() {
        while(true)
            std::cout << true << std::endl;
    };

    sc_fifo<T> *_datalinkIn;
    sc_fifo<T> *_datalinkOut;
    ICompressionSetup<T> *_setup;
    ICompressionCompress<T> *_compressor;
    ICompressionDecompress<T> *_decompressor;
};





#endif


//Call setup until setup return true
//databuffer
//do {
//    databuffer.push(newMeasurement);
//    status = _setup.setup(dataBuffer.front()
//} while (status == false);
//
//    _setup.setup(setupReceived);
//
//    //Init compressor
//    _compressor.init(_setup);
//    //Init decompressor
//    _decompressor.init(_setup);
//
//    //Compress and setup data-buffer
//    for element in databuffer{
//        cElement = compressor.encode(element);
//        send(cElement);
//    }
//
//        //Compress and new data
//        while (!fifoIn.empty()) {
//            cElement = compressor.encode(fifoIn.pop());
//            send(cElement);
//        }

