#ifndef SUBMISSION_H
#define SUBMISSION_H

#include <vector>
#include <map>

#include "data_set_h.h"

using namespace std;

struct submission{
	map<int, vector<int>> fleets;

	vector<int> fleet1;
	vector<int> fleet2;
	vector<int> fleet3;
	vector<int> fleet4;
	vector<int> fleet5;

	submission();
	void show_assigned_roads(data_set ds);

};

#endif
