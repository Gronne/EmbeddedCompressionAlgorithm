#pragma once
#ifndef __TEXTFILESESNSOR_H_INCLUDED__   
#define __TEXTFILESESNSOR_H_INCLUDED__   
#include "ISensor.h"
#include "Package.h"
#include <string>

using TextFileTypeT = std::string;
class TextFileSensor :
    public ISensor<TextFileTypeT>, public sc_module
{
public:

    TextFileSensor(sc_module_name name, sc_fifo<TextFileTypeT> *out, char* filename) : 
		sc_module(name),
		_out(out)
	{
		SC_THREAD(Measure);
		_filename = filename;
	}

    SC_HAS_PROCESS(TextFileSensor);
private:
    virtual void Measure() {
		// declare temp variables
		char tmp_val{};
		TextFileTypeT data = TextFileTypeT();
		// declare filepointer
		FILE* fp_data;
		fp_data = fopen(_filename, "r");
		//get size of file in number of characters and rewind file pointer.
		fseek(fp_data, 0, SEEK_END);
		size = ftell(fp_data);
		rewind(fp_data);

		//for each character in the file
		for (size_t i = 0; i < size || fscanf(fp_data, "%c", &tmp_val) != EOF; i++)
		{
			data += tmp_val;
		}
		_out->write(data);
		wait(20, SC_NS);
	}

	sc_fifo<TextFileTypeT> *_out;
    sc_uint<32> size;
    char* _filename;
};

#endif