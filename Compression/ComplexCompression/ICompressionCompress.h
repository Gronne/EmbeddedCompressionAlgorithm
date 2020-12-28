#pragma once
#include "../Input_Communication/Package.h"

template <class T>
class ICompressionCompress
{
public:
	virtual void encode(T) = 0;

private:


};