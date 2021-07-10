#include "cl_derived_2.h"
#include <iostream>
#include <string>

using namespace std;

void cl_derived_2::signal() {}

void cl_derived_2::heandler(string str) {
	str = " Text: " + this->get_object_name() + "->" + str;
	cout << endl << "Signal to " + this->get_object_name() + str;
}