#ifndef DATA_SET_H
#define DATA_SET_H

#include <vector>

#include "global_variables_h.h"
struct ride;

using namespace std;

struct data_set {
	int 			R, C, F, N, B, T;
	vector<ride*>	rides;
	string 			instance;
	data_set();
	data_set(string);

	void 			read_instance_file();
	void 			process_first_line(string);
	void 			process_ride_lines(string);

	//Could be private
	ride* 			find_close_ride(ride*);

	void 			find_k_closest_rides(ride*);

	void 			get_closest_distance(int, int); //not yet implemented
	void 			get_instance_details(vector<int>&);
};

#endif
