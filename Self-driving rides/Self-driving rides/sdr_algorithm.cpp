//Materials
// https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
// https://www.geeksforgeeks.org/vector-in-cpp-stl/
// https://www.geeksforgeeks.org/pair-in-cpp-stl/

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;

// Parameters
const int no_close_next_rides = 10;
string instance_name = "dataset/a_example.in";
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
	vector<ride*> rides;
	string instance;
	data_set() {
		instance = instance_name;
		read_instance_file(instance_name);

		// Read the data from the file with name from variable instance_name  
		// Place the data from the file in the respective variables and arrays  
		// Find the next close rides for each ride
		// Test the functionality of the code in the main function
	}

	vector<int> split_string_to_ints(string line) { 
		// Used to split string around spaces. 
	    stringstream ss_line(line); 
	    vector<int> values;
			// Read all words (numbers)
			do{
	        string word;
	        ss_line >> word;
	        //Check if still in the middle of the line
			if(word != ""){
				int value = stoi(word); //Convert string to int
		        values.push_back(value); 
		    }
		   //While there is more to read
	     } while(ss_line);
	     return values;  //return vector with string words(numbers) -> int values
	} 

	void process_first_line(string first_line){
		vector<int> values = split_string_to_ints(first_line);
		//initiate data_set 
		R = values[0];
		C = values[1];
		F = values[2];
		N = values[3];
		B = values[4];
		T = values[5];
	}

	void process_ride_lines(string ride_line){
		vector<int> values = split_string_to_ints(ride_line);
		int _a = values[0];
		int _b = values[1];
		int _x = values[2];
		int _y = values[3];
		int _s = values[4];
		int _f = values[5];
		//get a new "ride" initiated with values read on currennt line
		ride *new_ride = new ride(_a, _b, _x, _y, _s, _f);
		rides.push_back(new_ride);
	}

	void read_instance_file(string instance_name){
	ifstream wf(instance_name);
	if(wf.is_open()){
		//read first line of instance_name
		string first_line;
		getline (wf, first_line);
		process_first_line(first_line);
		//read the rest of instance_name lines
		string ride_line;
		while( getline (wf, ride_line)){
			//cout << ride_line << "\n";	//View the content of the file 'instance_name' while it's being read
			process_ride_lines(ride_line);
		}
	wf.close();
		}
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
	//Test run
	data_set d1;
	for(ride * x : d1.rides){
		//ride from [0, 0] to [1, 3], earliest start 2, latest finish 9
		cout << "Ride from [" << x->a << ", " << x->b << "] to [" << x->x << ", " << x->y
			<< "], earliest start " << x->s << ", latest finish " << x->f << endl;
	}

	
	return 0;
}
