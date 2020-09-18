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
#include "../include/ride_h.h"

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
		int line_number = 0;   // INITIAL VALUE
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

// unordered_map<ride_index, pair<ride_score, starting_time>>
unordered_map<int, pair<int, int>> ride_info;
// unordered_map<vehicle_index, vehicle_score>
unordered_map<int, int> vehicle_scores;

int get_score(const data_set& ds,const unordered_map<int, vector<int>>& fleets) {// To be done by Erlis

	int result = 0; // Contains the score of all vehicles combined including bonuses
	/*
	We assume that each ride is assigned to a vehicle only once
	and that M (the first value of each vector of the map) is always
	the number of rides assigned to the respective vehicle
	*/
	int bonus = ds.B;

	for (auto it = fleets.begin(); it != fleets.end(); it++) // Iterate for each vehicle
	{
		int vehicle_index = it->first;
		int vehicle_score = 0; // Contains the score of the current vehicle
		pair<int, int> position(0, 0); // Starting position of each vehicle
		int step = 0; // The starting step for each vehicle

		for (int i = 1; i < it->second.size(); i++) // Iterate for each ride of the current vehicle
		{
			int ride_score = 0; // Contains the score of the current ride
			int ride_index = it->second[i];
			ride* current_ride = ds.rides[ride_index];

			int a = current_ride->a;	int x = current_ride->x;	int earliest_start = current_ride->s;
			int b = current_ride->b;	int y = current_ride->y;	int latest_finish = current_ride->f;

			int distance_from_position_to_start = abs(a - position.first) + abs(b - position.second); // Distance from current position to the start intersection of the ride
			step += distance_from_position_to_start;

			if (step < earliest_start) // Including the waiting time until the earliest start
				step = earliest_start;

			int starting_time = step;

			int distance_from_start_to_finish = abs(x - a) + abs(y - b); // Distance from the start intersection to the finish intersection of the ride
			step += distance_from_start_to_finish;

			if (step <= latest_finish) {
				ride_score += distance_from_start_to_finish;
				if ((step - distance_from_start_to_finish) == earliest_start)
					ride_score += bonus;
			}

			position = make_pair(x, y); // At the end of the ride the vehicle is located at the finish intersection

			if (step <= ds.T) {
				ride_info[ride_index] = make_pair(ride_score, starting_time);
				vehicle_score += ride_score;
			}
			else {
				for (int j = i; j < it->second.size(); j++) {
					ride_index = it->second[j];
					ride_info[ride_index] = make_pair(0, -1);
				}
				break;
			}
		}
		vehicle_scores[vehicle_index] = vehicle_score;
		result += vehicle_score;
	}
	// Test your function by using both solutions of Enes and Lendrit
	return result;
}

int score_from_rides() {
	int score = 0;
	for (auto it = ride_info.begin(); it != ride_info.end(); it++) {
		int ride_score = it->second.first;
		score += ride_score;
	}
	return score;
}

int score_from_vehicles() {
	int score = 0;
	for (auto it = vehicle_scores.begin(); it != vehicle_scores.end(); it++) {
		int vehicle_score = it->second;
		score += vehicle_score;
	}
	return score;
}

