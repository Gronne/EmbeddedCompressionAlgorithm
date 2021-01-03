#pragma once
#include "DataTypes.h"

SC_MODULE(Receiver) {

	//Ports
	sc_in<bool> inClk;
	sc_in<bool> inReset;


	sc_in<sc_uint<NUM_BITS> > inData;
	sc_out<sc_uint<NUM_BITS> > outData;

	//handshake signals
	sc_out<bool> receiverReady;
	sc_in<bool> transmitterReady;
	//Variables

	//Process Declaration
	void receiverThread();

	//Constructor
	SC_CTOR(Receiver) {
		//Process Registration
		SC_CTHREAD(receiverThread, inClk.pos());
		reset_signal_is(inReset, true);
	}
};
