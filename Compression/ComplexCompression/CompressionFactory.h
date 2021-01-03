#pragma once
#include "Compressor.h"
#include "ComplexCompressorProducer.h"
#include "SimpleCompressorProducer.h"


class CompressionFactory {
public:
	using SimpleCompressT = SimpleCompressorProducer::SimpleCompressT;
	using ComplexCompressT = ComplexCompressorProducer::ComplexCompressT;

	template<class T>
	using SimpleModelT = SimpleCompressorProducer::SimpleModelT<T>;
	template<class T>
	using ComplexModelT = ComplexCompressorProducer::ComplexModelT<T>;

	template<class T, int prediction_size = 3>
	static Compression<T, ComplexCompressT, ComplexModelT<T>>* MakeComplexCompression(sc_fifo<T> *comInPipe, sc_fifo<ComplexCompressT> *comOutPipe, sc_fifo<ComplexCompressT> *decomInPipe, sc_fifo<T> *decomOutPipe) {
		return ComplexCompressorProducer::Produce(comInPipe, comOutPipe, decomInPipe, decomOutPipe);
	};

	template<class T>
	static Compression<T, SimpleCompressT, SimpleModelT<T>>* MakeSimpleCompression(sc_fifo<T>* comInPipe, sc_fifo<SimpleCompressT>* comOutPipe, sc_fifo<SimpleCompressT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return SimpleCompressorProducer::Produce(comInPipe, comOutPipe, decomInPipe, decomOutPipe);
	};
};