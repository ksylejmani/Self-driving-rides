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
#include <math.h>
#include <stdexcept> // std::runtime_error
using namespace std;

//Parameters
const int no_iterations = 100;
const int no_close_next_rides = 3;
const int no_replace_next_rides = 3;
const int difference_earliest_start_time = 5;
const int difference_latest_finish_time = 5;
string instance_name = "a_example";
string instance_path = "dataset/" + instance_name + ".in";
string solution_path = "solution/" + instance_name + ".out";


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
	    // read as many numbers as possible.
	    for (int number; ss_line >> number;) {
	        values.push_back(number);
	    }
		return values;
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

		fleets.insert(pair<int, vector<int>>(0, fleet1));
		fleets.insert(pair<int, vector<int>>(1, fleet2));
		fleets.insert(pair<int, vector<int>>(2, fleet3));
		fleets.insert(pair<int, vector<int>>(3, fleet4));
		fleets.insert(pair<int, vector<int>>(4, fleet5));

		//Assign rides manually
		// Make a test with F=5 fleets and N=15 rides
		// Make a hard coded (or even better a random) solution by making sure that all constraints are satisfied
		// Save the solution of fleets to the file with the name of the variable solution_path
		// Test the functionality of the code in the main function
	}
	void show_assigned_roads(data_set ds) {
		ofstream csv_file(solution_path);
		map<int, vector<int>> fleets = get_initial_solution_variant_1(ds) ;
		for (map<int, vector<int>>::iterator itr = fleets.begin(); itr != fleets.end(); itr++)
		{
			for (int j = 0; j < itr->second.size(); j++)
			{
				if (j == 0)
					csv_file << itr->second.at(j);
				else
					csv_file << " " << itr->second.at(j);
			}
			csv_file << endl;
		}
	}
};

map<int, vector<int>> read_solution_file(string solution_name) {		// Used to test get_score function, DOESN'T WORK
	map<int, vector<int>> result;
	ifstream mySolution(solution_name);
	if (mySolution.is_open()) {
		string line;
		int i = 0;
		while (getline(mySolution, line)) {
			vector<int> row;
			stringstream ss_line(line);
			int number;
			while (ss_line >> number) {
				row.push_back(number);
			}
			result.insert(pair<int, vector<int>>(i, row));
			i++;
		}
	}
	else
		throw runtime_error("Could not open solution");

	return result;
}

int get_score(data_set ds, map<int, vector<int>> fleets) {// To be done by Erlis

	int result = 0; // Contains the score of all vehicles combined including bonuses
	/*
	We assume that each ride is assigned to a vehicle only once
	and that M (the first value of each vector of the map) is always
	the number of rides assigned to the respective vehicle
	*/
	int bonus = ds.B;

	for (auto it = fleets.begin(); it != fleets.end(); it++) // Iterate for each vehicle
	{
		int vehicle_score = 0; // Contains the score of the current vehicle
		pair<int, int> position(0, 0); // Starting position of each vehicle
		int step = 0; // The starting step for each vehicle

		for (int j = 1; j < it->second.size(); j++) // Iterate for each ride of the current vehicle
		{
			int ride_score = 0; // Contains the score of the current ride
			int nr_of_current_ride = it->second[j];
			ride* current_ride = ds.rides[nr_of_current_ride];

			int a = current_ride->a;
			int b = current_ride->b;
			int x = current_ride->x;
			int y = current_ride->y;
			int earliest_start = current_ride->s;
			int latest_finish = current_ride->f;

			int distance_from_position_to_start = abs(a - position.first) + abs(b - position.second); // Distance from current position to the start intersection of the ride
			int distance_from_start_to_finish = abs(x - a) + abs(y - b); // Distance from the start intersection to the finish intersection of the ride
			
			int distance_from_position_to_finish = distance_from_position_to_start + distance_from_start_to_finish; // The distance which the vehicle travels
			if(step + distance_from_position_to_start < earliest_start) // Including the waiting time until the earliest start
				distance_from_position_to_finish += earliest_start - (step + distance_from_position_to_start);
				
			step += distance_from_position_to_finish;
			if (step > latest_finish)
				goto fundi;
			else {
				ride_score += distance_from_start_to_finish;
				if((step - distance_from_start_to_finish) == earliest_start)
					ride_score += bonus;
			}
			
			position = make_pair(x, y); // At the end of the ride the vehicle is located at the finish intersection

		fundi:
			vehicle_score += ride_score;
		}
		result += vehicle_score;
	}
	// Test your function by using both solutions of Enes and Lendrit
	return result;
}

