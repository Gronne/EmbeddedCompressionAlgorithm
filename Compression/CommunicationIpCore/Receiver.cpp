#include "Receiver.h"

void Receiver::receiverThread()
{
#pragma HLS RESOURCE variable=outData core=AXI4LiteS metadata="-bus_bundle slv0"
	sc_uint<NUM_BITS> data;
	//wait();
	while (true) {
		wait();

		receiverReady.write(true);

		do { wait(); } while (!(transmitterReady == true));

		// Read in data
		data = inData.read();
		receiverReady.write(false);
		outData.write(data);

		wait();
	}
}
