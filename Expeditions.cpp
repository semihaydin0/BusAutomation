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

#include "Expeditions.h"
#include "Worker.h"

using namespace std;

int Expeditions::AddExpedition()
{
	string departureP_, destinationP_, date_, time_, id_;
	int location1_, location2_, day_, month_, year_, price_, layout_, schemeselec;
	float when_;
ExpeditionsAGAIN1:
	cout << "Kalk�� yerinin plakas�n� giriniz :";
	cin >> location1_;
	cout << "Var�� yerinin plakas�n� giriniz :";
	cin >> location2_;
	if (location1_ < 1 || location1_ > 81 || location1_ == 0 && location2_ < 1 || location2_ > 81 || location2_ == 0)
	{
		system("cls");
		cout << "Ge�ersiz plaka giri�i yapt�n�z.Tekrar se�iniz." << endl;
		goto ExpeditionsAGAIN1;
	}
	else
	{
		departureP_ = Citys[location1_ - 1];
		destinationP_ = Citys[location2_ - 1];
		if (departureP_ == destinationP_)
		{
			system("cls");
			cout << "Kalk�� ve var�� yerleri ayn� olamaz.Tekrar se�iniz." << endl;
			goto ExpeditionsAGAIN1;
		}
	ExpeditionsAGAIN2:
		cout << "Sefer g�n�n� giriniz :";
		cin >> day_;
		if (day_ <= 31 && day_ >= 1)
		{
		ExpeditionsAGAIN3:
			cout << "Sefer ay�n� giriniz :";
			cin >> month_;
			if (month_ <= 12 && month_ >= 1)
			{
			ExpeditionsAGAIN4:
				cout << "Sefer y�l�n�z giriniz :";
				cin >> year_;
				if (year_ >= 2020)
				{
					stringstream a, b, c, d;
					a << day_; b << month_; c << year_;
					date_ = a.str() + "." + b.str() + "." + c.str();
				ExpeditionsAGAIN5:
					cout << "Sefer saatini giriniz.(�rne�in 17.30) :";
					cin >> time_;
					stringstream con(time_);
					con >> when_;
					if (when_ >= 00.00 && when_ <= 23.59)
					{
					ExpeditionsAGAIN6:
						cout << "Fiyat giriniz :";
						cin >> price_;
						if (price_ >= 1)
						{
						ExpeditionsAGAIN7:
							cout << "Koltuk d�zeni se�iniz.\n1-2+2\n2-2+1\nSe�iminiz :";
							cin >> schemeselec;
							switch (schemeselec)
							{
							case 1:
								layout_ = 46;
								break;
							case 2:
								layout_ = 38;
								break;
							default:cout << "Hatal� giri� yapt�n�z.Tekrar se�iniz." << endl;
								goto ExpeditionsAGAIN7;
								break;
							}
							if (CheckExpeditionEntry(departureP_, destinationP_, date_, time_, price_, layout_) == 0)
							{
								ExpeditionsID++;
								ofstream AddExpeditionsEntry;
								AddExpeditionsEntry.open("ExpeditionEntry.txt", ios::app);
								if (AddExpeditionsEntry.is_open())
								{
									AddExpeditionsEntry << ExpeditionsID << "\t" << departureP_ << "\t" << destinationP_ << "\t" << date_ << "\t" << time_ << "\t" << price_ << "\t" << layout_ << "\n";
									AddExpeditionsEntry.close();
									return 1;
								}
								else FileExp();
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
int Expeditions::EditExpedition(int LoggedWorkerID)
{
	//For worker
	int workerid_; string username_, password_, auth_, activity_;
	//
	int ExpeditionsID_, line = 0, editselec, day_, month_, year_, NewPrice, locprice, locseat; float when;
	string edittime, NewDate, NewTime, lone, ltwo, locdate, loctime;
	stringstream a, b, c, d, con;
	fstream ExP;
	ofstream Temp;
	ifstream Check("WorkerEntry.txt");
	if (Check.is_open())
	{
		while (!Check.eof())
		{
			Check >> workerid_ >> username_ >> password_ >> auth_ >> activity_;
			if (LoggedWorkerID == workerid_)
			{
				if (auth_ == "tam")
				{
					Check.close();
					cout << "D�zenlemek istedi�iniz seferin ID bilgisini giriniz :";
					cin >> ExpeditionsID_;
					ifstream ExCheck("ExpeditionEntry.txt");
					if (ExCheck.is_open())
					{
						while (!ExCheck.eof())
						{
							ExCheck >> ExpeditionsID >> departureP >> destinationP >> date >> time >> price >> layout;
							if (ExpeditionsID_ == ExpeditionsID)
							{
								lone = departureP; ltwo = destinationP; locdate = date; loctime = time; locprice = price; locseat = layout;
								ExCheck.close();
							ExpeditionsAGAIN1:
								cout << "L�tfen d�zenlemek istedi�iniz k�sm� se�iniz.\n1-Tarih\n2-Saat\n3-Fiyat\nSe�iminiz :";
								cin >> editselec;
								switch (editselec)
								{
								case 1:
									system("cls");
								ExpeditionsAGAIN2:
									cout << "Sefer g�n�n� giriniz :";
									cin >> day_;
									if (day_ <= 31 && day_ >= 1)
									{
									ExpeditionsAGAIN3:
										cout << "Sefer ay�n� giriniz :";
										cin >> month_;
										if (month_ <= 12 && month_ >= 1)
										{
										ExpeditionsAGAIN4:
											cout << "Sefer y�l�n�z giriniz :";
											cin >> year_;
											if (year_ >= 2020)
											{
												a << day_; b << month_; c << year_;
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
															ExP >> ExpeditionsID >> departureP >> destinationP >> date >> time >> price >> layout;
															if (ExpeditionsID == line)
															{
																Temp << ExpeditionsID << "\t" << departureP << "\t" << destinationP << "\t" << NewDate << "\t" << time << "\t" << price << "\t" << layout << "\n";
															}
															else
															{
																if (line <= ExpeditionsID)
																{
																	Temp << ExpeditionsID << "\t" << departureP << "\t" << destinationP << "\t" << date << "\t" << time << "\t" << price << "\t" << layout << "\n";
																}
															}
														}
														ExP.close();
														Temp.close();
														if (remove("ExpeditionEntry.txt") == 0)
														{
															if (rename("temp.txt", "ExpeditionEntry.txt") == 0)
															{
																return 1;
															}
														}
													}
													else FileExp();
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
													ExP >> ExpeditionsID >> departureP >> destinationP >> date >> time >> price >> layout;
													if (ExpeditionsID == line)
													{
														Temp << ExpeditionsID << "\t" << departureP << "\t" << destinationP << "\t" << date << "\t" << NewTime << "\t" << price << "\t" << layout << "\n";
													}
													else
													{
														if (line <= ExpeditionsID)
														{
															Temp << ExpeditionsID << "\t" << departureP << "\t" << destinationP << "\t" << date << "\t" << time << "\t" << price << "\t" << layout << "\n";
														}
													}
												}
												ExP.close();
												Temp.close();
												if (remove("ExpeditionEntry.txt") == 0)
												{
													if (rename("temp.txt", "ExpeditionEntry.txt") == 0)
													{
														return 1;
													}
												}
											}
											else FileExp();
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
													ExP >> ExpeditionsID >> departureP >> destinationP >> date >> time >> price >> layout;
													if (ExpeditionsID == line)
													{
														Temp << ExpeditionsID << "\t" << departureP << "\t" << destinationP << "\t" << date << "\t" << time << "\t" << NewPrice << "\t" << layout << "\n";
													}
													else
													{
														if (line <= ExpeditionsID)
														{
															Temp << ExpeditionsID << "\t" << departureP << "\t" << destinationP << "\t" << date << "\t" << time << "\t" << price << "\t" << layout << "\n";
														}
													}
												}
												ExP.close();
												Temp.close();
												if (remove("ExpeditionEntry.txt") == 0)
												{
													if (rename("temp.txt", "ExpeditionEntry.txt") == 0)
													{
														return 1;
													}
												}
											}
											else FileExp();
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
					else FileExp();
				}
				else
				{
					system("cls");
					cout << "Hesab�n�z�n yetkisi bu i�lem i�in yeterli de�ildir." << endl;
				}
			}
		}
	}
	else FileExp();
}
void Expeditions::GetExID()
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
		ExpeditionsID = s - 1;
		GetID.close();
	}
	else FileExp();
}
int Expeditions::CheckExpeditionEntry(string departureP_, string destinationP_, string date_, string time_, int price_, int layout_)
{
	int index = 0;
	ifstream CheckExped("ExpeditionEntry.txt");
	if (CheckExped.is_open())
	{
		while (!CheckExped.eof())
		{
			CheckExped >> ExpeditionsID >> departureP >> destinationP >> date >> time >> price >> layout;
			if (departureP == departureP_ && destinationP == destinationP_ && date == date_ && time == time_ && price == price_ && layout == layout_)
			{
				index = 1;
			}
		}
		return index;
		CheckExped.close();
	}
	else FileExp();
}
void Expeditions::FileExp()
{
	system("cls");
	cout << "Dosya a�ma hatas�.Kapat�l�yor...";
	Sleep(2500);
	exit(0);
}