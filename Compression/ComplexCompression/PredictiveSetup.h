#pragma once
#include "ICompressionSetup.h"

template<class T>
class PredictiveSetup : public ICompressionSetup<T>
{
public:
	PredictiveSetup() {};
	~PredictiveSetup() {};

	bool setup(T) { return false; };

private:

};