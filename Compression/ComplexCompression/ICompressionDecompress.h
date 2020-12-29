#pragma once
#include "../Input_Communication/Package.h"
#include "ICompressionSetup.h"

template <class DecompressT, class CompressT>
class ICompressionDecompress
{
public:
	virtual DecompressT decode(CompressT) = 0;
	virtual void setModel(ICompressionSetup<DecompressT,CompressT>*) = 0;
private:
	

};

