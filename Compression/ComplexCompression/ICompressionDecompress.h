#pragma once
#include "../Input_Communication/Package.h"

template <class T>
class ICompressionDecompress
{
public:
	virtual void decode(T) = 0;

private:
	

};

