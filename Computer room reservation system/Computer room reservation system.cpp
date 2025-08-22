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


//进入教师子菜单界面
void teacherMenu(Identity*& teacher)
{
	while (1)
	{
		//调用教师子菜单
		teacher->openMenu();
		//将父类指针转为子类指针，调用子类里其他接口
		Teacher* tea = (Teacher*)teacher;
		int select = 0; //选择
		cin >> select;
		if (select == 1)//查看所有预约
		{
			tea->showAllOrder();
		}
		else if (select == 2)//审核预约
		{
			tea->checkOrder();
		}
		else
		{
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return; //退出教师子菜单
		}
		
	}
}

//进入学生子菜单界面
void studentMenu(Identity*& student)
{
	while (1)
	{
		//调用用学生子菜单
		student->openMenu();

		//将父类指针转为子类指针，调用子类里其他接口
		Student* stu = (Student*)student;

		int select = 0;
		cin >> select;
		if (select == 1)//申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2)//查看我的预约
		{
			stu->showMyOrder();
		}
		else if (select == 3)//查看所有预约
		{
			stu->showAllOrder();
		}
		else if (select == 4)//取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			//delete student; //释放内存
			return; //退出学生子菜单
		}
	}
}

//进入管理员子菜单界面
void managerMenu(Identity& manager)
{
	while (1)
	{
		//调用管理员子菜单
		manager.openMenu();

		//将父类指针转为子类指针，调用子类里其他接口
		Manager* man = (Manager*)&manager;

		int select = 0; //选择
		cin >> select;
		switch (select)
		{
			case 1://添加账号
			{
				//cout << "添加账号" << endl;
				man->addPerson();
				break;
			}
			case 2://查看账号
			{
				//cout << "查看账号" << endl;
				man->showPerson();
				break;
			}
			case 3://查看机房
			{
				//cout << "查看机房" << endl;
				man->showComputer();
				break;
			}
			case 4://清空预约
			{
				//cout << "清空预约" << endl;
				man->cleanFile();
				break;
			}

			default:
			{
				//delete& manager;
				cout << "注销成功" << endl;
				system("pause");
				system("cls");
				//break;
				return; //退出管理员子菜单
			}

		}
	}
}

//登录功能  操作文件名、操作身份信息
void LogIn(string fileName, int type)
{
	//父类指针，用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if(!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	//准备接收用户信息	
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if(type == 1) //学生身份
	{
		cout << "请输入学号: ";
		cin >> id;

	}
	else if(type == 2) //教师身份
	{
		cout << "请输入工号: ";
		cin >> id;

	}
	cout << "请输入姓名: " << endl;
	cin >> name;
	cout << "请输入密码: " << endl;
	cin >> pwd;

	if (type == 1)//学生身份验证
	{
		//学生身份验证
		int fId;//文件中学号
		string fName;//文件中姓名
		string fPwd;//文件中密码
		while(ifs>>fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if(fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				//创建学生对象
				person = new Student(id, name, pwd);
				
				system("pause");
				system("cls");//清屏
				//进入学生子菜单
				studentMenu(person);
				delete person;
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师身份验证
		int fId;//文件中工号
		string fName;//文件中姓名
		string fPwd;//文件中密码
		while(ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if(fId == id && fName == name && fPwd == pwd)//由于用空格分隔，所以会分成三条信息
			{
				cout << "教师验证登录成功！" << endl;
				//创建教师对象
				person = new Teacher(id, name, pwd);
				
				system("pause");
				system("cls");//清屏
				//进入教师子菜单
				teacherMenu(person);
				delete person;
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName;//文件中姓名
		string fPwd;//文件中密码
		while(ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if(fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				//创建管理员对象
				person = new Manager(name, pwd);
				
				system("pause");
				system("cls");//清屏
				//进入管理员子菜单
				managerMenu(*person);
				delete person;
				return;
			}
		}
	}
	cout << "登录失败！" << endl;
	system("pause");//按任意键
	system("cls");//清屏
	return;
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
	



	system("pause");
	return 0;
}