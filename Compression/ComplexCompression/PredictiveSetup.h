#pragma once
#include "ICompressionSetup.h"
#include <vector>
#include <array>

template<class SensorT, class ModelT>
class PredictiveSetup : public ICompressionSetup<SensorT, ModelT>
{
public:
	PredictiveSetup() {};
	~PredictiveSetup() {};

	// ------------------------------------------------------------------------
	// !!!!! SHOULD BE MADE FROM VECTOR TO ARRAYS WITH TEMPLATES OR CONST !!!!!
	// ------------------------------------------------------------------------


	bool setup(SensorT dataPoint) { 
		//Add new datapoint ot periodeData
		_periodeData.push_back(dataPoint);

		//Return false untill periode detected
		if (detectPeriode(&_periodeData) == false)
			return false;
		
		//Create autoCorrelation matrix and vector. 3 to keep it simple
		const int predictionSize = 3; 
		std::vector<SensorT> autoVector = calcAutoVec(&_periodeData, predictionSize);	
		std::vector<SensorT> autoMatrix = createAutoMatrix(&autoVector, predictionSize);

		//Invert matrix
		std::vector<SensorT> invMatrix = inverseMatrix(&autoMatrix);

		//multiply inverted matrix and vector to get coefficients
		_coefficients = calcCoefficients(&invMatrix, &autoVector);

		//Return True
		return true;
	};


	ModelT* getModel() { return &_coefficients; };


private:
	bool detectPeriode(std::vector<SensorT> *periodeData) {
		return periodeData->size() > 10;
	};


	std::vector<SensorT> calcAutoVec(std::vector<SensorT>* periodeData, int length) {
		std::vector<SensorT> autoVec;

		return autoVec;
	}


	std::vector<SensorT> createAutoMatrix(std::vector<SensorT>* autoVec, int length) {
		std::vector<SensorT> autoMatrix;

		return autoMatrix;
	}


	std::vector<SensorT> inverseMatrix(std::vector<SensorT>* autoMatrix) {
		std::vector<SensorT> invMatrix;

		return invMatrix;
	}


	ModelT calcCoefficients(std::vector<SensorT>* invMatrix, std::vector<SensorT>* autoVecor) {
		ModelT coefficients;

		return coefficients;
	}


	std::vector<SensorT> _periodeData;
	ModelT _coefficients;
};