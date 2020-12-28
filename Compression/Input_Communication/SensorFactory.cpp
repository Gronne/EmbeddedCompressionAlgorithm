#include "SensorFactory.h"
#include "TextFileSensor.h"

ISensor<Package*>* SensorFactory::CreateTextFileSensor(sc_fifo<Package*>* fifo)
{
	ISensor<Package*>* textFileSensor = new TextFileSensor("textFileSensor", (char*)INPUT_FILE_A);
	textFileSensor->out(*fifo);
	return textFileSensor;
}