#include "Transmitter.h"
Transmitter::Transmitter(sc_module_name name)
{
	_data = new Package();
	
	SC_THREAD(ReadData);
}


void Transmitter::Transmit()
{
	out.write(_data);
}


void Transmitter::ReadData()
{
	while (true)
	{
		wait(in.data_written_event());
		_data = in.read();
		Transmit();
		
	}
}
