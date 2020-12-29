#pragma once
#include "ICompressionSetup.h"

template<class T>
class PredictiveSetup : public ICompressionSetup<T>
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