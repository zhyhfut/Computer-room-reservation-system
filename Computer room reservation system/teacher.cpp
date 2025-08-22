#include"teacher.hpp"


//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι��� ��ʦ���š�����������
Teacher::Teacher(int id, string name, string pwd)
{
	this->m_id = id; //��ʼ������
	this->m_name = name;
	this->m_pwd = pwd; //��ʼ������
}
//�˵�����
void Teacher::openMenu() //�̳и��࣬��������ʵ��
{
	cout << "��ӭ��ʦ��" << this->m_name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.���ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

void Teacher::processMenu()
{
	while (1)
	{
		this->openMenu(); //��ʾ�˵�
		int select = 0; //ѡ��
		cin >> select; //����ѡ��
		switch (select)
		{
			case 1: //�鿴����ԤԼ
			{
				this->showAllOrder();
				break;
			}
			case 2: //���ԤԼ
			{
				this->checkOrder();
				break;
			}
			default: //ע����¼
			{
				cout << "ע���ɹ�" << endl;
				system("pause");
				system("cls");
				return; //�˳���ʦ�Ӳ˵�
			}
		}
	}
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	dispAllOrder(); //����ȫ�ֺ�����ʾ����ԤԼ
}
//���ԤԼ
void Teacher::checkOrder()
{
	OrderFile of; //����ԤԼ�ļ�����
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	vector<int>v;
	int index = 0;
	cout << "����˵�ԤԼ��¼���£�" << endl;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1") //ֻ��ʾ����е�ԤԼ
		{
			v.push_back(i); //������е�ԤԼ�±��������
			cout << ++index << "�� ";
			cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
			cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
			cout << " ������" << of.m_orderData[i]["stuName"];
			cout << " ������" << of.m_orderData[i]["roomId"];
			string status= " ״̬�������";
			cout << status << endl;
		}
	}

	cout << "��ѡ��Ҫ��˵�ԤԼ�� ,0������" << endl;
	int select = 0;//�����û�ѡ���ԤԼ��¼
	int ret = 0;//����ԤԼ�����¼

	while (1)
	{
		cin >> select;
		if (select < 0 || select > v.size())
		{
			cout << "����������������룡" << endl;
			continue; //��������
		}
		if (select == 0)
		{
			return; //����
		}
		cout << "��������˽��" << endl;
		cout << "1��ͨ��" << endl;
		cout << "2����ͨ��" << endl;
		cin >> ret;
		if (ret == 1)
		{
			of.m_orderData[v[select - 1]]["status"] = "2"; //���ͨ��
			cout << "���ͨ����" << endl;
		}
		else if (ret == 2)
		{
			of.m_orderData[v[select - 1]]["status"] = "-1"; //��˲�ͨ��
			cout << "���δͨ����ԤԼʧ�ܣ�" << endl;
		}
		else
		{
			cout << "����������������룡" << endl;
			continue; //��������
		}
		of.updateOrder(); //����ԤԼ�ļ�
		cout << "��˳ɹ���" << endl;
		break; 
	}
	system("pause");
	system("cls"); 
}