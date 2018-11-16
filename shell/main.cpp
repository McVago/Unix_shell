#include "file_explorer.h"
#include "archive.h"
#include "directory.h"
#include "fstream"
#include <QApplication>
#include <iostream>
using namespace std;
string encrypt(string password, string key)
{
    string temp(key);
    while (key.size() < password.size())
        key = key + temp;
    for (size_t i = 0; i < password.size(); i++)
        password[i] ^= key[i];
    return password;
}
string decrypt(string password, string key)
{
    return encrypt(password,key);
}

void loadusers(vector<string> &users,vector<string> &passwords)
{
    fstream usersfile;
    string line;
    usersfile.open("users.txt");
    if (usersfile.is_open())
    {
        while (getline(usersfile,line))
            users.push_back(line);
    }
    usersfile.close();
    usersfile.open("passwords.txt");
    if (usersfile.is_open())
    {
        while (getline(usersfile,line))
            passwords.push_back(line);
    }
    usersfile.close();

}

void saveusers(vector<string> users, vector<string> passwords)
{
    fstream file;
    file.open("users.txt");
    for(size_t i = 0; i < users.size(); i++)
    {
        file << users[i];
    }
    file.close();
    file.open("passwords.txt");
    for(size_t i = 0; i < users.size(); i++)
    {
        file << passwords[i];
    }
    file.close();
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //File_Explorer w;
    //w.show();
    //a.exec();
    vector<string> users;
    vector<string> passwords;
    loadusers(users,passwords);

}
