#pragma once
#include "ICompressionCompress.h"

template<class DecompressT, class CompressT, class ModelT>
class PredictiveCompressor : public ICompressionCompress<DecompressT, CompressT, ModelT>
{
public:
	PredictiveCompressor() {};
	~PredictiveCompressor() {};

	CompressT encode(DecompressT sensorData) { 
		return CompressT(sensorData); 
	};

	void setModel(ICompressionSetup<DecompressT,ModelT> *setup) {

	};

private:


};