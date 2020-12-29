#pragma once
#include "../Input_Communication/Package.h"

template <class DecompressT, class CompressT>
class ICompressionDecompress
{
public:
	virtual DecompressT decode(CompressT) = 0;

private:
	

};

