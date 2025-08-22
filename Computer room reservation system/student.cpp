#include "student.hpp"

//默认构造
Student::Student()
{

}
//有参构造 学号、姓名、密码
Student::Student(int id, string name, string pwd)
{
	this->m_id = id; //初始化学号
	this->m_name = name;
	this->m_pwd = pwd; //初始化密码

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while(ifs >> com.m_ComId >> com.m_MaxNum)
	{
		vCom.push_back(com); //将机房信息添加到容器中
	}
	ifs.close(); //关闭文件
}
//菜单界面
void Student::openMenu()//继承父类，在子类中实现
{
	cout << "欢迎学生代表：" << this->m_name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//实现包含菜单循环和处理的processMenu
void Student::processMenu()
{
	while (1)
	{
		this->openMenu();

		int select = 0; //选择
		cin >> select; //接受选择

		switch (select)
		{
			case 1: //申请预约
			{
				this->applyOrder();
				break;
			}
			case 2: //查看我的预约
			{
				this->showMyOrder();
				break;
			}
			case 3: //查看所有预约
			{
				this->showAllOrder();
				break;
			}
			case 4: //取消预约
			{
				this->cancelOrder();
				break;
			}
			default: //注销登录
			{
				cout << "注销成功" << endl;
				system("pause");
				system("cls");
				return; //退出学生子菜单
			}
		}
	}
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放时间为周一到周五" << endl;
	cout << "请输入申请预约的时间" << endl;
	cout << "1. 周一" << endl;
	cout << "2. 周二" << endl;
	cout << "3. 周三" << endl;
	cout << "4. 周四" << endl;
	cout << "5. 周五" << endl;

	int date = 0;//日期
	int interval = 0;//时间段
	int room = 0; //机房编号

	while (1)
	{
		cin >> date; //接受日期
		if (date < 1 || date > 5)
		{
			cout << "输入错误，请重新输入！" << endl;
			continue; //重新输入
		}
		break; //输入正确，跳出循环
	}
	cout << "请输入预约时间段" << endl;
	cout << "1. 上午" << endl;
	cout << "2. 下午" << endl;
	while (1)
	{
		cin >> interval; //接受时间段
		if (interval < 1 || interval > 2)
		{
			cout << "输入错误，请重新输入！" << endl;
			continue; //重新输入
		}
		break; //输入正确，跳出循环
	}

	cout << "请输入预约机房编号" << endl;
	for(int i=0;i<vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "号机房容量：" << vCom[i].m_MaxNum << endl; //打印机房编号
	}

	while (1)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入错误，请重新输入！" << endl;
	}

	cout << "预约成功！审核中！" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app); //打开预约文件，追加写入
	ofs << "date:" << date <<" ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause"); //暂停
	system("cls"); //清屏
}
//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		//string 转 int：
		//string利用.c_str() 转 const char *
		//利用 atoi(const char *) 转 int
		if(this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))//找到自身预约
		{
			cout << "预约记录：" << "\t";
			cout << "日期：周" << of.m_orderData[i]["date"] << "\t";
			cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午":"下午") << "\t";
			cout << "机房编号：" << of.m_orderData[i]["roomId"] << "\t";
			string status = "状态：";
			//1 审核中 2 已预约 -1 预约失败 0 取消预约
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "已预约";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败，审核未通过";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
		system("pause"); //暂停
		system("cls"); //清屏
}

// 查看所有预约
void Student::showAllOrder()
{
	dispAllOrder();
}

// 取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的预约才能取消！" << endl;
	vector<int> cancelIndex; //存放最大容器的下标编号
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//先判断是自身学号
		if(this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//再筛选状态
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") //审核中或预约成功的才能取消
			{
				cancelIndex.push_back(i); //将下标存入容器
				cout << index++ << "、 ";
				cout << "预约日期： 周" << of.m_orderData[i]["date"];
				cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房编号：" << of.m_orderData[i]["roomId"];
				string staus = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
				if (of.m_orderData[i]["status"] == "1")
				{
					staus += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					staus += "预约成功";
				}
				cout << staus << endl;
			}
		}
	}

	cout << "请选择要取消的预约编号：,0代表返回"<< endl;
	int select = 0;
	while (1)
	{
		cin >> select; //接受用户输入
		if (select >= 0 || select <= cancelIndex.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[cancelIndex[select - 1]]["status"] = "0"; //将状态改为0
				of.updateOrder(); //更新预约记录
				cout << "取消预约成功！" << endl;
				break;
			}
		}
		cout << "输入错误，请重新输入！" << endl;
	}

	system("pause"); 
	system("cls"); 
}