#pragma once
#include "../Input_Communication/Package.h"

template <class DataT, class ModelT>
class ICompressionSetup
{
public:
	virtual bool setup(DataT) = 0;
	virtual ModelT getModel() = 0;
private:


};