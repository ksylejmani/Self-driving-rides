#include <vector>
#include <unordered_map>
#include <list>
#include <chrono>
#include <ctime>
#include <algorithm>

#include "../include/global_variables_h.h"
#include "../include/get_solutions_h.h"
#include "../include/data_set_h.h"

using namespace std;

vector <int> unassigned_rides;
	unordered_map<int, vector<int>> get_initial_solution_variant_1(data_set ds) {
		// Variant 1 - Fully random, to be done by Enes
		unordered_map<int, vector<int>> result;
		vector<int>* vehicles = new vector<int>[ds.F];
		srand(time(NULL));
		list<int> assigned_rides;
		//counters count the number of rides we assign to a car
		vector <int> Counters(ds.F, 0);
		//Implementation goes here ...
		for (int i = 0; i < ds.N; i++)
			unassigned_rides.push_back(i);
		random_shuffle(unassigned_rides.begin(), unassigned_rides.end());
		for (int i = 0; i < ds.F; i++)
		{
			int time_left = ds.T;
			//list of the rides that are unaffordable for the car i
			vector <int> unaffordable_rides;
			//while there is some time left, do ...
			while (time_left > initial_solution_time_left_margin*ds.T)
			{
				int random_ride = unassigned_rides.back();
				unassigned_rides.pop_back();
				//earliest_time is the number of steps that has passed by the time vehicle starts riding at the starting intersection , we firstly say that it is equal to the earliest start
				int earliest_time = ds.rides.at(random_ride)->s;

				//if this is the first ride for vehicle i
				if (time_left == ds.T) {
					if (ds.rides.at(random_ride)->s < (ds.rides.at(random_ride)->a + ds.rides.at(random_ride)->b))
						earliest_time = ds.rides.at(random_ride)->a + ds.rides.at(random_ride)->b;
				}
				//if this isn't the first ride for vehicle i
				else
				{
					//distance_last_first is the distance from the last intersection of the previous ride to the begining of the start intersection of the current ride
					int distance_last_first = abs(ds.rides.at(random_ride)->a - ds.rides.at(assigned_rides.back())->x) + abs(ds.rides.at(random_ride)->b - ds.rides.at(assigned_rides.back())->y);
					if (ds.rides.at(random_ride)->s < ds.T - time_left + distance_last_first)
						earliest_time = ds.T - time_left + distance_last_first;
				}

				int distance_between_intersections = abs(ds.rides.at(random_ride)->a - ds.rides.at(random_ride)->x) + abs(ds.rides.at(random_ride)->b - ds.rides.at(random_ride)->y);
				//if the ride ended before or in the latest step , do ...
				if (earliest_time + distance_between_intersections <= ds.rides.at(random_ride)->f)
				{
					assigned_rides.push_back(random_ride);
					vehicles[i].push_back(random_ride);
					time_left = ds.T - (earliest_time + distance_between_intersections);
					Counters.at(i)++;
					//if all rides are assigned or if we have checked all rides for the car i there is nothing left to check so go to the next car (break)
					if ((assigned_rides.size() == ds.N) || (unaffordable_rides.size() + assigned_rides.size() == ds.N) || time_left <= initial_solution_time_left_margin*ds.T ) {
						unassigned_rides.insert(unassigned_rides.end(),unaffordable_rides.begin(), unaffordable_rides.end());
						break;
					}
				}
				//if the ride didn't end before or in the last step (it's unaffordable for car i) , do ...
				else
				{
					unaffordable_rides.push_back(random_ride);
					//if all rides are unaffordable (pretty sure that this condition never gets true , put it for the sake of safeness) , or we have checked all rides , break .
					if ((unaffordable_rides.size() == ds.N - assigned_rides.size()) || (unaffordable_rides.size() == ds.N)) {
						unassigned_rides.insert(unassigned_rides.end(),unaffordable_rides.begin(), unaffordable_rides.end());
						break;
					}
				}
				//Test your solution in the main function

			}
			vehicles[i].insert(vehicles[i].begin(), Counters.at(i));
			result.insert(pair<int, vector<int>>(i, vehicles[i]));
			//if all rides are assigned for the cars up to i , do
			if (assigned_rides.size() == ds.N) {
				//if this isn't the last car left
				if (i != ds.F - 1)
				{
					//assign the rest of the cars 0 rides
					for (int j = i + 1; j < ds.F; j++) {
						vehicles[j].push_back(0);
						result.insert(pair<int, vector<int>>(j, vehicles[j]));
					}
				}
				break;
			}
		}
		return result;
	}

unordered_map<int, vector<int>> get_initial_solution_variant_2(data_set ds) {
	// Variant 2 - Smart random, to be done by Lendrit
	unordered_map<int, vector<int>> result;
	//Implementation goes here ...
	//Test your solution in the main function
	return result;
}

unordered_map<int, vector<int>> get_greedy_local_search_solution(data_set ds) {
	unordered_map<int, vector<int>> d;
	// d= get_initial_solution();// Variant 1 - Fully random, to be done by Enes
								 // Variant 2 - Smart random, to be done by Lendrit
	// d_quality= get_socore(ds,e);
	int i = 1;
	//while (i <= no_iterations) {
		// N= get_neighborhood();
		// e= choose_neighbour(N);
		// e_quality=get_socore(ds,e);
		// if(e_quality>d_quality)
				//d = e;
		//i++;
	//}
	return d;
}
