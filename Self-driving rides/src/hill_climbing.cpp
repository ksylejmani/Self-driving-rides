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

void print_data_set(const data_set& d1){
	for (ride* d_ride : d1.rides) {
		//ride from [0, 0] to [1, 3], earliest start 2, latest finish 9
		debug << "Ride from [" << d_ride->a << ", " << d_ride->b << "] to [" << d_ride->x << ", " << d_ride->y
			<< "], earliest start " << d_ride->s << ", latest finish " << d_ride->f << endl;

		//Output all the close rides
		int counter = 1;
		for (ride* close_rides : d_ride->close_next_rides) {
			debug << counter++ << " - Close intersection: [" << close_rides->x << ", " << close_rides->y << "]" << endl;
		}
		debug << endl;
	}
}

void print_unassigned(const vector<int>& unassigned){
	cout << "Unassigned rides: \n";
	for(auto it = unassigned.begin(); it != unassigned.end(); it++){
		debug<< *it <<" \t";
	}
}

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
	checked_close_next_rides = false;

	mark_assigned_rides();
}

void tweak_solution::tweak(){
	get_random_rides();
	replace_ride_with_unassigned();
}

void tweak_solution::get_random_rides(){
	random_vehicle = rand() % fleets.size();
	cout<<"random_vehicle "<<random_vehicle<<endl;

	random_ride = fleets[random_vehicle][ rand() % (fleets[random_vehicle].size()-1) ];
	cout<<"random_ride "<<random_ride<<endl;

	ride* ride_to_check = get_ride(random_ride).close_next_rides.at(rand() % no_close_next_rides);
	if(!ride_to_check->assigned)
		replacements.push(get_ride_index(ride_to_check));

	replacements.push(unassigned_rides[unassigned_rides.back()]);
	cout<<"replacements.top() "<<replacements.front()<<endl;
}

void tweak_solution::replace_ride_with_unassigned(){
	latest_removal = fleets.at(random_vehicle).at(random_ride+1);
	attempted_replacement = replacements.front();
	fleets.at(random_vehicle).at(random_ride+1) = attempted_replacement;
	replacements.pop();
}

//IF TWEAK DIDN'T YIELD A BETTER SOLUTION
void tweak_solution::undo_replace(){
	fleets.at(random_vehicle).at(random_ride+1) = latest_removal;
}

void tweak_solution::keep_replace(){
	unassigned_rides.push_back(latest_removal);
	unassigned_rides.erase(find(unassigned_rides.begin(), unassigned_rides.end(), attempted_replacement));

	get_ride(latest_removal).assigned = false;
	get_ride(attempted_replacement).assigned = true;

	checked_close_next_rides = false;
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


// stochastic+steepest
	// if(!checked_close_next_rides){
	// 	//get array with random order of elements
	// 	vector<int> shuffled_array(no_close_next_rides);
	// 	{
	// 		int i = 0;
	// 		std::for_each(shuffled_array.begin(), shuffled_array.end(), [&](int &n){ n = i; i++; });
	// 	}
	// 	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	// 	shuffle(shuffled_array.begin(), shuffled_array.end(), std::default_random_engine(seed));

	// 	for(auto random_index = shuffled_array.begin(); random_index != shuffled_array.end(); random_index++){
	// 		cout<<"random_index "<<*random_index<<endl;

	// 		ride* ride_to_check = get_ride(random_ride).close_next_rides.at(*random_index);
	// 		int index_to_check = get_ride_index(ride_to_check);
	// 		cout<<"index_to_check "<<index_to_check<<endl;

	// 		if(!((*ride_to_check).assigned)){
	// 			replacements.push(index_to_check);
	// 			tee<<"close_unassigned! "<<index_to_check<<"\n";
	// 		}
	// 	}
	// 	checked_close_next_rides = true;
	// 	cout<<"after for loop\n";
	// }	// if(!checked_close_next_rides)

//where replacements is queue


