#include <iostream>
#include <stdexcept>
#include <string>

#include "textReader.h"
#include "languageModel.h"

using namespace std;

int main(int argc, char* argv[]) {

	//Declare arguments
	int k;
	string filename;
	int out_len;

	//Check if valid arguments
	if (argc != 4) {
		cerr << "Wrong number of arguments. Expected 3, got "+to_string(argc-1)+"." << endl;
		return 1;
	}

	try {
		k = stoi(argv[1]);
	}
	catch (const invalid_argument &e) {
	       cerr << "slm: k must be an integer." << endl;
	       return 1;
	}

	filename = argv[2];
	out_len  = stoi(argv[3]);

	if (out_len < k) {
		cerr << "Output length must be greater or equal than k-gram length" << endl;
		return 1;
	}




	//Test read a file
	
	string text;
	textReader reader;
	try {
		text = reader.read(filename);

		//cout << text;
	}
	catch (const exception &e) {
		cerr << "slm: " << e.what() << endl;
		return 1;
	}

	LanguageModel model(k);
	model.train(text);



	return 0;
}
