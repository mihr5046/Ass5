#include "languageModel.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <random>

using namespace std;

LanguageModel::LanguageModel(size_t k) {
	if (k<=0) {
		throw invalid_argument(
			"k must be strictly positive"
			);
	}
	this->k = k;
}

void LanguageModel::train(const string &text) {
	if (text.size() <= k) {
		throw invalid_argument(
				"training text too short. Text length must be greater than k."
				);
	}
	for (char c : text) {
		alphabet.insert(c);
	}

	for (size_t i = 0; i <= text.size() - k; i++) {
		string gram = text.substr(i, k);
		kgram_counts[gram]++;
		
		if (i + k < text.size()) {
			char next_char = text[i+k];
			trans_counts[gram][next_char]++;
		}

	}
	
	//Segregates kgram counts in to separate vectors.
	for (const auto& entry:kgram_counts) {
		grams.push_back(entry.first);
		gram_counts.push_back(entry.second);
	}

}

string LanguageModel::generate(size_t length, double alpha) {

	//Check arguments are valid.
	if (length < k) {
		throw invalid_argument(
			"output length must be greater than or equal to k. Expected length >= "+to_string(k)+", got length = "+to_string(length)
			);
	}

	if (alpha < 0.0 ) {
		throw invalid_argument(
			"alpha must be greater than or equal 0, got alpha = "+to_string(alpha)+"."
			);
	}

	//Initialize variables
	string starting_gram;
	string output_text;
	map<string, map<char, double>> trans_probs;
	random_device r;
	default_random_engine rng(r());


	
	//Calculate transition probabilities with pseudocount.
	
	for (const auto& [gram, counts] : trans_counts) {
		size_t total = 0;
		for (const auto& [character, count] : counts) {
			total += count;
		}
		
		for (char character : alphabet) {
			size_t count = 0;
			auto iterator = counts.find(character);
			if (iterator != counts.end()) {
				count = (*iterator).second;
			}
			
			trans_probs[gram][character] =
				(count + alpha) /
				(total + alpha * alphabet.size());
		}
	}

	//Choose starting gram
	discrete_distribution<> kgram_dist(
			gram_counts.begin(), gram_counts.end()
			);

	starting_gram = grams[kgram_dist(rng)];
	output_text += starting_gram;

	//Sequentially add new character to output
	while (output_text.size() < length) {
		string current_gram = output_text.substr(output_text.size()-k);

		vector<char> characters;
		vector<double> char_probs;

		auto iterator = trans_probs.find(current_gram); 

		if (iterator != trans_probs.end()) { //Uses conditional probabilities if the gram already exists
			for (const auto& entry:(*iterator).second) {
				characters.push_back(entry.first);
				char_probs.push_back(entry.second);
			}
		}

		if (characters.empty()) { //Handles the case if a gram has never occured before
			if (alpha == 0.0) { // If no pseudocounts, stop writing.
				break;
			}

			for (char c : alphabet) { // If pseudocounts are allowed, give every letter in the alphabet equal probability.
				characters.push_back(c);
				char_probs.push_back(1.0/alphabet.size());
			}
		}

		discrete_distribution<> char_dist(
			       	char_probs.begin(), char_probs.end()
				);
		output_text += characters[char_dist(rng)];
	}

	return output_text;

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

/*
void LanguageModel::print_probs() {
	for (const auto& elem:trans_probs) {
		cout << elem.first << " : {" << endl;
		for (const auto& inner:elem.second) {
			cout << "\t" << inner.first << " : " << inner.second << endl;
		}
		cout << "}" << endl;
	}
}
*/


