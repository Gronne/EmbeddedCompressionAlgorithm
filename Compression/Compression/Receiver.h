#pragma once
#ifndef __RECEIVER_H_INCLUDED__   
#define __RECEIVER_H_INCLUDED__   
#include "IReceiver.h"
#include "Package.h"
class Receiver : public IReceiver<Package*>, public sc_module
{
public:
	Receiver(sc_module_name name);
	SC_HAS_PROCESS(Receiver);
private:
	Package* _data;
	virtual void Receive();
	virtual void WriteData();
};

#endif