#pragma once
#include "Compressor.h"
#include "ComplexCompressorProducer.h"
#include "SimpleCompressorProducer.h"


class CompressionFactory {
public:
	using SimpleCompressT = SimpleCompressorProduct::SimpleCompressT;
	using ComplexCompressT = ComplexCompressorProduct::ComplexCompressT;

	template<class T>
	using SimpleModelT = SimpleCompressorProduct::SimpleModelT<T>;
	template<class T>
	using ComplexModelT = ComplexCompressorProduct::ComplexModelT<T>;

	template<class T, int prediction_size = 3>
	static Compression<T, ComplexCompressT, ComplexModelT<T>>* MakeComplexCompression(sc_fifo<T> *comInPipe, sc_fifo<ComplexCompressT> *comOutPipe, sc_fifo<ComplexCompressT> *decomInPipe, sc_fifo<T> *decomOutPipe) {
		return ComplexCompressorProduct::Product(comInPipe, comOutPipe, decomInPipe, decomOutPipe);
	};

	template<class T>
	static Compression<T, SimpleCompressT, SimpleModelT<T>>* MakeSimpleCompression(sc_fifo<T>* comInPipe, sc_fifo<SimpleCompressT>* comOutPipe, sc_fifo<SimpleCompressT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return SimpleCompressorProduct::Product(comInPipe, comOutPipe, decomInPipe, decomOutPipe);
	};
};