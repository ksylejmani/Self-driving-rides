#include <vector>
#include <utility>
#include <map>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "submission_h.h"
#include "get_solutions_h.h"
using namespace std;

submission::submission() {
	//Assign rides manually
	// Make a test with F=5 fleets and N=15 rides
	// Make a hard coded (or even better a random) solution by making sure that all constraints are satisfied
	// Save the solution of fleets to the file with the name of the variable solution_path

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

}
void submission::show_assigned_roads(data_set ds) {
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
