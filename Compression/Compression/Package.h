#pragma once
#include "systemc.h"
#define PACKET_SIZE 512
#define DATA_SIZE (PACKET_SIZE-20)
typedef struct
{

	char Inputvalue;

	char Data[DATA_SIZE];
} Package;