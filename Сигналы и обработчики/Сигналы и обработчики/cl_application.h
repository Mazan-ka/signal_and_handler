#ifndef APPLICATION_H
#define APPLICATION_H

#include "cl_base.h"
#include <iostream>

//��������� ��������������
#define SIGNAL_D (void(cl_base::*)()) //������ ��� ��������� �� ����� �������
#define HEANDLER_D (void(cl_base::*)(string)) //������ ��� ��������� �� ����� �����������

class cl_application : public cl_base
{
public:
	cl_application(cl_base* p_parent) : cl_base(p_parent, "") {}; //�����������, ����������� �� cl_base
	void buildTree();
	int launch();
	void signal();
	void heandler(string str);
};

#endif