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
    for(int i = 0; i < d1.N; i++){
	    if (score >=  score_satisfactory_coefficient * d1.T * d1.F ){
	    	//what is the highest possible score?
	    	break;
	    }		
	    stochastic.tweak();
		int c_score = get_score(d1, fleets);
		if(c_score > score){
			stochastic.keep_replace();
			tee<<"Success! Iteration nr : "<<i<<" ";
			score = c_score;
		}
		else{
			stochastic.undo_replace();
		}
    }
}

tweak_solution::tweak_solution(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1){
	this->fleets = fleets;
	this->unassigned_rides = unassigned_rides;
	this->d1 = d1;

	mark_assigned_rides();
}

void tweak_solution::tweak(){
	get_random_rides();
	replace_ride_with_unassigned();
}

void tweak_solution::get_random_rides(){
	random_vehicle = rand() % fleets.size();
	cout<<"random_vehicle "<<random_vehicle<<endl;
	random_ride = fleets.at(random_vehicle).at( rand() % (fleets.at(random_vehicle).size() - 1));
	cout<<"random_ride "<<random_ride<<endl;

	ride* ride_to_check = get_ride (random_ride).close_next_rides.at (rand() % no_close_next_rides);

	if(!ride_to_check->assigned){
		cout<<"Not assigned\n";
		random_new_ride = get_ride_index (ride_to_check);
	}	else	{
		cout<<"Assigned!\n";
		random_new_ride = unassigned_rides.at (rand() % unassigned_rides.size() - 1);
	}
	cout<<"attempted_replacement "<<attempted_replacement<<endl;
	cout <<"random_new_ride "<< random_new_ride<<endl;
}

void tweak_solution::replace_ride_with_unassigned(){
	cout << "1\n";
	latest_removal = fleets.at (random_vehicle).at (random_ride+1);
	cout << "2\n";
	cout<<"latest_removal "<<latest_removal<<endl;
	attempted_replacement = random_new_ride;
	cout << "3\n";
	cout << "attempted_replacement "<<attempted_replacement<<endl;
	fleets.at (random_vehicle).at (random_ride+1) = attempted_replacement;
	cout<<"4\n";
}

//IF TWEAK DIDN'T YIELD A BETTER SOLUTION
void tweak_solution::undo_replace(){
	fleets.at(random_vehicle).at(random_ride+1) = latest_removal;
}

void tweak_solution::keep_replace(){
	unassigned_rides.push_back (latest_removal);
	unassigned_rides.erase (find (unassigned_rides.begin(), unassigned_rides.end(), attempted_replacement));

	get_ride (latest_removal).assigned = false;
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