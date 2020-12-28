#pragma once
#include "ICompressionDecompress.h"


template<class T>
class PredictiveDecompressor : public ICompressionDecompress<T>
{
public:
	PredictiveDecompressor() {};
	~PredictiveDecompressor() {};

	void decode(T) { };

private:

};