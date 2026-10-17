#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <string>
#include <map>
#include <set>

using namespace std;

class LanguageModel {
	public:
		//k-gram length
		int k;

		//map containing number of occurences of each k-gram
		map<string, int> kgram_counts;
		
		//Set of all possible characters
		set<char> alphabet;

	//public:
		//Constructor
		LanguageModel(int k);


		//Calculates transition probabilites for all combinations of k-grams and characters
		void train(const string &text);
		
		//Generates text of given length, using given pseudocount
		string generate(int lenght, float alpha=0.0);

};

#endif
