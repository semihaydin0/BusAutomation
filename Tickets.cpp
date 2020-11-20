//MIT License
//Copyright(c) 2020 Semih Aydýn
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

#include "Tickets.h"

using namespace std;

int Tickets::AddTicket(int UserID)
{
	int location1_, location2_, CustomerID = 0, ExpeditionID = 0, SeatNo = 0, CustomerChoose, CustomerSecim, CustomerSecim2, SelectedSeat, count = 0;;
	string departureP_, destinationP_;
	int Expedition[50]; int ExpeditionCount[50];
	ifstream ExpList("ExpeditionEntry.txt");
TicketAGAIN:
	cout << "1-Sefer Ara\n2-Listeden Seç\nSeçiminiz :";
	cin >> CustomerSecim;
	switch (CustomerSecim)
	{
	case 1:
		system("cls");
	TicketAGAIN2:
		count = 0;
		cout << "Kalkýþ yerinin plakasýný giriniz :";
		cin >> location1_;
		cout << "Varýþ yerinin plakasýný giriniz :";
		cin >> location2_;
		if (location1_ < 1 || location1_ > 81 || location1_ == 0 && location2_ < 1 || location2_ > 81 || location2_ == 0)
		{
			system("cls");
			cout << "Geçersiz plaka giriþi yaptýnýz.Tekrar seçiniz." << endl;
			goto TicketAGAIN2;
		}
		else
		{
			departureP_ = e.Citys[location1_ - 1];
			destinationP_ = e.Citys[location2_ - 1];
			if (departureP_ == destinationP_)
			{
				system("cls");
				cout << "Kalkýþ ve varýþ yerleri ayný olamaz.Tekrar seçiniz." << endl;
				goto TicketAGAIN2;
			}
			else
			{
			TicketAGAIN3:
				cout << "---Seferler---" << endl;
				string data;
				if (ExpList.is_open())
				{
					while (ExpList >> e.ExpeditionsID >> e.departureP >> e.destinationP >> e.date >> e.time >> e.price >> e.layout)
					{
						if (e.departureP == departureP_ && e.destinationP == destinationP_)
						{
							ExpeditionCount[count] = count + 1;
							Expedition[count] = e.ExpeditionsID;
							count++;
							if (e.layout == 46)
							{
								cout << count << "-" << e.departureP << "-" << e.destinationP << " " << e.date << "-" << e.time << " " << "2+2" << " " << e.price << "TL" << "\n";
							}
							else
							{
								cout << count << "-" << e.departureP << "-" << e.destinationP << " " << e.date << "-" << e.time << " " << "2+1" << " " << e.price << "TL" << "\n";
							}
						}
					}
					ExpList.close();
					if (count == 0)
					{
						system("cls");
						cout << "Aradýðýnýz kriterlere göre sefer bulunamadý." << endl;
						ExpList.close();
						goto TicketAGAIN;
					}
					else
					{
						cout << "Seçiminiz :";
						cin >> CustomerSecim2;
						int status = 0;
						for (int i = 0; i < count; i++)
						{
							if (ExpeditionCount[i] == CustomerSecim2)
							{
								status = 1;
								CustomerChoose = Expedition[i];
							}
						}
						if (status == 1)
						{
							SelectedSeat = Seats(CustomerChoose);
							TicketID++;
							ofstream AddTicketEntry;
							AddTicketEntry.open("TicketEntry.txt", ios::app);
							if (AddTicketEntry.is_open())
							{
								AddTicketEntry << TicketID << "\t" << UserID << "\t" << CustomerChoose << "\t" << SelectedSeat << "\n";
								AddTicketEntry.close();
								return 1;
							}
							else FileExp();
						}
						else
						{
							system("cls");
							cout << "Hatalý seçim yaptýnýz.Tekrar seçiniz." << endl;
							goto TicketAGAIN3;
						}
					}
				}
				else FileExp();
			}
		}
		break;
	case 2:
		system("cls");
	TicketAGAIN4:
		count = 0;
		cout << "---Seferler---" << endl;
		if (ExpList.is_open())
		{
			while (ExpList >> e.ExpeditionsID >> e.departureP >> e.destinationP >> e.date >> e.time >> e.price >> e.layout)
			{
				ExpeditionCount[count] = count + 1;
				Expedition[count] = e.ExpeditionsID;
				count++;
				if (e.layout == 46)
				{
					cout << count << "-" << e.departureP << "-" << e.destinationP << " " << e.date << "-" << e.time << " " << "2+2" << " " << e.price << "TL" << "\n";
				}
				else
				{
					cout << count << "-" << e.departureP << "-" << e.destinationP << " " << e.date << "-" << e.time << " " << "2+1" << " " << e.price << "TL" << "\n";
				}
			}
			ExpList.close();
			if (count == 0)
			{
				system("cls");
				cout << "Sefer bulunamadý." << endl;
				goto TicketAGAIN;
			}
			else
			{
				cout << "Seçiminiz :";
				cin >> CustomerSecim2;
				int status = 0;
				for (int i = 0; i < count; i++)
				{
					if (ExpeditionCount[i] == CustomerSecim2)
					{
						status = 1;
						CustomerChoose = Expedition[i];
					}
				}
				if (status == 1)
				{
					SelectedSeat = Seats(CustomerChoose);
					TicketID++;
					ofstream AddTicketEntry;
					AddTicketEntry.open("TicketEntry.txt", ios::app);
					if (AddTicketEntry.is_open())
					{
						AddTicketEntry << TicketID << "\t" << UserID << "\t" << CustomerChoose << "\t" << SelectedSeat << "\n";
						AddTicketEntry.close();
						return 1;
					}
					else FileExp();
				}
				else
				{
					system("cls");
					cout << "Hatalý seçim yaptýnýz.Tekrar seçiniz." << endl;
					goto TicketAGAIN4;
				}
			}
		}
		else FileExp();
		break;
	default:
		system("cls");
		cout << "Hatalý tuþlama gerçekleþtirdiniz.Tekrar seçiniz." << endl;
		goto TicketAGAIN;
		break;
	}
}
int Tickets::EditTicket()
{
	int TicketID_, status = 0, seat_, Choose, Expedition_;
EditAGAIN:
	cout << "Düzenlemek istediðiniz bilet ID bilgisini giriniz :";
	cin >> TicketID_;
	ifstream TicketData("TicketEntry.txt");
	fstream ChangeT;
	ofstream Temp;
	if (TicketData.is_open())
	{
		while (TicketData >> TicketID >> CustomerID >> ExpeditionsID >> Seat)
		{
			if (TicketID_ == TicketID)
			{
				status = 1;
				seat_ = Seat;
				Expedition_ = ExpeditionsID;
			}
		}
		TicketData.close();
		if (status == 1)
		{
			int line = 0;
			cout << "Sadece koltuk bilgilerini deðiþtirebilirsiniz.\nMevcut koltuk numarasý :" << seat_;
			Choose = Seats(Expedition_);
			ChangeT.open("TicketEntry.txt", ios::in);
			Temp.open("temp.txt", ios::out);
			if (ChangeT.is_open() && Temp.is_open())
			{
				while (!ChangeT.eof())
				{
					line++;
					ChangeT >> TicketID >> CustomerID >> ExpeditionsID >> Seat;
					if (TicketID_ == TicketID)
					{
						Temp << TicketID << "\t" << CustomerID << "\t" << ExpeditionsID << "\t" << Choose << "\n";
					}
					else
					{
						if (line <= TicketID)
						{
							Temp << TicketID << "\t" << CustomerID << "\t" << ExpeditionsID << "\t" << Seat << "\n";
						}
					}
				}
				ChangeT.close();
				Temp.close();
				if (remove("TicketEntry.txt") == 0)
				{
					if (rename("temp.txt", "TicketEntry.txt") == 0)
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
			cout << "Girilen bilet ID sine ait kayýt bulunamadý." << endl;
			goto EditAGAIN;
		}
	}
	else FileExp();
}
int Tickets::DeletingTicket(int LoggedWorkerID)
{
	int TicketID_; int status = 0;
DeleteAGAIN:
	if (w.GetAuthControl(LoggedWorkerID) == 1)
	{
		cout << "Silmek istediðiniz bilet ID bilgisini giriniz :";
		cin >> TicketID_;
		ifstream TicketData("TicketEntry.txt");
		fstream DeleteT;
		ofstream Temp;
		if (TicketData.is_open())
		{
			while (TicketData >> TicketID >> CustomerID >> ExpeditionsID >> Seat)
			{
				if (TicketID_ == TicketID)
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
						DeleteT >> TicketID >> CustomerID >> ExpeditionsID >> Seat;
						if (TicketID_ != TicketID)
						{
							Temp << TicketID << "\t" << CustomerID << "\t" << ExpeditionsID << "\t" << Seat << "\n";
						}
					}
					DeleteT.close();
					Temp.close();
					if (remove("TicketEntry.txt") == 0)
					{
						if (rename("temp.txt", "TicketEntry.txt") == 0)
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
				cout << "Girilen bilet ID sine ait kayýt bulunamadý." << endl;
				goto DeleteAGAIN;
			}
		}
		else FileExp();
	}
	else
	{
		system("cls");
		cout << "Yetkiniz bu iþlem için yeterli deðildir." << endl;
		return 0;
	}
}
void Tickets::GetTicketID()
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
		TicketID = s - 1;
		idvalue.close();
	}
	else FileExp();
}
int Tickets::Seats(int ExpeditionsID_)
{
	int layout_ = 0, Choose;
	int Seat_[46];
	ifstream Seats("ExpeditionEntry.txt");
	ifstream CheckTickets("TicketEntry.txt");
	if (Seats.is_open())
	{
		while (Seats >> e.ExpeditionsID >> e.departureP >> e.destinationP >> e.date >> e.time >> e.price >> e.layout)
		{
			if (ExpeditionsID_ == e.ExpeditionsID)
			{
				layout_ = e.layout;
			}
		}
		Seats.close();
		if (CheckTickets.is_open())
		{
			int a = 0;
			while (!CheckTickets.eof())
			{
				CheckTickets >> TicketID >> CustomerID >> ExpeditionsID >> Seat;
				if (ExpeditionsID_ == ExpeditionsID)
				{
					Seat_[a] = layout_;
					a++;
				}
			}
			CheckTickets.close();
			int status;
		CustomerChoose:
			if (layout_ == 46)
			{
				for (int i = 0; i < 12; i++)
				{
					for (int x = 0; x < 4; x++)
					{
						status = 0;
						for (int j = 0; j <= a; j++)
						{
							if (Seat_[j] == i * 4 + x + 1)
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
				cout << "Lütfen koltuk seçimi yapýnýz.\nSeçiminiz :";
				cin >> Choose;
				status = 0;
				for (int i = 0; i <= a; i++)
				{
					for (int x = 0; x < 4; x++)
					{
						for (int j = 0; j <= a; j++)
						{
							if (Seat_[j] == Choose)
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
					cout << "Bu koltuk daha önceden seçilmiþtir." << endl;
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
							if (Seat_[j] == i * 4 + x + 1)
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
				cout << "Lütfen koltuk seçimi yapýnýz.\nSeçiminiz :";
				cin >> Choose;
				status = 0;
				for (int i = 0; i <= a; i++)
				{
					for (int x = 0; x < 4; x++)
					{
						for (int j = 0; j <= a; j++)
						{
							if (Seat_[j] == Choose)
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
					cout << "Bu koltuk daha önceden seçilmiþtir." << endl;
					goto CustomerChoose;
				}
				else
				{
					return Choose;
				}
			}
		}
		else FileExp();
	}
	else FileExp();
}
void Tickets::CustomerTickets(int UserID)
{
	Expeditions e;
	int count = 0;
	int Expeditions_[50];
	int Seats_[50];
	ifstream UserTickets("TicketEntry.txt");
	if (UserTickets.is_open())
	{
		while (UserTickets >> TicketID >> CustomerID >> ExpeditionsID >> Seat)
		{
			if (UserID == CustomerID)
			{
				Expeditions_[count] = ExpeditionsID;
				Seats_[count] = Seat;
				count++;
			}
		}
		UserTickets.close();
		if (count == 0)
		{
			cout << "Bu hesaba ait bilet bilgileri bulunamadý." << endl;
		}
		else
		{
			ifstream UserExpData("ExpeditionEntry.txt");
			if (UserExpData.is_open())
			{
				int count_ = 0;
				while (UserExpData >> e.ExpeditionsID >> e.departureP >> e.destinationP >> e.date >> e.time >> e.price >> e.layout)
				{
					for (int i = 0; i < count; i++)
					{
						if (Expeditions_[i] == e.ExpeditionsID)
						{
							count_++;
							cout << count_ << "-" << e.departureP << "-" << e.destinationP << "\t" << e.date << "-" << e.time << "\t" << "Koltuk No:" << Seats_[i] << "\n";
						}
					}
				}
				cout << "Toplamda " << count << " adet kayýt bulundu." << endl;
			}
			else FileExp();
		}
	}
	else FileExp();
}
void Tickets::FileExp()
{
	system("cls");
	cout << "Dosya açma hatasý.Kapatýlýyor...";
	Sleep(2500);
	exit(0);
}
