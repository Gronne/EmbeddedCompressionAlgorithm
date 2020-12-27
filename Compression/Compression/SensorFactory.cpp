#include "SensorFactory.h"
#include "TextFileSensor.h"

template<class T>
ISensor<T>* SensorFactory<T>::CreateTextFileSensor(sc_fifo<T*> fifo)
{
	ISensor<T>* textFileSensor = new TextFileSensor<T>("textFileSensor", INPUT_FILE_A);
	textFileSensor->out = fifo;
	return textFileSensor;
}