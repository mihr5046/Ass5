#include "languageModel.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <random>

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

	for (size_t i = 0; i <= text.size() - k; i++) {
		string gram = text.substr(i, k);
		kgram_counts[gram]++;

		char next_char = text[i+k];
		trans_counts[gram][next_char]++;

	}
}

void LanguageModel::generate(size_t length, float alpha = 0.0) {
	




}

void LanguageModel::print_counts() {
	for (const auto& elem:kgram_counts) {
		cout << elem.first << " : " << elem.second << endl;
	}
}

void LanguageModel::print_trans() {
	for (const auto& elem:trans_counts) {
		cout << elem.first << " : {" << endl;
		for (const auto& inner:elem.second) {
			cout << "\t" << inner.first << " : " << inner.second << endl;
		}
		cout << "}" << endl;
	}
}
