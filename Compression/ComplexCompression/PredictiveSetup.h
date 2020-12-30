#pragma once
#include "ICompressionSetup.h"
#include <vector>

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
		
		//Create autoCorrelation matrix and vector


		//Invert matrix


		//multiply inverted matrix and vector to get coefficients

		
		// Save coefficients as the model


		//Return True
		return true;
	};


	ModelT* getModel() { return new ModelT(); };


private:

	bool detectPeriode(std::vector<SensorT> *periodeData) {
		return periodeData->size() > 10;
	};


	std::vector<SensorT> _periodeData;
};