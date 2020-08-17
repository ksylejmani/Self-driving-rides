//Materials
// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
// https://www.geeksforgeeks.org/vector-in-cpp-stl/
// https://www.geeksforgeeks.org/pair-in-cpp-stl/
#include <algorithm> 
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <sstream>
#include <fstream>
#include <queue>
#include <chrono>
#include <ctime>
#include <iomanip>
using namespace std;

//Parameters
const int no_close_next_rides = 3;
const int no_replace_next_rides = 3;
const int difference_earliest_start_time = 5;
const int difference_latest_finish_time = 5;
string instance_name = "b_should_be_easy";
string instance_path = "dataset/" + instance_name + ".in";
string solution_name = instance_name + ".out";

struct ride {
	int a, b, x, y, s, f;


	//pair <int, int> close_next_rides[no_close_next_rides];
	vector<ride*> close_next_rides;
	vector<ride*> close_replace_rides;

	ride() {	}
	ride(int _a, int _b, int _x, int _y, int _s, int _f) {
		a = _a; b = _b; x = _x; y = _y; s = _s; f = _f;
	}
};

struct data_set {
	int R, C, F, N, B, T;
	vector<ride*> rides;
	string instance;
	data_set() {
		// Read the data from the file with name from variable instance_name  
		instance = instance_path;

		// Place the data from the file in the respective variables and arrays  
		read_instance_file(instance);

		// Find the next close rides for each ride
		for (ride* d_ride : rides)
			find_k_closest_rides(d_ride, no_close_next_rides);
		// Test the functionality of the code in the main function
	}

	vector<int> split_string_to_ints(string line) {
		// Used to split string around spaces. 
		stringstream ss_line(line);
		vector<int> values;
		// Read all words (numbers)
		string word;
		do {
			ss_line >> word;
			//Check if still in the middle of the line
			if (word != "") {
				int value = stoi(word); //Convert string to int
				values.push_back(value);
			}
			//While there is more to read
		} while (ss_line);
		return values;  //return vector with string words(numbers) -> int values
	}

	void process_first_line(string first_line) {
		vector<int> values = split_string_to_ints(first_line);
		//initiate data_set  
		R = values[0];
		C = values[1];
		F = values[2];
		N = values[3];
		B = values[4];
		T = values[5];
	}

	void process_ride_lines(string ride_line) {
		vector<int> values = split_string_to_ints(ride_line);
		//get a new "ride" initiated with values read on currennt line and initiate variables appropriately
		ride* new_ride = new ride(values[0], values[1], values[2], values[3], values[4], values[5]);
		rides.push_back(new_ride);
	}

	void read_instance_file(string instance_name) {
		ifstream wf(instance_name);
		if (wf.is_open()) {
			//read first line of instance_name
			string first_line;
			getline(wf, first_line);
			process_first_line(first_line);
			//read the rest of instance_name lines
			string ride_line;
			while (getline(wf, ride_line)) {
				//cout << ride_line << "\n";	//View the content of the file 'instance_name' while it's being read
				process_ride_lines(ride_line);
			}
			wf.close();
		}
	}

	//Could be private
	ride* find_close_ride(ride* given_ride) {
		ride* closest_ride = new ride();

		//Longest distance possible is number of rows + number of columns (so we can have a starting value)
		int closest_distance = R + C;
		for (ride* check_ride : rides) {
			//Skip if the ride is identical with the given ride
			if (check_ride == given_ride)
				continue;

			//Find the closest ride based on the distance between points
			int check_distance = abs(given_ride->a - check_ride->x) + abs(given_ride->b - check_ride->y);

			if (closest_distance >= check_distance) {
				if (find(given_ride->close_next_rides.begin(), given_ride->close_next_rides.end(), check_ride) == given_ride->close_next_rides.end()) {
					closest_ride = check_ride;
					closest_distance = check_distance;
				}
			}
		}

		return closest_ride;
	}


	void find_k_closest_rides(ride* given_ride, int K) {
		//min(K, N - 1) in case K is bigger than the number of rides
		for (int i = 0; i < min(K, N - 1); i++)
			given_ride->close_next_rides.push_back(find_close_ride(given_ride));

	}
};

struct submission
{
	map<int, vector<int>> fleets;

	vector<int> fleet1;
	vector<int> fleet2;
	vector<int> fleet3;
	vector<int> fleet4;
	vector<int> fleet5;

