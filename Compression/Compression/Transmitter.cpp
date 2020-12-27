#include "Transmitter.h"

template<class T>
Transmitter<T>::Transmitter(sc_module_name name)
{
	SC_THREAD(Transmit);
	SC_THREAD(ReadData);
}

template<class T>
void Transmitter<T>::Transmit()
{
	while (true)
	{

	}
}

template<class T>
void Transmitter<T>::ReadData()
{
	while (true)
	{
		std::cout << "data: " << in.read() << " Simulation time: " << sc_time_stamp() << endl;
		wait(in.data_written_event());
	}
}
