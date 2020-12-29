#pragma once
#include "ICompressionDecompress.h"


template<class DecompressT, class CompressT>
class PredictiveDecompressor : public ICompressionDecompress<DecompressT, CompressT>
{
public:
	PredictiveDecompressor() {};
	~PredictiveDecompressor() {};

	DecompressT decode(CompressT compressedData) { 
		return DecompressT(compressedData); 
	};

	void setModel(ICompressionSetup<DecompressT> *setup) {

	};

private:

};