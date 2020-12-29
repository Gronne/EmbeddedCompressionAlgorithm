#pragma once
#include "Compressor.h"
#include "PredictiveSetup.h"
#include "PredictiveCompressor.h"
#include "PredictiveDecompressor.h"
#include "../Input_Communication/SensorFactory.h"
#include "../Input_Communication/Communication.h"

class CompressionFactory {
public:
	using SimpleCommunicationT = int;
	using ComplexCommunicationT = int;

	template<class T>
	static Compression<T, ComplexCommunicationT>* MakeComplexCompression(sc_fifo<T> *comInPipe, sc_fifo<ComplexCommunicationT> *comOutPipe, sc_fifo<ComplexCommunicationT> *decomInPipe, sc_fifo<T> *decomOutPipe) {
		return new Compression<T>("ComplexCompression", comInPipe, comOutPipe, decomInPipe, decomOutPipe, new PredictiveSetup<T>(), new PredictiveCompressor<T>(), new PredictiveDecompressor<T>());
	};

	template<class T>
	static Compression<T, SimpleCommunicationT>* MakeSimpleCompression(sc_fifo<T>* comInPipe, sc_fifo<SimpleCommunicationT>* comOutPipe, sc_fifo<SimpleCommunicationT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return new Compression<T>("SimpleCompression", comInPipe, comOutPipe, decomInPipe, decomOutPipe, new PredictiveSetup<T>(), new PredictiveCompressor<T>(), new PredictiveDecompressor<T>());
	};
};