#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept> // std::runtime_error
#include <math.h>	//abs()
#include <stdlib.h> //exit()
#include <iostream> //cerr<<

#include "../include/some_functions_h.h"
#include "../include/data_set_h.h"
#include "../include/global_variables_h.h"

using namespace std;


vector<int> split_string_to_ints(string line) {
	stringstream ss_line(line);
	vector<int> values;
    for (int number; ss_line >> number;){
        values.push_back(number);
    }
	return values;
}

unordered_map<int, vector<int>> read_solution_file(){
	unordered_map<int, vector<int>> fleets;
	ifstream wf(solution_path);
	if (wf.is_open()) {
		string line;
		int line_number = 1;   // INITIAL VALUE
		while (getline(wf, line)){
			fleets.insert(make_pair(line_number++, split_string_to_ints(line)));
		}
		wf.close();
	}
	else{
		cerr<<"\n\nCould not open solution file!\n\n";
		exit(EXIT_FAILURE);
	}
	return fleets;
}


int get_score(const data_set& ds, unordered_map<int, vector<int>> fleets) {// To be done by Erlis
	int result = 0; // Contains the score of all vehicles combined including bonuses
	/*
	We assume that each ride is assigned to a vehicle only once
	and that M (the first value of each vector of the map) is always
	the number of rides assigned to the respective vehicle
	*/
	int bonus = ds.B;

	for (auto it = fleets.begin(); it != fleets.end(); it++) // Iterate for each vehicle
	{
		int vehicle_score = 0; // Contains the score of the current vehicle
		pair<int, int> position(0, 0); // Starting position of each vehicle
		int step = 0; // The starting step for each vehicle

		for (int j = 1; j < it->second.size(); j++) // Iterate for each ride of the current vehicle
		{
			int ride_score = 0; // Contains the score of the current ride
			int nr_of_current_ride = it->second[j];
			ride* current_ride = ds.rides[nr_of_current_ride];

			int a = current_ride->a;	int b = current_ride->b;
			int x = current_ride->x;	int y = current_ride->y;
			int earliest_start = current_ride->s;	int latest_finish = current_ride->f;

			int distance_from_position_to_start = abs(a - position.first) + abs(b - position.second); // Distance from current position to the start intersection of the ride
			int distance_from_start_to_finish = abs(x - a) + abs(y - b); // Distance from the start intersection to the finish intersection of the ride

			int distance_from_position_to_finish = distance_from_position_to_start + distance_from_start_to_finish; // The distance which the vehicle travels
			if(step + distance_from_position_to_start < earliest_start) // Including the waiting time until the earliest start
				distance_from_position_to_finish += earliest_start - (step + distance_from_position_to_start);

			step += distance_from_position_to_finish;
			if (step > latest_finish)
				goto fundi;
			else {
				ride_score += distance_from_start_to_finish;
				if((step - distance_from_start_to_finish) == earliest_start)
					ride_score += bonus;
			}

			position = make_pair(x, y); // At the end of the ride the vehicle is located at the finish intersection

		fundi:
			vehicle_score += ride_score;
		}
		result += vehicle_score;
	}

	// Test your function by using both solutions of Enes and Lendrit
	return result;
}
