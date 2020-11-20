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
#pragma once
class Expeditions
{
public:
	Worker w;
	int price = 0, ExpeditionsID = 0, layout = 0;
	string departureP, destinationP, date, time;
	const string Citys[81] = { "Adana", "Ad�yaman", "Afyon","A�r�", "Amasya", "Ankara", "Antalya", "Artvin", "Ayd�n", "Bal�kesir", "Bilecik", "Bing�l", "Bitlis", "Bolu", "Burdur", "Bursa", "�anakkale", "�ank�r�", "�orum", "Denizli", "Diyarbak�r", "Edirne", "Elaz��", "Erzincan", "Erzurum", "Eski�ehir", "Gaziantep", "Giresun", "G�m��hane", "Hakkari", "Hatay", "Isparta", "Mersin", "�stanbul", "�zmir", "Kars", "Kastamonu", "Kayseri", "K�rklareli", "K�r�ehir", "Kocaeli", "Konya", "K�tahya", "Malatya", "Manisa", "Kahramanmara�", "Mardin", "Mu�la", "Mu�", "Nev�ehir", "Ni�de", "Ordu", "Rize", "Sakarya", "Samsun", "Siirt", "Sinop", "Sivas", "Tekirda�", "Tokat", "Trabzon", "Tunceli", "�anl�urfa", "U�ak", "Van", "Yozgat", "Zonguldak", "Aksaray", "Bayburt","Karaman", "K�r�kkale", "Batman", "��rnak","Bart�n", "Ardahan", "I�d�r", "Yalova", "Karab�k", "Kilis", "Osmaniye", "D�zce" };
	int AddExpedition();
	int EditExpedition(int LoggedWorkerID);
	void GetExID();
private:
	int CheckExpeditionEntry(string departureP_, string destinationP_, string date_, string time_, int price_, int layout_);
	void FileExp();
};