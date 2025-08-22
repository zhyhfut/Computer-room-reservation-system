#include<iostream>
using namespace std;
#include "identity.hpp"
#include <fstream>
#include<string>
#include"globalFile.hpp"
#include "student.hpp"
#include "teacher.hpp"
#include "manager.hpp"
#include "computerroom.hpp"

//*************使用函数模板实现通用的用户登录功能*************
////使用函数模板来创建一个通用的用户验证函数
//template <typename T>
//void userLogin(const string& fileName, const string& prompt)
//{
//	cout << prompt;
//	int id;
//	cin >> id;
//
//	cout << "请输入姓名: ";
//	string name;
//	cin >> name;
//
//	cout << "请输入密码: ";
//	string pwd;
//	cin >> pwd;
//
//	ifstream ifs;
//	ifs.open(fileName, ios::in);
//	//判断文件是否存在
//	if (!ifs.is_open())
//	{
//		cout << "文件不存在！" << endl;
//		ifs.close();
//		return;
//	}
//	//准备接收用户信息
//	int fId = 0;
//	string fName;
//	string fPwd;
//	bool loginSuccess = false;
//	while (ifs >> fId >> fName >> fPwd)
//	{
//		if (fId == id && fName == name && fPwd == pwd)
//		{
//			cout << "登录成功！" << endl;
//			system("pause");
//			system("cls");//清屏
//
//			Identity* person = new T(id, name, pwd); //创建对应身份的对象
//
//			//进入对应身份的子菜单
//			if(typeid(T) == typeid(Student))
//			{
//				studentMenu(person);
//			}
//			else if (typeid(T) == typeid(Teacher))
//			{
//				teacherMenu(person);
//			}
//			delete person; //释放内存
//			loginSuccess = true;
//			break;
//		}
//	}
//	if (!loginSuccess)
//	{
//		cout << "登录失败！" << endl;
//		system("pause");//按任意键
//		system("cls");//清屏
//	}
//	ifs.close(); //关闭文件
//}
//
//void managerLogin(const string& fileName)
//{
//	cout << "请输入姓名: ";
//	string name;
//	cin >> name;
//
//	cout << "请输入密码: ";
//	string pwd;
//	cin >> pwd;
//
//	ifstream ifs;
//	ifs.open(fileName, ios::in);
//	// ... 后续逻辑不变 ...
//	string fName, fPwd;
//	while (ifs >> fName && ifs >> fPwd)
//	{
//		if (fName == name && fPwd == pwd)
//		{
//			cout << "管理员验证登录成功！" << endl;
//			Identity* person = new Manager(name, pwd);
//			system("pause");
//			system("cls");
//			managerMenu(*person); // 管理员菜单的参数是引用，特殊处理
//			delete person;
//			ifs.close();
//			return;
//		}
//	}
//	cout << "登录失败！" << endl;
//	system("pause");//按任意键
//	system("cls");//清屏
//	ifs.close();
//	
//}


//登录功能  操作文件名、操作身份信息
void LogIn(string fileName, int type)
{
	//***************通用的用户验证函数***************
	/*if (type == 1) {
		userLogin<Student>(fileName, "请输入学号: ");
	}
	else if (type == 2) {
		userLogin<Teacher>(fileName, "请输入工号: ");
	}
	else if (type == 3) {
		managerLogin(fileName);
	}*/


	//封装为成员函数，利用多态实现身份验证
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1) // 学生
	{
		cout << "请输入学号: ";
		cin >> id;
	}
	else if (type == 2) // 教师
	{
		cout << "请输入工号: ";
		cin >> id;
	}

	cout << "请输入姓名: ";
	cin >> name;
	cout << "请输入密码: ";
	cin >> pwd;

	bool loginSuccess = false;

	if (type == 1) // 学生身份验证
	{
		int fId;
		string fName, fPwd;
		while (ifs >> fId >> fName >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				person = new Student(id, name, pwd);
				loginSuccess = true;
				break;
			}
		}
	}
	else if (type == 2) // 教师身份验证
	{
		int fId;
		string fName, fPwd;
		while (ifs >> fId >> fName >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				person = new Teacher(id, name, pwd);
				loginSuccess = true;
				break;
			}
		}
	}
	else if (type == 3) // 管理员身份验证
	{
		string fName, fPwd;
		while (ifs >> fName >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				person = new Manager(name, pwd);
				loginSuccess = true;
				break;
			}
		}
	}

	if (loginSuccess)
	{
		cout << "验证登录成功！" << endl;
		system("pause");
		system("cls");

		// 关键！无论 person 指向哪个子类对象，
		// 这里都会通过多态自动调用相应子类的 processMenu() 函数。
		person->processMenu();

		delete person; // 菜单处理结束后，释放内存
	}
	else
	{
		cout << "登录失败！" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();

}



int main()
{
	int select = 0; //选择身份

	while (1)
	{
		//搭建简易UI界面
		cout << "======================  欢迎来到zhy机房预约系统  ====================="
			<< endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";

		//传入人员接口
		cin >> select;
		switch(select)
		{
			case 1://学生身份
				LogIn(STUDENT_FILE, select);
				break;
			case 2://教师身份
				LogIn(TEACHER_FILE, select);
				break;
			case 3://管理员身份
				LogIn(ADMIN_FILE, select);
				break;
			case 0://退出系统
				cout << "感谢您的使用，欢迎下次光临！" << endl;
				system("pause");//按任意键
				return 0;//退出程序
				break;
				
			default:
				cout << "输入错误，请重新输入！" << endl;
				system("pause");//按任意键
				system("cls");//清屏
				break;
		}

	}
	return 0;
}