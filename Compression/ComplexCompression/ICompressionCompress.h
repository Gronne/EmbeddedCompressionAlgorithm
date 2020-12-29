#pragma once
#include "../Input_Communication/Package.h"
#include "ICompressionSetup.h"

template <class DecompressT, class CompressT>
class ICompressionCompress
{
public:
	virtual CompressT encode(DecompressT) = 0;
	virtual void setModel(ICompressionSetup<DecompressT>*) = 0;
private:


};