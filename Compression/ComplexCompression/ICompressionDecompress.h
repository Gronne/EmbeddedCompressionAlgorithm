#pragma once
#include "../Input_Communication/Package.h"
#include "ICompressionSetup.h"

template <class DecompressT, class CompressT, class ModelT>
class ICompressionDecompress
{
public:
	virtual DecompressT decode(CompressT) = 0;
	virtual void setModel(ICompressionSetup<DecompressT,ModelT>*) = 0;
private:
	

};

