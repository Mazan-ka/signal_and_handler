#ifndef APPLICATION_H
#define APPLICATION_H

#include "cl_base.h"
#include <iostream>

//директивы предпроцессора
#define SIGNAL_D (void(cl_base::*)()) //макрос дл€ указател€ на метод сигнала
#define HEANDLER_D (void(cl_base::*)(string)) //макрос дл€ указател€ на метод обработчика

class cl_application : public cl_base
{
public:
	cl_application(cl_base* p_parent) : cl_base(p_parent, "") {}; //конструктор, наследуемый от cl_base
	void buildTree();
	int launch();
	void signal();
	void heandler(string str);
};

#endif