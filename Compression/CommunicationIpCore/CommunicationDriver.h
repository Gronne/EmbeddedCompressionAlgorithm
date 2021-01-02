#pragma once
#include "DataTypes.h"
SC_MODULE(CommunicationDriver) {

	//Ports
	sc_in<bool> inClk;
	sc_out<bool> reset;
	sc_out<bool> inDataReady;

	sc_out<sc_uint<NUM_BITS> > inDataPort;
	sc_in<sc_uint<NUM_BITS> > outDataPort;

	int retval;

	//Process Declaration
	void test();
	//Constructor
	SC_CTOR(CommunicationDriver) : retval(-1) {

		//Process Registration
		SC_THREAD(test)
		sensitive << inClk.pos();
	}
};