	submission() {
		srand(time(NULL));                                         //seeding random numbers

		data_set ds;
		ds.R = 20;
		ds.C = 17;
		ds.F = 5;
		ds.N = 15;
		ds.B = 3;
		ds.T = 36;

		int random_numbers[4];
		int sum = 0;

		for (int i = 0; i < 4; i++)
		{
		label:
			random_numbers[i] = rand() % 4;                       //   4 vehicles e para ka sa rruge(i caktuam random) kan mi pershkru , prej tynev ma s'shumti njo munet mi pershkru 3 rruge
			if (random_numbers[i] == 0)
				goto label;
			sum = sum + random_numbers[i];
		}

		int assigned_rides[15];                                  // Vargu qe ruan se cilat rruge jane te pershkruare (ne menyre qe mos ti pershkruajme per te n ten here)

		for (int i = 0; i < 15; i++)
			assigned_rides[i] = -1;								//Fillimisht e inicializojme me -1 - sha

		fleet1.push_back(random_numbers[0]);

		for (int i = 0; i < random_numbers[0]; i++)
		{
		label_1:
			int x = rand() % 15;

			assigned_rides[i] = x;
			//vehicle 1 - shit ja caktum random rides
			if (i == 0)
				goto fleet;
			else
			{
				for (int j = 0; j < i; j++)
				{
					if (assigned_rides[j] == x)
					{
						goto label_1;
					}
				}
			}
		fleet:
			fleet1.push_back(x);
		}

		fleet2.push_back(random_numbers[1]);

		for (int i = random_numbers[0]; i < random_numbers[0] + random_numbers[1]; i++)
		{
		label_2:
			int x = rand() % 15;
			for (int j = 0; j < i; j++)
			{
				if (x == assigned_rides[j])
					goto label_2;
			}
			assigned_rides[i] = x;
			//vehicle 2 - shit ja caktum random rides
			fleet2.push_back(x);
		}

		fleet3.push_back(random_numbers[2]);

		for (int i = random_numbers[0] + random_numbers[1]; i < random_numbers[0] + random_numbers[1] + random_numbers[2]; i++)
		{
		label_3:
			int x = rand() % 15;
			for (int j = 0; j < i; j++)
			{
				if (x == assigned_rides[j])									//vehicle 3 - shit ja caktum random rides
					goto label_3;
			}
			assigned_rides[i] = x;
			fleet3.push_back(x);
		}

		fleet4.push_back(random_numbers[3]);

		for (int i = random_numbers[0] + random_numbers[1] + random_numbers[2]; i < sum; i++) {
		label_4:
			int x = rand() % 15;

			for (int j = 0; j < i; j++)
			{
				if (x == assigned_rides[j])									//vehicle 4 - shit ja caktum random rides
					goto label_4;
			}
			assigned_rides[i] = x;
			fleet4.push_back(x);
		}

		fleet5.push_back(15 - sum);

		for (int i = sum; i < 15; i++)
		{
		label_5:
			int x = rand() % 15;
			for (int j = 0; j < i; j++)
			{
				if (x == assigned_rides[j])									//vehicle 5 - shit ja caktum random rides
					goto label_5;
			}

			assigned_rides[i] = x;

			fleet5.push_back(x);
		}

		fleets.insert(pair<int, vector<int>>(1, fleet1));
		fleets.insert(pair<int, vector<int>>(2, fleet2));
		fleets.insert(pair<int, vector<int>>(3, fleet3));
		fleets.insert(pair<int, vector<int>>(4, fleet4));
		fleets.insert(pair<int, vector<int>>(5, fleet5));

		//Assign rides manually
		// Make a test with F=5 fleets and N=15 rides
		// Make a hard coded (or even better a random) solution by making sure that all constraints are satisfied
		// Save the solution of fleets to the file with the name of the variable solution_name
		// Test the functionality of the code in the main function
	}
	void show_assigned_roads() {
		ofstream csv_file(solution_name);
		for (map<int, vector<int>>::iterator itr = fleets.begin(); itr != fleets.end(); itr++)
		{
			for (int j = 0; j < itr->second.size(); j++)
			{
				if (j == 0)
					csv_file << itr->second.at(j);
				else
					csv_file << "  " << setw(2) << itr->second.at(j);
				/*csv_file<< "\t" << itr->second.at(j);*/
			}
			csv_file << endl;
		}
	}
};

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
	s.show_assigned_roads();
	return 0;
}
