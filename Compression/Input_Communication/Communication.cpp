#include "Communication.h"
#include "Transmitter.h"
#include "Receiver.h"

Communication::Communication(sc_module_name name, sc_fifo<Package*>* fifoInputData, sc_fifo<Package*>* fifoOutputData)
{
	


}

Communication::~Communication()
{
	delete fifoCommunication;
	delete transmitter;
	delete receiver;
}
