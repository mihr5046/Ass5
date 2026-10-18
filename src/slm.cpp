#include <iostream>
#include <stdexcept>
#include <string>

#include "textReader.h"
#include "languageModel.h"

using namespace std;

int main(int argc, char* argv[]) {

	//Declare arguments
	double alpha = 0.0;
	size_t k;
	string filename;
	size_t out_len;
	
	int arg_shift = 0;
	if ((argc == 6) && (string(argv[1]) == "-a")) {
		alpha = stod(argv[2]);
		arg_shift = 2;
			}
	//Check if valid arguments
	if (argc != 4 + arg_shift) {
		cerr << "Wrong number of arguments. Expected 3, got "+to_string(argc-arg_shift-1)+"." << endl;
		return 1;
	}

	try {
		k = stoi(argv[1+arg_shift]);
	}
	catch (const invalid_argument &e) {
	       cerr << "slm: k must be an integer." << endl;
	       return 1;
	}

	filename = argv[2+arg_shift];
	out_len  = stoi(argv[3+arg_shift]);

	if (out_len < k) {
		cerr << "Output length must be greater or equal than k-gram length" << endl;
		return 1;
	}

	//Read a file
	string in_text;
	string out_text;
	textReader reader;

	try {
		in_text = reader.read(filename);

		//cout << text;
	}
	catch (const exception &e) {
		cerr << "slm: " << e.what() << endl;
		return 1;
	}
	
	//Train model and generate new text
	LanguageModel model(k);
	model.train(in_text);
	out_text = model.generate(out_len, alpha);
	cout << out_text << endl;

	return 0;
}
