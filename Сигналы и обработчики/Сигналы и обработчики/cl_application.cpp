#include "cl_application.h"
#include "cl_base.h"
#include "cl_derived_1.h"
#include "cl_derived_2.h"
#include <iostream>
#include <string>

using namespace std;

void cl_application::buildTree()
{
	cl_base* app_parent(0), * app_child(0);
	int cl_num, is_ready;
	string parent_name, child_name;
	cin >> parent_name;
	set_object_name(parent_name);
	setState(1);
	set_type(1);
	app_parent = this;
	cin >> parent_name;
	while (parent_name != "endtree")
	{
		cin >> child_name >> cl_num >> is_ready;
		app_parent = this->find_object(parent_name); //получаем указатель на введенный родительский объект
		if (app_parent == nullptr) app_parent = this; //если app_parent нулевой, то присваем ему указатель на голвной объект
		switch (cl_num) //создаем объекты соответсвующих классов
		{
		case 1:
			app_child = new cl_application(app_parent);
			app_child->set_object_name(child_name);
			app_child->setState(is_ready);
			app_child->set_type(cl_num);
			break;
		case 2:
			app_child = new cl_derived_1(app_parent, child_name);
			app_child->setState(is_ready);
			app_child->set_type(cl_num);
			break;
		case 3:
			app_child = new cl_derived_2(app_parent, child_name);
			app_child->setState(is_ready);
			app_child->set_type(cl_num);
			break;
		/*case 4:
			app_child = new cl_derived_3 (app_parent, child_name);
			app_child->setState (is_ready);
			break;
		case 5:
			app_child = new cl_derived_4 (app_parent, child_name);
			app_child->setState (is_ready);
			break;
		case 6:
			app_child = new cl_derived_5 (app_parent, child_name);
			app_child->setState (is_ready);
			break;*/
		default:
			break;
		}
		cin >> parent_name;
	}
	cout << "Object tree";
	cout << "\n" << this->get_object_name();
	show_current_Tree(1); //вывод дерева иерархии объектов
	int num;
	string name_s, name_h;
	cl_base* ob_signal(0), * ob_heandler(0);
	cin >> num;
	cout << "\nSet connects";
	while (num != 0)
	{
		cin >> name_s >> name_h;
		ob_signal = this->find_object(name_s);
		ob_heandler = this->find_object(name_h);
		void (cl_base:: * signal)() = nullptr; //объ€вление и иницилизаци€ указател€ на метод сигнала
		void (cl_base:: * heandler)(string) = nullptr; //объ€вление и иницилизаци€ указател€ на метод обработчика
		switch (ob_signal->get_type())
		{ //создание нужного нам указател€ на метод сигнала
		case 1:
			signal = SIGNAL_D(&cl_application::signal);
			break;
		case 2:
			signal = SIGNAL_D(&cl_derived_1::signal);
			break;
		case 3:
			signal = SIGNAL_D(&cl_derived_2::signal);
			break;
		default:
			break;
		}
		switch (ob_heandler->get_type())
		{ //создание нужного нам указател€ на метод обработчика
		case 1:
			heandler = HEANDLER_D(&cl_application::heandler);
			break;
		case 2:
			heandler = HEANDLER_D(&cl_derived_1::heandler);
			break;
		case 3:
			heandler = HEANDLER_D(&cl_derived_2::heandler);
			break;
		default:
			break;
		}
		ob_signal->set_signal(signal, heandler, ob_heandler); //вызов метода установки сигнала дл€ сигнального объекта
		cout << endl << num << " " << name_s << " " << name_h;
		cin >> num;
	}

}

int cl_application::launch()
{
	string name_s, str;
	cin >> name_s;
	cl_base* p_signal = find_object(name_s);
	cout << "\nEmit signals";
	while (name_s != "endsignals")
	{
		cin >> str;
		switch (p_signal->get_type())
		{ //вызов метода emit_signal дл€ сигнального объекта
		case 1:
			p_signal->emit_signal(SIGNAL_D(&cl_application::signal), str);
			break;
		case 2:
			p_signal->emit_signal(SIGNAL_D(&cl_derived_1::signal), str);
			break;
		case 3:
			p_signal->emit_signal(SIGNAL_D(&cl_derived_2::signal), str);
			break;
		default:
			break;
		}
		cin >> name_s;
		p_signal = find_object(name_s);
	}
	return 0;
}

void cl_application :: signal() {} 

void cl_application :: heandler(string str) {
	str = " Text: " + this->get_object_name() + "->" + str;
	cout << endl << "Signal to " + this->get_object_name() + str;
}