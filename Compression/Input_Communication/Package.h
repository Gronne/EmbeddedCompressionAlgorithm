#pragma once
#ifndef __PACKAGE_H_INCLUDED__   
#define __PACKAGE_H_INCLUDED__   

#define PACKET_SIZE 512
#define DATA_SIZE (PACKET_SIZE-20)
typedef struct
{
	char* data;
} Package;

#endif