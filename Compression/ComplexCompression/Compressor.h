#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <systemc.h>
#include <iostream>
#include "ICompressionSetup.h"
#include "ICompressionCompress.h"
#include "ICompressionDecompress.h"
#include "../Input_Communication/Package.h"

template<class SensorT, class CompressedT, class ModelT>
class Compression :
    public sc_module
{
public:

    Compression(sc_module_name name, sc_fifo<SensorT> *comInPipe, sc_fifo<CompressedT> *comOutPipe, sc_fifo<CompressedT> *decomInPipe, sc_fifo<SensorT> *decomOutPipe, ICompressionSetup<SensorT, ModelT>* setup, ICompressionCompress<SensorT, CompressedT, ModelT>* compressor, ICompressionDecompress<SensorT, CompressedT, ModelT>* decompressor) :
        sc_module(name),
        _comInPipe(comInPipe),
        _comOutPipe(comOutPipe),
        _decomInPipe(decomInPipe),
        _decomOutPipe(decomOutPipe),
        _setup(setup),
        _compressor(compressor),
        _decompressor(decompressor)
    {
        SC_THREAD(setup_state);
        SC_THREAD(decompress_state);
        dont_initialize();
        sensitive << decompress_e;
        SC_THREAD(compress_state);
        dont_initialize();
        sensitive << compress_e;
    };
    SC_HAS_PROCESS(Compression);


private:
    void setup_state() {
        bool status;
        SensorT data;

        do{
            wait(_comInPipe->data_written_event());
            data = _comInPipe->read();
            setupDataBuffer.push(data);
            status = _setup->setup(data);
        } while (status == false);

        _compressor->setModel(_setup);
        _decompressor->setModel(_setup);

        decompress_e.notify();

        while(setupDataBuffer.size() > 0)
        {
            data = setupDataBuffer.front();
            setupDataBuffer.pop();
            CompressedT dataC = _compressor->encode(data);
            _comOutPipe->write(dataC);
        }

        compress_e.notify();
    };

   

    void compress_state() {
        SensorT sensorData;
        CompressedT comData;

        while (true) {
            wait(_comInPipe->data_written_event());
            sensorData = _comInPipe->read();
            comData = _compressor->encode(sensorData);
            _comOutPipe->write(comData);
        }
    }

    void decompress_state() {
        SensorT sensorData;
        CompressedT comData;

        while (true) {
            wait(_decomInPipe->data_written_event());
            comData = _decomInPipe->read();
            sensorData = _decompressor->decode(comData);
            std::cout << "Received decompressed data: " << sensorData << std::endl;
            //_decomOutPipe->write(sensorData);
        }
    }

    sc_fifo<SensorT> *_comInPipe;
    sc_fifo<CompressedT>* _comOutPipe;
    sc_fifo<CompressedT>* _decomInPipe;
    sc_fifo<SensorT> *_decomOutPipe;
    ICompressionSetup<SensorT,ModelT> *_setup;
    ICompressionCompress<SensorT, CompressedT, ModelT> *_compressor;
    ICompressionDecompress<SensorT, CompressedT, ModelT> *_decompressor;

    std::queue<SensorT> setupDataBuffer;
    sc_event compress_e;
    sc_event decompress_e;
};



#endif


