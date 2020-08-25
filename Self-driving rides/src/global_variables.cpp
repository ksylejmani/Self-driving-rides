#include "../include/global_variables_h.h"

const int no_iterations = 100;
const int no_close_next_rides = 3;
const int no_replace_next_rides =3;
const int difference_earliest_start_time = 5;
const int difference_latest_finish_time = 5;

string instance_name = "b_should_be_easy";
string instance_path = "dataset/" + instance_name + ".in";
string solution_path = "solution/" + instance_name + ".out";
