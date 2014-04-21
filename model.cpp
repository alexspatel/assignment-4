// model.cpp 4/21/2014 2pm


#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "model.h"

using namespace std;

// Brute force character generator
string brute_model::generate(int sz) {

	// copy first k characters to back to simulate wrap-around
	string working_data = data + data.substr(0, order);

	// pick random k-character substring as initial seed
	int start = rand() % (data.length() - order);
	string seed = working_data.substr(start, order);

	vector<char> list;
	string answer;
	answer.reserve(sz);

	for (int i = 0; i < sz; i++) {
		list.clear();
		int pos = working_data.find(seed);
		while (pos != string::npos && pos < data.length()) {
			char c = working_data[pos + order];
			list.push_back(c);
			pos = working_data.find(seed, pos+1);
		}
		char c = list[rand() % list.size()];
		answer.push_back(c);
		seed = seed.substr(1) + c;
	}

	return answer;
}


map_model::map_model(string s, int k) : markov_model(s,k) {;}

string map_model::generate(int sz)
{
	string answer;

	return answer;
}

unordered_map_model::unordered_map_model(string s, int k) : markov_model(s,k) {;}

string unordered_map_model::generate(int sz)
{
	string answer;

	return answer;
}

word_model::word_model(string s, int k) : markov_model(s,k) {;}

string word_model::generate(int sz)
{
	string answer;

	return answer;
}
