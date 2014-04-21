// model.h 4/21/2014 2pm

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <map>

class markov_model {
public:
	markov_model(std::string s, int k) { data = s; order = k; }
	virtual std::string generate(int size) = 0;
	
protected:
	std::string data;
	int order;
};

class brute_model : public markov_model {
public:
	brute_model(std::string s, int k) : markov_model(s, k) {}
	virtual std::string generate(int size);
};

class map_model : public markov_model {
	map_model(std::string s, int k);
	std::string generate(int size);

	std::map<std::string, std::vector<char>> ngram_map;
};

class unordered_map_model : public markov_model {
	unordered_map_model(std::string s, int k);
	std::string generate(int size);

	std::map<std::string, std::vector<char>> ngram_unordered_map;
};

class word_model : public markov_model {
	word_model(std::string s, int k);
	std::string generate(int size);

	std::map<std::string, std::vector<string>> ngram_word;
};


#endif

