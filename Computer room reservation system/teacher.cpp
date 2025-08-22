#include"teacher.hpp"


//默认构造
Teacher::Teacher()
{

}

//有参构造 教师工号、姓名、密码
Teacher::Teacher(int id, string name, string pwd)
{
	this->m_id = id; //初始化工号
	this->m_name = name;
	this->m_pwd = pwd; //初始化密码
}
//菜单界面
void Teacher::openMenu() //继承父类，在子类中实现
{
	cout << "欢迎教师：" << this->m_name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Teacher::processMenu()
{
	while (1)
	{
		this->openMenu(); //显示菜单
		int select = 0; //选择
		cin >> select; //接受选择
		switch (select)
		{
			case 1: //查看所有预约
			{
				this->showAllOrder();
				break;
			}
			case 2: //审核预约
			{
				this->checkOrder();
				break;
			}
			default: //注销登录
			{
				cout << "注销成功" << endl;
				system("pause");
				system("cls");
				return; //退出教师子菜单
			}
		}
	}
}

//查看所有预约
void Teacher::showAllOrder()
{
	dispAllOrder(); //调用全局函数显示所有预约
}
//审核预约
void Teacher::checkOrder()
{
	OrderFile of; //创建预约文件对象
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	vector<int>v;
	int index = 0;
	cout << "待审核的预约记录如下：" << endl;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1") //只显示审核中的预约
		{
			v.push_back(i); //将审核中的预约下标存入容器
			cout << ++index << "、 ";
			cout << "预约日期： 周" << of.m_orderData[i]["date"];
			cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 学号：" << of.m_orderData[i]["stuId"];
			cout << " 姓名：" << of.m_orderData[i]["stuName"];
			cout << " 机房：" << of.m_orderData[i]["roomId"];
			string status= " 状态：审核中";
			cout << status << endl;
		}
	}

	cout << "请选择要审核的预约： ,0代表返回" << endl;
	int select = 0;//接收用户选择的预约记录
	int ret = 0;//接收预约结果记录

	while (1)
	{
		cin >> select;
		if (select < 0 || select > v.size())
		{
			cout << "输入错误，请重新输入！" << endl;
			continue; //重新输入
		}
		if (select == 0)
		{
			return; //返回
		}
		cout << "请输入审核结果" << endl;
		cout << "1、通过" << endl;
		cout << "2、不通过" << endl;
		cin >> ret;
		if (ret == 1)
		{
			of.m_orderData[v[select - 1]]["status"] = "2"; //审核通过
			cout << "审核通过！" << endl;
		}
		else if (ret == 2)
		{
			of.m_orderData[v[select - 1]]["status"] = "-1"; //审核不通过
			cout << "审核未通过，预约失败！" << endl;
		}
		else
		{
			cout << "输入错误，请重新输入！" << endl;
			continue; //重新输入
		}
		of.updateOrder(); //更新预约文件
		cout << "审核成功！" << endl;
		break; 
	}
	system("pause");
	system("cls"); 
}