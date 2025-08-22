#include"manager.hpp"

//默认构造
Manager::Manager()
{
}

//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_name = name;
	this->m_pwd = pwd;

	//初始化容器 获取所有文件中信息
	this->initVector();


}

//选择菜单
void Manager::openMenu()
{
	cout << "欢迎管理员：" << this->m_name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Manager::processMenu()
{
	while (1)
	{
		this->openMenu(); //显示菜单
		int select = 0; //选择
		cin >> select; //接受选择
		switch (select)
		{
			case 1: //添加账号
			{
				this->addPerson();
				break;
			}
			case 2: //查看账号
			{
				this->showPerson();
				break;
			}
			case 3: //查看机房
			{
				this->showComputer();
				break;
			}
			case 4: //清空预约
			{
				this->cleanFile();
				break;
			}
			default: //注销登录
			{
				cout << "注销成功" << endl;
				system("pause");
				system("cls");
				return; //退出管理员子菜单
			}
		}
	}
}

//添加账号  
void Manager::addPerson()
{
	cout << "请输入添加账号类型" << endl;
	cout << "1. 添加学生" << endl;
	cout << "2. 添加老师" << endl;

	string fileName;//操作文件名
	string tip;//提示id号
	string errorTip; //重复错误提示

	ofstream ofs; //文件操作对象

	int select = 0;
	cin >> select;//接受用户选项
	if (select == 1) //添加学生
	{
		fileName = STUDENT_FILE;;
		tip = "请输入学号";
		errorTip = "学号重复，请重新输入！";
	}
	else if (select == 2) //添加老师
	{
		fileName = TEACHER_FILE;
		tip = "请输入工号";
		errorTip = "职工号重复，请重新输入！";
	}
	else
	{
		cout << "输入错误，请重新输入！" << endl;
		return;
	}
	ofs.open(fileName, ios::out | ios::app); //打开文件，追加写入

	int id;
	string name;
	string pwd;

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select); //检测学号/职工号是否重复
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break; //不重复，跳出循环
		}
	}


	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	//将信息写入文件
	ofs << id << " " << name << " " << pwd << endl;
	cout << "账号添加成功！" << endl;

	system("pause");
	system("cls"); //清屏
	ofs.close(); //关闭文件

	//嗲用初始化容器接口，重新获取文件中的数据
	this->initVector();
}

void printStudent(Student& s)
{
	cout << "学号：" << s.m_id << "\t姓名：" << s.m_name << "\t密码：" << s.m_pwd << endl;
}
void printTeacher(Teacher& t)
{
	cout << "学号：" << t.m_id << "\t姓名：" << t.m_name << "\t密码：" << t.m_pwd << endl;
}
//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1. 查看学生账号" << endl;
	cout << "2. 查看教师账号" << endl;

	int select = 0;
	cin >> select; //接受用户选项
	if (select == 1)
	{
		//查看学生
		cout << "学生账号信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent); //遍历学生容器，打印学生信息
	}
	else
	{
		//查看老师
		cout << "老师账号信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher); //遍历学生容器，打印学生信息
	}

	system("pause");
	system("cls"); 
}

//查看机房信息
void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	for(vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_ComId << "\t机房最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls"); //清屏
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc); //文件操作对象
	ofs.close();

	cout << "清空成功" << endl;
	system("pause");
	system("cls"); //清屏
}

//初始化容器
void Manager::initVector()
{
	//清空容器
	vStu.clear(); //清空学生容器
	vTea.clear(); //清空教师容器
	//读取信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if(!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		ifs.close();
		return;
	}

	Student stu;
	while(ifs >> stu.m_id >> stu.m_name >> stu.m_pwd)
	{
		vStu.push_back(stu); //将学生信息添加到容器中
	}

	//cout << "当前学生数量：" << vStu.size() << endl;
	ifs.close(); //关闭文件

	//读取信息老师
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while(ifs >> t.m_id >> t.m_name >> t.m_pwd)
	{
		vTea.push_back(t); //将教师信息添加到容器中
	}
	//cout << "当前教师数量：" << vTea.size() << endl;
	ifs.close(); //关闭文件

	//初始化机房信息
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom r;
	while(ifs >> r.m_ComId >> r.m_MaxNum)
	{
		vCom.push_back(r); //将机房信息添加到容器中
	}
	//cout << "当前机房数量：" << vCom.size() << endl;
	ifs.close(); //关闭文件
	
}

//查看去重  学号/职工号  检测类型
bool Manager::checkRepeat(int id,int type)
{
	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (it->m_id == id)
			{
				cout << "学号重复，请重新输入！" << endl;
				return true; //重复
			}
		}
	}
	else
	{
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (it->m_id == id)
			{
				cout << "职工号重复，请重新输入！" << endl;
				return true; //重复
			}
		}
	}
	return false; //默认不重复
}