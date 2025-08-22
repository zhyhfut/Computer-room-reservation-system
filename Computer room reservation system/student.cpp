#include "student.hpp"

//Ĭ�Ϲ���
Student::Student()
{

}
//�вι��� ѧ�š�����������
Student::Student(int id, string name, string pwd)
{
	this->m_id = id; //��ʼ��ѧ��
	this->m_name = name;
	this->m_pwd = pwd; //��ʼ������

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while(ifs >> com.m_ComId >> com.m_MaxNum)
	{
		vCom.push_back(com); //��������Ϣ��ӵ�������
	}
	ifs.close(); //�ر��ļ�
}
//�˵�����
void Student::openMenu()//�̳и��࣬��������ʵ��
{
	cout << "��ӭѧ������" << this->m_name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//ʵ�ְ����˵�ѭ���ʹ����processMenu
void Student::processMenu()
{
	while (1)
	{
		this->openMenu();

		int select = 0; //ѡ��
		cin >> select; //����ѡ��

		switch (select)
		{
			case 1: //����ԤԼ
			{
				this->applyOrder();
				break;
			}
			case 2: //�鿴�ҵ�ԤԼ
			{
				this->showMyOrder();
				break;
			}
			case 3: //�鿴����ԤԼ
			{
				this->showAllOrder();
				break;
			}
			case 4: //ȡ��ԤԼ
			{
				this->cancelOrder();
				break;
			}
			default: //ע����¼
			{
				cout << "ע���ɹ�" << endl;
				system("pause");
				system("cls");
				return; //�˳�ѧ���Ӳ˵�
			}
		}
	}
}

//����ԤԼ
void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������" << endl;
	cout << "����������ԤԼ��ʱ��" << endl;
	cout << "1. ��һ" << endl;
	cout << "2. �ܶ�" << endl;
	cout << "3. ����" << endl;
	cout << "4. ����" << endl;
	cout << "5. ����" << endl;

	int date = 0;//����
	int interval = 0;//ʱ���
	int room = 0; //�������

	while (1)
	{
		cin >> date; //��������
		if (date < 1 || date > 5)
		{
			cout << "����������������룡" << endl;
			continue; //��������
		}
		break; //������ȷ������ѭ��
	}
	cout << "������ԤԼʱ���" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	while (1)
	{
		cin >> interval; //����ʱ���
		if (interval < 1 || interval > 2)
		{
			cout << "����������������룡" << endl;
			continue; //��������
		}
		break; //������ȷ������ѭ��
	}

	cout << "������ԤԼ�������" << endl;
	for(int i=0;i<vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "�Ż���������" << vCom[i].m_MaxNum << endl; //��ӡ�������
	}

	while (1)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "����������������룡" << endl;
	}

	cout << "ԤԼ�ɹ�������У�" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app); //��ԤԼ�ļ���׷��д��
	ofs << "date:" << date <<" ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause"); //��ͣ
	system("cls"); //����
}
//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		//string ת int��
		//string����.c_str() ת const char *
		//���� atoi(const char *) ת int
		if(this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))//�ҵ�����ԤԼ
		{
			cout << "ԤԼ��¼��" << "\t";
			cout << "���ڣ���" << of.m_orderData[i]["date"] << "\t";
			cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����":"����") << "\t";
			cout << "������ţ�" << of.m_orderData[i]["roomId"] << "\t";
			string status = "״̬��";
			//1 ����� 2 ��ԤԼ -1 ԤԼʧ�� 0 ȡ��ԤԼ
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "��ԤԼ";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}
		system("pause"); //��ͣ
		system("cls"); //����
}

// �鿴����ԤԼ
void Student::showAllOrder()
{
	dispAllOrder();
}

// ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ���ԤԼ����ȡ����" << endl;
	vector<int> cancelIndex; //�������������±���
	int index = 1;
	for (int i = 0; i < of.m_Size; i++)
	{
		//���ж�������ѧ��
		if(this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//��ɸѡ״̬
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") //����л�ԤԼ�ɹ��Ĳ���ȡ��
			{
				cancelIndex.push_back(i); //���±��������
				cout << index++ << "�� ";
				cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
				cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " ������ţ�" << of.m_orderData[i]["roomId"];
				string staus = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
				if (of.m_orderData[i]["status"] == "1")
				{
					staus += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					staus += "ԤԼ�ɹ�";
				}
				cout << staus << endl;
			}
		}
	}

	cout << "��ѡ��Ҫȡ����ԤԼ��ţ�,0������"<< endl;
	int select = 0;
	while (1)
	{
		cin >> select; //�����û�����
		if (select >= 0 || select <= cancelIndex.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[cancelIndex[select - 1]]["status"] = "0"; //��״̬��Ϊ0
				of.updateOrder(); //����ԤԼ��¼
				cout << "ȡ��ԤԼ�ɹ���" << endl;
				break;
			}
		}
		cout << "����������������룡" << endl;
	}

	system("pause"); 
	system("cls"); 
}