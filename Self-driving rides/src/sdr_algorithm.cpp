#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "../include/global_variables_h.h"
#include "../include/ride_h.h"
#include "../include/data_set_h.h"
#include "../include/submission_h.h"
#include "../include/get_solutions_h.h"
#include "../include/some_functions_h.h"

using namespace std;

int main() {
	//Test run
	data_set d1;
	// for (ride* d_ride : d1.rides) {
	// 	//ride from [0, 0] to [1, 3], earliest start 2, latest finish 9
	// 	cout << "Ride from [" << d_ride->a << ", " << d_ride->b << "] to [" << d_ride->x << ", " << d_ride->y
	// 		<< "], earliest start " << d_ride->s << ", latest finish " << d_ride->f << endl;

	// 	//Output all the close rides
	// 	int counter = 1;
	// 	for (ride* close_rides : d_ride->close_next_rides) {
	// 		cout << counter++ << " - Close intersection: [" << close_rides->x << ", " << close_rides->y << "]" << endl;
	// 	}
	// 	cout << endl;
	// }

	cout<<"\nExistent solution file:\n";
	unordered_map<int, vector<int>> fleets = read_solution_file();
	int score = get_score(d1, fleets);
	cout << "Score: " << score << endl;

	cout<<"\nget_initial_solution_variant_1\n";
	// Test get_initial_solution_variant1
	fleets = get_initial_solution_variant_1(d1);
	int score1 = get_score(d1, fleets);
	cout << "\nget_initial_solution_variant_1 Score: " << score1 << endl;

	submission variant1(fleets);
	variant1.output_solution();

	// cout << "Unassigned rides: \n";
	// for(auto it = unassigned_rides_variant_1.begin(); it != unassigned_rides_variant_1.end(); it++){
	// 	cout<< *it <<" \t";
	// }

	system("pause");
	return 0;
}
