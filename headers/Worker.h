//MIT License
//Copyright(c) 2020 Semih Aydýn
//UTF - 8
//Display Languague : Turkish

#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <fstream>

#include "CaesarCypher.h"

using namespace std;
#pragma once
class Worker
{
public:
	int registrationID = 0, LoggedWorkerID = 0;
	int WorkerRegistration();
	int WorkerLogin();
	void GetWorkerID();
	int WorkerDeregistration(int WorkerIDValue);
	int WorkerResetPassword(int WorkerIDValue);
	int GetAuthControl(int ID);
private:
	CaesarCypher enc;
	string username, password, auth, activity;
	int AuthorityControl(string personauth, string auth);
	string GetWorkerAuth(int LoggedUserID);
	int WorkerRecordCheck(string workerusername);
	void FileExp();
};