#include <utility>

#include "../include/data_set_h.h"
#include "../include/submission_h.h"
#include "../include/get_solutions_h.h"
#include "../include/some_functions_h.h"
#include "../include/hill_climbing_h.h"
#include "../include/ride_h.h"
#include "../include/Timing_h.h"

using namespace std;

int main() {
	//Test run
	
	srand(time(NULL));
	data_set d1(instance_path);

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
	unordered_map<int, vector<int>> fleets;
	int score = get_score(d1, fleets);
	cout << "Score: " << score << endl;

	cout<<"\nget_initial_solution_variant_1\n";
	// Test get_initial_solution_variant1
	fleets = get_initial_solution_variant_1(d1);
	int score1 = get_score(d1, fleets);
	cout << "\nget_initial_solution_variant_1 Score: " << score1 << endl;
	cerr << "\nget_initial_solution_variant_1 Score: " << score1 << endl;

	std::cout << "\nunassigened.size(): "<<unassigned_rides_variant_1.size()<<endl;

	stochastic_hill_climbing(fleets, unassigned_rides_variant_1, d1);
	int score2 = get_score(d1, fleets);
	cout << "stochastic_hill_climbing Score2: " << score2 << endl;
	cerr << "stochastic_hill_climbing Score2: " << score2 << endl;

	int c = 0;
	for(ride* r1 : d1.rides){
		if(!r1->assigned)
			c++;
	}
	cout <<"\nunassigned: "<< c <<" vs "<<unassigned_rides_variant_1.size();

	submission hill_climbing(fleets);
	hill_climbing.output_solution();

	return 0;
}