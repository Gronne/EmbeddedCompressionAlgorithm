#pragma once
#include "ICompressionCompress.h"

template<class DecompressT, class CompressT>
class PredictiveCompressor : public ICompressionCompress<DecompressT, CompressT>
{
public:
	PredictiveCompressor() {};
	~PredictiveCompressor() {};

	CompressT encode(DecompressT) { return CompressT(); };

private:


};