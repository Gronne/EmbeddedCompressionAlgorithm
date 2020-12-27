#include "Input.h"
#include "Datatypes.h"
#include <stdlib.h>
Input::Input(sc_module_name name) : sc_module(name) {
	SC_THREAD(sensor);
}

void Input::sensor() {
	while (true) {
		FILE* fp_data;
		
		fp_data = fopen(INPUT_FILE_A, "r");
		fseek(fp_data, 0, SEEK_END);
		size = ftell(fp_data);
		char tmp_val[100];
		rewind(fp_data);
		Package* data = new Package();
		std::cout << size << std::endl;
		
		while (fscanf(fp_data, "%s", tmp_val) != -1)
		{
			printf("%s ", tmp_val);
			//data->Inputvalue = tmp_val;
			//printf("%s", data->Inputvalue);
			//out.write(data);
		}

		sc_stop;
		break;
	}
}