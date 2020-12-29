#pragma once
#include "ICompressionCompress.h"

template<class DecompressT, class CompressT>
class PredictiveCompressor : public ICompressionCompress<DecompressT, CompressT>
{
public:
	PredictiveCompressor() {};
	~PredictiveCompressor() {};

	CompressT encode(DecompressT sensorData) { 
		return CompressT(sensorData); 
	};

	void setModel(ICompressionSetup<DecompressT,CompressT> *setup) {

	};

private:


};