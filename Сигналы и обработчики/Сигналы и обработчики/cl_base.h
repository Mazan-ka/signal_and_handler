#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class cl_base
{
	string name = "";
	cl_base* parent;
	int ob_ready;
	int type; //номер типа класса объекта
	struct o_sh //Структура, хранящая связи сигнал <-> обработчик
	{
		cl_base* p_ob_heandler; //указатель на объект, принимающий сигнал
		void (cl_base ::* heandler) (string); //указатель на метод объекта, обрабатывающего сигнал
		void (cl_base ::* signal) (); //указатель на метод объекта, выдающего сигнал
		//-----------------конструктор структуры--------------------------------------------------------------------------
		o_sh(cl_base* p_ob_heandler, void (cl_base ::* heandler) (string), void (cl_base ::* signal) ())
		{
			this->p_ob_heandler = p_ob_heandler;
			this->heandler = heandler;
			this->signal = signal;
		}
	};
	
protected:
	vector <cl_base*> children; //вектор, хранящий детей объекта
	vector <o_sh*> connects; //вектор, хранящий имеющиеся связи объекта

public:
	cl_base(cl_base* p_parent, string object_name); //конструктор
	~cl_base(); //деструктор 

	void set_object_name(string object_name); //установка имени объекта
	string get_object_name(); //получение имени объекта

	void showTree(); //вывод дерева иерархии на экран
	void show_current_Tree(int level); //вывод текущего дерева иерархии

	void add_child(cl_base* p_child); //добавление ребенка в вектор
	void changeParent(cl_base* new_parent); //метод смены родителя

	void setState(int state); //метод установки состояния готовности объекта
	int getState(); //метод получения состояния объекта

	cl_base* find_object(string object_name); //метод поиска объекта в дереве иерархии по его имени
	cl_base* find_object_2(string object_coor); //поиск указателя на объект по координате
	void search(); //метод проверки принадлежности объекта заданнному дереву иерархии

	void set_signal(void (cl_base ::* p_signal) (), void (cl_base ::* p_heandler) (string), cl_base* p_ob_heandler); //метод установки сигнала
	void delete_signal(void (cl_base ::* p_signal) (), cl_base* p_ob_heandler); //метод удаления сигнала
	void emit_signal(void (cl_base ::* p_signal) (), string& s_command); //метод формирования сигнала

	int get_type(); //метод получения типа класса объекта
	void set_type(int i);

	cl_base* get_root(); //метод получения указателя на корневой объект
};

#endif