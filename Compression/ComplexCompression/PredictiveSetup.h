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


	bool setup(SensorT dataPoint) { 
		//Add new datapoint ot periodeData
		_periodeData.push_back(dataPoint);

		//Return false untill periode detected
		if (detectPeriode(&_periodeData) == false)
			return false;
		
		//Create autoCorrelation matrix and vector. 3 to keep it simple
		std::array<SensorT,4> autocorrelation = calcAutocorrelation(&_periodeData);	
		std::array<SensorT,3> autoVector = createAutoVector(&autocorrelation);
		std::array<SensorT, 3 * 3> autoMatrix = createAutoMatrix(&autocorrelation);

		//Invert matrix
		std::array<SensorT,3*3> invMatrix = inverse3x3Matrix(&autoMatrix);

		//multiply inverted matrix and vector to get coefficients
		_coefficients = calcCoefficients(&invMatrix, &autoVector);

		//Return True
		return true;
	};


	ModelT* getModel() { return &_coefficients; };


private:
	bool detectPeriode(std::vector<SensorT> *periodeData) {
		return periodeData->size() > 200;
	};


	std::array<SensorT, 4> calcAutocorrelation(std::vector<SensorT>* periodeData) {
		std::array<SensorT, 4> autocorrelation;
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


	std::array<SensorT, 3> createAutoVector(std::array<SensorT, 4>* autocorrelation) {
		std::array<SensorT, 3> autoVector;
		for (int index = 1; index < autocorrelation->size(); ++index)
			autoVector.at(index-1) = autocorrelation->at(index);
		return autoVector;
	}


	std::array<SensorT, 3*3> createAutoMatrix(std::array<SensorT, 4>* autocorrelation) {
		std::array<SensorT, 3*3> autoMatrix;
		int matSize = autocorrelation->size() - 1;
		for (int row = 0; row < matSize; ++row)
			for (int col = 0; col < matSize; ++col)
				autoMatrix.at(matSize*row + col) = autocorrelation->at(abs(row - col));
		return autoMatrix;
	}


	std::array<SensorT, 3*3> inverse3x3Matrix(std::array<SensorT, 3*3>* autoMatrix) {
		//Create same size identity matrix
		std::array<SensorT, 3 * 3> invMatrix { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

		//Minus First row from second and third
		scaleSubstraction(autoMatrix, &invMatrix, 0, 1, 0);
		scaleSubstraction(autoMatrix, &invMatrix, 0, 2, 0);
		//Scale rows
		scaleRows(autoMatrix, &invMatrix);

		//Minus second row from third
		scaleSubstraction(autoMatrix, &invMatrix, 1, 2, 1);
		scaleRows(autoMatrix, &invMatrix);

		//Minus second row from first
		scaleSubstraction(autoMatrix, &invMatrix, 1, 0, 1);
		scaleRows(autoMatrix, &invMatrix);

		//Minus third row from first and second
		scaleSubstraction(autoMatrix, &invMatrix, 2, 0, 2);
		scaleSubstraction(autoMatrix, &invMatrix, 2, 1, 2);
		scaleRows(autoMatrix, &invMatrix);

		//Return inverse matrix
		return invMatrix;
	}


	void scaleSubstraction(std::array<SensorT, 3 * 3>* originalMatrix, std::array<SensorT, 3 * 3>* IdentityMatrix, int primary, int secondary, int scaleCol) {
		//Get vectors from original
		std::array<SensorT, 3> primaryRowOri = getRow(originalMatrix, primary);
		std::array<SensorT, 3> secondaryRowOri = getRow(originalMatrix, secondary);
		//Get vectors from identity
		std::array<SensorT, 3> primaryRowIde = getRow(IdentityMatrix, primary);		
		std::array<SensorT, 3> secondaryRowIde = getRow(IdentityMatrix, secondary);

		//Scale original vectors
		SensorT primScaling = primaryRowOri.at(scaleCol);
		SensorT secScaling = secondaryRowOri.at(scaleCol);
		scaleRow(&primaryRowOri, secScaling);
		scaleRow(&secondaryRowOri, primScaling);
		//Scale identity vectors
		scaleRow(&primaryRowIde, secScaling);
		scaleRow(&secondaryRowIde, primScaling);

		//Substract original vectors
		substractRows(&primaryRowOri, &secondaryRowOri);
		//Substract idenity vectors
		substractRows(&primaryRowIde, &secondaryRowIde);


		//Set substracted row back into Original
		setRow(originalMatrix, &secondaryRowOri, secondary);
		//Set substracted row back into Identity
		setRow(IdentityMatrix, &secondaryRowIde, secondary);
	}


	void substractRows(std::array<SensorT, 3*3> *matrix, int primary, int secondary) {
		for (int col = 0; col < 3; ++col)
			matrix->at(3 * secondary + col) = matrix->at(3 * secondary + col) - matrix->at(3 * primary + col);
	}


	std::array<SensorT, 3> substractRows(std::array<SensorT, 3>* vecPrimary, std::array<SensorT, 3>* vecSecondary) {
		std::array<SensorT, 3> newVec{};
		for (int col = 0; col < 3; ++col)
			vecSecondary->at(col) = vecSecondary->at(col) - vecPrimary->at(col);
		return newVec;
	}


	void scaleRows(std::array<SensorT, 3 * 3>* originalMatrix, std::array<SensorT, 3 * 3>* identityMatrix) {
		for (int index = 0; index < 3; ++index) {
			SensorT scalingFactor = 1/originalMatrix->at(index * 3 + index);
			scaleRow(originalMatrix, index, scalingFactor);
			scaleRow(identityMatrix, index, scalingFactor);
		}
	}


	void scaleRow(std::array<SensorT, 3*3> *matrix, int rowNr, SensorT scalingFactor) {
		int matrixSize = 3;
		for (int index = 0; index < matrixSize; ++index)
			matrix->at(matrixSize * rowNr + index) = matrix->at(matrixSize * rowNr + index) * scalingFactor;
	}

	void scaleRow(std::array<SensorT, 3>* vec, SensorT scalingFactor) {
		int matrixSize = 3;
		for (int index = 0; index < matrixSize; ++index)
			vec->at(index) = vec->at(index) * scalingFactor;
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
		for (auto &elem : result)
			coefficients.push_back(ModelT::value_type(elem));
		return coefficients;
	}

	
	std::array<SensorT, 3> multSymMatWVec(std::array<SensorT, 3*3>* matrix, std::array<SensorT, 3>* vector) {
		std::array<SensorT, 3> resultVec;
		int matSize = vector->size();
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