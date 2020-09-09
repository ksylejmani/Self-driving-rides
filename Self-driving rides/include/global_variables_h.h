#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <string>

using namespace std;

//Parameters
//see global_variables.cpp
extern const int no_iterations;
extern const int no_close_next_rides;
extern const int no_replace_next_rides;
extern const int difference_earliest_start_time;
extern const int difference_latest_finish_time;
extern const double initial_solution_time_left_margin;
extern const double score_satisfactory_coefficient;
extern string 	 instance_name;
extern string	 instance_path;
extern string	 solution_path;

#endif
