#include "Receiver.h"

void Receiver::receiverThread()
{
	sc_uint<NUM_BITS> data;
	//wait();
	while (true) {
		receiverReady.write(true);

		do { wait(); } while (!(transmitterReady == true));

		// Read in data
		data = inData.read();
		std::cout << data << std::endl;
		receiverReady.write(false);
		outData.write(data);

		wait();
	}
}