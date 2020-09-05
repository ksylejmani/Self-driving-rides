#ifndef GET_SOLUTIONS_H
#define GET_SOLUTIONS_H

#include <unordered_map>
#include <vector>

#include "data_set_h.h"

unordered_map<int, vector<int>> get_initial_solution_variant_1(data_set ds);
unordered_map<int, vector<int>> get_initial_solution_variant_2(data_set ds);
unordered_map<int, vector<int>> get_greedy_local_search_solution(data_set ds);

#endif
