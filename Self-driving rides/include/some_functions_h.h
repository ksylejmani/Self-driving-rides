#ifndef SOME_FUNCTIONS_H
#define SOME_FUNCTIONS_H

#include <unordered_map>
#include <vector>
#include <string>
#include <time.h> //clock_t, clock, CLOCKS_PER_SEC 
#include <iostream>

#include "data_set_h.h"

using namespace std;

vector<int> 						split_string_to_ints(string);
unordered_map<int, vector<int>>		read_solution_file();

int get_score (const data_set&, unordered_map<int, vector<int>>);


struct Timing{
	clock_t t;
	string func_name;
	Timing(string func_name){
		t = clock();
		this->func_name = func_name;
	}
	~Timing(){
		t = clock() -t;
		cerr<<"\nFunction "<<func_name<<" took: "<< t <<"clicks ("<< ((float)t)/CLOCKS_PER_SEC<<"seconds) to complete.";
	}
};

#endif
