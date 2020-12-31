#include "CommunicationDriver.h"
void CommunicationDriver::test() {

	//Variables
	sc_uint<NUM_BITS> data;
	sc_uint<NUM_BITS> receivedData;
	//Initialization
	data = 0x5;
	
	reset.write(true);
	wait();
	reset.write(false);
	wait();

	outDataPort.write(data);
	
	wait();
	wait();

	receivedData = inDataPort.read();

	wait();

	if (receivedData == data)
		retval = 0;
	else
		retval = 1;
}