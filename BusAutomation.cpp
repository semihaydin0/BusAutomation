#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;
class Customer
{
public:
	string activetype;
	int id, LoggedUserID, activityindex;
	Customer() {
		id = 0; LoggedUserID = 0; activityindex = 0; index = 0;
		kadi = ""; sif = ""; activetype = "";
		kullaniciadi = ""; sifre = "";
	}
	void setname(string kullanici) {
		kadi = kullanici;
	}
	void setpass(string sifre) {
		sif = sifre;
	}
	int CustomerEntry()
	{
		cout << "L�tfen kullan�c� ad� ve �ifrenizi belirleyiniz." << endl;
	again:
		cout << "Kullan�c� Ad� :";
		cin >> kullaniciadi;
		cout << "�ifre :";
		cin >> sifre;
		string active = "aktif";
		if (CustomerRecordCheck(kullaniciadi) == 0)
		{
			id++;
			ofstream AddEntry;
			AddEntry.open("CustomerEntry.txt", ios::app);
			if (AddEntry.is_open())
			{
				AddEntry << id << "\t" << kullaniciadi << "\t" << sifre << "\t" << active << "\n";
				AddEntry.close();
				return 1;
			}
			else
			{
				ErrorActions();
			}
		}
		else
		{
			cout << "Girdi�iniz kullan�c� ad� daha �nceden al�nm��t�r." << endl;
			goto again;
		}
	}
	int CustomerLogin()
	{
		int kuid = 0, account = 0, status = 0, sum = 0;
		string kuadi = "", kusifre = "", aktivite = "", active = "aktif", inactive = "inaktif", kadi, sif;
		cout << "Kullan�c� Ad� :";
		cin >> kadi;
		cout << "�ifre :";
		cin >> sif;
		ifstream customerloginfile("CustomerEntry.txt");
		if (customerloginfile.is_open())
		{
			while (customerloginfile >> kuid >> kuadi >> kusifre >> aktivite)
			{
				if (kadi == kuadi && sif == kusifre)
				{
					account = 1;
					if (aktivite == active)
					{
						status = 1;
						LoggedUserID = kuid;
					}
					else status = 0;
				}
				sum = account + status;
			}
			return sum;
		}
		else
		{
			ErrorActions();
		}
	}
	void CustomerUserID()
	{
		int s = 0;
		string data;
		ifstream idvalue("CustomerEntry.txt");
		if (idvalue.is_open())
		{
			while (!idvalue.eof())
			{
				getline(idvalue, data);
				s++;
			}
			id = s - 1;
			idvalue.close();
		}
		else
		{
			ErrorActions();
		}
	}
	int CustomerDeregistration(int UserIDValue)
	{
		int deregid = 0, line = 0;
		string dereguser = "", deregpass = "", deregactive = "";
		fstream Dereg;
		ofstream Temp;
		string deactive = "inaktif";
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
					Temp << deregid << "\t" << dereguser << "\t" << deregpass << "\t" << deactive << "\n";
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
			remove("CustomerEntry.txt");
			rename("temp.txt", "CustomerEntry.txt");
			return 1;
		}
		else
		{
			ErrorActions();
		}
	}
	int CustomerChangePassword(int UserIDValue)
	{
		string NewPassword; int line = 0, changeid = 0;
		string changeuser = "", changepass = "", changeactive = "";
		fstream ChangeP;
		ofstream Temp;
		cout << "Yeni �ifrenizi giriniz :";
		cin >> NewPassword;
		ChangeP.open("CustomerEntry.txt", ios::in);
		Temp.open("temp.txt", ios::out);
		if (ChangeP.is_open() && Temp.is_open())
		{
			while (!ChangeP.eof())
			{
				line++;
				ChangeP >> changeid >> changeuser >> changepass >> changeactive;
				if (UserIDValue == line)
				{
					Temp << changeid << "\t" << changeuser << "\t" << NewPassword << "\t" << changeactive << "\n";
				}
				else
				{
					if (line <= changeid)
					{
						Temp << changeid << "\t" << changeuser << "\t" << changepass << "\t" << changeactive << "\n";
					}
				}
			}
			ChangeP.close();
			Temp.close();
			remove("CustomerEntry.txt");
			rename("temp.txt", "CustomerEntry.txt");
			return 1;
		}
		else
		{
			ErrorActions();
		}
	}
	~Customer() {

	}
private:
	string kullaniciadi, sifre;
	int index;
	int CustomerRecordCheck(string username)
	{
		index = 0;
		ifstream CheckEntry("CustomerEntry.txt");
		if (CheckEntry.is_open())
		{
			while (!CheckEntry.eof())
			{
				CheckEntry >> id >> kadi >> sif >> activetype;
				if (username == kadi)
				{
					index = 1;
				}
			}
			CheckEntry.close();
			return index;
		}
		else
		{
			ErrorActions();
		}
	}
	void ErrorActions()
	{
		system("cls");
		cout << "Dosya a�ma hatas�.Kapat�l�yor...";
		Sleep(2500);
		exit(0);
	}
protected:
	string kadi, sif;
};

