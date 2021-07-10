#include "cl_base.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

//#define SIGNAL_D (void (cl_base :: *)()) //макрос дл€ указател€ на метод

using namespace std;

cl_base::cl_base(cl_base* p_parent /*= 0*/, string object_name /*= "Object_root"*/)
{
	set_object_name(object_name);
	parent = p_parent;
	if (p_parent)
	{
		parent->children.push_back(this); //записываем нового ребенка в конец вектора
	}
}

void cl_base::set_object_name(string object_name)
{
	name = object_name;
}

string cl_base::get_object_name()
{
	return name;
}

void cl_base::showTree()
{
	vector <cl_base*> :: iterator it_child; //объ€вление итератора дл€ вектора children
	it_child = children.begin(); //иницилизаци€ итератора
	while (it_child != children.end())
	{
		switch ((*it_child)->getState()) //проверка готовности объекта
		{
		case 1:
			cout << "\nThe object " << (*it_child)->get_object_name() << " is ready";
			break;
		case 0:
			cout << "\nThe object " << (*it_child)->get_object_name() << " is not ready";
			break;
		default:
			cout << "\nThe object " << (*it_child)->get_object_name() << " is not ready";
			break;
		}
		if (!((*it_child)->children.empty()))(*it_child)->showTree(); //рекурсивный вызов showTree 
		it_child++;
	}
}

void cl_base::changeParent(cl_base* new_parent)
{
	if (this->children.empty()) return;
	vector <cl_base*> ::iterator it_child;
	it_child = parent->children.begin();
	while (it_child != parent->children.end())
	{
		if (this == (*it_child))
		{
			parent->children.erase(it_child); //удар€ем ребенка из вектора прошлого родител€
			break;
		}
		it_child++;
	}
	parent = new_parent;
	new_parent->children.push_back(this); //добавл€ем ребенка в вектор нового родител€
}

cl_base* cl_base::find_object(string object_name)
{
	if (object_name == get_root()->get_object_name()) return get_root(); //если им€ объекта равно имени головного объекта, то возвращаем указатель на него
	cl_base* pointer = 0;
	vector <cl_base*> ::iterator it_child;
	it_child = this->children.begin();
	while (it_child != this->children.end())
	{
		if ((*it_child)->get_object_name() == object_name)
		{
			pointer = (*it_child);
		}
		if (pointer != 0) return pointer;
		it_child++;
	}
	for (int i = this->children.size() - 1; i >= 0; i--)
	{
		it_child--; //с конца вектора начинаем углубл€тьс€ в него
		if (!((*it_child)->children.empty())) pointer = ((*it_child)->find_object(object_name)); //вызываем рекурсивно наш метод дл€ последнего ребенка в векторе
		if (pointer != 0) break;
	}
	return 	pointer;
}

void cl_base::setState(int state)
{
	ob_ready = state;
}

int cl_base::getState()
{
	return ob_ready;
}

void cl_base::show_current_Tree(int level)
{
	vector <cl_base*> ::iterator it_child;
	it_child = children.begin();
	while (it_child != children.end())
	{
		cout << endl << setw(4 * level) << ""; //делаем форматированный вывод в поле из 4*level символов
		cout << (*it_child)->get_object_name();
		level++;
		if (!((*it_child)->children.empty()))(*it_child)->show_current_Tree(level); //рекурсивно вызываем наш метод если вектор не пустой
		it_child++;
		level--;
	}
}

cl_base* cl_base::find_object_2(string object_coor) //получаем координату на объекту типа /root/ob_1/ob_2
{
	int count = 0, place = 0;
	cl_base* pointer = 0;
	string result = "";
	vector <cl_base*> ::iterator it_child;
	it_child = this->children.begin();
	for (int i = 0; i < object_coor.size() - 1; i++) //ищем символы '/' в строке и считаем их количество
	{
		if (object_coor[i] != '/') continue;
		else count++;
		place = i;
		if (count == 2) break;
	}
	if (count == 1) result = object_coor.erase(0, 1); //если нашли один слеш, то он в начале строки и мы обрезаем его
	else
	{ //если нашли два слеша, то вырезаем то, что находитс€ между ними, а оставшеюс€ строку без первого слеша записываем в другую переменную
		for (int j = 1; j < place; j++)
		{
			result += object_coor[j];
		}
		object_coor.erase(0, place);
	}
	while (it_child != this->children.end()) //ищем совпадени€ строки
	{
		if ((*it_child)->get_object_name() == result)
		{
			pointer = (*it_child);
		}
		it_child++;
	}
	if (pointer == 0) return nullptr;
	if (count != 1) pointer = pointer->find_object_2(object_coor); //рекурсивный вызов метода дл€ оставшейс€ строки
	return pointer;
}

