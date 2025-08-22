#pragma once//��ֹͷ�ļ��ظ�����
#include<ostream>
#include<string>
using namespace std;

class Manager; //ǰ������������Manager�����Identity��˽�г�Ա
class Student;
class Teacher;
class Identity 
{
	friend class Manager; //����Manager�����Identity��˽�г�Ա
	friend class Student; //����Student�����Identity��˽�г�Ա
	friend class Teacher; //����Teacher�����Identity��˽�г�Ա
	friend void printStudent(Student& s);
	friend void printTeacher(Teacher& t);
public:

	virtual void openMenu() = 0; //���麯��������ݶ�Ӧ�Ĳ˵�

private:
	string m_name;
	string m_pwd;//����
};

