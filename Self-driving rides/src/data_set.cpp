#include <algorithm> 
#include <utility>
#include <sstream>
#include <fstream>
#include <queue>
#include <math.h>

#include "../include/data_set_h.h"
#include "../include/some_functions_h.h"
#include "../include/ride_h.h"
#include "../include/Timing_h.h"
#include "../include/global_variables_h.h"

data_set::data_set(){}

data_set::data_set(string instance_path)
	: instance(instance_path)
 {
	Timing t("data_set");
	// Read and place the data from the file in the respective variables and arrays  
	read_instance_file(instance);
	//optimize storage
	rides.shrink_to_fit();
	// Find the next close rides for each ride
	for (ride* d_ride : rides){
		find_k_closest_rides(d_ride);
	}
	// Test the functionality of the code in the main function
}

vector<int> data_set::split_string_to_ints(string line) {
	// Used to split string around spaces. 
	stringstream ss_line(line);
	vector<int> values;
    // read as many numbers as possible.
    for (int number; ss_line >> number;) {
        values.push_back(number);
    }
	return values;
}

void data_set::process_first_line(string first_line) {
	vector<int> values = split_string_to_ints(first_line);
	//initiate data_set  
	R = values[0];	C = values[1];	F = values[2];
	N = values[3];	B = values[4];	T = values[5];

	rides.reserve(N); //optimize the vector rides to allocate accordingly
}

void data_set::process_ride_lines(string ride_line) {
	vector<int> values = split_string_to_ints(ride_line);
	//get a new "ride" initiated with values read on currennt line and initiate variables appropriately
	ride* new_ride = new ride(values[0], values[1], values[2], values[3], values[4], values[5]);
	rides.push_back(new_ride);
}

void data_set::read_instance_file(string instance_name) {
	Timing t("read_instance_file");
	ifstream wf(instance_name);
	if (wf.is_open()) {
		//read first line of instance_name
		string first_line;
		getline(wf, first_line);
		process_first_line(first_line);
		//read the rest of instance_name lines
		string ride_line;
		while (getline(wf, ride_line)) {
			process_ride_lines(ride_line);
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
		int check_distance = abs(given_ride->x - check_ride->a) + abs(given_ride->y - check_ride->b);

		if (closest_distance >= check_distance) {
			if ( find (given_ride->close_next_rides.begin(), given_ride->close_next_rides.end(), check_ride) == given_ride->close_next_rides.end()) {
				closest_ride = check_ride;
				closest_distance = check_distance;
				// closest_distance = get_closest_distance(closest_distance, check_distance);
			}
		}
	}
	return closest_ride;
}
void data_set::find_k_closest_rides(ride* given_ride) {
	//min(K, N - 1) in case K is bigger than the number of rides
	int number_of_close_next_rides = min(no_close_next_rides, N - 1);
	for (int i = 0; i < number_of_close_next_rides ; i++)
		given_ride->close_next_rides.push_back(find_close_ride(given_ride));

}
void data_set::get_instance_details(vector<int>& info){
	info[0] = this->R; info[1] = this->C; info[2] = this->F;
	info[3] = this->N; info[4] = this->B; info[5] = this->T;
}
