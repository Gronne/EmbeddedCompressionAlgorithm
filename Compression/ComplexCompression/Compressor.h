#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <systemc.h>
#include <iostream>
#include "ICompressionSetup.h"
#include "ICompressionCompress.h"
#include "ICompressionDecompress.h"
#include "../Input_Communication/Package.h"

template<class SensorT, class CompressedT>
class Compression :
    public sc_module
{
public:
    Compression(sc_module_name name, sc_fifo<SensorT> *comInPipe, sc_fifo<CompressedT> *comOutPipe, sc_fifo<CompressedT> *decomInPipe, sc_fifo<SensorT> *decomOutPipe, ICompressionSetup<SensorT>* setup, ICompressionCompress<SensorT>* compressor, ICompressionDecompress<SensorT>* decompressor) :
        sc_module(name),
        _comInPipe(comInPipe),
        _comOutPipe(comOutPipe),
        _decomInPipe(decomInPipe),
        _decomOutPipe(decomOutPipe),
        _setup(setup),
        _compressor(compressor),
        _decompressor(decompressor)
    {
        SC_THREAD(run);
    };
    SC_HAS_PROCESS(Compression);


private:
    void run() {
        bool status;
        SensorT data;

        do{
            wait(_comInPipe->data_written_event());
            data = _comInPipe->read();
            std::cout << data << std::endl;
        } while (true);

    };


    sc_fifo<SensorT> *_comInPipe;
    sc_fifo<CompressedT>* _comOutPipe;
    sc_fifo<CompressedT>* _decomInPipe;
    sc_fifo<SensorT> *_decomOutPipe;
    ICompressionSetup<SensorT> *_setup;
    ICompressionCompress<SensorT> *_compressor;
    ICompressionDecompress<SensorT> *_decompressor;
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

