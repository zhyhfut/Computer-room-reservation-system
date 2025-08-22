#include"orderFile.hpp"

//分割字符串
std::pair<string,string> key_value_create(string data)
{
	string key;
	string value;
	int pos = data.find(":");
	if (pos != -1)
	{
		key = data.substr(0, pos);
		value = data.substr(pos + 1, data.size() - pos - 1);
	}
	return make_pair(key,value);
}

//构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE,ios::in);

	string date;  //日期
	string interval;//时间段
	string stuId;//学生编号
	string stuName;//学生姓名
	string roomId;//机房编号
	string status;//预约状态

	this->m_Size = 0; //记录条数

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//cout << date << endl;
		//cout << interval << endl;
		//cout << stuId << endl;
		//cout << stuName << endl;
		//cout << roomId << endl;
		//cout << status << endl;

		string key;
		string value;
		map<string, string> m;
		//截取文件内预约信息 不能通过函数返回map，并使用操作m.insert(key_value_create(date).begin(),key_value_create(date).end());
		//因为begin与end调用了两次函数，产生了两个map对象，但放在了一个insert用法里
		m.insert(key_value_create(date));
		m.insert(key_value_create(interval));
		m.insert(key_value_create(stuId));
		m.insert(key_value_create(stuName));
		m.insert(key_value_create(roomId));
		m.insert(key_value_create(status));

		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;

	}

	ifs.close(); //关闭文件

	////测试最大map容器
	//for (map<int, map<string, string>> ::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
	//{
	//	cout << "条数为： " << it->first << " value= " << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << " key = " << mit->first << " value = " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

//更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return; // 预约记录0条，直接return
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";//第一个[]访问到条数，第二个[]访问到数据
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;

	}
	ofs.close();
}

//显示所有预约
void dispAllOrder()
{
	OrderFile of; //创建预约文件对象
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、 ";
		cout << "预约日期： 周" << of.m_orderData[i]["date"];
		cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房：" << of.m_orderData[i]["roomId"];
		string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}