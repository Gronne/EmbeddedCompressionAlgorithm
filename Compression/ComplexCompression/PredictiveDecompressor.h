#pragma once
#include "ICompressionDecompress.h"
#include <deque>


template<class DecompressT, class CompressT, class ModelT>
class PredictiveDecompressor : public ICompressionDecompress<DecompressT, CompressT, ModelT>
{
public:
	PredictiveDecompressor() {};
	~PredictiveDecompressor() {};

	DecompressT decode(CompressT error) { 
		//Predict point
		DecompressT predictedPoint = predictPoint(_coefficients, &_dataBuffer);

		//Get sensor data by adding error
		DecompressT sensorData = predictedPoint + error;

		//Push sensorData into list
		_dataBuffer.push_front(sensorData);
		_dataBuffer.pop_back();

		//Return sensorData
		return sensorData;
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