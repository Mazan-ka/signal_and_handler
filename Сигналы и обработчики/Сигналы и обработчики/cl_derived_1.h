#ifndef DERIVED_1_H
#define DERIVED_1_H

#include "cl_base.h"
#include <string>

using namespace std;

class cl_derived_1 : public cl_base
{
public:
	cl_derived_1(cl_base* p_parent, string object_name) : cl_base(p_parent, object_name) {}; //конструктор, наследуемый от cl_base
	void signal();
	void heandler(string str);
};

#endif