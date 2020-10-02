#include <algorithm> 
#include <utility>
#include <sstream>
#include <fstream>
#include <queue>
#include <math.h>

#include "../include/data_set_h.h"
#include "../include/some_functions_h.h"
#include "../include/ride_h.h"
#include "../include/global_variables_h.h"

data_set::data_set(){}

data_set::data_set(string instance)
	: instance(instance)
 {
	read_instance_file();
	rides.shrink_to_fit();
	for (ride* d_ride : rides){
		find_k_closest_rides(d_ride);
	}
}

void data_set::process_first_line(string first_line) {
	vector<int> values = split_string_to_ints(first_line);
	//initialize data_set  
	R = values[0];	C = values[1];	F = values[2];
	N = values[3];	B = values[4];	T = values[5];

	rides.reserve(N);
}

void data_set::process_ride_lines(string ride_line, int ride_index) {
	vector<int> values = split_string_to_ints(ride_line);
	if(values[0] + values[1] + abs(values[2] - values[0]) + abs(values[3] - values[1]) <= values[5]){	
		ride* new_ride = new ride(values[0], values[1], values[2], values[3], values[4], values[5]);
		map_virtual_rides_to_file_rides[rides.size()] = ride_index;
		rides.push_back(new_ride);
	}
}

void data_set::read_instance_file() {
	ifstream wf(instance);
	if (wf.is_open()) {
		//read first line of instance
		string first_line;
		getline(wf, first_line);
		process_first_line(first_line);
		//read the rest of instance lines
		string ride_line;
		int ride_index = 0;
		while (getline(wf, ride_line)) {
			process_ride_lines(ride_line, ride_index);
			ride_index++;
		}
		wf.close();
	}
}

//Could be private
ride* data_set::find_close_ride(ride* given_ride) {
	ride* closest_ride = new ride();

	//Longest distance possible is number of rows + number of columns (so we can have a starting value)
	int closest_distance = R + C;
	for (ride* check_ride : rides) {
		//Skip if the ride is identical with the given ride
		if (check_ride == given_ride)
			continue;

		//Find the closest ride based on the distance between points
		int check_distance = get_closest_distance(given_ride, check_ride);

		if (closest_distance >= check_distance) {
			if ( find (given_ride->close_next_rides.begin(), given_ride->close_next_rides.end(), check_ride) == given_ride->close_next_rides.end()) {
				closest_ride = check_ride;
				closest_distance = check_distance;
				// closest_distance = some_func(closest_distance, check_distance);
			}
		}
	}
	return closest_ride;
}
int data_set::get_closest_distance(ride* given_ride, ride* check_ride){
	int given_ride_intersections_distance = abs(given_ride->a - given_ride->x) + abs(given_ride->b - given_ride->y); 
	int time = given_ride->s + given_ride_intersections_distance;
	time += abs(given_ride->x - check_ride->a) + abs(given_ride->y - check_ride->b);
	return abs(check_ride->s - time);

}
void data_set::find_k_closest_rides(ride* given_ride) {
	//min(K, N - 1) in case K is bigger than the number of rides
	int number_of_close_next_rides = min(no_close_next_rides, (int) rides.size() - 1);
	for (int i = 0; i < number_of_close_next_rides ; i++){
		given_ride->close_next_rides.push_back(find_close_ride(given_ride));
	}
}
void data_set::get_instance_details(vector<int>& info){
	info[0] = this->R; info[1] = this->C; info[2] = this->F;
	info[3] = this->N; info[4] = this->B; info[5] = this->T;
}