void cl_base :: search()
{
	string coor, str;
	cin >> coor;
	str = this->get_object_name();
	while (coor != "//") {
		if (coor == "/" + str) { //отдельный вывод, если введена координта корневого объекта
			cout << endl << "/" + str << " Object name: " << str;
			cin >> coor;
			continue;
		}
		if ((coor[0] == '/') && (coor[1] == '/')) { //вывод дл€ координаты уникального объекта
			coor.erase(0, 2);
			//if (coor == "root") {cout << endl << "//" << coor << " Object name: " << this->get_object_name(); cin >> coor; continue;} ;
			if (find_object(coor) != 0) {
				cout << endl << "//" << coor << " Object name: " << find_object(coor)->get_object_name();
			}
			else {
				cout << endl << "//" << coor << " Object not found";
			}
		}
		else { //вывод дл€ координаты не уникального объекта
			if (coor.find(str) > 0) coor.erase(0, str.size() + 1);
			if (find_object_2(coor) != 0) {
				cout << endl << "/" + str + coor << " Object name: " << find_object_2(coor)->get_object_name();
			}
			else {
				cout << endl << "/" + str + coor << " Object not found";
			}
		}
		cin >> coor;
	}
}

void cl_base::set_type(int i)
{
	type = i;
}

int cl_base::get_type()
{
	return type;
}

/*void cl_base::delete_signal(void (cl_base ::* p_signal) (), cl_base* p_ob_heandler)
{
	vector <o_sh*> ::iterator it_connects;
	it_connects = connects.begin();
	while (it_connects < connects.end())
	{
		if (((*it_connects)->signal == p_signal) && ((*it_connects)->p_ob_heandler == p_ob_heandler)) //если равны методы сигнала и объекты обработчики, то удал€ем св€зь
		{
			connects.erase(it_connects);
			return;
		}
		it_connects++;
	}
}*/

cl_base :: ~cl_base() 
{
	for (int i = 0; i < children.size(); i++) delete this->children[i];
	for (int i = 0; i < connects.size(); i++) delete this->connects[i];
}

void cl_base::emit_signal(void (cl_base ::* p_signal) (), string& s_command)
{
	(this->*(p_signal))();
	int i = 0;
	while (i < this->connects.size())
	{
		if (this->connects[i]->signal == p_signal)
			((this->connects[i]->p_ob_heandler)->*(this->connects[i]->heandler))(s_command); //дл€ объекта обработчика вызываетс€ через разыменование метод обработчика, и передаетс€ туда ссылка на строку
		i++;
	}
}

void cl_base::set_signal(void (cl_base ::* p_signal) (), void (cl_base ::* p_heandler) (string), cl_base* p_ob_heandler)
{
	o_sh* pointer = nullptr;
	if (this->connects.size() > 0)
	{
		int i = 0;
		while (i < this->connects.size())
		{
			if (connects[i]->p_ob_heandler == p_ob_heandler && connects[i]->signal == p_signal && connects[i]->heandler == p_heandler) return; //если така€ св€зть существует то return
			i++;
		}
	}
	pointer = new o_sh(p_ob_heandler, p_heandler, p_signal); //динамические создаем структуру, котора€ будет хранить все данные о свз€и
	this->connects.push_back(pointer); //записываем в конец вектора св€зи новый объект
}

cl_base* cl_base::get_root()
{
	cl_base* p = this;
	while (p->parent != nullptr)
		p = p->parent;
	return p;
}
