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

//*************ʹ�ú���ģ��ʵ��ͨ�õ��û���¼����*************
////ʹ�ú���ģ��������һ��ͨ�õ��û���֤����
//template <typename T>
//void userLogin(const string& fileName, const string& prompt)
//{
//	cout << prompt;
//	int id;
//	cin >> id;
//
//	cout << "����������: ";
//	string name;
//	cin >> name;
//
//	cout << "����������: ";
//	string pwd;
//	cin >> pwd;
//
//	ifstream ifs;
//	ifs.open(fileName, ios::in);
//	//�ж��ļ��Ƿ����
//	if (!ifs.is_open())
//	{
//		cout << "�ļ������ڣ�" << endl;
//		ifs.close();
//		return;
//	}
//	//׼�������û���Ϣ
//	int fId = 0;
//	string fName;
//	string fPwd;
//	bool loginSuccess = false;
//	while (ifs >> fId >> fName >> fPwd)
//	{
//		if (fId == id && fName == name && fPwd == pwd)
//		{
//			cout << "��¼�ɹ���" << endl;
//			system("pause");
//			system("cls");//����
//
//			Identity* person = new T(id, name, pwd); //������Ӧ��ݵĶ���
//
//			//�����Ӧ��ݵ��Ӳ˵�
//			if(typeid(T) == typeid(Student))
//			{
//				studentMenu(person);
//			}
//			else if (typeid(T) == typeid(Teacher))
//			{
//				teacherMenu(person);
//			}
//			delete person; //�ͷ��ڴ�
//			loginSuccess = true;
//			break;
//		}
//	}
//	if (!loginSuccess)
//	{
//		cout << "��¼ʧ�ܣ�" << endl;
//		system("pause");//�������
//		system("cls");//����
//	}
//	ifs.close(); //�ر��ļ�
//}
//
//void managerLogin(const string& fileName)
//{
//	cout << "����������: ";
//	string name;
//	cin >> name;
//
//	cout << "����������: ";
//	string pwd;
//	cin >> pwd;
//
//	ifstream ifs;
//	ifs.open(fileName, ios::in);
//	// ... �����߼����� ...
//	string fName, fPwd;
//	while (ifs >> fName && ifs >> fPwd)
//	{
//		if (fName == name && fPwd == pwd)
//		{
//			cout << "����Ա��֤��¼�ɹ���" << endl;
//			Identity* person = new Manager(name, pwd);
//			system("pause");
//			system("cls");
//			managerMenu(*person); // ����Ա�˵��Ĳ��������ã����⴦��
//			delete person;
//			ifs.close();
//			return;
//		}
//	}
//	cout << "��¼ʧ�ܣ�" << endl;
//	system("pause");//�������
//	system("cls");//����
//	ifs.close();
//	
//}


//��¼����  �����ļ��������������Ϣ
void LogIn(string fileName, int type)
{
	//***************ͨ�õ��û���֤����***************
	/*if (type == 1) {
		userLogin<Student>(fileName, "������ѧ��: ");
	}
	else if (type == 2) {
		userLogin<Teacher>(fileName, "�����빤��: ");
	}
	else if (type == 3) {
		managerLogin(fileName);
	}*/


	//��װΪ��Ա���������ö�̬ʵ�������֤
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1) // ѧ��
	{
		cout << "������ѧ��: ";
		cin >> id;
	}
	else if (type == 2) // ��ʦ
	{
		cout << "�����빤��: ";
		cin >> id;
	}

	cout << "����������: ";
	cin >> name;
	cout << "����������: ";
	cin >> pwd;

	bool loginSuccess = false;

	if (type == 1) // ѧ�������֤
	{
		int fId;
		string fName, fPwd;
		while (ifs >> fId >> fName >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				person = new Student(id, name, pwd);
				loginSuccess = true;
				break;
			}
		}
	}
	else if (type == 2) // ��ʦ�����֤
	{
		int fId;
		string fName, fPwd;
		while (ifs >> fId >> fName >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				person = new Teacher(id, name, pwd);
				loginSuccess = true;
				break;
			}
		}
	}
	else if (type == 3) // ����Ա�����֤
	{
		string fName, fPwd;
		while (ifs >> fName >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				person = new Manager(name, pwd);
				loginSuccess = true;
				break;
			}
		}
	}

	if (loginSuccess)
	{
		cout << "��֤��¼�ɹ���" << endl;
		system("pause");
		system("cls");

		// �ؼ������� person ָ���ĸ��������
		// ���ﶼ��ͨ����̬�Զ�������Ӧ����� processMenu() ������
		person->processMenu();

		delete person; // �˵�����������ͷ��ڴ�
	}
	else
	{
		cout << "��¼ʧ�ܣ�" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();

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
	return 0;
}