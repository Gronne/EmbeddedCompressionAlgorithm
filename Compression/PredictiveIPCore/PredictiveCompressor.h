#pragma once
#include "../ComplexCompression/ICompressionCompress.h"
#include <deque>
#include <iostream>
#include "Datatypes.h"
template<class DecompressT, class CompressT, class ModelT>
class PredictiveCompressor : public ICompressionCompress<DecompressT, CompressT, ModelT>, public sc_module
{
public:
	//
	sc_in<bool> inClk;
	sc_in<bool> inBufferDataReady;
	sc_in<bool> inSensorDataReady;
	sc_out<bool> outCompressorDataReady;
	//
	PredictiveCompressor(sc_module_name name):sc_module(name) {};
	~PredictiveCompressor() { delete _coefficients; };

	CompressT encode(DecompressT sensorData) {
		//Predict point
		DecompressT predictedPoint = predictPoint(_coefficients, &_dataBuffer);

		//Calculate error
		CompressT error = sensorData - predictedPoint;

		//Push sensorData into list
		_dataBuffer.push_front(sensorData);
		_dataBuffer.pop_back();

		//Return error
		return error;
	};

	void setModel(ICompressionSetup<DecompressT, ModelT>* setup) {
		_coefficients = setup->getModel();
		for (auto& e : *_coefficients)
			_dataBuffer.push_front(0);
	};

private:
	DecompressT predictPoint(ModelT* coefficients, std::deque<DecompressT>* dataBuffer) {
		DecompressT newPoint = coefficients->at(0) * dataBuffer->at(0);
		for (int index = 1; index < coefficients->size(); ++index)
			newPoint = newPoint + coefficients->at(index) * dataBuffer->at(index);
		return newPoint;
	}

	ModelT* _coefficients;
	std::deque<DecompressT> _dataBuffer;
};