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


//�����ʦ�Ӳ˵�����
void teacherMenu(Identity*& teacher)
{
	while (1)
	{
		//���ý�ʦ�Ӳ˵�
		teacher->openMenu();
		//������ָ��תΪ����ָ�룬���������������ӿ�
		Teacher* tea = (Teacher*)teacher;
		int select = 0; //ѡ��
		cin >> select;
		if (select == 1)//�鿴����ԤԼ
		{
			tea->showAllOrder();
		}
		else if (select == 2)//���ԤԼ
		{
			tea->checkOrder();
		}
		else
		{
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return; //�˳���ʦ�Ӳ˵�
		}
		
	}
}

//����ѧ���Ӳ˵�����
void studentMenu(Identity*& student)
{
	while (1)
	{
		//������ѧ���Ӳ˵�
		student->openMenu();

		//������ָ��תΪ����ָ�룬���������������ӿ�
		Student* stu = (Student*)student;

		int select = 0;
		cin >> select;
		if (select == 1)//����ԤԼ
		{
			stu->applyOrder();
		}
		else if (select == 2)//�鿴�ҵ�ԤԼ
		{
			stu->showMyOrder();
		}
		else if (select == 3)//�鿴����ԤԼ
		{
			stu->showAllOrder();
		}
		else if (select == 4)//ȡ��ԤԼ
		{
			stu->cancelOrder();
		}
		else
		{
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			//delete student; //�ͷ��ڴ�
			return; //�˳�ѧ���Ӳ˵�
		}
	}
}

//�������Ա�Ӳ˵�����
void managerMenu(Identity& manager)
{
	while (1)
	{
		//���ù���Ա�Ӳ˵�
		manager.openMenu();

		//������ָ��תΪ����ָ�룬���������������ӿ�
		Manager* man = (Manager*)&manager;

		int select = 0; //ѡ��
		cin >> select;
		switch (select)
		{
			case 1://����˺�
			{
				//cout << "����˺�" << endl;
				man->addPerson();
				break;
			}
			case 2://�鿴�˺�
			{
				//cout << "�鿴�˺�" << endl;
				man->showPerson();
				break;
			}
			case 3://�鿴����
			{
				//cout << "�鿴����" << endl;
				man->showComputer();
				break;
			}
			case 4://���ԤԼ
			{
				//cout << "���ԤԼ" << endl;
				man->cleanFile();
				break;
			}

			default:
			{
				//delete& manager;
				cout << "ע���ɹ�" << endl;
				system("pause");
				system("cls");
				//break;
				return; //�˳�����Ա�Ӳ˵�
			}

		}
	}
}

//��¼����  �����ļ��������������Ϣ
void LogIn(string fileName, int type)
{
	//����ָ�룬����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if(!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	//׼�������û���Ϣ	
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if(type == 1) //ѧ�����
	{
		cout << "������ѧ��: ";
		cin >> id;

	}
	else if(type == 2) //��ʦ���
	{
		cout << "�����빤��: ";
		cin >> id;

	}
	cout << "����������: " << endl;
	cin >> name;
	cout << "����������: " << endl;
	cin >> pwd;

	if (type == 1)//ѧ�������֤
	{
		//ѧ�������֤
		int fId;//�ļ���ѧ��
		string fName;//�ļ�������
		string fPwd;//�ļ�������
		while(ifs>>fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if(fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				//����ѧ������
				person = new Student(id, name, pwd);
				
				system("pause");
				system("cls");//����
				//����ѧ���Ӳ˵�
				studentMenu(person);
				delete person;
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId;//�ļ��й���
		string fName;//�ļ�������
		string fPwd;//�ļ�������
		while(ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if(fId == id && fName == name && fPwd == pwd)//�����ÿո�ָ������Ի�ֳ�������Ϣ
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				//������ʦ����
				person = new Teacher(id, name, pwd);
				
				system("pause");
				system("cls");//����
				//�����ʦ�Ӳ˵�
				teacherMenu(person);
				delete person;
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName;//�ļ�������
		string fPwd;//�ļ�������
		while(ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if(fName == name && fPwd == pwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				//��������Ա����
				person = new Manager(name, pwd);
				
				system("pause");
				system("cls");//����
				//�������Ա�Ӳ˵�
				managerMenu(*person);
				delete person;
				return;
			}
		}
	}
	cout << "��¼ʧ�ܣ�" << endl;
	system("pause");//�������
	system("cls");//����
	return;
}



int main()
{
	int select = 0; //ѡ�����

	while (1)
	{
		//�����UI����
		cout << "======================  ��ӭ����zhy����ԤԼϵͳ  ====================="
			<< endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.ѧ������           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.��    ʦ           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.�� �� Ա           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "��������ѡ��: ";

		//������Ա�ӿ�
		cin >> select;
		switch(select)
		{
			case 1://ѧ�����
				LogIn(STUDENT_FILE, select);
				break;
			case 2://��ʦ���
				LogIn(TEACHER_FILE, select);
				break;
			case 3://����Ա���
				LogIn(ADMIN_FILE, select);
				break;
			case 0://�˳�ϵͳ
				cout << "��л����ʹ�ã���ӭ�´ι��٣�" << endl;
				system("pause");//�������
				return 0;//�˳�����
				break;
				
			default:
				cout << "����������������룡" << endl;
				system("pause");//�������
				system("cls");//����
				break;
		}

	}
	



	system("pause");
	return 0;
}