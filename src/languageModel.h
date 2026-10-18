#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class LanguageModel {
	private:
		//k-gram length
		size_t k;

		//map containing number of occurences of each k-gram
		map<string, int> kgram_counts;

		vector<string> grams;

		vector<double> gram_counts;
		
		//map containing number of transitions from a particular gram to a character
		map<string, map<char, int>> trans_counts;
		
		//Set of all possible characters
		set<char> alphabet;

	public:
		//Constructor
		LanguageModel(size_t k);


		//Calculates transition probabilites for all combinations of k-grams and characters
		void train(const string &text);
		
		//Generates text of given length, using given pseudocount
		string generate(size_t lenght, double alpha=0.0);

		//Debugging funtions
		void print_counts();

		void print_trans();

		void print_probs();

};
#endif
