// ComplexCompression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HuffmanCompressor.h"
#include "HuffmanSetup.h"
#include "HuffmanDecompressor.h"
#include "Compressor.h"
#include "CompressionFactory.h"
#include "../Input_Communication/SensorFactory.h"
#include "../Input_Communication/Communication.h"

// Huffman coding algorithm
int sc_main(int argc, char** argv)
{
    //---------Pipes---------
    //Simple
    sc_fifo<SensorFactory::TextFileSensorSubT> sensorToCompressorSimplePipe;
    sc_fifo<CompressionFactory::SimpleCommunicationT> compressorToTransmitterSimplePipe;
    sc_fifo<CompressionFactory::SimpleCommunicationT> receiverToDecompressorSimplePipe;
    sc_fifo<SensorFactory::TextFileSensorSubT> decompressorOutSimplePipe;
    //Complex 
    sc_fifo<SensorFactory::SinusSensorSubT> sensorToCompressorComplexPipe;
    sc_fifo<CompressionFactory::ComplexCommunicationT> compressorToTransmitterComplexPipe;
    sc_fifo<CompressionFactory::ComplexCommunicationT> receiverToDecompressorComplexPipe;
    sc_fifo<SensorFactory::SinusSensorSubT> decompressorOutComplexPipe;


    //--------Filters--------
    //Simple
    SensorFactory::TextFileSensorT* textSensor = SensorFactory::CreateTextFileSensor(&sensorToCompressorSimplePipe);
    Communication<CompressionFactory::SimpleCommunicationT> simpleCommunicator(&compressorToTransmitterSimplePipe, &receiverToDecompressorSimplePipe);
    Compression<SensorFactory::TextFileSensorSubT, CompressionFactory::SimpleCommunicationT> *simpleCompression = CompressionFactory::MakeSimpleCompression<SensorFactory::TextFileSensorSubT>(&sensorToCompressorSimplePipe, &compressorToTransmitterSimplePipe, &receiverToDecompressorSimplePipe, &decompressorOutSimplePipe);
    //Complex
    SensorFactory::SinusSensorT* sinusSensor = SensorFactory::CreateSinusSensor(&sensorToCompressorComplexPipe);
    Communication<CompressionFactory::ComplexCommunicationT> complexCommunicator(&compressorToTransmitterComplexPipe, &receiverToDecompressorComplexPipe);
    Compression<SensorFactory::SinusSensorSubT, CompressionFactory::ComplexCommunicationT> *complexCompression = CompressionFactory::MakeComplexCompression<SensorFactory::SinusSensorSubT>(&sensorToCompressorComplexPipe, &compressorToTransmitterComplexPipe, &receiverToDecompressorComplexPipe, &decompressorOutComplexPipe);


    //---------Start---------
    sc_start(200, SC_MS);

    //---------Clean---------
    delete textSensor;
    delete sinusSensor;
    //delete simpleCompression;
    //delete complexCompression;

    //Terminate
    return 0;
}


