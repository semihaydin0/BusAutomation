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

#include "Customer.h"
#include "Worker.h"
#include "Expeditions.h"
#include "Tickets.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");
	Customer c;
	Worker w;
	Expeditions e;
	Tickets t;
	int secim, hak = 3, result = 0;
	cout << "Merhaba , otomasyona hoşgeldiniz lütfen seçim yapınız." << endl;
MainMenu:
	cout << "1-Müşteri Girişi\n2-Yetkili Girişi\n3-Müşteri Kaydı\n9-Çıkış\nSeçiminiz :";
	cin >> secim;
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