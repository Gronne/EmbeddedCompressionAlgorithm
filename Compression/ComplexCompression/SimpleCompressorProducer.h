#pragma once

#include "../Input_Communication/SensorFactory.h"
#include "Compressor.h"
#include "HuffmanCompressor.h"
#include "HuffmanDecompressor.h"
#include "HuffmanSetup.h"
#include "Compressor.h"


class SimpleCompressorProducer
{
public:
	using SimpleCompressT = string;
	template<class T>
	using SimpleModelT = Node<typename T::value_type>;

	template<class T>
	static Compression<T, SimpleCompressT, SimpleModelT<T>>* Produce(sc_fifo<T>* comInPipe, sc_fifo<SimpleCompressT>* comOutPipe, sc_fifo<SimpleCompressT>* decomInPipe, sc_fifo<T>* decomOutPipe) {
		return new Compression<T, SimpleCompressT, SimpleModelT<T>>( "SimpleCompression", 
																	 comInPipe, 
																	 comOutPipe, 
																	 decomInPipe, 
																	 decomOutPipe, 
																	 new HuffmanSetup<T>("HuffmanSetup"), 
																	 new HuffmanCompressor<T, SimpleCompressT>("HuffmanCompressor"), 
																	 new HuffmanDecompressor<T, SimpleCompressT>("HuffmanDecompressor")
																   );
	};

};
