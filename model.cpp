// model.cpp 4/21/2014 2pm


#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "model.h"
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

// Brute force character generator
string brute_model::generate(int sz) {

	// copy first k characters to back to simulate wrap-around
	string working_data = data + data.substr(0, order);

	// pick random k-character substring as initial seed
	int start = rand() % (data.length() - order);
	string seed = working_data.substr(start, order);
	//cout << "start: " << working_data[start] << endl;

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
		//cout << "char: " << c << endl;
	}

	return answer;
}


map_model::map_model(string s, int k) : markov_model(s,k) {;}

string map_model::generate(int sz)
{

	// copy first k characters to back to simulate wrap-around
	string working_data = data + data.substr(0, order);
	vector<char> list;
	string answer;
	answer.reserve(sz);
	map<string,vector<char>>::iterator it; // iterator for map
	string gram;
	
	// add each k-gram string to the map
	for( int i = 0; i < sz; i++ )
	{
		gram = "";
		for( int j = 0; j < order; j++ )
		{
			gram += working_data[i + j];
		}
		it = ngram_map.find(gram);
		if( it != ngram_map.end() )	// gram already in the map, add char to vector
		{
			list.push_back(working_data[i + 3]);
			ngram_map[gram] = list; // update the vector of chars
		}
		else
		{
			list.clear(); // empty the list of chars
			list.push_back(working_data[i + 3]); // push the following letter to the vector
			ngram_map.insert(pair<string,vector<char>>( gram, list )); // insert into map
		}		
	}

	// pick random k-character substring as initial seed
	int start = rand() % (data.length() - order);
	string seed = working_data.substr(start, order);

	int pos = working_data.find(seed);
	int len = (sz + pos); // number of iterations

	int count = 0;

	for( int i = pos; i < len; i++ )
	{
		string gram = "";
		for( int j = 0; j < order; j++ )
		{
			gram += working_data[pos + count + j]; // current gram
		}
		it = ngram_map.find(gram); // iterator to current gram
		if( it != ngram_map.end() ) // if the gram is already in the list
		{
			answer += gram;
			vector<char> list2 = it->second;
			char c = list2[rand() % list.size()]; // pick a char from the list by random
			answer += c; // add the char to the answer
		}
		else
		{
			answer += gram; // if the char is not in the list, just add the gram to the answer
		}
		count += 3; 
	}

	answer = answer.substr(0,sz);
	return answer;
}





u_map_model::u_map_model(string s, int k) : markov_model(s,k) {;}

string u_map_model::generate(int sz)
{
	map<string,vector<char>> ngram_umap;

	 // copy first k characters to back to simulate wrap-around
	string working_data = data + data.substr(0, order);
	vector<char> list;
	string answer;
	answer.reserve(sz);
	map<string,vector<char>>::iterator it; // iterator for map
	string gram;
	
	// add each k-gram string to the map
	for( int i = 0; i < sz; i++ )
	{
		gram = "";
		for( int j = 0; j < order; j++ )
		{
			gram += working_data[i + j];
		}
		it = ngram_umap.find(gram);
		if( it != ngram_umap.end() )	// gram already in the map, add char to vector
		{
			list.push_back(working_data[i + 3]);
			ngram_umap[gram] = list; // update the vector of chars
			cout << "updated list" << endl;
		}
		else
		{
			list.clear(); // empty the list of chars
			list.push_back(working_data[i + 3]); // push the following letter to the vector
			ngram_umap.insert(pair<string,vector<char>>( gram, list )); // insert into map
		}		
	}

	// pick random k-character substring as initial seed
	int start = rand() % (data.length() - order);
	string seed = working_data.substr(start, order);

	cout << "start: " << working_data[start] << endl; // starting char
	int pos = working_data.find(seed);
	int len = (sz + pos);

	cout << endl << endl;
	int count = 0;

	for( int i = pos; i < len; i++ )
	{
		string gram = "";
		for( int j = 0; j < order; j++ )
		{
			gram += working_data[pos + count + j];
		}

		it = ngram_umap.find(gram);
		if( it != ngram_umap.end() )
		{
			answer += gram;
			vector<char> list2 = it->second;
			char c = list2[rand() % list.size()];
			answer += c;
		}
		else
		{
			answer += gram;
		}
		count += 3; 
	}

	answer = answer.substr(0,sz);
	return answer;
}




word_model::word_model(string s, int k) : markov_model(s,k) {;}

string word_model::generate(int sz)
{
	 // copy first k characters to back to simulate wrap-around
	string working_data = data + data.substr(0, order);
	string answer;
	answer.reserve(sz);
	map<string,string>::iterator it; // iterator for map
	string gram;
	string words = "";
	int start = rand() % (data.length() - order);
	string seed = working_data.substr(start, order);
	string next[100];

	//cout << "start: " << working_data[start] << endl; // starting char
	int pos = working_data.find(seed);
	
	// add each k-gram string to the map
		int i = 0;
		gram = "";
		// find the next occurence of a wordbreaker		
		working_data = working_data.substr(start,sz); // string of text that will be used
		istringstream iss(working_data);
		string text[1000];
		do
		{
			iss >> gram;
			//cout << "Substring: " << gram << endl;
			text[i] = gram; // put the word into a distinct element of text[]
			for( int j = 0; j < order + 1; j++ )
			{
				iss >> gram;	
				//cout << "gram: " << gram << " ";		
				text[i] += gram; 
				
				text[i] += " ";
				if( j = order)
				{
					iss >> gram;
					next[i] = gram;
				}
			}
			//cout << "Substring: " << text[i] << endl;
			words += text[i];

			it = ngram_word.find(words);
			if( it != ngram_word.end() )	// gram already in the map, add text[] to string
			{
				ngram_word[words] += next[i]; // update the string of words
				//cout << "updated list" << endl;
			}
			else
			{
				words = ""; // empty the string
				words = text[i];
				ngram_word.insert(pair<string,string>( text[i], next[0] )); // insert into map
			}	
			
			i++; // increment the counter
		} while (iss);

	
			
	

	// pick random k-character substring as initial seed
	//int start = rand() % (data.length() - order);
	

	//cout << "start: " << working_data[start] << endl; // starting char
	int len = (sz + pos);

	//cout << endl << endl;
	int count = 0;

	for( int i = pos; i < len; i++ )
	{
		it = ngram_word.find(text[i]);
		if( it != ngram_word.end() )
		{
			/*answer += text[i]; 
			string next = it->second;
			int randomWord = next[rand() % next.size()];*/
			//answer += randomWord;
			cout << "found the gram";
		}
		else
		{
			//answer += text[i];
			//cout << "didn't find the gram.";
		}
	}
	
	answer = answer.substr(0,sz);
	return answer;
}
