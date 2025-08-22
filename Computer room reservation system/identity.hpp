#pragma once//防止头文件重复包含
#include<ostream>
#include<string>
using namespace std;

class Manager; //前向声明，允许Manager类访问Identity的私有成员
class Student;
class Teacher;
class Identity 
{
	friend class Manager; //允许Manager类访问Identity的私有成员
	friend class Student; //允许Student类访问Identity的私有成员
	friend class Teacher; //允许Teacher类访问Identity的私有成员
	friend void printStudent(Student& s);
	friend void printTeacher(Teacher& t);
public:

	virtual void openMenu() = 0; //纯虚函数，打开身份对应的菜单

private:
	string m_name;
	string m_pwd;//密码
};

