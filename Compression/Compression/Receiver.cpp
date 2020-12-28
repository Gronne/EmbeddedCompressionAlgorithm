#include "Receiver.h"

Receiver::Receiver(sc_module_name name)
{
	_data = new Package();
	SC_THREAD(Receive);
	
}

void Receiver::Receive()
{
	while (true)
	{
		wait(in.data_written_event());
		_data = in.read();
		WriteData();
		
	}
}

void Receiver::WriteData()
{
	/*
	for (size_t i = 0; i < strlen(_data->data); i++)
	{
		cout << _data->data[i];
	}
	cout << endl;
	*/
	out.write(_data);
}
