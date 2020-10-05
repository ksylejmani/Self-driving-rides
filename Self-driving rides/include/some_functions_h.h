#ifndef SOME_FUNCTIONS_H
#define SOME_FUNCTIONS_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include "data_set_h.h"

//struct data_set;

using namespace std;

vector<int> 						split_string_to_ints(string);
unordered_map<int, vector<int>>		read_solution_file();

struct score_calculator {
	data_set ds;
	unordered_map<int, vector<int>>* fleets;
	int score;

	// unordered_map<ride_index, pair<ride_score, starting_time>>
	unordered_map<int, pair<int, int>> ride_info;

	// unordered_map<vehicle_index, vehicle_score>
	unordered_map<int, int> vehicle_scores;

	// Used to temporarily save changes made by delta-get_score
	unordered_map<int, pair<int, int>> ride_info_changes;
	pair<int, int> vehicle_scores_change;
	int previous_ride;
	int new_score;

	score_calculator();
	score_calculator(const data_set& ds, unordered_map<int, vector<int>>* fleets);

	void save_changes();

	// Fills vehicle_scores
	int get_score();
	// Fills ride_info
	int get_score_for_one_vehicle(const int& vehicle_index);
	int get_score_for_one_ride(const int& ride_index, pair<int, int>& position, int& step);

	int score_from_rides();
	int score_from_vehicles();

	// Delta get_score
	// Calculates the difference of score if only one ride is changed
	int get_score(const int& vehicle_index, const int& previous_ride_index_in_vector, const int& new_ride);
};

// Delta get_score
//int get_score(const data_set&, const unordered_map<int, vector<int>>&, const int& previous_score, const int& vehicle_index, const int& previous_ride, const int& new_ride);
int get_score_for_one_vehicle(const data_set&, const vector<int>&); // By Enes

#endif
