//MIT License
//Copyright(c) 2020 Semih Aydın
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

using namespace std;
void ErrorActions()
{
	system("cls");
	cout << "Dosya açma hatası.Kapatılıyor...";
	Sleep(2500);
	exit(0);
}

class Customer
{
public:
	int registrationID = 0, LoggedUserID = 0;
	int CustomerRegistration()
	{
		string username, password;
		cout << "Lütfen kullanıcı adı ve şifrenizi belirleyiniz." << endl;
	again:
		cout << "Kullanıcı Adı :";
		cin >> username;
		cout << "Şifre :";
		cin >> password;
		if (CustomerRecordCheck(username) == 0)
		{
			registrationID++;
			ofstream AddEntry;
			AddEntry.open("CustomerEntry.txt", ios::app);
			if (AddEntry.is_open())
			{
				AddEntry << registrationID << "\t" << username << "\t" << password << "\t" << "aktif" << "\n";
				AddEntry.close();
				return 1;
			}
			else ErrorActions();
		}
		else
		{
			cout << "Girdiğiniz kullanıcı adı daha önceden alınmıştır." << endl;
			goto again;
		}
	}
	int CustomerLogin()
	{
		int userid, status = 0, account = 0, sum = 0;
		string username, password, activity, _username, _password;
		cout << "Kullanıcı Adı :";
		cin >> _username;
		cout << "Şifre :";
		cin >> _password;
		ifstream CustomerRecordFile("CustomerEntry.txt");
		if (CustomerRecordFile.is_open())
		{
			while (CustomerRecordFile >> userid >> username >> password >> activity)
			{
				if (_username == username && _password == password)
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
		else ErrorActions();
	}
	void CustomerUserID()
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
		else ErrorActions();
	}
	int CustomerDeregistration(int UserIDValue)
	{
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
			remove("CustomerEntry.txt");
			rename("temp.txt", "CustomerEntry.txt");
			return 1;
		}
		else ErrorActions();
	}
	int CustomerChangePassword(int UserIDValue)
	{
		string NewPassword; int line = 0, changeid = 0;
		fstream ChangeP;
		ofstream Temp;
		cout << "Yeni şifrenizi giriniz :";
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
					Temp << changeid << "\t" << username << "\t" << NewPassword << "\t" << activity << "\n";
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
			remove("CustomerEntry.txt");
			rename("temp.txt", "CustomerEntry.txt");
			return 1;
		}
		else ErrorActions();
	}
