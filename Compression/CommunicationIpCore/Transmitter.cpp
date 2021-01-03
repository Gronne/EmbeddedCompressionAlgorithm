#include "Transmitter.h"

void Transmitter::transmitterThread()
{
#pragma HLS RESOURCE variable=inData core=AXI4LiteS metadata="-bus_bundle slv0"
#pragma HLS RESOURCE variable=inDataReady core=AXI4LiteS metadata="-bus_bundle slv0"
	sc_uint<NUM_BITS> data;
	while (true)
	{
		wait();

		transmitterReady.write(false);
		// Wait for input data
		do { wait(); } while (!(inDataReady == true));
		data = inData.read();
		// Wait for receiver to signal ready
		do { wait(); } while (!(receiverReady == true));
		// Read input data
		outData.write(data);
		// Signal to receiver that data is ready
		transmitterReady.write(true);
		// Wait for receiver to have received the data.
		do { wait(); } while (!(receiverReady == false));
	}
}
