#include <utility>
#include <ctime>

#include "../include/data_set_h.h"
#include "../include/submission_h.h"
#include "../include/get_solutions_h.h"
#include "../include/some_functions_h.h"
#include "../include/hill_climbing_h.h"
#include "../include/ride_h.h"

using namespace std;

int main() {
	//Test run
	
	srand(time(NULL));
	data_set d1(instance_path);

	// cout<<"\nExistent solution file:\n";
	// unordered_map<int, vector<int>> fleets = read_solution_file();
	// int score = get_score(d1, fleets);
	// cout << "Score: " << score << endl;
 
	cout<<"\nget_initial_solution_variant_1\n";
	// Test get_initial_solution_variant1
	unordered_map<int, vector<int>> fleets;
	fleets = get_initial_solution_variant_1(d1);
	int score1 = get_score(d1, fleets);
	cout << "\nget_initial_solution_variant_1 Score: " << score1 << endl;

	submission init(fleets);
	init.output_solution();

	cout<<"unassigned size: "<<unassigned_rides_variant_1.size()<<endl;

	stochastic_hill_climbing(fleets, unassigned_rides_variant_1, d1);
	int score2 = get_score(d1, fleets);
	cout << "stochastic_hill_climbing Score2: " << score2 << endl;


	cout<<"unassigned size: "<<unassigned_rides_variant_1.size()<<endl;
	char y;
	cout<<"hill? ";
	cin>>y;
	if(y =='y'){
		submission hill_climbing(fleets);
		hill_climbing.output_solution();
	}

	return 0;
}
