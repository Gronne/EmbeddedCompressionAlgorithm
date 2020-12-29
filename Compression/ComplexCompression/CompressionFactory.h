#pragma once
#include "Compressor.h"
#include "PredictiveSetup.h"
#include "PredictiveCompressor.h"
#include "PredictiveDecompressor.h"
#include "../Input_Communication/SensorFactory.h"
#include "../Input_Communication/Communication.h"

class CompressionFactory {
public:
	using SimpleCompressT = string;
	using ComplexCompressT = SensorFactory::SinusSensorSubT;

	template<typename T>
	using SimpleModelT = Node<typename T::value_type>;
	using ComplexModelT = int;

	template<class T>
	static Compression<T, ComplexCompressT, ComplexModelT>* MakeComplexCompression(sc_fifo<T> *comInPipe, sc_fifo<ComplexCompressT> *comOutPipe, sc_fifo<ComplexCompressT> *decomInPipe, sc_fifo<T> *decomOutPipe) {
		return new Compression<T, ComplexCompressT, ComplexModelT>("ComplexCompression", comInPipe, comOutPipe, decomInPipe, decomOutPipe, new PredictiveSetup<T>(), new PredictiveCompressor<T, ComplexCompressT>(), new PredictiveDecompressor<T, ComplexCompressT>());
	};

	template<class T>
	static Compression<T, SimpleCompressT, SimpleModelT<T>>* MakeSimpleCompression(sc_fifo<T>* comInPipe, sc_fifo<SimpleCompressT>* comOutPipe, sc_fifo<SimpleCompressT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return new Compression<T, SimpleCompressT, SimpleModelT<T>>("SimpleCompression", comInPipe, comOutPipe, decomInPipe, decomOutPipe, new HuffmanSetup<T>("HuffmanSetup"), new HuffmanCompressor<T, SimpleCompressT>("HuffmanCompressor"), new HuffmanDecompressor<T, SimpleCompressT>("HuffmanDecompressor"));
	};
};