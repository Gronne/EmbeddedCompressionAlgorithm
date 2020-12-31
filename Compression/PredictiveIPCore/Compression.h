#pragma once
#include "../ComplexCompression/ICompressionCompress.h"
#include "../ComplexCompression/ICompressionDecompress.h"
#include "../ComplexCompression/ICompressionSetup.h"
#include "Datatypes.h"
#include <queue>
#include <vector>
class Compression :
    public sc_module
{
public:
    
    using SensorT = int;
    using ModelT = std::vector<int>;
    using CompressedT = int;

    sc_in<bool> inSensorDataReady;
    sc_out<bool> outModelReady;
    sc_in<SensorT> inSensorData;
    sc_out<ModelT> outModelCoefficientData;

    Compression(sc_module_name name) :
        sc_module(name)
    {
        SC_THREAD(setup_state);

        SC_THREAD(decompress_state);
        dont_initialize();
        SC_THREAD(compress_state);
        dont_initialize();
    };
    SC_HAS_PROCESS(Compression);

private:
    void setup_state() {
        bool status;
        SensorT data;

        do {
            wait(_comInPipe->data_written_event());
            data = _comInPipe->read();
            setupDataBuffer.push(data);
            status = _setup->setup(data);
        } while (status == false);

        _compressor->setModel(_setup);
        _decompressor->setModel(_setup);

        decompress_e.notify();

        while (setupDataBuffer.size() > 0)
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

    ICompressionSetup<SensorT, ModelT>* _setup;
    ICompressionCompress<SensorT, CompressedT, ModelT>* _compressor;
    ICompressionDecompress<SensorT, CompressedT, ModelT>* _decompressor;
    std::queue<SensorT> setupDataBuffer;

};

