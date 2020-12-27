#include "Input.h"
#include "Datatypes.h"
#include <stdlib.h>
Input::Input(sc_module_name name) : sc_module(name) {
	SC_THREAD(sensor);
}

void Input::sensor() {
	while (true) {
		FILE* fp_data;
		char tmp_val;
		fp_data = fopen(INPUT_FILE_A, "r");
		fseek(fp_data, 0, SEEK_END);
		size = ftell(fp_data);
		rewind(fp_data);
		Package* data = new Package();
		std::cout << size << std::endl;
		for (size_t i = 0; i < size; i++)
		{
			if (fscanf(fp_data, "%c", &tmp_val) == EOF) {
				sc_stop;
				break;
			}
			data->Inputvalue = tmp_val;
			printf("%c", data->Inputvalue);
			out.write(data);
			wait(20, SC_MS);
		}
		
	}
}