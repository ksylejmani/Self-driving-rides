#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>

#include "../include/submission_h.h"
#include "../include/global_variables_h.h"

using namespace std;

submission::submission(const unordered_map<int, vector<int>>& fleets, string solution)
	: fleets(fleets), solution(solution){}

void submission::output_solution() {
	ofstream csv_file(solution);
	for (unordered_map<int, vector<int>>::iterator itr = fleets.begin(); itr != fleets.end(); itr++){
		
		int j = 0;
		csv_file << itr->second.at(j);
		j++;

		for (;j < itr->second.size(); j++)
			csv_file << " " << map_virtual_rides_to_file_rides.at(itr->second.at(j));
		csv_file << endl;
	}
	csv_file.close();
}
