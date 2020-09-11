#ifndef SOME_FUNCTIONS_H
#define SOME_FUNCTIONS_H

#include <unordered_map>
#include <string>
#include <iostream>

struct data_set;

using namespace std;

vector<int> 						split_string_to_ints(string);
unordered_map<int, vector<int>>		read_solution_file();

int get_score (const data_set&, unordered_map<int, vector<int>>);

#endif
