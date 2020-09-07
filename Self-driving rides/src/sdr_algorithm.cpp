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
	for (ride* d_ride : d1.rides) {
		//ride from [0, 0] to [1, 3], earliest start 2, latest finish 9
		cout << "Ride from [" << d_ride->a << ", " << d_ride->b << "] to [" << d_ride->x << ", " << d_ride->y
			<< "], earliest start " << d_ride->s << ", latest finish " << d_ride->f << endl;

		//Output all the close rides
		int counter = 1;
		for (ride* close_rides : d_ride->close_next_rides) {
			cout << counter++ << " - Close intersection: [" << close_rides->x << ", " << close_rides->y << "]" << endl;
		}
		cout << endl;
	}
	//Test of submission structure
	submission s;
	s.show_assigned_roads(d1);

	// Test get_score function
	data_set ds;
	/*
	unordered_map<int, vector<int>> fleets = read_solution_file(solution_path); DOESN'T WORK
	int score = get_score(ds, fleets);
	cout << "Score: " << score << endl;
	*/
	unordered_map<int, vector<int>> fleets; // Putting solution values manually because the read_solution_file() function isn't working
	vector<int> vehicle_1 {1, 0}; // Solution values for a_example.out
	vector<int> vehicle_2 {2, 2, 1};
	fleets.insert(pair<int, vector<int>> (0, vehicle_1));
	fleets.insert(pair<int, vector<int>> (1, vehicle_2));
	int score = get_score(ds, fleets);
	cout << "Score: " << score << endl;

	cout<<"\nget_initial_solution_variant_1\n";
	// Test get_initial_solution_variant1
	fleets = get_initial_solution_variant_1(ds);
	int score1 = get_score(ds, fleets);
	cout << "Score1: " << score1 << endl;
	system("Pause");
	return 0;
}
