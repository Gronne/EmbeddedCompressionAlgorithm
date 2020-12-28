#pragma once
#include "../Input_Communication/Package.h"

template <class T>
class ICompressionSetup
{
public:
	virtual bool setup(T) = 0;

private:


};