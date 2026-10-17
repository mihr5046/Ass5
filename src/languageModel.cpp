#include "languageModel.h"
#include <string>
#include <stdexcept>

using namespace std;

LanguageModel::LanguageModel(int k) {
	if (k<=0) {
		throw invalid_argument(
			"k-gram length must be positive"
			);
	}
	this->k = k;
}

void LanguageModel::train(const string &text) {
	for (char c : text) {
		alphabet.insert(c);
	}
}
