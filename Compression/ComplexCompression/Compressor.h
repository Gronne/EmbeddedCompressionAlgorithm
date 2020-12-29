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
    Compression(sc_module_name name, sc_fifo<SensorT> *comInPipe, sc_fifo<CompressedT> *comOutPipe, sc_fifo<CompressedT> *decomInPipe, sc_fifo<SensorT> *decomOutPipe, ICompressionSetup<SensorT>* setup, ICompressionCompress<SensorT, CompressedT>* compressor, ICompressionDecompress<SensorT, CompressedT>* decompressor) :
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
            std::cout << "Compressor: " << data << std::endl;
            status = _setup->setup(data);
        } while (status == false);

    };

    void sendSetupData() {
    };

    void compress() {
        SensorT sensorData;
        CompressedT comData;
        while (true) {
            wait(_comInPipe->data_written_event());
            sensorData = _comInPipe->read();
            comData = _compressor->encode(sensorData);
            _comOutPipe->write(comData);
        }
    }

    void decompress() {
        SensorT sensorData;
        CompressedT comData;
        while (true) {
            wait(_decomInPipe->data_written_event());
            comData = _decomInPipe->read();
            sensorData = _decompressor->decode(comData);
            _decomOutPipe->write(sensorData);
        }
    }

    sc_fifo<SensorT> *_comInPipe;
    sc_fifo<CompressedT>* _comOutPipe;
    sc_fifo<CompressedT>* _decomInPipe;
    sc_fifo<SensorT> *_decomOutPipe;
    ICompressionSetup<SensorT> *_setup;
    ICompressionCompress<SensorT, CompressedT> *_compressor;
    ICompressionDecompress<SensorT, CompressedT> *_decompressor;
};



#endif


