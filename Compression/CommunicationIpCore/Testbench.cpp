#include "DataTypes.h"
#include "Transmitter.h"
#include "Receiver.h"
#include "CommunicationDriver.h"
int sc_main(int argc, char** argv)
{
	sc_trace_file* tracefile;

	sc_signal<bool> s_reset;
	sc_signal<bool> s_transmitterReady;
	sc_signal<bool> s_receiverReady;
	sc_signal<sc_uint<NUM_BITS> > s_data_input;
	sc_signal<sc_uint<NUM_BITS> > s_data_internal;
	sc_signal<sc_uint<NUM_BITS> > s_data_output;

	sc_clock s_clk("s_clk", 8, SC_NS);
	Transmitter transmitter("transmitter");
	Receiver receiver("receiver");
	CommunicationDriver driver("driver");

	// Create tracefile
	tracefile = sc_create_vcd_trace_file("Communication_Wave");
	if (!tracefile) cout << "Could not create trace file." << endl;

	// Set resolution of trace file to be in 1 N
	tracefile->set_time_unit(1, SC_NS);
	sc_trace(tracefile, s_clk, "clock");
	sc_trace(tracefile, s_reset, "reset");
	sc_trace(tracefile, s_data_input, "data");
	sc_trace(tracefile, s_transmitterReady, "transmitterReady");
	sc_trace(tracefile, s_receiverReady, "receiverReady");

	//bind ports, and signals
	transmitter.inClk(s_clk);
	transmitter.inData(s_data_input);
	transmitter.inReset(s_reset);
	transmitter.outData(s_data_internal);

	receiver.inClk(s_clk);
	receiver.inData(s_data_internal);
	receiver.inReset(s_reset);
	receiver.outData(s_data_output);

	driver.inClk(s_clk);
	driver.inDataPort(s_data_input);
	driver.outDataPort(s_data_output);

	// Sim for 200
	int end_time = 200;
	std::cout << "INFO: Simulating" << std::endl;
	// start simulation
	sc_start(end_time, SC_NS);

	if (driver.retval == 0) {
		printf("Test passed !\n");
	}
	else {
		printf("Test failed !!!\n");
	}
	sc_close_vcd_trace_file(tracefile);
	std::cout << "Created Communication_Wave.vcd" << std::endl;
	return driver.retval;
    return 0;
}