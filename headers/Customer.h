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

#include "CaesarCypher.h"

using namespace std;
#pragma once
class Customer
{
public:
	int registrationID = 0, LoggedUserID = 0;
	int CustomerRegistration();
	int CustomerLogin();
	void CustomerUserID();
	int CustomerDeregistration(int UserIDValue);
	int CustomerChangePassword(int UserIDValue);
private:
	CaesarCypher enc;
	string username, password, activity;
	int CustomerRecordCheck(string _username);
	void FileExp();
};