private:
	string username, password, activity;
	int CustomerRecordCheck(string _username)
	{
		int index = 0;
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
		else ErrorActions();
	}
};
class Worker
{
public:
	int registrationID = 0, LoggedWorkerID = 0;
	int WorkerRegistration()
	{
		string _username,_password,authority;
		char auth;
		cout << "Lütfen çalışan kişi için kullanıcı adı ve şifre belirleyiniz." << endl;
	workerentry:
		cout << "Kullanıcı Adı :";
		cin >> _username;
		cout << "Şifre :";
		cin >> _password;
	againauth:
		cout << "Lütfen yetki türü seçiniz.\n1-Tam\n2-Yarı\nSeçiminiz :" << endl;
		cin >> auth;
		switch (auth)
		{
		case '1':authority = "tam";
			break;
		case '2':authority = "yarı";
			break;
		default:cout << "Hatalı seçim yaptınız tekrar deneyin.";
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
					AddWorkerEntry << registrationID << "\t" << _username << "\t" << _password << "\t" << authority << "\t" << "aktif" << "\n";
					AddWorkerEntry.close();
					return 1;
				}
				else ErrorActions();
			}
			else
			{
				system("cls");
				cout << "Girmiş olduğunuz kullanıcı adı daha önceden alınmıştır." << endl;
				goto workerentry;
			}
		}
		else
		{
			system("cls");
			cout << "Oluşturmaya çalıştığınız hesabın yetkisi sizin yetkinizden yüksek olduğu için hesap oluşturulamadı." << endl;
			goto workerentry;
		}
	}
	int WorkerLogin()
	{
		int account = 0, status = 0, sum = 0;
		string _username, _password;
		cout << "Kullanıcı Adı :";
		cin >> _username;
		cout << "Şifre :";
		cin >> _password;
		ifstream WorkerLoginFile("WorkerEntry.txt");
		if (WorkerLoginFile.is_open())
		{
			while (WorkerLoginFile >> registrationID >> username >> password >> auth >> activity)
			{
				if (_username == username && _password == password)
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
		else ErrorActions();
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
			registrationID = s - 1;
			GetUser.close();
		}
		else ErrorActions();
	}
	int WorkerDeregistration(int WorkerIDValue)
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
			remove("WorkerEntry.txt");
			rename("temp.txt", "WorkerEntry.txt");
			return 1;
		}
		else ErrorActions();
	}
	int WorkerResetPassword(int WorkerIDValue)
	{
		int line = 0;
		fstream WorkerP;
		ofstream Temp;
		string NewPassword;
		cout << "Yeni şifrenizi giriniz :";
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
					Temp << registrationID << "\t" << username << "\t" << NewPassword << "\t" << auth << "\t" << activity << "\n";
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
			remove("WorkerEntry.txt");
			rename("temp.txt", "WorkerEntry.txt");
			return 1;
		}
		else ErrorActions();
	}
	int GetAuthControl(int ID)
	{
		int x;
		x = AuthorityControl(GetWorkerAuth(ID), "tam");
		return x;
	}
