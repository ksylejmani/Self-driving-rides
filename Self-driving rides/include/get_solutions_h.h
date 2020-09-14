#ifndef GET_SOLUTIONS_H
#define GET_SOLUTIONS_H

#include <unordered_map>
#include <vector>

struct data_set;

using namespace std;

extern vector<int> unassigned_rides_variant_1;
unordered_map<int, vector<int>> get_initial_solution_variant_1 (const data_set&);
unordered_map<int, vector<int>> get_initial_solution_variant_2 (const data_set&);
unordered_map<int, vector<int>> get_greedy_local_search_solution (const data_set&);

#endif
