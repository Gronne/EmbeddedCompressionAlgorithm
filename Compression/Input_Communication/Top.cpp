#include "Top.h"
#include "Datatypes.h"
#include "TextFileSensor.h"
#include "SensorFactory.h"
#include "Transmitter.h"
#include "Receiver.h"

Top::Top(sc_module_name name) : sc_module(name)  {
	fifoInputData = new sc_fifo<Package*>("fifoInputData");
	
	fifoOutputData = new sc_fifo<Package*>("fifoOutputData");
	fifoCommunication = new sc_fifo<Package*>("fifoCommunication");

	sensor = SensorFactory::CreateTextFileSensor(fifoInputData);
	transmitter = new Transmitter("transmitter");
	transmitter->in(*fifoInputData);
	transmitter->out(*fifoCommunication);
	receiver = new Receiver("receiver");
	receiver->in(*fifoCommunication);
	receiver->out(*fifoOutputData);
	
	//communication = new Communication("communication", fifoInputData, fifoOutputData);

}

Top:: ~Top() {
	delete sensor;
	delete communication;
	delete fifoInputData;
	delete fifoOutputData;
}