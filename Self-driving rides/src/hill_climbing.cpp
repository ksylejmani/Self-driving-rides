#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <chrono>       // std::chrono::system_clock
#include <iterator> 	// std::distance
#include <stdexcept>      // std::out_of_range

#include "../include/hill_climbing_h.h"
#include "../include/ride_h.h"
#include "../include/dual_output_h.h"
#include "../include/some_functions_h.h"
using namespace std;

void stochastic_hill_climbing(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1){
	tweak_solution stochastic(fleets, unassigned_rides, d1);
	cout<<"stochastic\n";
    int score = get_score(d1, fleets);
    cout<<"Score\n";
    for(int i = 1; i< 10000; i++){
    	//what is the highest possible score?

	    if(!stochastic.tweak()){
	    	break;
	    }
		cout<< "Vehicle "<<stochastic.random_vehicle <<" ride_fleets_index "<<stochastic.random_ride_fleets_index <<" ride "
			<< stochastic.random_ride <<" random new ride "<< stochastic.random_new_ride<<endl;
	    	
		int c_score = get_score(d1, fleets);
		if(c_score > score){
			stochastic.keep_replace();
			cout<<"Score after tweeak: "<<c_score<<endl;
			cout << "Success! Iteration nr : " << i << "==========\n";
			score = c_score;
		}
		else{
			stochastic.undo_tweak();
		}
    }
}

tweak_solution::tweak_solution(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1)
	: fleets(fleets), unassigned_rides(unassigned_rides), d1(d1), successful_tweak(false)
{
	mark_assigned_rides();
}

bool tweak_solution::tweak(){
	if(!unassigned_rides.empty()){
		cout<<"Not empty\n";
		if(!successful_tweak)
		{
			 get_random_rides();
		}
		else
		{
			get_replacements(random_vehicle, random_ride_fleets_index);
		}
		replace_ride_with_unassigned();
		return true;
	} 
	else {
		cout<<"false";
		return false;
	}
}

void tweak_solution::get_random_rides(){
	random_vehicle = rand() % fleets.size();
	cout<<"random_vehicle "<<random_vehicle<<endl;
	random_ride_fleets_index = (fleets.at(random_vehicle).size() >= 2) ? ((rand() % (fleets.at(random_vehicle).size() - 2)) + 1) : 1;
	cout<<"random_ride_fleets_index "<<random_ride_fleets_index<<endl;
	get_replacements(random_vehicle, random_ride_fleets_index);
}

void tweak_solution::get_replacements(size_t random_vehicle, size_t random_ride_fleets_index){
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

void tweak_solution::replace_ride_with_unassigned(){
	if(random_ride_fleets_index < fleets.at( random_vehicle).size() - 2){
		ride_to_remove = fleets.at (random_vehicle).at (random_ride_fleets_index + 1);
		attempted_replacement = random_new_ride;		
		fleets.at (random_vehicle).at (random_ride_fleets_index + 1) = attempted_replacement;
	}
	else{
		ride_to_remove = -1;
		attempted_replacement = random_new_ride;		
		fleets.at (random_vehicle).push_back(attempted_replacement);
	}
}

//IF TWEAK DIDN'T YIELD A BETTER SOLUTION
void tweak_solution::undo_tweak(){
	undo_replace_ride_with_unassigned();
}

void tweak_solution::undo_replace_ride_with_unassigned(){
	if(ride_to_remove != -1)
	{
		fleets.at(random_vehicle).at(random_ride_fleets_index + 1) = ride_to_remove;
	}
	else
	{
		fleets.at(random_vehicle).pop_back();
	}
	successful_tweak = false;
}

void tweak_solution::keep_replace(){
	if(ride_to_remove != -1)
	{
		unassigned_rides.push_back(ride_to_remove);
	}
	unassigned_rides.erase (find (unassigned_rides.begin(), unassigned_rides.end(), attempted_replacement));

	if(ride_to_remove != -1){
		get_ride (ride_to_remove).assigned = false;
	}
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

void tweak_solution::restate_number_of_rides_per_vehicle(){
	for(auto vehicle =  fleets.begin(); vehicle != fleets.end(); vehicle++){
		vehicle->second[0] =  vehicle->second.size() -1;
	}
}