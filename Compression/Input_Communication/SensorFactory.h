#pragma once
#ifndef __SENSORFACTORY_H_INCLUDED__   
#define __SENSORFACTORY_H_INCLUDED__   
#include "ISensor.h"
#include "Package.h"
#include "Datatypes.h"
#include "TextFileSensor.h"
#include "SinusSensor.h"

class SensorFactory : public sc_module
{
public:
	using TextFileSensorSubT = Package*;
	using TextFileSensorT = ISensor<TextFileSensorSubT>;
	using SinusSensorSubT = int;
	using SinusSensorT = ISensor<SinusSensorSubT>;

	static TextFileSensorT* CreateTextFileSensor(sc_fifo<Package*> *pipe) {
		return new TextFileSensor("textFileSensor", pipe, (char*)INPUT_FILE_A);
	}

	static SinusSensorT* CreateSinusSensor(sc_fifo<int> *pipe, int measurementSpeed = 100) {
		return new SinusSensor("sinusSensor", pipe, measurementSpeed);
	};



};
#endif
