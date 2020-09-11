#include <iostream>

#include "../include/Timing_h.h"

using namespace std;

Timing::Timing(string func_name){
	t = clock();
	this->func_name = func_name;
}
Timing::~Timing(){
	t = clock() -t;
	cerr<<"\nFunction "<<func_name<<" took: "<< t <<"clicks ("<< ((float)t)/CLOCKS_PER_SEC<<"seconds) to complete.";
}
