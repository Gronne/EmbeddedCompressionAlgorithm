#pragma once
#include "Compressor.h"
#include "PredictiveSetup.h"
#include "PredictiveCompressor.h"
#include "PredictiveDecompressor.h"
#include "../Input_Communication/SensorFactory.h"
#include "../Input_Communication/Communication.h"

class CompressionFactory {
public:
	using SimpleCompressT = int;
	using ComplexCompressT = int;

	template<class T>
	static Compression<T, ComplexCompressT>* MakeComplexCompression(sc_fifo<T> *comInPipe, sc_fifo<ComplexCompressT> *comOutPipe, sc_fifo<ComplexCompressT> *decomInPipe, sc_fifo<T> *decomOutPipe) {
		return new Compression<T, ComplexCompressT>("ComplexCompression", comInPipe, comOutPipe, decomInPipe, decomOutPipe, new PredictiveSetup<T>(), new PredictiveCompressor<T>(), new PredictiveDecompressor<T>());
	};

	template<class T>
	static Compression<T, SimpleCompressT>* MakeSimpleCompression(sc_fifo<T>* comInPipe, sc_fifo<SimpleCompressT>* comOutPipe, sc_fifo<SimpleCompressT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return new Compression<T, SimpleCompressT>("SimpleCompression", comInPipe, comOutPipe, decomInPipe, decomOutPipe, new PredictiveSetup<T>(), new PredictiveCompressor<T>(), new PredictiveDecompressor<T>());
	};
};