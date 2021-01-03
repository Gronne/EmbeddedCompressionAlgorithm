#pragma once

#include <vector>

#include "../Input_Communication/SensorFactory.h"
#include "Compressor.h"
#include "PredictiveCompressor.h"
#include "PredictiveDecompressor.h"
#include "PredictiveSetup.h"
#include "Compressor.h"


class ComplexCompressorProduct
{
public:
	using ComplexCompressT = SensorFactory::SinusSensorSubT;
	template<class T>
	using ComplexModelT = std::vector<T>;

	template<class T, int prediction_size = 3>
	static Compression<T, ComplexCompressT, ComplexModelT<T>>* Product(sc_fifo<T>* comInPipe, sc_fifo<ComplexCompressT>* comOutPipe, sc_fifo<ComplexCompressT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return new Compression<T, ComplexCompressT, ComplexModelT<T>>(	"ComplexCompression", 
																		comInPipe, 
																		comOutPipe, 
																		decomInPipe, 
																		decomOutPipe, 
																		new PredictiveSetup<T, ComplexCompressorProduct::ComplexModelT<T>, prediction_size>(), 
																		new PredictiveCompressor<T, ComplexCompressT, ComplexCompressorProduct::ComplexModelT<T>>(), 
																		new PredictiveDecompressor<T, ComplexCompressT, ComplexCompressorProduct::ComplexModelT<T>>()
																	  );
	};

};
