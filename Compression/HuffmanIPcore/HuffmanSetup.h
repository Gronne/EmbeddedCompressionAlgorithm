#pragma once
#include <systemc.h>
#include "Datatypes.h"


SC_MODULE(HuffmanSetup)
{
	// signals
	sc_in<bool> _sensor_ready;
	sc_out<bool> _Setup_complete;

	// ports 
	sc_in <bool> clk;

	//sc_in<sc_uint<NUM_CHAR_BITS>> indata;
	sc_in<sc_uint<NUM_BITS>> ctrl;
	sc_out<sc_uint<NUM_BOOL_BITS>> outdata;

	sc_fifo_in<sc_uint<NUM_CHAR_BITS>> indata;

	// process declaration
	void setup();
	void getModel();

	SC_CTOR(HuffmanSetup) {
		//Process Registration
		SC_CTHREAD(setup, clk.pos());
		SC_CTHREAD(getModel, clk.pos());

	}


};

