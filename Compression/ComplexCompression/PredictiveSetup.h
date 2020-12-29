#pragma once
#include "ICompressionSetup.h"

template<class T, class ModelT>
class PredictiveSetup : public ICompressionSetup<T, ModelT>
{
public:
	PredictiveSetup() {};
	~PredictiveSetup() {};

	bool setup(T) { 
		return _counter++>= 10; 
	};

private:
	int _counter = 0;
};