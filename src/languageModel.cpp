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

string LanguageModel::generate(size_t length, float alpha) {

	//Check arguments are valid.
	if (length < k) {
		throw invalid_argument(
			"Reqested length too short. Must be greater than or equal to k."
			);
	}

	if (alpha < 0 ) {
		throw invalid_argument(
			"Pseudocount parameter alpha must be greater than or equal 0, got alpha = "+to_string(alpha)+"."
			);
	}
	
	//Calculate transition probabilities with pseudocount.
	//map<string, map<char, float>> trans_probs;
	for (const auto& i:trans_counts) {
		string gram = i.first;
		for (const auto& j:i.second) {
			char character = j.first;
			trans_probs[gram][character] = 
				(trans_counts[gram][character] + alpha)
				/(kgram_counts[gram] + alpha*alphabet.size());
		}
	}

	return "temp";





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

void LanguageModel::print_probs() {
	for (const auto& elem:trans_probs) {
		cout << elem.first << " : {" << endl;
		for (const auto& inner:elem.second) {
			cout << "\t" << inner.first << " : " << inner.second << endl;
		}
		cout << "}" << endl;
	}
}

