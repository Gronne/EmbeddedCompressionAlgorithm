#pragma once
#include "ICompressionSetup.h"
#include <vector>
#include <array>
#include <math.h>
#include <iostream>

template<class SensorT, class ModelT, int MATRIX_SIZE = 3>
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
		std::array<SensorT,MATRIX_SIZE+1> autocorrelation = calcAutocorrelation(&_periodeData);	
		std::array<SensorT,MATRIX_SIZE> autoVector = createAutoVector(&autocorrelation);
		std::array<SensorT, MATRIX_SIZE * MATRIX_SIZE> autoMatrix = createAutoMatrix(&autocorrelation);

		//Invert matrix
		std::array<SensorT, MATRIX_SIZE * MATRIX_SIZE> invMatrix = inverseMatrix(&autoMatrix);

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


	std::array<SensorT, MATRIX_SIZE+1> calcAutocorrelation(std::vector<SensorT>* periodeData) {
		std::array<SensorT, MATRIX_SIZE+1> autocorrelation;
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


	std::array<SensorT, MATRIX_SIZE> createAutoVector(std::array<SensorT, MATRIX_SIZE+1>* autocorrelation) {
		std::array<SensorT, MATRIX_SIZE> autoVector;
		for (int index = 1; index < autocorrelation->size(); ++index)
			autoVector.at(index-1) = autocorrelation->at(index);
		return autoVector;
	}


	std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE> createAutoMatrix(std::array<SensorT, MATRIX_SIZE+1>* autocorrelation) {
		std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE> autoMatrix;
		int matSize = autocorrelation->size() - 1;
		for (int row = 0; row < matSize; ++row)
			for (int col = 0; col < matSize; ++col)
				autoMatrix.at(matSize*row + col) = autocorrelation->at(abs(row - col));
		return autoMatrix;
	}


	std::array<SensorT, MATRIX_SIZE*MATRIX_SIZE> inverseMatrix(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE>* autoMatrix) {
		//Create same size identity matrix
		std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE> invMatrix = createIdentityMatrix();

		//--------------- Under diagonal ---------------
		for (int row = 0; row < MATRIX_SIZE-1; ++row) {
			for (int underRow = row + 1; underRow < MATRIX_SIZE; ++underRow) {
				//Minus First row from second and third
				scaleSubstraction(autoMatrix, &invMatrix, row, underRow, row);
			}
			//Scale rows
			scaleRows(autoMatrix, &invMatrix);
		}

		//--------------- Over diagonal ---------------
		for (int row = MATRIX_SIZE - 1; row > 0; --row) {
			for (int overRow = row - 1; overRow >= 0; --overRow) {
				//Minus First row from second and third
				scaleSubstraction(autoMatrix, &invMatrix, row, overRow, row);
			}
			//Scale rows
			scaleRows(autoMatrix, &invMatrix);
		}

		//Return inverse matrix
		return invMatrix;
	}

	std::array<SensorT, MATRIX_SIZE * MATRIX_SIZE> createIdentityMatrix() {
		std::array<SensorT, MATRIX_SIZE * MATRIX_SIZE> identityMatrix{};
		for (int count = 0; count < MATRIX_SIZE; ++count)
			identityMatrix.at(MATRIX_SIZE * count + count) = 1;
		return identityMatrix;
	}


	void scaleSubstraction(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE>* originalMatrix, std::array<SensorT, MATRIX_SIZE * MATRIX_SIZE>* IdentityMatrix, int primary, int secondary, int scaleCol) {
		//Get vectors from original
		std::array<SensorT, MATRIX_SIZE> primaryRowOri = getRow(originalMatrix, primary);
		std::array<SensorT, MATRIX_SIZE> secondaryRowOri = getRow(originalMatrix, secondary);
		//Get vectors from identity
		std::array<SensorT, MATRIX_SIZE> primaryRowIde = getRow(IdentityMatrix, primary);
		std::array<SensorT, MATRIX_SIZE> secondaryRowIde = getRow(IdentityMatrix, secondary);

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


	void substractRows(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE> *matrix, int primary, int secondary) {
		for (int col = 0; col < MATRIX_SIZE; ++col)
			matrix->at(MATRIX_SIZE * secondary + col) = matrix->at(MATRIX_SIZE * secondary + col) - matrix->at(MATRIX_SIZE * primary + col);
	}


	std::array<SensorT, MATRIX_SIZE> substractRows(std::array<SensorT, MATRIX_SIZE>* vecPrimary, std::array<SensorT, MATRIX_SIZE>* vecSecondary) {
		std::array<SensorT, MATRIX_SIZE> newVec{};
		for (int col = 0; col < MATRIX_SIZE; ++col)
			vecSecondary->at(col) = vecSecondary->at(col) - vecPrimary->at(col);
		return newVec;
	}


	void scaleRows(std::array<SensorT, MATRIX_SIZE * MATRIX_SIZE>* originalMatrix, std::array<SensorT, MATRIX_SIZE * MATRIX_SIZE>* identityMatrix) {
		for (int index = 0; index < MATRIX_SIZE; ++index) {
			SensorT scalingFactor = 1/originalMatrix->at(index * MATRIX_SIZE + index);
			scaleRow(originalMatrix, index, scalingFactor);
			scaleRow(identityMatrix, index, scalingFactor);
		}
	}


	void scaleRow(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE> *matrix, int rowNr, SensorT scalingFactor) {
		for (int index = 0; index < MATRIX_SIZE; ++index)
			matrix->at(MATRIX_SIZE * rowNr + index) = matrix->at(MATRIX_SIZE * rowNr + index) * scalingFactor;
	}

	void scaleRow(std::array<SensorT, MATRIX_SIZE>* vec, SensorT scalingFactor) {
		int matrixSize = MATRIX_SIZE;
		for (int index = 0; index < matrixSize; ++index)
			vec->at(index) = vec->at(index) * scalingFactor;
	}


	std::array<SensorT, MATRIX_SIZE> getRow(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE> *matrix, int rowNr) {
		std::array<SensorT, MATRIX_SIZE> newRow;
		for (int col = 0; col < newRow.size(); ++col)
			newRow.at(col) = matrix->at(rowNr * newRow.size() + col);
		return newRow;
	}

	
	void setRow(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE>*matrix, std::array<SensorT, MATRIX_SIZE>*vec, int rowNr) {
		for (int col = 0; col < vec->size(); ++col)
			matrix->at(rowNr * vec->size() + col) = vec->at(col);
	}


	ModelT calcCoefficients(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE>* invMatrix, std::array<SensorT, MATRIX_SIZE>* autoVector) {
		ModelT coefficients;
		std::array<SensorT, MATRIX_SIZE> result = multSymMatWVec(invMatrix, autoVector);
		for (auto &elem : result)
			coefficients.push_back(ModelT::value_type(elem));
		return coefficients;
	}

	
	std::array<SensorT, MATRIX_SIZE> multSymMatWVec(std::array<SensorT, MATRIX_SIZE* MATRIX_SIZE>* matrix, std::array<SensorT, MATRIX_SIZE>* vector) {
		std::array<SensorT, MATRIX_SIZE> resultVec;
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


