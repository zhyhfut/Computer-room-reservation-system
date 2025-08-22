#pragma once
#include<iostream>
using namespace std;
#include "identity.hpp"
#include<string>
#include<fstream>
#include "globalFile.hpp"
#include<vector>
#include "student.hpp"
#include "teacher.hpp"
#include<algorithm>
#include "computerroom.hpp"
class Manager :public Identity
{
	
public:

	//Ĭ�Ϲ���
	Manager();

	//�вι���  ����Ա����������
	Manager(string name, string pwd);

	//ѡ��˵�
	virtual void openMenu();

	//����˺�  
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ��������Ϊ��ȥ�أ�
	void initVector();
	//ȥ��
	bool checkRepeat(int id, int type);
	//������Ϣ
	vector<ComputerRoom> vCom;
private:
	//ѧ������
	vector<Student> vStu;
	//��ʦ����
	vector<Teacher> vTea;

};