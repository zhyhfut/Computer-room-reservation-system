#include"manager.hpp"

//Ĭ�Ϲ���
Manager::Manager()
{
}

//�вι���
Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_name = name;
	this->m_pwd = pwd;

	//��ʼ������ ��ȡ�����ļ�����Ϣ
	this->initVector();


}

//ѡ��˵�
void Manager::openMenu()
{
	cout << "��ӭ����Ա��" << this->m_name << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

void Manager::processMenu()
{
	while (1)
	{
		this->openMenu(); //��ʾ�˵�
		int select = 0; //ѡ��
		cin >> select; //����ѡ��
		switch (select)
		{
			case 1: //����˺�
			{
				this->addPerson();
				break;
			}
			case 2: //�鿴�˺�
			{
				this->showPerson();
				break;
			}
			case 3: //�鿴����
			{
				this->showComputer();
				break;
			}
			case 4: //���ԤԼ
			{
				this->cleanFile();
				break;
			}
			default: //ע����¼
			{
				cout << "ע���ɹ�" << endl;
				system("pause");
				system("cls");
				return; //�˳�����Ա�Ӳ˵�
			}
		}
	}
}

//����˺�  
void Manager::addPerson()
{
	cout << "����������˺�����" << endl;
	cout << "1. ���ѧ��" << endl;
	cout << "2. �����ʦ" << endl;

	string fileName;//�����ļ���
	string tip;//��ʾid��
	string errorTip; //�ظ�������ʾ

	ofstream ofs; //�ļ���������

	int select = 0;
	cin >> select;//�����û�ѡ��
	if (select == 1) //���ѧ��
	{
		fileName = STUDENT_FILE;;
		tip = "������ѧ��";
		errorTip = "ѧ���ظ������������룡";
	}
	else if (select == 2) //�����ʦ
	{
		fileName = TEACHER_FILE;
		tip = "�����빤��";
		errorTip = "ְ�����ظ������������룡";
	}
	else
	{
		cout << "����������������룡" << endl;
		return;
	}
	ofs.open(fileName, ios::out | ios::app); //���ļ���׷��д��

	int id;
	string name;
	string pwd;

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select); //���ѧ��/ְ�����Ƿ��ظ�
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break; //���ظ�������ѭ��
		}
	}


	cout << "������������" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	//����Ϣд���ļ�
	ofs << id << " " << name << " " << pwd << endl;
	cout << "�˺���ӳɹ���" << endl;

	system("pause");
	system("cls"); //����
	ofs.close(); //�ر��ļ�

	//���ó�ʼ�������ӿڣ����»�ȡ�ļ��е�����
	this->initVector();
}

void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_id << "\t������" << s.m_name << "\t���룺" << s.m_pwd << endl;
}
void printTeacher(Teacher& t)
{
	cout << "ѧ�ţ�" << t.m_id << "\t������" << t.m_name << "\t���룺" << t.m_pwd << endl;
}
//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1. �鿴ѧ���˺�" << endl;
	cout << "2. �鿴��ʦ�˺�" << endl;

	int select = 0;
	cin >> select; //�����û�ѡ��
	if (select == 1)
	{
		//�鿴ѧ��
		cout << "ѧ���˺���Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent); //����ѧ����������ӡѧ����Ϣ
	}
	else
	{
		//�鿴��ʦ
		cout << "��ʦ�˺���Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher); //����ѧ����������ӡѧ����Ϣ
	}

	system("pause");
	system("cls"); 
}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for(vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_ComId << "\t�������������" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls"); //����
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc); //�ļ���������
	ofs.close();

	cout << "��ճɹ�" << endl;
	system("pause");
	system("cls"); //����
}

//��ʼ������
void Manager::initVector()
{
	//�������
	vStu.clear(); //���ѧ������
	vTea.clear(); //��ս�ʦ����
	//��ȡ��Ϣ
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if(!ifs.is_open())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		ifs.close();
		return;
	}

	Student stu;
	while(ifs >> stu.m_id >> stu.m_name >> stu.m_pwd)
	{
		vStu.push_back(stu); //��ѧ����Ϣ��ӵ�������
	}

	//cout << "��ǰѧ��������" << vStu.size() << endl;
	ifs.close(); //�ر��ļ�

	//��ȡ��Ϣ��ʦ
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while(ifs >> t.m_id >> t.m_name >> t.m_pwd)
	{
		vTea.push_back(t); //����ʦ��Ϣ��ӵ�������
	}
	//cout << "��ǰ��ʦ������" << vTea.size() << endl;
	ifs.close(); //�ر��ļ�

	//��ʼ��������Ϣ
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom r;
	while(ifs >> r.m_ComId >> r.m_MaxNum)
	{
		vCom.push_back(r); //��������Ϣ��ӵ�������
	}
	//cout << "��ǰ����������" << vCom.size() << endl;
	ifs.close(); //�ر��ļ�
	
}

//�鿴ȥ��  ѧ��/ְ����  �������
bool Manager::checkRepeat(int id,int type)
{
	if (type == 1)
	{
		//���ѧ��
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (it->m_id == id)
			{
				cout << "ѧ���ظ������������룡" << endl;
				return true; //�ظ�
			}
		}
	}
	else
	{
		//�����ʦ
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (it->m_id == id)
			{
				cout << "ְ�����ظ������������룡" << endl;
				return true; //�ظ�
			}
		}
	}
	return false; //Ĭ�ϲ��ظ�
}