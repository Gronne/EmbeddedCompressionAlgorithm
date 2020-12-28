#include "Top.h"
#include "Datatypes.h"
#include "TextFileSensor.h"
#include "SensorFactory.h"
#include "Transmitter.h"
#include "Receiver.h"

Top::Top(sc_module_name name) : sc_module(name)  {
	fifoInputData = new sc_fifo<Package*>("fifoInputData");
	fifoCommunication = new sc_fifo<Package*>("fifoCommunication");
	fifoOutputData = new sc_fifo<Package*>("fifoOutputData");

	sensor = SensorFactory::CreateTextFileSensor(fifoInputData);
	
	transmitter = new Transmitter("transmitter");
	transmitter->in(*fifoInputData);
	transmitter->out(*fifoCommunication);
	receiver = new Receiver("receiver");
	receiver->in(*fifoCommunication);
	receiver->out(*fifoOutputData);


	//sensor = new TextFileSensor("sensor", (char*)INPUT_FILE_A);
	//sensor->out(fifo);
	//FILE* fp_data;
	//char* tmp_val;
	//fp_data = fopen(INPUT_FILE_A, "r");

	//if (fscanf(fp_data, "%s", &tmp_val) != EOF)
	//{
	//	printf("%s", &tmp_val);
	//}
	//else {
	//	cout << "End of Input Stream: Simulation Stops" << endl;
	//	sc_stop();
	//}
}

Top:: ~Top() {
	delete sensor;
	delete transmitter;
}