
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <chrono>       // std::chrono::system_clock
#include <iterator> 	// std::distance
#include <stdexcept>      // std::out_of_range

#include "../include/hill_climbing_h.h"
#include "../include/ride_h.h"
#include "../include/some_functions_h.h"
using namespace std;

void stochastic_hill_climbing(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1){
	tweak_solution stochastic(fleets, unassigned_rides, d1);
	int score = get_score(d1, fleets);
    for(int i = 1; i < no_iterations; i++){
	    if(!stochastic.tweak()){
	    	break;
	    }
		int current_score = get_score(d1, fleets);
		if(current_score > score){
			stochastic.keep_tweak();
			score = current_score; //for next iteration
		}
		else
		{
			stochastic.undo_tweak();
		}
    }
    stochastic.fix_number_of_rides_per_vehicle();
}

tweak_solution::tweak_solution(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1)
	: fleets(fleets), unassigned_rides(unassigned_rides), d1(d1), successful_tweak(false)
{
	mark_assigned_rides();
}

bool tweak_solution::tweak(){
	if(!unassigned_rides.empty())
	{
		if(!successful_tweak)
		{
			t_replace_random_ride();
		}
		else
		{
			t_replace_subsequent_rides();
		}
		return true;
	} 
	else 
	{
		return false;
	}
}

void tweak_solution::t_replace_subsequent_rides(){
	ht_get_replacements();
	if(random_ride_fleets_index < fleets.at(random_vehicle).size() - 2)
	{
		ht_replace_ride();
	}
	else
	{
		ht_append_new_ride();
	}
	attempted_tweak = 'S';
}

void tweak_solution::t_replace_random_ride(){
	ht_get_random_rides();
	ht_get_replacements();
	ht_replace_ride();
	attempted_tweak = 'R';
}

void tweak_solution::ht_get_random_rides(){
	random_vehicle = rand() % fleets.size();
	while(fleets.at(random_vehicle).size() < 3)
	{
		random_vehicle = rand() % fleets.size();
	}

	if(fleets.at(random_vehicle).size() >= 4)
	{
		random_ride_fleets_index = (rand() % (fleets.at(random_vehicle).size() - 2)) + 1;
	} 
	else
	{
		random_ride_fleets_index = 1;
	}
}


void tweak_solution::ht_get_replacements(){
	random_ride = fleets.at(random_vehicle).at( random_ride_fleets_index );
	ride* ride_to_check = get_ride (random_ride).close_next_rides.at (rand() % no_close_next_rides);
	if(!ride_to_check->assigned)
	{
		random_new_ride = get_ride_index (ride_to_check);
	}	
	else
	{
		random_new_ride = unassigned_rides.at (rand() % unassigned_rides.size());
	}
}

void tweak_solution::ht_replace_ride(){

	ride_to_remove = fleets.at (random_vehicle).at (random_ride_fleets_index + 1);
	attempted_replacement = random_new_ride;	
	fleets.at (random_vehicle).at (random_ride_fleets_index + 1) = attempted_replacement;
}

void tweak_solution::ht_append_new_ride(){
	ride_to_remove = -1;
	attempted_replacement = random_new_ride;		
	fleets.at (random_vehicle).push_back(attempted_replacement);
}

//IF TWEAK DIDN'T YIELD A BETTER SOLUTION
void tweak_solution::undo_tweak(){
	switch(attempted_tweak){
		case 'R':
		u_revert_replacement();
		break;
		case 'S':
		u_revert_subsequent();
		break;
	}
}

void tweak_solution::u_revert_replacement(){
	fleets.at(random_vehicle).at(random_ride_fleets_index + 1) = ride_to_remove;
	successful_tweak = false;
}

void tweak_solution::u_revert_subsequent(){
	if(ride_to_remove == -1)
	{
		hu_revert_append();
	}
	else
	{
		u_revert_replacement();
	}
}

void tweak_solution::hu_revert_append(){
	fleets.at(random_vehicle).pop_back();
	successful_tweak = false;

}
//IF TWEAK YIELDED A BETTER SOLTUION
void tweak_solution::keep_tweak(){
	switch(attempted_tweak){
		case 'R':
		k_replace_random();
		break;
		case 'S':
		k_subsequent();
		break;
	}
}

void tweak_solution::k_subsequent(){
	if(ride_to_remove == -1)
	{
		hk_append();
	}
	else
	{
		k_replace_random();
	}
}

void tweak_solution::k_replace_random(){
	unassigned_rides.push_back(ride_to_remove);
	unassigned_rides.erase (find (unassigned_rides.begin(), unassigned_rides.end(), attempted_replacement));

	get_ride (ride_to_remove).assigned = false;
	get_ride (attempted_replacement).assigned = true;

	random_ride_fleets_index++;
	successful_tweak = true;
}

void tweak_solution::hk_append(){
	unassigned_rides.erase (find (unassigned_rides.begin(), unassigned_rides.end(), attempted_replacement));
	get_ride (attempted_replacement).assigned = true;

	random_ride_fleets_index++;
	successful_tweak = true;
}

//HELPER FUNCTIONS
void tweak_solution::mark_assigned_rides(){
	for(auto vehicle : fleets ){
		for(auto ride =  vehicle.second.begin() + 1; ride != vehicle.second.end(); ride++){
			get_ride(*ride).assigned = true;
		}
	}
}
int tweak_solution::get_ride_index(ride* ride){
	return  distance(d1.rides.begin(), find(d1.rides.begin(), d1.rides.end(), ride));
}
ride& tweak_solution::get_ride(int ride_index){
	return *(d1.rides.at(ride_index));
}

void tweak_solution::fix_number_of_rides_per_vehicle(){
	for(auto vehicle =  fleets.begin(); vehicle != fleets.end(); vehicle++){
		vehicle->second[0] =  vehicle->second.size() -1;
	}
}