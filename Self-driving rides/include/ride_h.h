#ifndef RIDE_H
#define RIDE_H

#include <vector>

#include "global_variables_h.h"

using namespace std;

struct ride {
	int	a, b, x, y, s, f;

	vector<ride*> close_next_rides;
	vector<ride*> close_replace_rides;

	bool assigned;
	
	ride() {	}
	
	ride (int _a, int _b, int _x, int _y, int _s, int _f)
		: a(_a), b(_b), x(_x), y(_y), s(_s), f(_f), assigned(false)	{}
};

#endif
