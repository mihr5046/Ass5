#include <iostream>
#include <stdexcept>
#include <string>

#include "textReader.h"
#include "languageModel.h"

using namespace std;

int main(int argc, char* argv[]) {

	//Declare arguments
	double alpha = 0.0;
	int k_input;
	string filename;
	int length_input;
	int arg_shift = 0;

	//Check arguments are valid
	if (argc > 1 && string(argv[1]) == "-a") {
		try {
			alpha = stod(argv[2]);
			arg_shift = 2;
		}
		catch (const invalid_argument &e) {
			cerr << "slm: alpha must be a positive real number" << endl;
			return 1;
		}
	}

	if (argc != 4 + arg_shift) {
		cerr << "slm: wrong number of arguments. Expected 3, got "+to_string(argc-arg_shift-1)+"." << endl;
		return 1;
	}

	try {
		k_input = stoi(argv[1+arg_shift]);
	}

	catch (const invalid_argument &e) {
		cerr << "slm: k must be an integer." << endl;
		return 1;
	}

	if (k_input<=0) {
		cerr << "slm: k must be strictly positive" << endl;
		return 1;
	}
	
	try {
		length_input = stoi(argv[3+arg_shift]);
	}

	catch (const invalid_argument &e) {
		cerr << "slm: length must be an integer" << endl;
		return 1;
	}
	if (length_input <=0) {
		cerr << "slm: length must be positive" << endl;
		return 1;
	}

	size_t k = static_cast<size_t>(k_input);
	size_t length = static_cast<size_t>(length_input);
	filename = argv[2+arg_shift];

	string in_text;
	string out_text;
	textReader reader;

	try {
		in_text = reader.read(filename);
		LanguageModel model(k);
		model.train(in_text);
		out_text = model.generate(length, alpha);
		cout << out_text << endl;
	}
	catch (const exception &e) {
		cerr << "slm: " << e.what() << endl;
		return 1;
	}

	return 0;
}
