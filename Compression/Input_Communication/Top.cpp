#include "Top.h"
#include "Datatypes.h"
#include "TextFileSensor.h"
#include "SensorFactory.h"
#include "Transmitter.h"
#include "Receiver.h"

Top::Top(sc_module_name name) : sc_module(name)  {
	fifoInputData = new sc_fifo<Package*>("fifoInputData");
	
	fifoOutputData = new sc_fifo<Package*>("fifoOutputData");

	sensor = SensorFactory::CreateTextFileSensor(fifoInputData);
	
	communication = new Communication("communication", fifoInputData, fifoOutputData);

}

Top:: ~Top() {
	delete sensor;
	delete communication;
	delete fifoInputData;
	delete fifoOutputData;
}