#include <cstdlib>
#include <iostream>
#include <ctime>
 
#include "../include/hill_climbing_h.h"
#include "../include/some_functions_h.h"
#include "../include/global_variables_h.h"

using namespace std;

void stochastic_hill_climbing(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1){
	tweak_solution stochastic(fleets, unassigned_rides, d1);
    int score = get_score(d1, fleets);
    while(true){
    if (score >=  score_satisfactory_coefficient * d1.T * d1.F )
    	//what is the highest possible score?
    	break;

    	stochastic.tweak();
    	int c_score = get_score(d1, fleets);
    	if(c_score > score){
    		checked_close_next_rides = false;
    		stochastic.keep_replace();
    	}
    	else{
    		stochastic.undo_replace();
    	}
    // }
}

tweak_solution::tweak_solution(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1){
	this->fleets = fleets;
	this->unassigned_rides = unassigned_rides;
	this->d1 = d1;
	checked_close_next_rides = false;

	mark_assigned_rides();
}

void tweak_solution::tweak(){
	get_random_rides();
	replace_ride_with_unassigned();
}

void tweak_solution::get_random_rides(){
	Timing t("get_random_rides");

	srand(time(nullptr));
	random_vehicle = rand() % d1.F + 1;
	random_ride = rand() % (fleets[random_vehicle].size() - 1);

	if(!checked_close_next_rides){
		//get array with random order of elements
		vector<int> shuffled_array(no_close_next_rides);
		std::for_each(shuffled_array.begin(), shuffled_array.end(), [](int &n){ n++; });
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(shuffled_array.begin(), shuffled_array.end(), std::default_random_engine(seed));

		//get ride from close_next_rides and check if it has been assigned
		auto check_assignment = [&](int n){
			ride* ride_to_check = get_ride(random_ride).close_next_rides[n];
			int index_to_check = get_ride_index(ride_to_check);
			if(!((*ride_to_check).assigned))
				replacements.push(index_to_check);
		};
		for_each(shuffled_array.begin(), shuffled_array.end(), check_assignment);
		checked_close_next_rides = true;
	}

	if(replacements.empty()){
		replacements.push(unassigned_rides[rand() % unassigned_rides.size()])
	}
}

void tweak_solution::replace_ride_with_unassigned(){
	latest_replacement = fleets[random_vehicle][random_ride+1];
	fleets[random_vehicle][random_ride+1] = replacements.front();
	replacements.pop();
}

//IF TWEAK DIDN'T YIELD A BETTER SOLUTION
void tweak_solution::undo_replace(){
	fleets[random_vehicle][random_ride+1] = latest_replacement;
}

void tweak_solution::keep_replace(){
	auto iterator = find(unassigned_rides.rbegin(), unassigned_rides.rend(), latest_replacement);
	*iterator = -1;
}

//HELPER FUNCTIONS
void tweak_solution::mark_assigned_rides(){
	for(auto vehicle : fleets ){
		for(auto ride : vehicle.second){
			get_ride(ride).assigned = true;
		}
	}
}
int tweak_solution::get_ride_index(ride* ride){
	return  distance(d1.rides.begin(), find(d1.rides.begin(), d1.rides.end(), ride));
}
ride& tweak_solution::get_ride(int ride_index){
	return *(d1.rides[ride_index]);
}
