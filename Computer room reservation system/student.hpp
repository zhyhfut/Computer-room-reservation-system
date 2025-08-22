#pragma once
#include "identity.hpp"
#include<iostream>
#include<vector>
#include"computerroom.hpp"
#include<fstream>
#include"globalFile.hpp"
#include "orderFile.hpp"
using namespace std;

class MAnager; //前向声明
class Student : public Identity
{
	friend class Manager; //Manager类可以访问Student类的私有成员
	friend void printStudent(Student& s);
public:

	//默认构造
	Student();
	//有参构造 学号、姓名、密码
	Student(int id, string name, string pwd);
	//菜单界面
	virtual void openMenu();//继承父类，在子类中实现

	//申请预约
	void applyOrder();
	//查看自身预约
	void showMyOrder();
	
	// 查看所有预约
	void showAllOrder();

	// 取消预约
	void cancelOrder();

	//机房信息
	vector<ComputerRoom> vCom;

private:
	//学生学号
	int m_id;
	
};