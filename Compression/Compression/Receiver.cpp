#include "Receiver.h"
template<class T>
Receiver<T>::Receiver(sc_module_name name)
{
	SC_THREAD(Receive);
	SC_THREAD(WriteData);
}
template<class T>
void Receiver<T>::Receive()
{
	while (true)
	{

	}
}

template<class T>
void Receiver<T>::WriteData()
{
	while (true)
	{

	}
}
