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
    sc_fifo<CompressionFactory::SimpleCompressT> compressorToTransmitterSimplePipe;
    sc_fifo <CompressionFactory::SimpleCompressT> receiverToDecompressorSimplePipe;
    sc_fifo<SensorFactory::TextFileSensorSubT> decompressorOutSimplePipe;
    //Complex 
    sc_fifo<SensorFactory::SinusSensorSubT> sensorToCompressorComplexPipe;
    sc_fifo<CompressionFactory::ComplexCompressT> compressorToTransmitterComplexPipe;
    sc_fifo<CompressionFactory::ComplexCompressT> receiverToDecompressorComplexPipe;
    sc_fifo<SensorFactory::SinusSensorSubT> decompressorOutComplexPipe;


    //--------Filters--------
    //Simple
    auto* textSensor = SensorFactory::CreateTextFileSensor(&sensorToCompressorSimplePipe);
    Communication<CompressionFactory::SimpleCompressT> simpleCommunicator(&compressorToTransmitterSimplePipe, &receiverToDecompressorSimplePipe);
    auto *simpleCompression = CompressionFactory::MakeSimpleCompression<SensorFactory::TextFileSensorSubT>(&sensorToCompressorSimplePipe, &compressorToTransmitterSimplePipe, &receiverToDecompressorSimplePipe, &decompressorOutSimplePipe);

    //Complex
    auto* sinusSensor = SensorFactory::CreateSinusSensor(&sensorToCompressorComplexPipe);
    Communication<CompressionFactory::ComplexCompressT> complexCommunicator(&compressorToTransmitterComplexPipe, &receiverToDecompressorComplexPipe);
    auto *complexCompression = CompressionFactory::MakeComplexCompression<SensorFactory::SinusSensorSubT, 3>(&sensorToCompressorComplexPipe, &compressorToTransmitterComplexPipe, &receiverToDecompressorComplexPipe, &decompressorOutComplexPipe);


    //---------Start---------
    sc_start(200, SC_MS);

    //---------Clean---------
    delete textSensor;
    delete sinusSensor;
    delete simpleCompression;
    delete complexCompression;

    //Terminate
    return 0;
}


