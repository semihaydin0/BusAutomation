//MIT License
//Copyright(c) 2020 Semih Ayd�n
//UTF - 8
//Display Languague : Turkish

#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <windows.h>

#include "Worker.h"

using namespace std;

int Worker::WorkerRegistration()
{
	string _username, _password, authority;
	char auth;
	cout << "L�tfen �al��an ki�i i�in kullan�c� ad� ve �ifre belirleyiniz." << endl;
workerentry:
	cout << "Kullan�c� Ad� :";
	cin >> _username;
	cout << "�ifre :";
	cin >> _password;
againauth:
	cout << "L�tfen yetki t�r� se�iniz.\n1-Tam\n2-Yar�\nSe�iminiz :" << endl;
	cin >> auth;
	switch (auth)
	{
	case '1':authority = "tam";
		break;
	case '2':authority = "yar�";
		break;
	default:cout << "Hatal� se�im yapt�n�z tekrar deneyin.";
		goto againauth;
		break;
	}
	if (AuthorityControl(GetWorkerAuth(LoggedWorkerID), authority) == 1)
	{
		if (WorkerRecordCheck(_username) == 0)
		{
			registrationID++;
			ofstream AddWorkerEntry;
			AddWorkerEntry.open("WorkerEntry.txt", ios::app);
			if (AddWorkerEntry.is_open())
			{
				AddWorkerEntry << registrationID << "\t" << enc.Encryption(_username) << "\t" << enc.Encryption(_password) << "\t" << authority << "\t" << "aktif" << "\n";
				AddWorkerEntry.close();
				return 1;
			}
			else FileExp();
		}
		else
		{
			system("cls");
			cout << "Girmi� oldu�unuz kullan�c� ad� daha �nceden al�nm��t�r." << endl;
			goto workerentry;
		}
	}
	else
	{
		system("cls");
		cout << "Olu�turmaya �al��t���n�z hesab�n yetkisi sizin yetkinizden y�ksek oldu�u i�in hesap olu�turulamad�." << endl;
		goto workerentry;
	}
}
int Worker::WorkerLogin()
{
	int account = 0, status = 0, sum = 0;
	string _username, _password;
	cout << "Kullan�c� Ad� :";
	cin >> _username;
	cout << "�ifre :";
	cin >> _password;
	ifstream WorkerLoginFile("WorkerEntry.txt");
	if (WorkerLoginFile.is_open())
	{
		while (WorkerLoginFile >> registrationID >> username >> password >> auth >> activity)
		{
			if (_username == enc.Decryption(username) && _password == enc.Decryption(password))
			{
				account = 1;
				if (activity == "aktif")
				{
					status = 1;
					LoggedWorkerID = registrationID;
				}
				else status = 0;
			}
			sum = account + status;
		}
		return sum;
	}
	else FileExp();
}
void Worker::GetWorkerID()
{
	int s = 0;
	string data;
	ifstream GetUser("WorkerEntry.txt");
	if (GetUser.is_open())
	{
		while (!GetUser.eof())
		{
			getline(GetUser, data);
			s++;
		}
		registrationID = s - 1;
		GetUser.close();
	}
	else FileExp();
}
int Worker::WorkerDeregistration(int WorkerIDValue)
{
	int line = 0;
	fstream WorkerDereg;
	ofstream Temp;
	WorkerDereg.open("WorkerEntry.txt", ios::in);
	Temp.open("temp.txt", ios::out);
	if (WorkerDereg.is_open() && Temp.is_open())
	{
		while (!WorkerDereg.eof())
		{
			line++;
			WorkerDereg >> registrationID >> username >> password >> auth >> activity;
			if (WorkerIDValue == line)
			{
				Temp << registrationID << "\t" << username << "\t" << password << "\t" << auth << "\t" << "inaktif" << "\n";
			}
			else
			{
				if (line <= registrationID)
				{
					Temp << registrationID << "\t" << username << "\t" << password << "\t" << auth << "\t" << activity << "\n";
				}
			}
		}
		WorkerDereg.close();
		Temp.close();
		if (remove("WorkerEntry.txt") == 0)
		{
			if (rename("temp.txt", "WorkerEntry.txt") == 0)
			{
				return 1;
			}
		}
	}
	else FileExp();
}
int Worker::WorkerResetPassword(int WorkerIDValue)
{
	int line = 0;
	fstream WorkerP;
	ofstream Temp;
	string NewPassword;
	cout << "Yeni �ifrenizi giriniz :";
	cin >> NewPassword;
	WorkerP.open("WorkerEntry.txt", ios::in);
	Temp.open("temp.txt", ios::out);
	if (WorkerP.is_open() && Temp.is_open())
	{
		while (!WorkerP.eof())
		{
			line++;
			WorkerP >> registrationID >> username >> password >> auth >> activity;
			if (WorkerIDValue == line)
			{
				Temp << registrationID << "\t" << username << "\t" << enc.Encryption(NewPassword) << "\t" << auth << "\t" << activity << "\n";
			}
			else
			{
				if (line <= registrationID)
				{
					Temp << registrationID << "\t" << username << "\t" << password << "\t" << auth << "\t" << activity << "\n";
				}
			}
		}
		WorkerP.close();
		Temp.close();
		if (remove("WorkerEntry.txt") == 0)
		{
			if (rename("temp.txt", "WorkerEntry.txt") == 0)
			{
				return 1;
			}
		}
	}
	else FileExp();
}
int Worker::GetAuthControl(int ID)
{
	int x;
	x = AuthorityControl(GetWorkerAuth(ID), "tam");
	return x;
}
int Worker::AuthorityControl(string personauth, string auth)
{
	ifstream Control("WorkerEntry.txt");
	if (Control.is_open())
	{
		while (!Control.eof())
		{
			Control >> registrationID >> username >> password >> auth >> activity;
			if (personauth == auth || personauth == "tam" && auth == "yar�")
			{
				return 1;
			}
			else return 0;
		}
		Control.close();
	}
	else FileExp();
}
string Worker::GetWorkerAuth(int LoggedUserID)
{
	ifstream GetWA("WorkerEntry.txt");
	if (GetWA.is_open())
	{
		while (!GetWA.eof())
		{
			GetWA >> registrationID >> username >> password >> auth >> activity;
			if (LoggedUserID == registrationID)
			{
				return auth;
			}
		}
		GetWA.close();
	}
	else FileExp();
}
int Worker::WorkerRecordCheck(string workerusername)
{
	int index = 0;
	ifstream WorkerCheck("WorkerEntry.txt");
	if (WorkerCheck.is_open())
	{
		while (!WorkerCheck.eof())
		{
			WorkerCheck >> registrationID >> username >> password >> auth >> activity;
			if (workerusername == enc.Decryption(username))
			{
				index = 1;
			}
		}
		WorkerCheck.close();
		return index;
	}
	else FileExp();
}
void Worker::FileExp()
{
	system("cls");
	cout << "Dosya a�ma hatas�.Kapat�l�yor...";
	Sleep(2500);
	exit(0);
}