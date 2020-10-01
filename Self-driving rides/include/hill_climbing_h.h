#ifndef HILL_CLIMBING
#define HILL_CLIMBING

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

    int score_before_tweak;
    bool successful_tweak;
    char attempted_tweak;

	tweak_solution(unordered_map<int, vector<int>>& fleets, vector<int>& unassigned_rides, data_set& d1);

	/*
	NAMING CONVENTION FOR THE FOLLOWING FUNCTIONS:
		t_*		- call to execute full tweak
		ht_*	- helper tweaks, call within full tweak functions
		k_*		- keep a given tweak, call if satisfied with tweak
		hk_*	- helper keep tweak, call within keep functions
		u_*		- undo tweak, call if not satisfied with tweak
		hu_*	- helper undo tweak, call within undo functions

		no prefix, contains "tweak"			- call appropraiate tweak functions
		no prefix, doesn't contain "tweak"	- general function
	*/

	//do tweaks
	bool tweak();   
	void t_replace_random_ride();
	void t_replace_subsequent_rides();

	void ht_get_random_rides();
	void ht_get_replacements();

	void ht_replace_ride();
	void ht_append_new_ride();

	//if twek yields a better solution
	void keep_tweak();
	void k_replace_random();
	void k_subsequent();
	void hk_append();

	//if tweak didnt yield a better solution
	void undo_tweak();
	void u_revert_replacement();
	void u_revert_subsequent();
	void hu_revert_append();

	//helper functions
    int get_ride_index(ride* ride);
    ride& get_ride(int ride_index);
    void mark_assigned_rides();
    void fix_number_of_rides_per_vehicle();
};

#endif
