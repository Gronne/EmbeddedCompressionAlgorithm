#pragma once
#include "ICompressionSetup.h"
#include <vector>
#include <array>
#include <math.h>

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
		std::vector<SensorT> autocorrelation = calcAutocorrelation(&_periodeData, predictionSize+1);	
		std::vector<SensorT> autoVector = createAutoVector(&autocorrelation);
		std::vector<SensorT> autoMatrix = createAutoMatrix(&autocorrelation);

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


	std::vector<SensorT> calcAutocorrelation(std::vector<SensorT>* periodeData, int length) {
		std::vector<SensorT> autocorrelation;
		
		return autocorrelation;
	}


	std::vector<SensorT> createAutoVector(std::vector<SensorT>* autocorrelation) {
		std::vector<SensorT> autoVector;
		for (int index = 1; index < autocorrelation->size(); ++index)
			autoVector.push_back(autocorrelation->at(index));
		return autoVector;
	}


	std::vector<SensorT> createAutoMatrix(std::vector<SensorT>* autocorrelation) {
		std::vector<SensorT> autoMatrix;
		int matSize = autocorrelation->size() - 1;
		for (int row = 0; row < matSize; ++row)
			for (int col = 0; col < matSize; ++col)
				autoMatrix.push_back(autocorrelation->at(abs(row - col)));
		return autoMatrix;
	}


	std::vector<SensorT> inverseMatrix(std::vector<SensorT>* autoMatrix) {
		std::vector<SensorT> invMatrix;

		return invMatrix;
	}


	ModelT calcCoefficients(std::vector<SensorT>* invMatrix, std::vector<SensorT>* autoVector) {
		ModelT coefficients;
		std::vector<SensorT> result = multMatWVec(invMatrix, autoVector);
		for (auto elem : result)
			coefficients.push_back(ModelT::value_type(elem));
		return coefficients;
	}

	
	std::vector<SensorT> multMatWVec(std::vector<SensorT>* matrix, std::vector<SensorT>* vector) {
		std::vector<SensorT> resultVec;

		return resultVec;
	}


	std::vector<SensorT> _periodeData;
	ModelT _coefficients;
};