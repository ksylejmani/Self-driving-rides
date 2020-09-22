#ifndef SOME_FUNCTIONS_H
#define SOME_FUNCTIONS_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

struct data_set;

using namespace std;

vector<int> 						split_string_to_ints(string);
unordered_map<int, vector<int>>		read_solution_file();

int get_score(const data_set&, const unordered_map<int, vector<int>>&);
int get_score_for_one_vehicle(const data_set&, const unordered_map<int, vector<int>>&, const int& vehicle_index);
int get_score_for_one_ride(const data_set&, const int& ride_index, pair<int, int>& position, int& step);

// Delta get_score
int get_score(const data_set&, const unordered_map<int, vector<int>>&, const int& previous_score, const int& vehicle_index, const int& previous_ride, const int& new_ride);
int delta_get_score_ver2(const data_set&, const unordered_map<int, vector<int>>&, const int& previous_score, const int& vehicle_index, const int& previous_ride_index_in_vector, const int& new_ride);

int get_score_for_one_vehicle(const data_set&, const vector<int>&); // By Enes

int score_from_rides();
int score_from_vehicles();

#endif
