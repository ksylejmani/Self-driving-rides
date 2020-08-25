#ifndef SOME_FUNCTIONS_H
#define SOME_FUNCTIONS_H

#include <map>
#include <vector>
#include <string>

#include "data_set_h.h"

using namespace std;

map<int, vector<int>>	 read_solution_file(string solution_name);
int						 get_score(data_set ds, map<int, vector<int>> fleets);

#endif
