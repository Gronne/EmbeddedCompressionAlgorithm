#pragma once
#include "DataTypes.h"
SC_MODULE(Transmitter) {
	//Ports
	sc_in<bool> inClk;
	sc_in<bool> inReset;
	sc_in<sc_uint<NUM_BITS>> inData;
	sc_out<sc_uint<NUM_BITS>> outData;

	//handshake signals
	sc_out<bool> transmitterReady;
	sc_in<bool> receiverReady;
	//Variables

	//Process Declaration
	void transmitterThread();

	//Constructor
	SC_CTOR(Transmitter) {
		//Process Registration
		SC_CTHREAD(transmitterThread, inClk.pos());
		reset_signal_is(inReset, true);
	}
}


