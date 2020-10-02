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

int get_score(const data_set& ds, const unordered_map<int, vector<int>>& fleets, unordered_map<int, pair<int, int>>& ride_info,unordered_map<int, int>& vehicle_scores) {
int get_score_for_one_vehicle(const data_set& ds, const unordered_map<int, vector<int>>& fleets, const int& vehicle_index , unordered_map<int, pair<int, int>>& ride_info) ;
int get_score_for_one_ride(const data_set&, const int& ride_index, pair<int, int>& position, int& step);

// Delta get_score
//int get_score(const data_set&, const unordered_map<int, vector<int>>&, const int& previous_score, const int& vehicle_index, const int& previous_ride, const int& new_ride);

int get_score(const data_set& ds, const unordered_map<int, vector<int>>& fleets, const int& previous_score, const int& vehicle_index, const int& previous_ride_index_in_vector, const int& new_ride , unordered_map<int, pair<int, int>>& new_ride_info , unordered_map<int,  int>& new_vehicle_scores);
int get_score_for_one_vehicle(const data_set&, const vector<int>&); // By Enes

int score_from_rides();
int score_from_vehicles();

#endif