map<int, vector<int>> get_initial_solution_variant_1(data_set ds) {
		// Variant 1 - Fully random, to be done by Enes
		map<int, vector<int>> result;
		vector<int>* vehicles = new vector<int>[ds.F];
		srand(time(NULL));
		list<int> assigned_rides;
		//counters count the number of rides we assign to a car
		vector <int> Counters(ds.F, 0);
		//Implementation goes here ...
		for (int i = 0; i < ds.F; i++)
		{
			int time_left = ds.T;
			//list of the rides that are unaffordable for the car i
			list <int> unaffordable_rides;
			//while there is some time left, do ...
			while (time_left != 0)
			{
			label:
				int random_ride = rand() % ds.N;
				for (auto it = assigned_rides.begin(); it != assigned_rides.end(); it++)
					if (*it == random_ride)
						goto label;
				for (auto itr = unaffordable_rides.begin(); itr != unaffordable_rides.end(); itr++)
					if (*itr == random_ride)
						goto label;

				//earliest_time is the number of steps that has passed by the time vehicle starts riding at the starting intersection , we firstly say that it is equal to the earliest start
				int earliest_time = ds.rides.at(random_ride)->s;

				//if this is the first ride for vehicle i
				if (time_left == ds.T) {
					if (ds.rides.at(random_ride)->s < (ds.rides.at(random_ride)->a + ds.rides.at(random_ride)->b))
						earliest_time = ds.rides.at(random_ride)->a + ds.rides.at(random_ride)->b;
				}
				//if this isn't the first ride for vehicle i
				else
				{
					//distance_last_first is the distance from the last intersection of the previous ride to the begining of the start intersection of the current ride
					int distance_last_first = abs(ds.rides.at(random_ride)->a - ds.rides.at(assigned_rides.back())->x) + abs(ds.rides.at(random_ride)->b - ds.rides.at(assigned_rides.back())->y);
					if (ds.rides.at(random_ride)->s < ds.T - time_left + distance_last_first)
						earliest_time = ds.T - time_left + distance_last_first;
				}

				int distance_between_intersections = abs(ds.rides.at(random_ride)->a - ds.rides.at(random_ride)->x) + abs(ds.rides.at(random_ride)->b - ds.rides.at(random_ride)->y);
				//if the ride ended before or in the latest step , do ...
				if (earliest_time + distance_between_intersections <= ds.rides.at(random_ride)->f)
				{
					assigned_rides.push_back(random_ride);
					vehicles[i].push_back(random_ride);
					time_left = ds.T - (earliest_time + distance_between_intersections);
					Counters.at(i)++;
					//if all rides are assigned or if we have checked all rides for the car i there is nothing left to check so go to the next car (break) 
					if ( (assigned_rides.size() == ds.N) || (unaffordable_rides.size() + assigned_rides.size() == ds.N))
						break;				
				}
				//if the ride didn't end before or in the last step (it's unaffordable for car i) , do ...
				else
				{
					unaffordable_rides.push_back(random_ride);
					//if all rides are unaffordable (pretty sure that this condition never gets true , put it for the sake of safeness) , or we have checked all rides , break .
					if ((unaffordable_rides.size() == ds.N - assigned_rides.size()) || (unaffordable_rides.size() == ds.N))
						break;
				}
				//Test your solution in the main function

			}
			vehicles[i].insert(vehicles[i].begin(), Counters.at(i));
			result.insert(pair<int, vector<int>>(i, vehicles[i]));
			//if all rides are assigned for the cars up to i , do
			if (assigned_rides.size() == ds.N) {
				//if this isn't the last car left
				if (i != ds.F - 1)
				{
					//assign the rest of the cars 0 rides
					for (int j = i + 1; j < ds.F; j++) {
						vehicles[j].push_back(0);
						result.insert(pair<int, vector<int>>(j, vehicles[j]));
					}
				}
				break;
			}
		}
		return result;
	}
}

map<int, vector<int>> get_initial_solution_variant_2(data_set ds) {
	// Variant 2 - Smart random, to be done by Lendrit
	map<int, vector<int>> result;
	//Implementation goes here ...
	//Test your solution in the main function
	return result;
}

map<int, vector<int>> get_greedy_local_search_solution(data_set ds) {
	map<int, vector<int>> d;
	// d= get_initial_solution();// Variant 1 - Fully random, to be done by Enes
								 // Variant 2 - Smart random, to be done by Lendrit
	// d_quality= get_socore(ds,e);
	int i = 1;
	//while (i <= no_iterations) {
		// N= get_neighborhood();
		// e= choose_neighbour(N);
		// e_quality=get_socore(ds,e);
		// if(e_quality>d_quality)
				//d = e;
		//i++;
	//}
	return d;
}

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
	map<int, vector<int>> fleets = read_solution_file(solution_path); DOESN'T WORK
	int score = get_score(ds, fleets);
	cout << "Score: " << score << endl;
	*/
	map<int, vector<int>> fleets; // Putting solution values manually because the read_solution_file() function isn't working
	vector<int> vehicle_1 {1, 0}; // Solution values for a_example.out
	vector<int> vehicle_2 {2, 2, 1};
	fleets.insert(pair<int, vector<int>> (0, vehicle_1));
	fleets.insert(pair<int, vector<int>> (1, vehicle_2));
	int score = get_score(ds, fleets);
	cout << "Score: " << score << endl;
	
	return 0;
}
