#pragma once
#include "../Input_Communication/Package.h"
#include "ICompressionSetup.h"

template <class DecompressT, class CompressT, class ModelT>
class ICompressionCompress
{
public:
	virtual CompressT encode(DecompressT) = 0;
	virtual void setModel(ICompressionSetup<DecompressT,ModelT>*) = 0;
private:


};