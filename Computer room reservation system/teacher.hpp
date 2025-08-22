#pragma once
#include "identity.hpp"
#include <iostream>
#include<string>
#include"orderFile.hpp"
#include<vector>
using namespace std;
class Manager; //ǰ������
class Teacher : public Identity
{
	friend class Manager; //Manager����Է���Teacher���˽�г�Ա
	friend void printTeacher(Teacher& t);
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι��� ��ʦ���š�����������
	Teacher(int id, string name, string pwd);

	//�˵�����
	virtual void openMenu(); //�̳и��࣬��������ʵ��

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void checkOrder();

	//ְ����
private:
	int m_id; // ��ʦ����
};