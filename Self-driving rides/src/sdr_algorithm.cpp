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

	cout<<"Self driving rides solution for instance: " << instance_name << endl;

	unordered_map<int, vector<int>> fleets;

	// cout<<"\nExistent solution file:\n";
	// fleets = read_solution_file();
	// int score = get_score(d1, fleets);
	// cout << "Score: " << score << endl;

	fleets = get_initial_solution_variant_1(d1);
	int score1 = get_score(d1, fleets);
	cout << "\nget_initial_solution_variant_1 Score: " << score1 << endl;

	stochastic_hill_climbing(fleets, unassigned_rides_variant_1, d1);
	int score2 = get_score(d1, fleets);
	cout << "stochastic_hill_climbing Score2: " << score2 << endl;

	submission hill_climbing(fleets, solution_path);
	hill_climbing.output_solution();
	
	system("pause");
	return 0;
}
