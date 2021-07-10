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
	int type; //����� ���� ������ �������
	struct o_sh //���������, �������� ����� ������ <-> ����������
	{
		cl_base* p_ob_heandler; //��������� �� ������, ����������� ������
		void (cl_base ::* heandler) (string); //��������� �� ����� �������, ��������������� ������
		void (cl_base ::* signal) (); //��������� �� ����� �������, ��������� ������
		//-----------------����������� ���������--------------------------------------------------------------------------
		o_sh(cl_base* p_ob_heandler, void (cl_base ::* heandler) (string), void (cl_base ::* signal) ())
		{
			this->p_ob_heandler = p_ob_heandler;
			this->heandler = heandler;
			this->signal = signal;
		}
	};
	
protected:
	vector <cl_base*> children; //������, �������� ����� �������
	vector <o_sh*> connects; //������, �������� ��������� ����� �������

public:
	cl_base(cl_base* p_parent, string object_name); //�����������
	~cl_base(); //���������� 

	void set_object_name(string object_name); //��������� ����� �������
	string get_object_name(); //��������� ����� �������

	void showTree(); //����� ������ �������� �� �����
	void show_current_Tree(int level); //����� �������� ������ ��������

	void add_child(cl_base* p_child); //���������� ������� � ������
	void changeParent(cl_base* new_parent); //����� ����� ��������

	void setState(int state); //����� ��������� ��������� ���������� �������
	int getState(); //����� ��������� ��������� �������

	cl_base* find_object(string object_name); //����� ������ ������� � ������ �������� �� ��� �����
	cl_base* find_object_2(string object_coor); //����� ��������� �� ������ �� ����������
	void search(); //����� �������� �������������� ������� ���������� ������ ��������

	void set_signal(void (cl_base ::* p_signal) (), void (cl_base ::* p_heandler) (string), cl_base* p_ob_heandler); //����� ��������� �������
	void delete_signal(void (cl_base ::* p_signal) (), cl_base* p_ob_heandler); //����� �������� �������
	void emit_signal(void (cl_base ::* p_signal) (), string& s_command); //����� ������������ �������

	int get_type(); //����� ��������� ���� ������ �������
	void set_type(int i);

	cl_base* get_root(); //����� ��������� ��������� �� �������� ������
};

#endif