// Delta get_score
// Calculates the difference of score if only one ride is changed
int get_score(const data_set& ds, const unordered_map<int, vector<int>>& fleets, const int& previous_score, const int& vehicle_index, const int& previous_ride, const int& new_ride) {
	int bonus = ds.B;
	int time_left = ds.T;

	int vehicle_score = 0; // Contains the score of the vehicle
	pair<int, int> position(0, 0); // Starting position of the vehicle
	int step = 0; // The starting step for each vehicle

	for (int j = 1; j < fleets.at(vehicle_index).size(); j++) // Iterate for each ride of the vehicle
	{
		int ride_score = 0; // Contains the score of the current ride
		int nr_of_current_ride = fleets.at(vehicle_index)[j];
		ride* current_ride = ds.rides[nr_of_current_ride];

		int a = current_ride->a;	int x = current_ride->x;	int earliest_start = current_ride->s;
		int b = current_ride->b;	int y = current_ride->y;	int latest_finish = current_ride->f;

		int distance_from_position_to_start = abs(a - position.first) + abs(b - position.second); // Distance from current position to the start intersection of the ride
		step += distance_from_position_to_start;

		if (step < earliest_start) // Including the waiting time until the earliest start
			step = earliest_start;

		int distance_from_start_to_finish = abs(x - a) + abs(y - b); // Distance from the start intersection to the finish intersection of the ride
		step += distance_from_start_to_finish;

		if (step <= latest_finish) {
			ride_score += distance_from_start_to_finish;
			if ((step - distance_from_start_to_finish) == earliest_start)
				ride_score += bonus;
		}

		position = make_pair(x, y); // At the end of the ride the vehicle is located at the finish intersection

		if (step <= ds.T) {
			vehicle_score += ride_score;
		}
		else
			break;
	}

	int new_score = previous_score - vehicle_score;

	int new_vehicle_score = 0;
	position = make_pair(0, 0);
	step = 0;
	for (int j = 1; j < fleets.at(vehicle_index).size(); j++) // Iterate for each ride of the current vehicle
	{
		int ride_score = 0; // Contains the score of the current ride
		int nr_of_current_ride = fleets.at(vehicle_index)[j];
		ride* current_ride;
		if (nr_of_current_ride == previous_ride)
			current_ride = ds.rides[new_ride];
		else
			current_ride = ds.rides[nr_of_current_ride];

		int a = current_ride->a;	int x = current_ride->x;	int earliest_start = current_ride->s;
		int b = current_ride->b;	int y = current_ride->y;	int latest_finish = current_ride->f;

		int distance_from_position_to_start = abs(a - position.first) + abs(b - position.second); // Distance from current position to the start intersection of the ride
		step += distance_from_position_to_start;

		if (step < earliest_start) // Including the waiting time until the earliest start
			step = earliest_start;

		int distance_from_start_to_finish = abs(x - a) + abs(y - b); // Distance from the start intersection to the finish intersection of the ride
		step += distance_from_start_to_finish;

		if (step <= latest_finish) {
			ride_score += distance_from_start_to_finish;
			if ((step - distance_from_start_to_finish) == earliest_start)
				ride_score += bonus;
		}

		position = make_pair(x, y); // At the end of the ride the vehicle is located at the finish intersection

		if (step <= ds.T) {
			new_vehicle_score += ride_score;
		}
		else
			break;
	}

	new_score += new_vehicle_score;

	return new_score;
}

int get_score_for_one_vehicle(const data_set& ds,const vector<int>& scoring_vehicle) {
		int score = 0;
		if (scoring_vehicle.size()==1)
			return score;
		int time_passed = 0;
		int distance_from_zero_intersection = ds.rides.at(scoring_vehicle[1])->a + ds.rides.at(scoring_vehicle[1])->b;
		for (int i = 1; i < scoring_vehicle.size(); i++)
		{
			int distance_between_intersections = 0;
			int distance_last_first = 0;
			distance_between_intersections = abs(ds.rides.at(scoring_vehicle[i])->a - ds.rides.at(scoring_vehicle[i])->x) + abs(ds.rides.at(scoring_vehicle[i])->b - ds.rides.at(scoring_vehicle[i])->y);
			if (i == 1)
			{
				score += distance_between_intersections;
				if (ds.rides.at(scoring_vehicle[i])->s >= distance_from_zero_intersection) {
					time_passed = ds.rides.at(scoring_vehicle[i])->s;
					score += ds.B;
					time_passed += distance_between_intersections;
					continue;
				}
				time_passed += distance_between_intersections+ distance_from_zero_intersection;
				continue;
			}
			distance_last_first = abs(ds.rides.at(scoring_vehicle[i])->a - ds.rides.at(scoring_vehicle[i - 1])->x) + abs(ds.rides.at(scoring_vehicle[i])->b - ds.rides.at(scoring_vehicle[i - 1])->y);
			time_passed += distance_last_first ; 
			score += distance_between_intersections; 
			if (ds.rides.at(scoring_vehicle[i])->s >= time_passed) {
				time_passed = ds.rides.at(scoring_vehicle[i])->s;
				time_passed += distance_between_intersections;
				score += ds.B;
				continue;
			}
			time_passed += distance_between_intersections;
		}
		return score;
	}
