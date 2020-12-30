#pragma once
#include "ICompressionDecompress.h"


template<class DecompressT, class CompressT, class ModelT>
class PredictiveDecompressor : public ICompressionDecompress<DecompressT, CompressT, ModelT>
{
public:
	PredictiveDecompressor() {};
	~PredictiveDecompressor() {};

	DecompressT decode(CompressT compressedData) { 
		return DecompressT(compressedData); 
	};

	void setModel(ICompressionSetup<DecompressT,ModelT> *setup) {

	};

private:

};