// main.cpp 4/21/2014 3pm


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "model.h"
#include <algorithm>

using namespace std;

void init_random() {
	// use this to get the same random sequence every time
//	srand(1234);

	// use this to get a different random sequence every time
	time_t t = time(NULL);
	srand(t);
}

int main(int argc, char* argv[]) {
	string infile;
	int k;
	int sz;
	string model_type;

	// allow command line "markov filename k sz model", or partial
	// command line, prompting for missing items
	if (argc > 1) infile = string(argv[1]);
	else {
		cout << "Enter a filename: ";
		cin >> infile;
	}

	if (argc > 2) k = atoi(argv[2]);
	else {
		cout << "Enter Markov model order (k): ";
		cin >> k;
	}

	if (argc > 3) sz = atoi(argv[3]);
	else {
		cout << "Enter size of output text: ";
		cin >> sz;
	}

	if (argc > 4) model_type = string(argv[4]);
	else {
		cout << "Enter method (brute, map, umap, word): ";
		cin >> model_type;
	}


	// get text from input file
	ifstream in(infile);
	if (!in) {
		cerr << "Error opening input file \"" << infile << "\"!" << endl;
		return -1;
	}
	// get all strings; extra whitespace will be ignored 
	ostringstream text;
	while (!in.eof()) {
		string s;
		in >> s;
		text << s << ' ';
	}
	in.close();

	// create model, generate output
	markov_model* model;

	if (model_type == "brute") model = new brute_model(text.str(), k);
	else if (model_type == "map") model = new map_model(text.str(), k);
	else if (model_type == "umap") model = new u_map_model(text.str(), k);
	else if (model_type == "word") model = new word_model(text.str(), k);
	else {
		cout << "That model is not yet implemented, sorry." << endl;
		return -1;
	}

	// Performance of operation
	vector<int> numbers;
		for (int i = 0; i < 10000000; i++) 
		{
			numbers.push_back(rand());
		}
		
		clock_t t1, t2;
		
		t1 = clock();
		sort(numbers.begin(), numbers.end());
		t2 = clock();
		
		cout << "Sorted 10,000,000 numbers in " << (t2 - t1)/double(CLOCKS_PER_SEC) << " seconds." << endl;


	init_random();
	cout << "RESULT:" << endl;
	cout << model->generate(sz) << endl;

	delete model;


	

	system("pause");
	
	return 0;
}
