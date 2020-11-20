//MIT License
//Copyright(c) 2020 Semih Aydýn
//UTF - 8
//Display Languague : Turkish

#include "Customer.h"

using namespace std;

int Customer::CustomerRegistration()
{
	index = 0;
	string username, password;

	cout << "Lütfen kullanýcý adý ve þifrenizi belirleyiniz." << endl;
again:
	cout << "Kullanýcý Adý :";
	cin >> username;
	cout << "Þifre :";
	cin >> password;

	if (CustomerRecordCheck(username) == 0)
	{
		registrationID++;
		ofstream AddEntry;
		AddEntry.open("CustomerEntry.txt", ios::app);

		if (AddEntry.is_open())
		{
			AddEntry << registrationID << "\t" << enc.Encryption(username) << "\t" << enc.Encryption(password) << "\t" << "aktif" << "\n";
			AddEntry.close();
			index = 1;
			return index;
		}
		else FileExp(); return index;
	}
	else
	{
		cout << "Girdiðiniz kullanýcý adý daha önceden alýnmýþtýr." << endl;
		goto again;
	}
}
int Customer::CustomerLogin()
{
	int userid, status = 0, account = 0, sum = 0;
	string username, password, activity, _username, _password;
	ifstream CustomerRecordFile("CustomerEntry.txt");

	cout << "Kullanýcý Adý :";
	cin >> _username;
	cout << "Þifre :";
	cin >> _password;

	if (CustomerRecordFile.is_open())
	{

		while (CustomerRecordFile >> userid >> username >> password >> activity)
		{

			if (_username == enc.Decryption(username) && _password == enc.Decryption(password))
			{
				account = 1;

				if (activity == "aktif")
				{
					status = 1;
					LoggedUserID = userid;
				}
				else status = 0;
			}

			sum = account + status;
		}

		return sum;
	}
	else FileExp(); return 0;
}
void Customer::CustomerUserID()
{
	int s = 0;
	string data;
	ifstream IDValue("CustomerEntry.txt");

	if (IDValue.is_open())
	{

		while (!IDValue.eof())
		{
			getline(IDValue, data);
			s++;
		}
		registrationID = s - 1;
		IDValue.close();
	}
	else FileExp();
}
int Customer::CustomerDeregistration(int UserIDValue)
{
	index = 0;
	int deregid = 0, line = 0;
	string dereguser, deregpass, deregactive;
	fstream Dereg;
	ofstream Temp;

	Dereg.open("CustomerEntry.txt", ios::in);
	Temp.open("temp.txt", ios::out);

	if (Dereg.is_open() && Temp.is_open())
	{

		while (!Dereg.eof())
		{
			line++;
			Dereg >> deregid >> dereguser >> deregpass >> deregactive;

			if (UserIDValue == line)
			{
				Temp << deregid << "\t" << dereguser << "\t" << deregpass << "\t" << "inaktif" << "\n";
			}
			else
			{

				if (line <= deregid)
				{
					Temp << deregid << "\t" << dereguser << "\t" << deregpass << "\t" << deregactive << "\n";
				}
			}
		}
		Dereg.close();
		Temp.close();

		if (remove("CustomerEntry.txt") == 0)
		{

			if (rename("temp.txt", "CustomerEntry.txt") == 0)
			{
				index = 1;
			}
		}

		return index;
	}
	else FileExp(); return index;
}
int Customer::CustomerChangePassword(int UserIDValue)
{
	index = 0;
	string NewPassword; int line = 0, changeid = 0;
	fstream ChangeP;
	ofstream Temp;

	cout << "Yeni þifrenizi giriniz :";
	cin >> NewPassword;

	ChangeP.open("CustomerEntry.txt", ios::in);
	Temp.open("temp.txt", ios::out);

	if (ChangeP.is_open() && Temp.is_open())
	{

		while (!ChangeP.eof())
		{
			line++;
			ChangeP >> changeid >> username >> password >> activity;

			if (UserIDValue == line)
			{
				Temp << changeid << "\t" << username << "\t" << enc.Encryption(NewPassword) << "\t" << activity << "\n";
			}
			else
			{

				if (line <= changeid)
				{
					Temp << changeid << "\t" << username << "\t" << password << "\t" << activity << "\n";
				}
			}
		}
		ChangeP.close();
		Temp.close();

		if (remove("CustomerEntry.txt") == 0)
		{

			if (rename("temp.txt", "CustomerEntry.txt") == 0)
			{
				index = 1;
			}
		}

		return index;
	}
	else FileExp(); return index;
}
int Customer::CustomerRecordCheck(string _username)
{
	index = 0;
	ifstream CheckEntry("CustomerEntry.txt");

	if (CheckEntry.is_open())
	{

		while (!CheckEntry.eof())
		{
			CheckEntry >> registrationID >> username >> password >> activity;

			if (_username == username)
			{
				index = 1;
			}
		}
		CheckEntry.close();

		return index;
	}
	else FileExp(); return index;
}
void Customer::FileExp()
{
	system("cls");
	cout << "Dosya açma hatasý.Kapatýlýyor...";
	Sleep(2500);

	exit(0);
}