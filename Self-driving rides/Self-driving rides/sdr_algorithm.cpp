//Materials
// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
// https://www.geeksforgeeks.org/vector-in-cpp-stl/
// https://www.geeksforgeeks.org/pair-in-cpp-stl/

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
using namespace std;

// Parameters
const int no_close_next_rides = 10;
string instance_name = "a_example.in";
string solution_name = "a_example.out";

struct ride {
	int a, b, x, y, s, f;
	pair <int, int> close_next_rides[no_close_next_rides];
	ride() {

	}
	ride(int _a, int _b, int _x, int _y, int _s, int _f) {
		a = _a; b = _b; x = _x; y = _y; s = _s; f = _f;
	}
};

struct data_set {
	int R, C, F, N, B, T;
	ride* rides;
	data_set() {
		rides = new ride[N];

		// Read the date from the file with name from variable instance_name
		// Place the date from the file in the respective variables and arrays
		// Find the next close rides for each ride
		// Test the functionality of the code in the main function
	}

};

struct submission
{
	map<int,vector<int>> fleets;
	submission() {
		data_set ds;
		ds.R = 20;
		ds.C = 17;
		ds.F = 5;
		ds.N = 15;
		ds.B = 3;
		ds.T = 36;
		//Assign rides manually
		// Make a test with F=5 fleets and N=15 rides
		// Make a hard coded (or even better a random) solution by making sure that all constraints are satisfied
		// Save the solution of fleets to the file with the name of the variable solution_name
		// Test the functionality of the code in the main function
	}
};
int main() {
	return 0;
}