#include "Input.h"
#include "Datatypes.h"
#include "fstream"
#include <stdlib.h>
Input::Input(sc_module_name name) : sc_module(name) {
	SC_THREAD(sensor);
}

void Input::sensor() {
	while (true) {
		fstream file;
		char ch;
		file.open(INPUT_FILE_A, ios::in);
		Package* data = new Package();
		if (!file) {
			std::cout << "file not found" << endl;
		}
		else {
			while (1) {
				file >> ch;
				if (file.eof())
					break;
				std::cout << ch;
			}
		}

		data->Inputvalue;
		printf("%c", data->Inputvalue);
		out.write(data);
		wait(20, SC_MS);
		
	}
}