#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <chrono>       // std::chrono::system_clock
#include <iterator> 	// std::distance

#include "../include/hill_climbing_h.h"
#include "../include/ride_h.h"
#include "../include/Timing_h.h"
#include "../include/dual_output_h.h"
#include "../include/some_functions_h.h"
using namespace std;

ofstream debug("debug.txt");
oteestream    tee(debug, cout);

void stochastic_hill_climbing(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1){
	Timing t("stochastic_hill_climbing");
	tweak_solution stochastic(fleets, unassigned_rides, d1);

    int score = get_score(d1, fleets);
    
    for(int i = 0; i< d1.N; i++){
    	//what is the highest possible score?

	    if(!stochastic.tweak())
	    	break;

		int c_score = get_score(d1, fleets);
		cout<<"Score after tweak: "<<c_score<<endl;
		if(c_score > score){
			stochastic.keep_replace();
			tee<<"Success! Iteration nr : "<<i<<"==========\n";
			score = c_score;
		}
		else{
			stochastic.undo_tweak();
		}
    }
}

tweak_solution::tweak_solution(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1)
	: fleets(fleets), unassigned_rides(unassigned_rides), d1(d1)
{
	mark_assigned_rides();
}

bool tweak_solution::tweak(){
	if(!unassigned_rides.empty()){
		get_random_rides();
		replace_ride_with_unassigned();
		return true;
	}
	return false;
}

void tweak_solution::get_random_rides(){
	random_vehicle = rand() % fleets.size();
	random_ride_fleets_index = rand() % (fleets.at(random_vehicle).size() - 1);
	random_ride = fleets.at(random_vehicle).at( random_ride_fleets_index );

	ride* ride_to_check = get_ride (random_ride).close_next_rides.at (rand() % no_close_next_rides);

	if(!ride_to_check->assigned){
		random_new_ride = get_ride_index (ride_to_check);
	}	else	{
		random_new_ride = unassigned_rides.at (rand() % unassigned_rides.size());
	}
}

void tweak_solution::replace_ride_with_unassigned(){
	ride_to_remove = fleets.at (random_vehicle).at (random_ride_fleets_index + 1);
	attempted_replacement = random_new_ride;
	fleets.at (random_vehicle).at (random_ride_fleets_index + 1) = attempted_replacement;
}

//IF TWEAK DIDN'T YIELD A BETTER SOLUTION
void tweak_solution::undo_tweak(){
	undo_replace_ride_with_unassigned();
}

void tweak_solution::undo_replace_ride_with_unassigned(){
	fleets.at(random_vehicle).at(random_ride_fleets_index + 1) = ride_to_remove;
}

void tweak_solution::keep_replace(){
	unassigned_rides.push_back (ride_to_remove);
	unassigned_rides.erase (find (unassigned_rides.begin(), unassigned_rides.end(), attempted_replacement));

	get_ride (ride_to_remove).assigned = false;
	get_ride (attempted_replacement).assigned = true;
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
	return *(d1.rides.at(ride_index));
}
