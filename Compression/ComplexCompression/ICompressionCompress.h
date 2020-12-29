#pragma once
#include "../Input_Communication/Package.h"

template <class DecompressT, class CompressT>
class ICompressionCompress
{
public:
	virtual CompressT encode(DecompressT) = 0;

private:


};