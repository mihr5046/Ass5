#include "languageModel.h"
#include <string>
#include <stdexcept>

using namespace std;

LanguageModel::LanguageModel(size_t k) {
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

	for (size_t i = 0; i <= text.size(); i++) {
		string gram = text.substr(i, k);
		kgram_counts[gram]++;
	}

void LanguageModel::print_counts() {
	for (const auto& elem:kgram_counts) {
		cout << elem.first << " : " << elem.second << endl;
		}
	}
}
