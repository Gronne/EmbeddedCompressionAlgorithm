#pragma once
#include "Compressor.h"
#include "PredictiveSetup.h"
#include "PredictiveCompressor.h"
#include "PredictiveDecompressor.h"

template<class T>
class CompressionFactory {
public:
	static Compression<T>* MakeComplexCompression(sc_module_name name, sc_fifo<T> *in, sc_fifo<T> *out) {
		return new Compression<T>(name, in, out, new PredictiveSetup<T>(), new PredictiveCompressor<T>(), new PredictiveDecompressor<T>());;
	};

};