class Worker :public Customer
{
public:
	int id; char authsecim; int LoggedWorkerID;
	string workername, workerpass, workerauth, workeractive;
	Worker() {
		id = 0; LoggedWorkerID = 0;
		workername = ""; workerpass = ""; workerauth = ""; workeractive = "";
	}
	string GetUserName() {
		return kadi;
	}
	string GetUserPass() {
		return sif;
	}
	int WorkerEntry()
	{
		string workerkadi, workersif, activetype = "aktif", authority = "";
		cout << "L�tfen �al��an ki�i i�in kullan�c� ad� ve �ifre belirleyiniz." << endl;
	workerentry:
		cout << "Kullan�c� Ad� :";
		cin >> workerkadi;
		setname(workerkadi);
		cout << "�ifre :";
		cin >> workersif;
		setpass(workersif);
	againauthsecim:
		cout << "L�tfen yetki t�r� se�iniz." << endl;
		cout << "1-Tam\n2-Yar�" << endl;
		cout << "Se�iminiz :";
		cin >> authsecim;
		switch (authsecim)
		{
		case '1':authority = "tam";
			break;
		case '2':authority = "yar�";
			break;
		default:cout << "Hatal� se�im yapt�n�z tekrar deneyin.";
			goto againauthsecim;
			break;
		}
		if (AuthorityControl(GetWorkerAuth(LoggedWorkerID), authority) == 1)
		{
			if (WorkerRecordCheck(workerkadi) == 0)
			{
				id++;
				ofstream AddWorkerEntry;
				AddWorkerEntry.open("WorkerEntry.txt", ios::app);
				if (AddWorkerEntry.is_open())
				{
					AddWorkerEntry << id << "\t" << GetUserName() << "\t" << GetUserPass() << "\t" << authority << "\t" << activetype << "\n";
					AddWorkerEntry.close();
					return 1;
				}
				else
				{
					ErrorActions();
				}
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
			cout << "Olu�turmaya �al��t���n�z yetki sizin yetkinizden d���k oldu�u i�in hesap olu�turulamad�." << endl;
			goto workerentry;
		}
	}
	int WorkerLogin()
	{
		int waccount = 0, status = 0, sum = 0;
		string wkadi, wsif, active = "aktif";
		cout << "Kullan�c� Ad� :";
		cin >> wkadi;
		cout << "�ifre :";
		cin >> wsif;
		ifstream WorkerLoginFile("WorkerEntry.txt");
		if (WorkerLoginFile.is_open())
		{
			while (WorkerLoginFile >> id >> workername >> workerpass >> workerauth >> workeractive)
			{
				if (wkadi == workername && workerpass == wsif)
				{
					waccount = 1;
					if (workeractive == active)
					{
						status = 1;
						LoggedWorkerID = id;
					}
					else status = 0;
				}
				sum = waccount + status;
			}
			return sum;
		}
		else
		{
			ErrorActions();
		}
	}
	void GetWorkerID()
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
			id = s - 1;
			GetUser.close();
		}
		else
		{
			ErrorActions();
		}
	}
	int WorkerDeregistration(int WorkerIDValue)
	{
		int workerderegid = 0; int line = 0;
		string dereguser = "", deregpass = "", deregactive = "", deregauth = "", deactive = "inaktif";
		fstream WorkerDereg;
		ofstream Temp;
		WorkerDereg.open("WorkerEntry.txt", ios::in);
		Temp.open("temp.txt", ios::out);
		if (WorkerDereg.is_open() && Temp.is_open())
		{
			while (!WorkerDereg.eof())
			{
				line++;
				WorkerDereg >> workerderegid >> dereguser >> deregpass >> deregauth >> deregactive;
				if (WorkerIDValue == line)
				{
					Temp << workerderegid << "\t" << dereguser << "\t" << deregpass << "\t" << deregauth << "\t" << deactive << "\n";
				}
				else
				{
					if (line <= workerderegid)
					{
						Temp << workerderegid << "\t" << dereguser << "\t" << deregpass << "\t" << deregauth << "\t" << deregactive << "\n";
					}
				}
			}
			WorkerDereg.close();
			Temp.close();
			remove("WorkerEntry.txt");
			rename("temp.txt", "WorkerEntry.txt");
			return 1;
		}
		else
		{
			ErrorActions();
		}
	}
	int WorkerResetPassword(int WorkerIDValue)
	{
		string NewPassword; int line = 0, workerchangeid = 0;
		string wchangeuser = "", wchangepass = "", wauth = "", wchangeactive = "";
		fstream WorkerP;
		ofstream Temp;
		cout << "Yeni �ifrenizi giriniz :";
		cin >> NewPassword;
		WorkerP.open("WorkerEntry.txt", ios::in);
		Temp.open("temp.txt", ios::out);
		if (WorkerP.is_open() && Temp.is_open())
		{
			while (!WorkerP.eof())
			{
				line++;
				WorkerP >> workerchangeid >> wchangeuser >> wchangepass >> wauth >> wchangeactive;
				if (WorkerIDValue == line)
				{
					Temp << workerchangeid << "\t" << wchangeuser << "\t" << NewPassword << "\t" << wauth << "\t" << wchangeactive << "\n";
				}
				else
				{
					if (line <= workerchangeid)
					{
						Temp << workerchangeid << "\t" << wchangeuser << "\t" << wchangepass << "\t" << wauth << "\t" << wchangeactive << "\n";
					}
				}
			}
			WorkerP.close();
			Temp.close();
			remove("WorkerEntry.txt");
			rename("temp.txt", "WorkerEntry.txt");
			return 1;
		}
		else
		{
			ErrorActions();
		}
	}
	int GetAuthControl(int ID)
	{
		int x;
		x = AuthorityControl(GetWorkerAuth(ID), "tam");
		return x;
	}
	~Worker() {

	}
