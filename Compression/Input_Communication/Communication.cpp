#include "Communication.h"
#include "Transmitter.h"
#include "Receiver.h"

Communication::Communication(sc_module_name name, sc_fifo<Package*>* fifoInputData, sc_fifo<Package*>* fifoOutputData)
{
	fifoCommunication = new sc_fifo<Package*>("fifoCommunication");

	
	transmitter = new Transmitter("transmitter");
	transmitter->in(*fifoInputData);
	transmitter->out(*fifoCommunication);
	receiver = new Receiver("receiver");
	receiver->in(*fifoCommunication);
	receiver->out(*fifoOutputData);
}

Communication::~Communication()
{
	delete fifoCommunication;
	delete transmitter;
	delete receiver;
}
