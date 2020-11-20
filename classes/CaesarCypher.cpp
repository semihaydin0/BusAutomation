//MIT License
//Copyright(c) 2020 Semih Aydýn
//UTF - 8
//Display Languague : Turkish


#include <iostream>
#include <string>

#include "CaesarCypher.h"

using namespace std;

string CaesarCypher::Encryption(string data)
{
    
    for (int i = 0; data[i] != '\0'; ++i)
    {
        ch = data[i];
        
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if (ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
            data[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
            data[i] = ch;
        }
    }
    
    return data;
}
string CaesarCypher::Decryption(string data)
{
    
    for (int i = 0; data[i] != '\0'; ++i)
    {
        ch = data[i];
        
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
            data[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
            data[i] = ch;
        }
    }
    
    return data;
}