private:
	int AuthorityControl(string personauth, string auth)
	{
		ifstream Control("WorkerEntry.txt");
		if (Control.is_open())
		{
			while (!Control.eof())
			{
				Control >> id >> workername >> workerpass >> workerauth >> workeractive;
				if (personauth == auth || personauth == "tam" && auth == "yar�")
				{
					return 1;
				}
				else return 0;
			}
			Control.close();
		}
		else
		{
			ErrorActions();
		}
	}
	string GetWorkerAuth(int LoggedUserID)
	{
		ifstream GetWA("WorkerEntry.txt");
		if (GetWA.is_open())
		{
			while (!GetWA.eof())
			{
				GetWA >> id >> workername >> workerpass >> workerauth >> workeractive;
				if (LoggedUserID == id)
				{
					return workerauth;
				}
			}
			GetWA.close();
		}
		else
		{
			ErrorActions();
		}
	}
	int WorkerRecordCheck(string workerusername)
	{
		ifstream WorkerCheck("WorkerEntry.txt");
		if (WorkerCheck.is_open())
		{
			while (!WorkerCheck.eof())
			{
				WorkerCheck >> id >> workername >> workerpass >> workerauth >> workeractive;
				if (workerusername == workername)
				{
					return 1;
				}
			}
			return 0;
			WorkerCheck.close();
		}
		else
		{
			ErrorActions();
		}
	}
	void ErrorActions()
	{
		system("cls");
		cout << "Dosya a�ma hatas�.Kapat�l�yor...";
		Sleep(2500);
		exit(0);
	}
};
class Expeditions
{
public:
	Worker w;
	string loc1, loc2, date, time; int price, id, scheme;
	const string Citys[81] = { "Adana", "Ad�yaman", "Afyon","A�r�", "Amasya", "Ankara", "Antalya", "Artvin", "Ayd�n", "Bal�kesir", "Bilecik", "Bing�l", "Bitlis", "Bolu", "Burdur", "Bursa", "�anakkale", "�ank�r�", "�orum", "Denizli", "Diyarbak�r", "Edirne", "Elaz��", "Erzincan", "Erzurum", "Eski�ehir", "Gaziantep", "Giresun", "G�m��hane", "Hakkari", "Hatay", "Isparta", "Mersin", "�stanbul", "�zmir", "Kars", "Kastamonu", "Kayseri", "K�rklareli", "K�r�ehir", "Kocaeli", "Konya", "K�tahya", "Malatya", "Manisa", "Kahramanmara�", "Mardin", "Mu�la", "Mu�", "Nev�ehir", "Ni�de", "Ordu", "Rize", "Sakarya", "Samsun", "Siirt", "Sinop", "Sivas", "Tekirda�", "Tokat", "Trabzon", "Tunceli", "�anl�urfa", "U�ak", "Van", "Yozgat", "Zonguldak", "Aksaray", "Bayburt","Karaman", "K�r�kkale", "Batman", "��rnak","Bart�n", "Ardahan", "I�d�r", "Yalova", "Karab�k", "Kilis", "Osmaniye", "D�zce" };
	Expeditions() {
		loc1 = ""; loc2 = ""; date = ""; time = "";
		price = 0; id = 0; scheme = 0;
	}
	int AddExpedition()
	{
		int location1, location2, day, month, year, price1, scheme1;
		float when;
		string first, second, date1, time1, id1;
		int schemeselec;
	ExpeditionsAGAIN1:
		cout << "Kalk�� yerinin plakas�n� giriniz :";
		cin >> location1;
		cout << "Var�� yerinin plakas�n� giriniz :";
		cin >> location2;
		if (location1 < 1 || location1 > 81 || location1 == 0 && location2 < 1 || location2 > 81 || location2 == 0)
		{
			system("cls");
			cout << "Ge�ersiz plaka giri�i yapt�n�z.Tekrar se�iniz." << endl;
			goto ExpeditionsAGAIN1;
		}
		else
		{
			first = Citys[location1 - 1];
			second = Citys[location2 - 1];
			if (first == second)
			{
				system("cls");
				cout << "Kalk�� ve var�� yerleri ayn� olamaz.Tekrar se�iniz." << endl;
				goto ExpeditionsAGAIN1;
			}
		ExpeditionsAGAIN2:
			cout << "Sefer g�n�n� giriniz :";
			cin >> day;
			if (day <= 31 && day >= 1)
			{
			ExpeditionsAGAIN3:
				cout << "Sefer ay�n� giriniz :";
				cin >> month;
				if (month <= 12 && month >= 1)
				{
				ExpeditionsAGAIN4:
					cout << "Sefer y�l�n�z giriniz :";
					cin >> year;
					if (year >= 2020)
					{
						stringstream a, b, c, d;
						a << day; b << month; c << year;
						date1 = a.str() + "." + b.str() + "." + c.str();
					ExpeditionsAGAIN5:
						cout << "Sefer saatini giriniz.(�rne�in 17.30) :";
						cin >> time1;
						stringstream con(time1);
						con >> when;
						if (when >= 00.00 && when <= 23.59)
						{
						ExpeditionsAGAIN6:
							cout << "Fiyat giriniz :";
							cin >> price1;
							if (price1 >= 1)
							{
							ExpeditionsAGAIN7:
								cout << "Koltuk d�zeni se�iniz." << endl;
								cout << "1-2+2\n2-2+1" << endl;
								cout << "Se�iminiz :";
								cin >> schemeselec;
								switch (schemeselec)
								{
								case 1:
									scheme1 = 46;
									break;
								case 2:
									scheme1 = 38;
									break;
								default:cout << "Hatal� giri� yapt�n�z.Tekrar se�iniz." << endl;
									goto ExpeditionsAGAIN7;
									break;
								}
								if (CheckExpeditionEntry(first, second, date1, time1, price1, scheme1) == 0)
								{
									id++;
									ofstream AddExpeditionsEntry;
									AddExpeditionsEntry.open("ExpeditionEntry.txt", ios::app);
									if (AddExpeditionsEntry.is_open())
									{
										AddExpeditionsEntry << id << "\t" << first << "\t" << second << "\t" << date1 << "\t" << time1 << "\t" << price1 << "\t" << scheme1 << "\n";
										AddExpeditionsEntry.close();
										return 1;
									}
									else
									{
										ErrorActions();
									}
								}
								else
								{
									system("cls");
									cout << "Olu�turmaya �al��t���n�z sefer halihaz�rda mevcuttur.�lk k�sma y�nlendiriliyorsunuz..." << endl;
									goto ExpeditionsAGAIN1;
								}
							}
							else
							{
								cout << "Hatal� fiyat girdiniz.Tekrar se�iniz." << endl;
								goto ExpeditionsAGAIN6;
							}
						}
						else
						{
							cout << "Hatal� saat girdiniz.Tekrar se�iniz." << endl;
							goto ExpeditionsAGAIN5;
						}
					}
					else
					{
						cout << "2020 y�l� �ncesine sefer olu�turulamaz.Tekrar se�iniz." << endl;
						goto ExpeditionsAGAIN4;
					}
				}
				else
				{
					cout << "Hatal� ay se�imi yapt�n�z.Tekrar se�iniz." << endl;
					goto ExpeditionsAGAIN3;
				}
			}
			else
			{
				cout << "Hatal� g�n se�imi yapt�n�z.Tekrar se�iniz." << endl;
				goto ExpeditionsAGAIN2;
			}
		}
	}
	int EditExpedition(int LoggedWorkerID)
	{
		int workerid, sfrid, line = 0, editselec, day, month, year, NewPrice; float when;
		string wname, wpass, wauth, wactive, fullcontrol = "tam", edittime, NewDate, NewTime;
		string lone, ltwo, locdate, loctime; int locprice, locseat;
		stringstream a, b, c, d, con;
		fstream ExP;
		ofstream Temp;
		ifstream Check("WorkerEntry.txt");
		if (Check.is_open())
		{
			while (!Check.eof())
			{
				Check >> workerid >> wname >> wpass >> wauth >> wactive;
				if (LoggedWorkerID == workerid)
				{
					if (wauth == fullcontrol)
					{
						Check.close();
						cout << "D�zenlemek istedi�iniz sefer id bilgisini giriniz :";
						cin >> sfrid;
						ifstream ExCheck("ExpeditionEntry.txt");
						if (ExCheck.is_open())
						{
							while (!ExCheck.eof())
							{
								ExCheck >> id >> loc1 >> loc2 >> date >> time >> price >> scheme;
								if (sfrid == id)
								{
									lone = loc1; ltwo = loc2; locdate = date; loctime = time; locprice = price; locseat = scheme;
									ExCheck.close();
								ExpeditionsAGAIN1:
									cout << "L�tfen d�zenlemek istedi�iniz k�sm� se�iniz." << endl;
									cout << "1-Tarih\n2-Saat\n3-Fiyat" << endl;
									cout << "Se�iminiz :";
									cin >> editselec;
									switch (editselec)
									{
									case 1:
										system("cls");
									ExpeditionsAGAIN2:
										cout << "Sefer g�n�n� giriniz :";
										cin >> day;
										if (day <= 31 && day >= 1)
										{
										ExpeditionsAGAIN3:
											cout << "Sefer ay�n� giriniz :";
											cin >> month;
											if (month <= 12 && month >= 1)
											{
											ExpeditionsAGAIN4:
												cout << "Sefer y�l�n�z giriniz :";
												cin >> year;
												if (year >= 2020)
												{
													a << day; b << month; c << year;
													NewDate = a.str() + "." + b.str() + "." + c.str();
													if (CheckExpeditionEntry(lone, ltwo, NewDate, loctime, locprice, locseat) == 0)
													{
														ExP.open("ExpeditionEntry.txt", ios::in);
														Temp.open("temp.txt", ios::out);
														if (ExP.is_open() && Temp.is_open())
														{
															while (!ExP.eof())
															{
																line++;
																ExP >> id >> loc1 >> loc2 >> date >> time >> price >> scheme;
																if (sfrid == line)
																{
																	Temp << id << "\t" << loc1 << "\t" << loc2 << "\t" << NewDate << "\t" << time << "\t" << price << "\t" << scheme << "\n";
																}
																else
																{
																	if (line <= id)
																	{
																		Temp << id << "\t" << loc1 << "\t" << loc2 << "\t" << date << "\t" << time << "\t" << price << "\t" << scheme << "\n";
																	}
																}
															}
															ExP.close();
															Temp.close();
															remove("ExpeditionEntry.txt");
															rename("temp.txt", "ExpeditionEntry.txt");
															return 1;
														}
														else
														{
															ErrorActions();
														}
													}
													else
													{
														system("cls");
														cout << "Ayn� sefer zaten olu�turulmu�.Tekrar deneyin." << endl;
														a.str(""); b.str(""); c.str("");
														goto ExpeditionsAGAIN1;
													}

												}
												else
												{
													cout << "2020 y�l� �ncesine sefer olu�turulamaz.Tekrar se�iniz." << endl;
													goto ExpeditionsAGAIN4;
												}
											}
											else
											{
												cout << "Hatal� ay se�imi yapt�n�z.Tekrar se�iniz." << endl;
												goto ExpeditionsAGAIN3;
											}
										}
										else
										{
											cout << "Hatal� g�n se�imi yapt�n�z.Tekrar se�iniz." << endl;
											goto ExpeditionsAGAIN2;
										}
										break;
									case 2:
										system("cls");
									ExpeditionsAGAIN5:
										cout << "Sefer saatini giriniz.(�rne�in 17.30) :";
										cin >> NewTime;
										con << NewTime;
										con >> when;
										if (when >= 00.00 && when <= 23.59)
										{
											if (CheckExpeditionEntry(lone, ltwo, locdate, NewTime, locprice, locseat) == 0)
											{
												ExP.open("ExpeditionEntry.txt", ios::in);
												Temp.open("temp.txt", ios::out);
												if (ExP.is_open() && Temp.is_open())
												{
													while (!ExP.eof())
													{
														line++;
														ExP >> id >> loc1 >> loc2 >> date >> time >> price >> scheme;
														if (sfrid == line)
														{
															Temp << id << "\t" << loc1 << "\t" << loc2 << "\t" << date << "\t" << NewTime << "\t" << price << "\t" << scheme << "\n";
														}
														else
														{
															if (line <= id)
															{
																Temp << id << "\t" << loc1 << "\t" << loc2 << "\t" << date << "\t" << time << "\t" << price << "\t" << scheme << "\n";
															}
														}
													}
													ExP.close();
													Temp.close();
													remove("ExpeditionEntry.txt");
													rename("temp.txt", "ExpeditionEntry.txt");
													return 1;
												}
												else
												{
													ErrorActions();
												}
											}
											else
											{
												system("cls");
												cout << "Ayn� sefer zaten olu�turulmu�.Tekrar deneyin." << endl;
												con.str("");
												goto ExpeditionsAGAIN1;
											}
										}
										else
										{
											cout << "Hatal� saat girdiniz.Tekrar se�iniz." << endl;
											goto ExpeditionsAGAIN5;
										}
										break;
									case 3:
										system("cls");
									ExpeditionsAGAIN6:
										cout << "Fiyat giriniz :";
										cin >> NewPrice;
										if (price > 0)
										{
											if (CheckExpeditionEntry(lone, ltwo, locdate, loctime, NewPrice, locseat) == 0)
											{
												ExP.open("ExpeditionEntry.txt", ios::in);
												Temp.open("temp.txt", ios::out);
												if (ExP.is_open() && Temp.is_open())
												{
													while (!ExP.eof())
													{
														line++;
														ExP >> id >> loc1 >> loc2 >> date >> time >> price >> scheme;
														if (sfrid == line)
														{
															Temp << id << "\t" << loc1 << "\t" << loc2 << "\t" << date << "\t" << time << "\t" << NewPrice << "\t" << scheme << "\n";
														}
														else
														{
															if (line <= id)
															{
																Temp << id << "\t" << loc1 << "\t" << loc2 << "\t" << date << "\t" << time << "\t" << price << "\t" << scheme << "\n";
															}
														}
													}
													ExP.close();
													Temp.close();
													remove("ExpeditionEntry.txt");
													rename("temp.txt", "ExpeditionEntry.txt");
													return 1;
												}
												else
												{
													ErrorActions();
												}
											}
											else
											{
												system("cls");
												cout << "Ayn� sefer zaten olu�turulmu�.Tekrar deneyin." << endl;
												goto ExpeditionsAGAIN1;
											}
										}
										else
										{
											cout << "Hatal� fiyat girdiniz.Tekrar giriniz." << endl;
											goto ExpeditionsAGAIN6;
										}
										break;
									default:
										cout << "Hatal� se�im yapt�n�z.Tekrar se�iniz." << endl;
										goto ExpeditionsAGAIN1;
										break;
									}
								}
							}
							system("cls");
							cout << "Girdi�iniz sefer id'ye ait sefer bulunamad�." << endl;
							ExCheck.close();
						}
						else
						{
							ErrorActions();
						}
					}
					else
					{
						system("cls");
						cout << "Hesab�n�z�n yetkisi bu i�lem i�in yeterli de�ildir." << endl;
					}
				}
			}
		}
		else
		{
			ErrorActions();
		}
	}
	void GetExID()
	{
		int s = 0;
		string data;
		ifstream GetID("ExpeditionEntry.txt");
		if (GetID.is_open())
		{
			while (!GetID.eof())
			{
				getline(GetID, data);
				s++;
			}
			id = s - 1;
			GetID.close();
		}
		else
		{
			ErrorActions();
		}
	}
	~Expeditions() {

	}
private:
	int CheckExpeditionEntry(string kalkis, string varis, string tarih, string saat, int fiyat, int koltuk)
	{
		string id, loc1, loc2, date, time;
		int price;
		ifstream CheckExped("ExpeditionEntry.txt");
		if (CheckExped.is_open())
		{
			while (!CheckExped.eof())
			{
				CheckExped >> id >> loc1 >> loc2 >> date >> time >> price >> scheme;
				if (kalkis == loc1 && varis == loc2 && tarih == date && saat == time && fiyat == price && koltuk == scheme)
				{
					return 1;
				}
			}
			return 0;
			CheckExped.close();
		}
		else
		{
			ErrorActions();
		}
	}
	void ErrorActions()
	{
		system("cls");
		cout << "Dosya a�ma hatas�.Kapat�l�yor...";
		Sleep(2500);
		exit(0);
	}
};
class Tickets
{
public:
	Expeditions e;
	Customer c;
	Worker w;
	int id, customerid, seferid, koltuk, sayi;
	Tickets() {
		id = 0; customerid = 0; seferid = 0; koltuk = 0; sayi = 0;
	}
	int AddTicket(int UserID)
	{
		ifstream ExpList("ExpeditionEntry.txt");
		int CustomerID = 0, ExpeditionID = 0, SeatNo = 0; int CustomerChoose, location1, location2, CustomerSecim, CustomerSecim2, SelectedSeat;
		string kalkis, varis; int sfrid[50]; int sfrsayisi[50];
	TicketAGAIN:
		cout << "1-Sefer Ara\n2-Listeden Se�" << endl;
		cout << "Se�iminiz :";
		cin >> CustomerSecim;
		switch (CustomerSecim)
		{
		case 1:
			system("cls");
		TicketAGAIN2:
			cout << "Kalk�� yerinin plakas�n� giriniz :";
			cin >> location1;
			cout << "Var�� yerinin plakas�n� giriniz :";
			cin >> location2;
			if (location1 < 1 || location1 > 81 || location1 == 0 && location2 < 1 || location2 > 81 || location2 == 0)
			{
				system("cls");
				cout << "Ge�ersiz plaka giri�i yapt�n�z.Tekrar se�iniz." << endl;
				goto TicketAGAIN2;
			}
			else
			{
				kalkis = e.Citys[location1 - 1];
				varis = e.Citys[location2 - 1];
				if (kalkis == varis)
				{
					system("cls");
					cout << "Kalk�� ve var�� yerleri ayn� olamaz.Tekrar se�iniz." << endl;
					goto TicketAGAIN2;
				}
				else
				{
				TicketAGAIN3:
					sayi = 0;
					cout << "---Seferler---" << endl;
					string data; int sayi = 0;
					if (ExpList.is_open())
					{
						while (ExpList >> e.id >> e.loc1 >> e.loc2 >> e.date >> e.time >> e.price >> e.scheme)
						{
							if (e.loc1 == kalkis && e.loc2 == varis)
							{
								sfrsayisi[sayi] = sayi + 1;
								sfrid[sayi] = e.id;
								sayi++;
								if (e.scheme == 46)
								{
									cout << sayi << "-" << e.loc1 << "-" << e.loc2 << " " << e.date << "-" << e.time << " " << "2+2" << " " << e.price << "TL" << "\n";
								}
								else
								{
									cout << sayi << "-" << e.loc1 << "-" << e.loc2 << " " << e.date << "-" << e.time << " " << "2+1" << " " << e.price << "TL" << "\n";
								}
							}
						}
						ExpList.close();
						if (sayi == 0)
						{
							system("cls");
							cout << "Arad���n�z kriterlere g�re sefer bulunamad�." << endl;
							goto TicketAGAIN;
						}
						else
						{
							cout << "Se�iminiz :";
							cin >> CustomerSecim2;
							int status = 0;
							for (int i = 0; i < sayi; i++)
							{
								if (sfrsayisi[i] == CustomerSecim2)
								{
									status = 1;
									CustomerChoose = sfrid[i];
								}
							}
							if (status == 1)
							{
								SelectedSeat = Seats(CustomerChoose);
								id++;
								ofstream AddTicketEntry;
								AddTicketEntry.open("TicketEntry.txt", ios::app);
								if (AddTicketEntry.is_open())
								{
									AddTicketEntry << id << "\t" << UserID << "\t" << CustomerChoose << "\t" << SelectedSeat << "\n";
									AddTicketEntry.close();
									return 1;
								}
								else
								{
									ErrorActions();
								}
							}
							else
							{
								system("cls");
								cout << "Hatal� se�im yapt�n�z.Tekrar se�iniz." << endl;
								goto TicketAGAIN3;
							}
						}
					}
					else
					{
						ErrorActions();
					}
				}
			}
			break;
		case 2:
			system("cls");
		TicketAGAIN4:
			sayi = 0;
			cout << "---Seferler---" << endl;
			if (ExpList.is_open())
			{
				while (ExpList >> e.id >> e.loc1 >> e.loc2 >> e.date >> e.time >> e.price >> e.scheme)
				{
					sfrsayisi[sayi] = sayi + 1;
					sfrid[sayi] = e.id;
					sayi++;
					if (e.scheme == 46)
					{
						cout << sayi << "-" << e.loc1 << "-" << e.loc2 << " " << e.date << "-" << e.time << " " << "2+2" << " " << e.price << "TL" << "\n";
					}
					else
					{
						cout << sayi << "-" << e.loc1 << "-" << e.loc2 << " " << e.date << "-" << e.time << " " << "2+1" << " " << e.price << "TL" << "\n";
					}
				}
				ExpList.close();
				if (sayi == 0)
				{
					system("cls");
					cout << "Sefer bulunamad�." << endl;
					goto TicketAGAIN;
				}
				else
				{
					cout << "Se�iminiz :";
					cin >> CustomerSecim2;
					int status = 0;
					for (int i = 0; i < sayi; i++)
					{
						if (sfrsayisi[i] == CustomerSecim2)
						{
							status = 1;
							CustomerChoose = sfrid[i];
						}
					}
					if (status == 1)
					{
						SelectedSeat = Seats(CustomerChoose);
						id++;
						ofstream AddTicketEntry;
						AddTicketEntry.open("TicketEntry.txt", ios::app);
						if (AddTicketEntry.is_open())
						{
							AddTicketEntry << id << "\t" << UserID << "\t" << CustomerChoose << "\t" << SelectedSeat << "\n";
							AddTicketEntry.close();
							return 1;
						}
						else
						{
							ErrorActions();
						}
					}
					else
					{
						system("cls");
						cout << "Hatal� se�im yapt�n�z.Tekrar se�iniz." << endl;
						goto TicketAGAIN4;
					}
				}
			}
			else
			{
				ErrorActions();
			}
			break;
		default:
			system("cls");
			cout << "Hatal� tu�lama ger�ekle�tirdiniz.Tekrar se�iniz." << endl;
			goto TicketAGAIN;
			break;
		}
	}
	int EditTicket()
	{
		int ticket; int status = 0; int kltk; int Choose; int sfr;
	EditAGAIN:
		cout << "D�zenlemek istedi�iniz bilet id bilgisini giriniz :";
		cin >> ticket;
		ifstream TicketData("TicketEntry.txt");
		fstream ChangeT;
		ofstream Temp;
		if (TicketData.is_open())
		{
			while (TicketData >> id >> customerid >> seferid >> koltuk)
			{
				if (ticket == id)
				{
					status = 1;
					kltk = koltuk;
					sfr = seferid;
				}
			}
			TicketData.close();
			if (status == 1)
			{
				int line = 0;
				cout << "Sadece koltuk bilgilerini de�i�tirebilirsiniz." << endl;
				cout << "Mevcut koltuk numaras� :" << kltk << endl;
				Choose = Seats(sfr);
				ChangeT.open("TicketEntry.txt", ios::in);
				Temp.open("temp.txt", ios::out);
				if (ChangeT.is_open() && Temp.is_open())
				{
					while (!ChangeT.eof())
					{
						line++;
						ChangeT >> id >> customerid >> seferid >> koltuk;
						if (ticket == id)
						{
							Temp << id << "\t" << customerid << "\t" << seferid << "\t" << Choose << "\n";
						}
						else
						{
							if (line <= id)
							{
								Temp << id << "\t" << customerid << "\t" << seferid << "\t" << koltuk << "\n";
							}
						}
					}
					ChangeT.close();
					Temp.close();
					remove("TicketEntry.txt");
					rename("temp.txt", "TicketEntry.txt");
					return 1;
				}
				else
				{
					ErrorActions();
				}
			}
			else
			{
				system("cls");
				cout << "Girilen bilet id sine ait kay�t bulunamad�." << endl;
				goto EditAGAIN;
			}
		}
		else
		{
			ErrorActions();
		}
	}
	int DeletingTicket(int LoggedWorkerID)
	{
		int tid; int status = 0;
	DeleteAGAIN:
		if (w.GetAuthControl(LoggedWorkerID) == 1)
		{
			cout << "Silmek istedi�iniz bilet id bilgisini giriniz :";
			cin >> tid;
			ifstream TicketData("TicketEntry.txt");
			fstream DeleteT;
			ofstream Temp;
			if (TicketData.is_open())
			{
				while (TicketData >> id >> customerid >> seferid >> koltuk)
				{
					if (tid == id)
					{
						status = 1;
					}
				}
				TicketData.close();
				if (status == 1)
				{
					DeleteT.open("TicketEntry.txt", ios::in);
					Temp.open("temp.txt", ios::out);
					if (DeleteT.is_open() && Temp.is_open())
					{
						while (!DeleteT.eof())
						{
							DeleteT >> id >> customerid >> seferid >> koltuk;
							if (tid != id)
							{
								Temp << id << "\t" << customerid << "\t" << seferid << "\t" << koltuk << "\n";
							}
						}
						DeleteT.close();
						Temp.close();
						remove("TicketEntry.txt");
						rename("temp.txt", "TicketEntry.txt");
						return 1;
					}
					else
					{
						ErrorActions();
					}
				}
				else
				{
					system("cls");
					cout << "Girilen bilet id sine ait kay�t bulunamad�." << endl;
					goto DeleteAGAIN;
				}
			}
			else
			{
				ErrorActions();
			}
		}
		else
		{
			system("cls");
			cout << "Yetkiniz bu i�lem i�in yeterli de�ildir." << endl;
			return 0;
		}
	}
	void GetTicketID()
	{
		int s = 0;
		string data;
		ifstream idvalue("TicketEntry.txt");
		if (idvalue.is_open())
		{
			while (!idvalue.eof())
			{
				getline(idvalue, data);
				s++;
			}
			id = s - 1;
			idvalue.close();
		}
		else
		{
			ErrorActions();
		}
	}
	int Seats(int sfrid)
	{
		int layaot = 0; int Choose;
		int koltuklar[46];
		ifstream Seats("ExpeditionEntry.txt");
		ifstream CheckTickets("TicketEntry.txt");
		if (Seats.is_open())
		{
			while (Seats >> e.id >> e.loc1 >> e.loc2 >> e.date >> e.time >> e.price >> e.scheme)
			{
				if (sfrid == e.id)
				{
					layaot = e.scheme;
				}
			}
			Seats.close();
			if (CheckTickets.is_open())
			{
				int a = 0;
				while (!CheckTickets.eof())
				{
					CheckTickets >> id >> customerid >> seferid >> koltuk;
					if (sfrid == seferid)
					{
						koltuklar[a] = koltuk;
						a++;
					}
				}
				CheckTickets.close();
				int status;
			CustomerChoose:
				if (layaot == 46)
				{
					for (int i = 0; i < 12; i++)
					{
						for (int x = 0; x < 4; x++)
						{
							status = 0;
							for (int j = 0; j <= a; j++)
							{
								if (koltuklar[j] == i * 4 + x + 1)
								{
									status = 1;
								}
							}
							if (status != 1 && i * 4 + x + 1 <= 46)
							{
								cout << i * 4 + x + 1 << "\t";
							}
							else
							{
								cout << "\t";
							}
						}
						cout << "\n";
					}
					cout << "L�tfen koltuk se�imi yap�n�z." << endl;
					cout << "Se�iminiz :";
					cin >> Choose;
					status = 0;
					for (int i = 0; i <= a; i++)
					{
						for (int x = 0; x < 4; x++)
						{
							for (int j = 0; j <= a; j++)
							{
								if (koltuklar[j] == Choose)
								{
									status = 1;
								}
							}
						}
					}
					if (Choose < 1 || Choose>46)
					{
						system("cls");
						cout << "Ge�ersiz koltuk se�imi.Tekrar se�iniz." << endl;
						goto CustomerChoose;
					}
					else if (status == 1)
					{
						system("cls");
						cout << "Bu koltuk daha �nceden se�ilmi�tir." << endl;
						goto CustomerChoose;
					}
					else
					{
						return Choose;
					}
				}
				else
				{
					for (int i = 0; i < 10; i++)
					{
						for (int x = 0; x < 4; x++)
						{
							status = 0;
							for (int j = 0; j <= a; j++)
							{
								if (koltuklar[j] == i * 4 + x + 1)
								{
									status = 1;
								}
							}
							if (status != 1 && i * 4 + x + 1 <= 38)
							{
								cout << i * 4 + x + 1 << "\t";
							}
							else
							{
								cout << "\t";
							}
						}
						cout << "\n";
					}
					cout << "L�tfen koltuk se�imi yap�n�z." << endl;
					cout << "Se�iminiz :";
					cin >> Choose;
					status = 0;
					for (int i = 0; i <= a; i++)
					{
						for (int x = 0; x < 4; x++)
						{
							for (int j = 0; j <= a; j++)
							{
								if (koltuklar[j] == Choose)
								{
									status = 1;
								}
							}
						}
					}
					if (Choose < 1 || Choose>38)
					{
						system("cls");
						cout << "Ge�ersiz koltuk se�imi.Tekrar se�iniz." << endl;
						goto CustomerChoose;
					}
					else if (status == 1)
					{
						system("cls");
						cout << "Bu koltuk daha �nceden se�ilmi�tir." << endl;
						goto CustomerChoose;
					}
					else
					{
						return Choose;
					}
				}
			}
			else
			{
				ErrorActions();
			}
		}
		else
		{
			ErrorActions();
		}
	}
	~Tickets() {

	}
private:
	int ticketid, userid, sfrid, seat, a;
	void ErrorActions()
	{
		system("cls");
		cout << "Dosya a�ma hatas�.Kapat�l�yor...";
		Sleep(2500);
		exit(0);
	}
	friend void CustomerTickets(int UserID);
};
void CustomerTickets(int UserID)
{
	Expeditions e;
	Tickets t;
	int sfrs[50];
	int seats[50];
	ifstream UserTickets("TicketEntry.txt");
	if (UserTickets.is_open())
	{
		t.a = 0;
		while (UserTickets >> t.ticketid >> t.userid >> t.sfrid >> t.seat)
		{
			if (UserID == t.userid)
			{
				sfrs[t.a] = t.sfrid;
				seats[t.a] = t.seat;
				t.a++;
			}
		}
		UserTickets.close();
		if (t.a == 0)
		{
			cout << "Bu hesaba ait bilet bilgileri bulunamad�." << endl;
		}
		else
		{
			ifstream UserExpData("ExpeditionEntry.txt");
			if (UserExpData.is_open())
			{
				int b = 0;
				while (UserExpData >> e.id >> e.loc1 >> e.loc2 >> e.date >> e.time >> e.price >> e.scheme)
				{
					for (int i = 0; i < t.a; i++)
					{
						if (sfrs[i] == e.id)
						{
							b++;
							cout << b << "-" << e.loc1 << "-" << e.loc2 << "\t" << e.date << "-" << e.time << "\t" << "Koltuk No:" << seats[i] << "\n";
						}
					}
				}
				cout << "Toplamda " << t.a << " adet kay�t bulundu." << endl;
			}
			else
			{
				t.ErrorActions();
			}
		}
	}
	else
	{
		t.ErrorActions();
	}
}
int main()
{
	setlocale(LC_ALL, "Turkish");
	int secim, hak = 3, result = 0;
	cout << "Merhaba , otomasyona ho�geldiniz l�tfen se�im yap�n�z." << endl;
MainMenu:
	cout << "1-M��teri Giri�i" << "\n" << "2-Yetkili Giri�i" << "\n" << "3-M��teri Kayd�" << "\n" << "9-��k��" << endl;
	cout << "Se�iminiz :";
	cin >> secim;
	Tickets t;
	Expeditions e;
	Customer c;
	Worker w;
	do
	{
		switch (secim)
		{
		case 1:
			system("cls");
		CustomerLoginAGAIN:
			result = c.CustomerLogin();
			if (result == 2)
			{
				system("cls");
				cout << "Giri� ba�ar�l�.M��teri paneline y�nlendiriliyor..." << endl;
				Sleep(2000);
				system("cls");
				int CustomerSecim1;
			CustomerAGAIN1:
				cout << "-----M��teri Paneli-----" << endl;
				cout << "1-Bilet Al" << endl;
				cout << "2-Biletlerim" << endl;
				cout << "3-��k�� Yap" << endl;
				cout << "9-Kullan�c� ��lemleri" << endl;
				cout << "Se�iminiz :";
				cin >> CustomerSecim1;
				switch (CustomerSecim1)
				{
				case 1:
					system("cls");
					t.GetTicketID();
					if (t.AddTicket(c.LoggedUserID) == 1)
					{
						system("cls");
						cout << "Bilet al�m� ba�ar�yla ger�ekle�tirildi." << endl;
						goto CustomerAGAIN1;
					}
					break;
				case 2:
					system("cls");
					int secim;
					CustomerTickets(c.LoggedUserID);
				CustomerAGAINx:
					cout << "Geri d�nmek i�in 9 tu�una bas�n�z :";
					cin >> secim;
					if (secim != 9)
					{
						cout << "Hatal� tu�lama yapt�n�z." << endl;
						goto CustomerAGAINx;
					}
					else
					{
						system("cls");
						goto CustomerAGAIN1;
					}
					break;
				case 3:
					system("cls");
					cout << "��k�� yap�ld�..." << endl;
					goto MainMenu;
					break;
				case 9:system("cls");
					int CustomerSecim2;
				CustomerAGAIN2:
					cout << "---Kullan�c� ��lemleri---" << endl;
					cout << "1-�ifre G�ncelleme" << endl;
					cout << "2-Hesap Kapatma" << endl;
					cout << "Se�iminiz :";
					cin >> CustomerSecim2;
					switch (CustomerSecim2)
					{
					case 1:
						if (c.CustomerChangePassword(c.LoggedUserID) == 1)
						{
							cout << "�ifre de�i�tirme i�lemi ba�ar�yla tamamland�.Ana men�ye geri d�n�l�yor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					case 2:
						if (c.CustomerDeregistration(c.LoggedUserID) == 1)
						{
							cout << "Hesap kapatma i�lemi ba�ar�yla tamamland�.Ana men�ye geri d�n�l�yor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					default:
						system("cls");
						cout << "Hatal� se�im yapt�n�z.L�tfen tekrar se�im yap�n�z" << endl;
						goto CustomerAGAIN2;
						break;
					}
					break;
				default:cout << "Hatal� se�im yapt�n�z.L�tfen tekrar se�im yap�n�z" << endl;
					goto CustomerAGAIN1;
					break;
				}
			}
			else if (result == 1)
			{
				system("cls");
				cout << "Bu m��teri hesab� kapat�lm��t�r.Ana men�ye y�nlendiriliyorsunuz..." << endl;
				Sleep(2500);
				system("cls");
				goto MainMenu;
			}
			else
			{
				system("cls");
				hak--;
				cout << "Giri� ba�ar�s�z" << endl;
				cout << "Kalan hak say�n�z : " << hak << endl;
				if (hak == 0)
				{
					cout << "�ok fazla hatal� oturum a�ma giri�iminde bulundunuz.Program kapat�l�yor.";
					Sleep(2500);
					exit(0);
				}
				else
				{
					goto CustomerLoginAGAIN;
				}
			}
			break;
		case 2:
			system("cls");
		WorkerLoginAGAIN:
			result = w.WorkerLogin();
			if (result == 2)
			{
				system("cls");
				cout << "Giri� ba�ar�l�.Yetkili paneline y�nlendiriliyor..." << endl;
				Sleep(2000);
				system("cls");
			WorkerAGAIN1:
				cout << "-----Yetkili Paneli-----" << endl;
				cout << "1-Sefer Ekle" << endl;
				cout << "2-Sefer D�zenle" << endl;
				cout << "3-Bilet ��lemleri" << endl;
				cout << "4-��k�� Yap" << endl;
				cout << "9-Yetkili ��lemleri" << endl;
				int WorkerSecim1, WorkerSecim2;
				cout << "Se�iminiz :";
				cin >> WorkerSecim1;
				switch (WorkerSecim1)
				{
				case 1:
					system("cls");
					e.GetExID();
					if (e.AddExpedition() == 1)
					{
						system("cls");
						cout << "Sefer ekleme i�leminiz ba�ar�yla ger�ekle�tirildi." << endl;
						goto WorkerAGAIN1;
					}
					break;
				case 2:
					system("cls");
					if (e.EditExpedition(w.LoggedWorkerID) == 1)
					{
						system("cls");
						cout << "Sefer d�zenleme i�lemi ba�ar�yla tamamland�." << endl;
						goto WorkerAGAIN1;
					}
					else
					{
						goto WorkerAGAIN1;
					}
					break;
				case 3:
					system("cls");
					cout << "---Bilet ��lemleri---" << endl;
					cout << "1-Bilet D�zenleme" << endl;
					cout << "2-Bilet Sil" << endl;
					cout << "Se�iminiz :";
					cin >> WorkerSecim2;
					switch (WorkerSecim2)
					{
					case 1:
						system("cls");
						if (t.EditTicket() == 1)
						{
							system("cls");
							cout << "Bilet d�zenleme i�lemi ba�ar�l�." << endl;
							goto WorkerAGAIN1;
						}
						break;
					case 2:
						system("cls");
						if (t.DeletingTicket(w.LoggedWorkerID) == 1)
						{
							system("cls");
							cout << "Bilet silme i�lemi ba�ar�yla tamamland�." << endl;
							goto WorkerAGAIN1;
						}
						else
						{
							goto WorkerAGAIN1;
						}
						break;
					default:
						break;
					}
					break;
				case 4:
					system("cls");
					cout << "��k�� yap�ld�..." << endl;
					goto MainMenu;
					break;
				case 9:
					system("cls");
				WorkerAGAIN2:
					cout << "---Yetkili ��lemleri---" << endl;
					cout << "1-�ifre G�ncelleme" << endl;
					cout << "2-Hesap Kapatma" << endl;
					cout << "3-Yeni �al��an Kayd� Ekle" << endl;
					cout << "Se�iminiz :";
					cin >> WorkerSecim2;
					switch (WorkerSecim2)
					{
					case 1:
						system("cls");
						if (w.WorkerResetPassword(w.LoggedWorkerID) == 1)
						{
							cout << "�ifre de�i�tirme i�lemi ba�ar�yla tamamland�.Ana men�ye geri d�n�l�yor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					case 2:
						system("cls");
						if (w.WorkerDeregistration(w.LoggedWorkerID) == 1)
						{
							cout << "Hesap kapatma i�lemi ba�ar�yla tamamland�.Ana men�ye geri d�n�l�yor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					case 3:
						system("cls");
						w.GetWorkerID();
						if (w.WorkerEntry() == 1)
						{
							system("cls");
							cout << "Kay�t i�leminiz ba�ar�yla ger�ekle�tirildi." << endl;
							goto WorkerAGAIN1;
						}
						break;
					default:system("cls");
						cout << "Hatal� se�im yapt�n�z.L�tfen tekrar se�im yap�n�z" << endl;
						goto WorkerAGAIN2;
						break;
					}
					break;
				default:system("cls");
					cout << "Hatal� se�im yapt�n�z.L�tfen tekrar se�im yap�n�z" << endl;
					goto WorkerAGAIN1;
					break;
				}
			}
			else if (result == 1)
			{
				system("cls");
				cout << "Bu yetkili hesab� kapat�lm��t�r.Ana men�ye y�nlendiriliyorsunuz..." << endl;
				Sleep(2500);
				goto MainMenu;
			}
			else
			{
				system("cls");
				hak--;
				cout << "Giri� ba�ar�s�z" << endl;
				cout << "Kalan hak say�n�z : " << hak << endl;
				if (hak == 0)
				{
					cout << "�ok fazla hatal� oturum a�ma giri�iminde bulundunuz.Program kapat�l�yor.";
					Sleep(2500);
					exit(0);
				}
				else
				{
					goto WorkerLoginAGAIN;
				}
			}
			break;
		case 3:
			system("cls");
			c.CustomerUserID();
			if (c.CustomerEntry() == 1)
			{
				system("cls");
				cout << "Kay�t i�leminiz ba�ar�yla ger�ekle�tirildi.Giri� yapabilirsiniz." << endl;
				goto MainMenu;
			}
			break;
		case 9:
			exit(0);
			break;
		default:
			system("cls");
			cout << "Hatal� se�im yapt�n�z.L�tfen tekrar se�im yap�n�z" << endl;
			goto MainMenu;
		}
	} while (secim != 1 && secim != 2 && secim != 9);
	system("pause");
	return 0;
}
//