private:
	string username, password, auth, activity;
	int AuthorityControl(string personauth, string auth)
	{
		ifstream Control("WorkerEntry.txt");
		if (Control.is_open())
		{
			while (!Control.eof())
			{
				Control >> registrationID >> username >> password >> auth >> activity;
				if (personauth == auth || personauth == "tam" && auth == "yarı")
				{
					return 1;
				}
				else return 0;
			}
			Control.close();
		}
		else ErrorActions();
	}
	string GetWorkerAuth(int LoggedUserID)
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
		else ErrorActions();
	}
	int WorkerRecordCheck(string workerusername)
	{
		int status = 0;
		ifstream WorkerCheck("WorkerEntry.txt");
		if (WorkerCheck.is_open())
		{
			while (!WorkerCheck.eof())
			{
				WorkerCheck >> registrationID >> username >> password >> auth >> activity;
				if (workerusername == username)
				{
					status = 1;
				}
			}
			if (status == 1) return 1;
			else return 0;
			WorkerCheck.close();
		}
		else ErrorActions();
	}
};
class Expeditions
{
public:
	Worker w;
	string loc1, loc2, date, time; int price=0, id=0, scheme=0;
	const string Citys[81] = { "Adana", "Adıyaman", "Afyon","Ağrı", "Amasya", "Ankara", "Antalya", "Artvin", "Aydın", "Balıkesir", "Bilecik", "Bingöl", "Bitlis", "Bolu", "Burdur", "Bursa", "Çanakkale", "Çankırı", "Çorum", "Denizli", "Diyarbakır", "Edirne", "Elazığ", "Erzincan", "Erzurum", "Eskişehir", "Gaziantep", "Giresun", "Gümüşhane", "Hakkari", "Hatay", "Isparta", "Mersin", "İstanbul", "İzmir", "Kars", "Kastamonu", "Kayseri", "Kırklareli", "Kırşehir", "Kocaeli", "Konya", "Kütahya", "Malatya", "Manisa", "Kahramanmaraş", "Mardin", "Muğla", "Muş", "Nevşehir", "Niğde", "Ordu", "Rize", "Sakarya", "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdağ", "Tokat", "Trabzon", "Tunceli", "Şanlıurfa", "Uşak", "Van", "Yozgat", "Zonguldak", "Aksaray", "Bayburt","Karaman", "Kırıkkale", "Batman", "Şırnak","Bartın", "Ardahan", "Iğdır", "Yalova", "Karabük", "Kilis", "Osmaniye", "Düzce" };
	int AddExpedition()
	{
		int location1, location2, day, month, year, price1, scheme1;
		float when;
		string first, second, date1, time1, id1;
		int schemeselec;
	ExpeditionsAGAIN1:
		cout << "Kalkış yerinin plakasını giriniz :";
		cin >> location1;
		cout << "Varış yerinin plakasını giriniz :";
		cin >> location2;
		if (location1 < 1 || location1 > 81 || location1 == 0 && location2 < 1 || location2 > 81 || location2 == 0)
		{
			system("cls");
			cout << "Geçersiz plaka girişi yaptınız.Tekrar seçiniz." << endl;
			goto ExpeditionsAGAIN1;
		}
		else
		{
			first = Citys[location1 - 1];
			second = Citys[location2 - 1];
			if (first == second)
			{
				system("cls");
				cout << "Kalkış ve varış yerleri aynı olamaz.Tekrar seçiniz." << endl;
				goto ExpeditionsAGAIN1;
			}
		ExpeditionsAGAIN2:
			cout << "Sefer gününü giriniz :";
			cin >> day;
			if (day <= 31 && day >= 1)
			{
			ExpeditionsAGAIN3:
				cout << "Sefer ayını giriniz :";
				cin >> month;
				if (month <= 12 && month >= 1)
				{
				ExpeditionsAGAIN4:
					cout << "Sefer yılınız giriniz :";
					cin >> year;
					if (year >= 2020)
					{
						stringstream a, b, c, d;
						a << day; b << month; c << year;
						date1 = a.str() + "." + b.str() + "." + c.str();
					ExpeditionsAGAIN5:
						cout << "Sefer saatini giriniz.(Örneğin 17.30) :";
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
								cout << "Koltuk düzeni seçiniz." << endl;
								cout << "1-2+2\n2-2+1" << endl;
								cout << "Seçiminiz :";
								cin >> schemeselec;
								switch (schemeselec)
								{
								case 1:
									scheme1 = 46;
									break;
								case 2:
									scheme1 = 38;
									break;
								default:cout << "Hatalı giriş yaptınız.Tekrar seçiniz." << endl;
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
									cout << "Oluşturmaya çalıştığınız sefer halihazırda mevcuttur.İlk kısma yönlendiriliyorsunuz..." << endl;
									goto ExpeditionsAGAIN1;
								}
							}
							else
							{
								cout << "Hatalı fiyat girdiniz.Tekrar seçiniz." << endl;
								goto ExpeditionsAGAIN6;
							}
						}
						else
						{
							cout << "Hatalı saat girdiniz.Tekrar seçiniz." << endl;
							goto ExpeditionsAGAIN5;
						}
					}
					else
					{
						cout << "2020 yılı öncesine sefer oluşturulamaz.Tekrar seçiniz." << endl;
						goto ExpeditionsAGAIN4;
					}
				}
				else
				{
					cout << "Hatalı ay seçimi yaptınız.Tekrar seçiniz." << endl;
					goto ExpeditionsAGAIN3;
				}
			}
			else
			{
				cout << "Hatalı gün seçimi yaptınız.Tekrar seçiniz." << endl;
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
						cout << "Düzenlemek istediğiniz sefer id bilgisini giriniz :";
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
									cout << "Lütfen düzenlemek istediğiniz kısmı seçiniz." << endl;
									cout << "1-Tarih\n2-Saat\n3-Fiyat" << endl;
									cout << "Seçiminiz :";
									cin >> editselec;
									switch (editselec)
									{
									case 1:
										system("cls");
									ExpeditionsAGAIN2:
										cout << "Sefer gününü giriniz :";
										cin >> day;
										if (day <= 31 && day >= 1)
										{
										ExpeditionsAGAIN3:
											cout << "Sefer ayını giriniz :";
											cin >> month;
											if (month <= 12 && month >= 1)
											{
											ExpeditionsAGAIN4:
												cout << "Sefer yılınız giriniz :";
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
														else ErrorActions();
													}
													else
													{
														system("cls");
														cout << "Aynı sefer zaten oluşturulmuş.Tekrar deneyin." << endl;
														a.str(""); b.str(""); c.str("");
														goto ExpeditionsAGAIN1;
													}

												}
												else
												{
													cout << "2020 yılı öncesine sefer oluşturulamaz.Tekrar seçiniz." << endl;
													goto ExpeditionsAGAIN4;
												}
											}
											else
											{
												cout << "Hatalı ay seçimi yaptınız.Tekrar seçiniz." << endl;
												goto ExpeditionsAGAIN3;
											}
										}
										else
										{
											cout << "Hatalı gün seçimi yaptınız.Tekrar seçiniz." << endl;
											goto ExpeditionsAGAIN2;
										}
										break;
									case 2:
										system("cls");
									ExpeditionsAGAIN5:
										cout << "Sefer saatini giriniz.(Örneğin 17.30) :";
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
												else ErrorActions();
											}
											else
											{
												system("cls");
												cout << "Aynı sefer zaten oluşturulmuş.Tekrar deneyin." << endl;
												con.str("");
												goto ExpeditionsAGAIN1;
											}
										}
										else
										{
											cout << "Hatalı saat girdiniz.Tekrar seçiniz." << endl;
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
												else ErrorActions();
											}
											else
											{
												system("cls");
												cout << "Aynı sefer zaten oluşturulmuş.Tekrar deneyin." << endl;
												goto ExpeditionsAGAIN1;
											}
										}
										else
										{
											cout << "Hatalı fiyat girdiniz.Tekrar giriniz." << endl;
											goto ExpeditionsAGAIN6;
										}
										break;
									default:
										cout << "Hatalı seçim yaptınız.Tekrar seçiniz." << endl;
										goto ExpeditionsAGAIN1;
										break;
									}
								}
							}
							system("cls");
							cout << "Girdiğiniz sefer id'ye ait sefer bulunamadı." << endl;
							ExCheck.close();
						}
						else ErrorActions();
					}
					else
					{
						system("cls");
						cout << "Hesabınızın yetkisi bu işlem için yeterli değildir." << endl;
					}
				}
			}
		}
		else ErrorActions();
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
		else ErrorActions();
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
		else ErrorActions();
	}
};
class Tickets
{
public:
	Expeditions e;
	Customer c;
	Worker w;
	int id=0, customerid = 0, seferid = 0, koltuk = 0, sayi = 0;
	int AddTicket(int UserID)
	{
		ifstream ExpList("ExpeditionEntry.txt");
		int CustomerID = 0, ExpeditionID = 0, SeatNo = 0; int CustomerChoose, location1, location2, CustomerSecim, CustomerSecim2, SelectedSeat;
		string kalkis, varis; int sfrid[50]; int sfrsayisi[50];
	TicketAGAIN:
		cout << "1-Sefer Ara\n2-Listeden Seç" << endl;
		cout << "Seçiminiz :";
		cin >> CustomerSecim;
		switch (CustomerSecim)
		{
		case 1:
			system("cls");
		TicketAGAIN2:
			cout << "Kalkış yerinin plakasını giriniz :";
			cin >> location1;
			cout << "Varış yerinin plakasını giriniz :";
			cin >> location2;
			if (location1 < 1 || location1 > 81 || location1 == 0 && location2 < 1 || location2 > 81 || location2 == 0)
			{
				system("cls");
				cout << "Geçersiz plaka girişi yaptınız.Tekrar seçiniz." << endl;
				goto TicketAGAIN2;
			}
			else
			{
				kalkis = e.Citys[location1 - 1];
				varis = e.Citys[location2 - 1];
				if (kalkis == varis)
				{
					system("cls");
					cout << "Kalkış ve varış yerleri aynı olamaz.Tekrar seçiniz." << endl;
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
							cout << "Aradığınız kriterlere göre sefer bulunamadı." << endl;
							goto TicketAGAIN;
						}
						else
						{
							cout << "Seçiminiz :";
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
								else ErrorActions();
							}
							else
							{
								system("cls");
								cout << "Hatalı seçim yaptınız.Tekrar seçiniz." << endl;
								goto TicketAGAIN3;
							}
						}
					}
					else ErrorActions();
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
					cout << "Sefer bulunamadı." << endl;
					goto TicketAGAIN;
				}
				else
				{
					cout << "Seçiminiz :";
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
						else ErrorActions();
					}
					else
					{
						system("cls");
						cout << "Hatalı seçim yaptınız.Tekrar seçiniz." << endl;
						goto TicketAGAIN4;
					}
				}
			}
			else ErrorActions();
			break;
		default:
			system("cls");
			cout << "Hatalı tuşlama gerçekleştirdiniz.Tekrar seçiniz." << endl;
			goto TicketAGAIN;
			break;
		}
	}
	int EditTicket()
	{
		int ticket; int status = 0; int kltk; int Choose; int sfr;
	EditAGAIN:
		cout << "Düzenlemek istediğiniz bilet id bilgisini giriniz :";
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
				cout << "Sadece koltuk bilgilerini değiştirebilirsiniz." << endl;
				cout << "Mevcut koltuk numarası :" << kltk << endl;
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
				else ErrorActions();
			}
			else
			{
				system("cls");
				cout << "Girilen bilet id sine ait kayıt bulunamadı." << endl;
				goto EditAGAIN;
			}
		}
		else ErrorActions();
	}
	int DeletingTicket(int LoggedWorkerID)
	{
		int tid; int status = 0;
	DeleteAGAIN:
		if (w.GetAuthControl(LoggedWorkerID) == 1)
		{
			cout << "Silmek istediğiniz bilet id bilgisini giriniz :";
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
					else ErrorActions();
				}
				else
				{
					system("cls");
					cout << "Girilen bilet id sine ait kayıt bulunamadı." << endl;
					goto DeleteAGAIN;
				}
			}
			else ErrorActions();
		}
		else
		{
			system("cls");
			cout << "Yetkiniz bu işlem için yeterli değildir." << endl;
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
		else ErrorActions();
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
					cout << "Lütfen koltuk seçimi yapınız." << endl;
					cout << "Seçiminiz :";
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
						cout << "Geçersiz koltuk seçimi.Tekrar seçiniz." << endl;
						goto CustomerChoose;
					}
					else if (status == 1)
					{
						system("cls");
						cout << "Bu koltuk daha önceden seçilmiştir." << endl;
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
					cout << "Lütfen koltuk seçimi yapınız." << endl;
					cout << "Seçiminiz :";
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
						cout << "Geçersiz koltuk seçimi.Tekrar seçiniz." << endl;
						goto CustomerChoose;
					}
					else if (status == 1)
					{
						system("cls");
						cout << "Bu koltuk daha önceden seçilmiştir." << endl;
						goto CustomerChoose;
					}
					else
					{
						return Choose;
					}
				}
			}
			else ErrorActions();
		}
		else ErrorActions();
	}
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
				cout << "Bu hesaba ait bilet bilgileri bulunamadı." << endl;
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
					cout << "Toplamda " << t.a << " adet kayıt bulundu." << endl;
				}
				else ErrorActions();
			}
		}
		else ErrorActions();
	}
