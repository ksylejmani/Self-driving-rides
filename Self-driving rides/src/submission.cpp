#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "../include/submission_h.h"
#include "../include/get_solutions_h.h"

using namespace std;

submission::submission(const unordered_map<int, vector<int>>& fleets){
	this->fleets = fleets;
}


void submission::output_solution() {
	ofstream csv_file(solution_path);
	for (unordered_map<int, vector<int>>::iterator itr = fleets.begin(); itr != fleets.end(); itr++){
		
		int j = 0;
		csv_file << itr->second.at(j);
		j++;

		for (;j < itr->second.size(); j++)
			csv_file << " " << itr->second.at(j);
		csv_file << endl;
	}
}
