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
		std::array<SensorT,3> autocorrelation = calcAutocorrelation(&_periodeData);	
		std::array<SensorT,3> autoVector = createAutoVector(&autocorrelation);
		std::array<SensorT,3*3> autoMatrix = createAutoMatrix(&autocorrelation);

		//Invert matrix
		std::array<SensorT,3*3> invMatrix = inverseMatrix(&autoMatrix);

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


	std::array<SensorT, 3> calcAutocorrelation(std::vector<SensorT>* periodeData) {
		std::array<SensorT, 3> autocorrelation;
		for (int lag = 0; lag < autocorrelation.size(); ++lag)
			autocorrelation.at(lag) = calcAutoWLag(periodeData, lag);
		return autocorrelation;
	}


	SensorT calcAutoWLag(std::vector<SensorT>* signal, int lag) {
		SensorT accumulatedValue = signal->at(0) * signal->at(lag);
		for (int index = 1; index + lag < signal->size(); ++index)
			accumulatedValue = accumulatedValue + signal->at(index) * signal->at(index + lag);	//Everything else will be 0
		return accumulatedValue;
	}


	std::array<SensorT, 3> createAutoVector(std::array<SensorT, 3>* autocorrelation) {
		std::array<SensorT, 3> autoVector;
		for (int index = 1; index < autocorrelation->size(); ++index)
			autoVector.at(index-1) = autocorrelation->at(index);
		return autoVector;
	}


	std::array<SensorT, 3*3> createAutoMatrix(std::array<SensorT, 3>* autocorrelation) {
		std::array<SensorT, 3*3> autoMatrix;
		int matSize = autocorrelation->size() - 1;
		for (int row = 0; row < matSize; ++row)
			for (int col = 0; col < matSize; ++col)
				autoMatrix.at(matSize*row + col) = autocorrelation->at(abs(row - col));
		return autoMatrix;
	}


	std::array<SensorT, 3*3> inverseMatrix(std::array<SensorT, 3*3>* autoMatrix) {
		std::array<SensorT, 3 * 3> invMatrix { };

		//Can only invert a 3x3 matrix


		return invMatrix;
	}


	void substractRows(std::array<SensorT, 3*3> *matrix, int primary, int secondary) {
		for (int col = 0; col < 3; ++col)
			matrix->at(3 * secondary + col) = matrix->at(3 * secondary + col) - matrix->at(3 * primary + col);
	}


	void scaleRow(std::array<SensorT, 3*3> *matrix, int rowNr, SensorT scalingFactor) {
		int matrixSize = 3;
		for (int index = 0; index < matrixSize; ++index)
			matrix->at(matrixSize * rowNr + index) = matrix->at(matrixSize * rowNr + index) * scalingFactor;
	}


	std::array<SensorT, 3> getRow(std::array<SensorT, 3*3> *matrix, int rowNr) {
		std::array<SensorT, 3> newRow;
		for (int col = 0; col < newRow.size(); ++col)
			newRow.at(col) = matrix->at(rowNr * newRow.size() + col);
		return newRow;
	}

	
	void setRow(std::array<SensorT, 3*3>*matrix, std::array<SensorT, 3>*vec, int rowNr) {
		for (int col = 0; col < vec->size(); ++col)
			matrix->at(rowNr * vec->size() + col) = vec->at(col);
	}


	ModelT calcCoefficients(std::array<SensorT, 3*3>* invMatrix, std::array<SensorT, 3>* autoVector) {
		ModelT coefficients;
		std::array<SensorT, 3> result = multSymMatWVec(invMatrix, autoVector);
		for (auto elem : result)
			coefficients.push_back(ModelT::value_type(elem));
		return coefficients;
	}

	
	std::array<SensorT, 3> multSymMatWVec(std::array<SensorT, 3*3>* matrix, std::array<SensorT, 3>* vector) {
		std::array<SensorT, 3> resultVec;
		int matSize = vector->size() - 1;
		for (int row = 0; row < matSize; ++row) {
			SensorT value = matrix->at(matSize*row + 0) * vector->at(0);
			for (int col = 1; col < matSize; ++col)
				value = value + matrix->at(matSize * row + col) * vector->at(col);
			resultVec.at(row) = value;
		}
		return resultVec;
	}


	std::vector<SensorT> _periodeData;
	ModelT _coefficients;
};