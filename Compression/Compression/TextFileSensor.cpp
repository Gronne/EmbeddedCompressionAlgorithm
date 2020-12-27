#include "TextFileSensor.h"
#include "Datatypes.h"
void TextFileSensor::Measure()
{
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
				out.write(data);
				/* for (size_t i = 0; i < strlen(data->data); i++)
				{
					cout << data->data[i];
				}
				cout << endl;
				*/
				// reset charCounter, tmp_final.
				charCounter = 0;
				memset(tmp_final, 0, 55);
				data = new Package();
			}
		}

	}
}


TextFileSensor::TextFileSensor(sc_module_name name, char* filename) : sc_module(name) {
	SC_THREAD(Measure);
	_filename = filename;
}