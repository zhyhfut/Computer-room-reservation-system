#pragma once
#include "identity.hpp"
#include <iostream>
#include<string>
#include"orderFile.hpp"
#include<vector>
using namespace std;
class Manager; //前向声明
class Teacher : public Identity
{
	friend class Manager; //Manager类可以访问Teacher类的私有成员
	friend void printTeacher(Teacher& t);
public:
	//默认构造
	Teacher();

	//有参构造 教师工号、姓名、密码
	Teacher(int id, string name, string pwd);

	//菜单界面
	virtual void openMenu(); //继承父类，在子类中实现

	//查看所有预约
	void showAllOrder();

	//审核预约
	void checkOrder();

	//职工号
private:
	int m_id; // 教师工号
};