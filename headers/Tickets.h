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

#include "Customer.h"
#include "Worker.h"
#include "Expeditions.h"

using namespace std;
#pragma once
class Tickets
{
public:
	Expeditions e;
	Customer c;
	Worker w;
	int TicketID = 0, CustomerID = 0, ExpeditionsID = 0, Seat = 0;
	int AddTicket(int UserID);
	int EditTicket();
	int DeletingTicket(int LoggedWorkerID);
	void GetTicketID();
	int Seats(int ExpeditionsID);
	void CustomerTickets(int UserID);
private:
	void FileExp();
};