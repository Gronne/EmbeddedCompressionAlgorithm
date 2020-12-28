#pragma once
#include "ICompressionCompress.h"

template<class T>
class PredictiveCompressor : public ICompressionCompress<T>
{
public:
	PredictiveCompressor() {};
	~PredictiveCompressor() {};

	void encode(T) { };

private:


};