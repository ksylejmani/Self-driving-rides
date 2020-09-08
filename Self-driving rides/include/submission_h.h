#ifndef SUBMISSION_H
#define SUBMISSION_H

#include <vector>
#include <unordered_map>

#include "data_set_h.h"

using namespace std;

struct submission{
	//Goals:
	//Get solution via consturctor
	//Place solution to a file
	unordered_map<int, vector<int>> fleets;

	submission(const unordered_map<int, vector<int>>&);
	void output_solution();

};

#endif
