#pragma once
#ifndef __TEXTFILESESNSOR_H_INCLUDED__   
#define __TEXTFILESESNSOR_H_INCLUDED__   
#include "ISensor.h"
#include "Package.h"
#include <string>
class TextFileSensor :
    public ISensor<Package*>, public sc_module
{
public:

    TextFileSensor(sc_module_name name, sc_fifo<Package*> *out, char* filename) : 
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
		char tmp_val;
		char tmp_final[55];
		Package* data = new Package();
		int charCounter = 0;
		memset(tmp_final, 0, 55);
		// declare filepointer
		FILE* fp_data;
		fp_data = fopen(_filename, "r");
		//get size of file in number of characters and rewind file pointer.
		fseek(fp_data, 0, SEEK_END);
		size = ftell(fp_data);
		rewind(fp_data);

		//for each character in the file
		for (size_t i = 0; i < size; i++)
		{
			// If end of file is reached (-1) then break out of the for loop and stop the thread. 
			if (fscanf(fp_data, "%c", &tmp_val) == -1)
			{
				sc_stop;
				break;
			}
			else {
				// if the character is a letter in the alphabet. 
				if ((tmp_val >= 'a' && tmp_val <= 'z') || (tmp_val >= 'A' && tmp_val <= 'Z'))
				{
					//add it to the tmp_final which is a variable that holds a whole word.
					tmp_final[charCounter] = tolower(tmp_val);
					charCounter++;
				}
				else if (tmp_val == 32 || tmp_val == '\n') {
					// write the data to the fifo
					data->data = tmp_final;
					_out->write(data);
					wait(20, SC_NS);

					// reset charCounter, tmp_final.
					charCounter = 0;
					memset(tmp_final, 0, 55);
					data = new Package();

				}
			}

		}
	}

	sc_fifo<Package*> *_out;
    sc_uint<32> size;
    char* _filename;
};

#endif