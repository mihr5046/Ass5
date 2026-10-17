#include "textReader.h"

#include <fstream>
#include <stdexcept>

using namespace std;

string textReader::read(const string &filename) {

	ifstream file(filename);
	
	if (!file.is_open()) {
		throw runtime_error(
				"cannot open file ' " + filename + "'"
				);
	}

	string text;

	char c;
	while (file.get(c)) {
		text+=c;
	}

	return text;
}
