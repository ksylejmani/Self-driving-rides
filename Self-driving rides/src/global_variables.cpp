#include "../include/global_variables_h.h"

const int no_iterations = 10000;
const int no_close_next_rides = 4;
const int no_replace_next_rides =3;
const int difference_earliest_start_time = 5;
const int difference_latest_finish_time = 5;
const double initial_solution_time_left_margin=0.1;
const double score_satisfactory_coefficient = 0.5;

string instance_name;
string instance_path;
string solution_path;

unordered_map<int, int> map_virtual_rides_to_file_rides;

