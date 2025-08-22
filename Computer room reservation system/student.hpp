#pragma once
#include "identity.hpp"
#include<iostream>
#include<vector>
#include"computerroom.hpp"
#include<fstream>
#include"globalFile.hpp"
#include "orderFile.hpp"
using namespace std;

class MAnager; //ǰ������
class Student : public Identity
{
	friend class Manager; //Manager����Է���Student���˽�г�Ա
	friend void printStudent(Student& s);
public:

	//Ĭ�Ϲ���
	Student();
	//�вι��� ѧ�š�����������
	Student(int id, string name, string pwd);
	//�˵�����
	virtual void openMenu();//�̳и��࣬��������ʵ��

	//����ԤԼ
	void applyOrder();
	//�鿴����ԤԼ
	void showMyOrder();
	
	// �鿴����ԤԼ
	void showAllOrder();

	// ȡ��ԤԼ
	void cancelOrder();

	//������Ϣ
	vector<ComputerRoom> vCom;

private:
	//ѧ��ѧ��
	int m_id;
	
};