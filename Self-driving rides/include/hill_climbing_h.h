#ifndef HILL_CLIMBING
#define HILL_CLIMBING

#include <queue>
#include <unordered_map>

#include "data_set_h.h"

using namespace std;

// void simple_hill_climbing();
// void steepest_ascent_hill_climbing();
void stochastic_hill_climbing(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1);

struct tweak_solution
{
	unordered_map<int, vector<int>>& fleets;
	vector<int>& 					unassigned_rides;
	data_set& 						d1;

    size_t random_vehicle; 				// vehicle to improve it's rides

    size_t random_ride_fleets_index;	// to start improving from
    int random_ride;					// to start improving from

    int random_new_ride;				// to improve with

    int ride_to_remove;					//what has been removed
    int attempted_replacement;			// to improve with (copy of random_new_ride)

    bool successful_tweak;

	tweak_solution(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1);

	bool tweak();   
	void replace_ride_with_unassigned();
	void get_random_rides();
	void get_replacements();

	//if twek yields a better solution
	void keep_tweak();
	void keep_replace();
	//if tweak didnt yield a better solution
	void undo_tweak();
	void undo_replace_ride_with_unassigned();

	//helper functions
    int get_ride_index(ride* ride);
    ride& get_ride(int ride_index);
    void mark_assigned_rides();
    void fix_number_of_rides_per_vehicle();
};

#endif
