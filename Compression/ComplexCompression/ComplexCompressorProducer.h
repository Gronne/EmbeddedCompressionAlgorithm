#pragma once

#include <vector>

#include "../Input_Communication/SensorFactory.h"
#include "Compressor.h"
#include "PredictiveCompressor.h"
#include "PredictiveDecompressor.h"
#include "PredictiveSetup.h"
#include "Compressor.h"


class ComplexCompressorProducer
{
public:
	using ComplexCompressT = SensorFactory::SinusSensorSubT;
	template<class T>
	using ComplexModelT = std::vector<T>;

	template<class T, int prediction_size = 3>
	static Compression<T, ComplexCompressT, ComplexModelT<T>>* Produce(sc_fifo<T>* comInPipe, sc_fifo<ComplexCompressT>* comOutPipe, sc_fifo<ComplexCompressT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return new Compression<T, ComplexCompressT, ComplexModelT<T>>(	"ComplexCompression", 
																		comInPipe, 
																		comOutPipe, 
																		decomInPipe, 
																		decomOutPipe, 
																		new PredictiveSetup<T, ComplexCompressorProducer::ComplexModelT<T>, prediction_size>(), 
																		new PredictiveCompressor<T, ComplexCompressT, ComplexCompressorProducer::ComplexModelT<T>>(), 
																		new PredictiveDecompressor<T, ComplexCompressT, ComplexCompressorProducer::ComplexModelT<T>>()
																	  );
	};

};
