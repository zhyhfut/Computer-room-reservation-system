#include"orderFile.hpp"

//�ָ��ַ���
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

//���캯��
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE,ios::in);

	string date;  //����
	string interval;//ʱ���
	string stuId;//ѧ�����
	string stuName;//ѧ������
	string roomId;//�������
	string status;//ԤԼ״̬

	this->m_Size = 0; //��¼����

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
		//��ȡ�ļ���ԤԼ��Ϣ ����ͨ����������map����ʹ�ò���m.insert(key_value_create(date).begin(),key_value_create(date).end());
		//��Ϊbegin��end���������κ���������������map���󣬵�������һ��insert�÷���
		m.insert(key_value_create(date));
		m.insert(key_value_create(interval));
		m.insert(key_value_create(stuId));
		m.insert(key_value_create(stuName));
		m.insert(key_value_create(roomId));
		m.insert(key_value_create(status));

		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;

	}

	ifs.close(); //�ر��ļ�

	////�������map����
	//for (map<int, map<string, string>> ::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
	//{
	//	cout << "����Ϊ�� " << it->first << " value= " << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << " key = " << mit->first << " value = " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

//����ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return; // ԤԼ��¼0����ֱ��return
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";//��һ��[]���ʵ��������ڶ���[]���ʵ�����
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;

	}
	ofs.close();
}