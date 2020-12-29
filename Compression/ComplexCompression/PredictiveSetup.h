#pragma once
#include "ICompressionSetup.h"

template<class T, class ModelT = int>
class PredictiveSetup : public ICompressionSetup<T, ModelT>
{
public:
	PredictiveSetup() {};
	~PredictiveSetup() {};

	bool setup(T) { 
		return _counter++>= 10; 
	};

	ModelT* getModel() { return &ModelT(); };

private:
	int _counter = 0;
};