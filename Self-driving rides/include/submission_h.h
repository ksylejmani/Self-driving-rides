#ifndef SUBMISSION_H
#define SUBMISSION_H

#include <vector>
#include <unordered_map>

using namespace std;

struct submission{
	//Goals:
	//Get solution via consturctor
	//Place solution to a file
	string solution;
	unordered_map<int, vector<int>> fleets;

	submission(const unordered_map<int, vector<int>>&, string);
	void output_solution();

};

#endif
