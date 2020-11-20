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

using namespace std;
#pragma once
class CaesarCypher
{
public :
    string Encryption(string data);
    string Decryption(string data);
private :
    const int key = 5;
    char ch='\0';
};