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

	//默认构造
	Manager();

	//有参构造  管理员姓名，密码
	Manager(string name, string pwd);

	//选择菜单
	virtual void openMenu();

	//添加账号  
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//初始化容器（为了去重）
	void initVector();
	//去重
	bool checkRepeat(int id, int type);
	//机房信息
	vector<ComputerRoom> vCom;
private:
	//学生容器
	vector<Student> vStu;
	//教师容器
	vector<Teacher> vTea;

};