private:
	int ticketid, userid, sfrid, seat, a;
};
int main()
{
	setlocale(LC_ALL, "Turkish");
	int secim, hak = 3, result = 0;
	cout << "Merhaba , otomasyona hoşgeldiniz lütfen seçim yapınız." << endl;
MainMenu:
	cout << "1-Müşteri Girişi\n2-Yetkili Girişi\n3-Müşteri Kaydı\n9-Çıkış\nSeçiminiz :";
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
				cout << "Giriş başarılı.Müşteri paneline yönlendiriliyor..." << endl;
				Sleep(2000);
				system("cls");
				int CustomerSecim1;
			CustomerAGAIN1:
				cout << "-----Müşteri Paneli-----\n1-Bilet Al\n2-Biletlerim\n3-Çıkış Yap\n9-Kullanıcı İşlemleri\nSeçiminiz :";
				cin >> CustomerSecim1;
				switch (CustomerSecim1)
				{
				case 1:
					system("cls");
					t.GetTicketID();
					if (t.AddTicket(c.LoggedUserID) == 1)
					{
						system("cls");
						cout << "Bilet alımı başarıyla gerçekleştirildi." << endl;
						goto CustomerAGAIN1;
					}
					break;
				case 2:
					system("cls");
					int secim;
					t.CustomerTickets(c.LoggedUserID);
				CustomerAGAINx:
					cout << "Geri dönmek için 9 tuşuna basınız :";
					cin >> secim;
					if (secim != 9)
					{
						cout << "Hatalı tuşlama yaptınız." << endl;
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
					cout << "Çıkış yapıldı..." << endl;
					goto MainMenu;
					break;
				case 9:system("cls");
					int CustomerSecim2;
				CustomerAGAIN2:
					cout << "---Kullanıcı İşlemleri---\n1-Şifre Güncelleme\n2-Hesap Kapatma\nSeçiminiz :";
					cin >> CustomerSecim2;
					switch (CustomerSecim2)
					{
					case 1:
						if (c.CustomerChangePassword(c.LoggedUserID) == 1)
						{
							cout << "Şifre değiştirme işlemi başarıyla tamamlandı.Ana menüye geri dönülüyor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					case 2:
						if (c.CustomerDeregistration(c.LoggedUserID) == 1)
						{
							cout << "Hesap kapatma işlemi başarıyla tamamlandı.Ana menüye geri dönülüyor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					default:
						system("cls");
						cout << "Hatalı seçim yaptınız.Lütfen tekrar seçim yapınız" << endl;
						goto CustomerAGAIN2;
						break;
					}
					break;
				default:cout << "Hatalı seçim yaptınız.Lütfen tekrar seçim yapınız" << endl;
					goto CustomerAGAIN1;
					break;
				}
			}
			else if (result == 1)
			{
				system("cls");
				cout << "Bu müşteri hesabı kapatılmıştır.Ana menüye yönlendiriliyorsunuz..." << endl;
				Sleep(2500);
				system("cls");
				goto MainMenu;
			}
			else
			{
				system("cls");
				hak--;
				cout << "Giriş başarısız" << endl;
				cout << "Kalan hak sayınız : " << hak << endl;
				if (hak == 0)
				{
					cout << "Çok fazla hatalı oturum açma girişiminde bulundunuz.Program kapatılıyor.";
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
				cout << "Giriş başarılı.Yetkili paneline yönlendiriliyor..." << endl;
				Sleep(2000);
				system("cls");
			WorkerAGAIN1:
				cout << "-----Yetkili Paneli-----\n1-Sefer Ekle\n2-Sefer Düzenle\n3-Bilet İşlemleri\n4-Çıkış Yap\n9-Yetkili İşlemleri\nSeçiminiz :" << endl;
				int WorkerSecim1, WorkerSecim2;
				cin >> WorkerSecim1;
				switch (WorkerSecim1)
				{
				case 1:
					system("cls");
					e.GetExID();
					if (e.AddExpedition() == 1)
					{
						system("cls");
						cout << "Sefer ekleme işleminiz başarıyla gerçekleştirildi." << endl;
						goto WorkerAGAIN1;
					}
					break;
				case 2:
					system("cls");
					if (e.EditExpedition(w.LoggedWorkerID) == 1)
					{
						system("cls");
						cout << "Sefer düzenleme işlemi başarıyla tamamlandı." << endl;
						goto WorkerAGAIN1;
					}
					else
					{
						goto WorkerAGAIN1;
					}
					break;
				case 3:
					system("cls");
					cout << "---Bilet İşlemleri---\n1-Bilet Düzenleme\n2-Bilet Sil\nSeçiminiz :";
					cin >> WorkerSecim2;
					switch (WorkerSecim2)
					{
					case 1:
						system("cls");
						if (t.EditTicket() == 1)
						{
							system("cls");
							cout << "Bilet düzenleme işlemi başarılı." << endl;
							goto WorkerAGAIN1;
						}
						break;
					case 2:
						system("cls");
						if (t.DeletingTicket(w.LoggedWorkerID) == 1)
						{
							system("cls");
							cout << "Bilet silme işlemi başarıyla tamamlandı." << endl;
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
					cout << "Çıkış yapıldı..." << endl;
					goto MainMenu;
					break;
				case 9:
					system("cls");
				WorkerAGAIN2:
					cout << "---Yetkili İşlemleri---\n1-Şifre Güncelleme\n2-Hesap Kapatma\n3-Yeni Çalışan Kaydı Ekle\nSeçiminiz :";
					cin >> WorkerSecim2;
					switch (WorkerSecim2)
					{
					case 1:
						system("cls");
						if (w.WorkerResetPassword(w.LoggedWorkerID) == 1)
						{
							cout << "Şifre değiştirme işlemi başarıyla tamamlandı.Ana menüye geri dönülüyor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					case 2:
						system("cls");
						if (w.WorkerDeregistration(w.LoggedWorkerID) == 1)
						{
							cout << "Hesap kapatma işlemi başarıyla tamamlandı.Ana menüye geri dönülüyor...";
							Sleep(2000);
							system("cls");
							goto MainMenu;
						}
						break;
					case 3:
						system("cls");
						w.GetWorkerID();
						if (w.WorkerRegistration() == 1)
						{
							system("cls");
							cout << "Kayıt işleminiz başarıyla gerçekleştirildi." << endl;
							goto WorkerAGAIN1;
						}
						break;
					default:system("cls");
						cout << "Hatalı seçim yaptınız.Lütfen tekrar seçim yapınız" << endl;
						goto WorkerAGAIN2;
						break;
					}
					break;
				default:system("cls");
					cout << "Hatalı seçim yaptınız.Lütfen tekrar seçim yapınız" << endl;
					goto WorkerAGAIN1;
					break;
				}
			}
			else if (result == 1)
			{
				system("cls");
				cout << "Bu yetkili hesabı kapatılmıştır.Ana menüye yönlendiriliyorsunuz..." << endl;
				Sleep(2500);
				goto MainMenu;
			}
			else
			{
				system("cls");
				hak--;
				cout << "Giriş başarısız" << endl;
				cout << "Kalan hak sayınız : " << hak << endl;
				if (hak == 0)
				{
					cout << "Çok fazla hatalı oturum açma girişiminde bulundunuz.Program kapatılıyor.";
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
			if (c.CustomerRegistration() == 1)
			{
				system("cls");
				cout << "Kayıt işleminiz başarıyla gerçekleştirildi.Giriş yapabilirsiniz." << endl;
				goto MainMenu;
			}
			break;
		case 9:
			exit(0);
			break;
		default:
			system("cls");
			cout << "Hatalı seçim yaptınız.Lütfen tekrar seçim yapınız" << endl;
			goto MainMenu;
		}
	} while (secim != 1 && secim != 2 && secim != 9);
	system("pause");
	return 0;
}