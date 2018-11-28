#include "file_explorer.h"
#include "archive.h"
#include "directory.h"
#include "fstream"
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <QApplication>
#include <iostream>
#include <sys/stat.h>
#include "huffman.cpp"
#include "Node.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

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
        size_t i = 0;
        while (getline(usersfile,line))
        {
            passwords.push_back(encrypt(line,users[i]));
            i++;
        }
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
        file << '\n';
    }
    file.close();
    fstream passfile;
    passfile.open("passwords.txt");
    for(size_t i = 0; i < passwords.size(); i++)
    {
        passfile << encrypt(passwords[i],users[i]);
        passfile << '\n';
    }
    passfile.close();
}
/*  FUNCTION FOR THE TAB AUTOCOMPLETE
int kbhit(int key)
{
    int ch = getch();
    if (ch == key)
    {
        ungetch(ch);
        return 1;
    }
    else
        return 0;
}
*/
bool adduser(vector<string> &users,string newuser)
{
    bool flag = 0;
    for(vector<string>::iterator i = users.begin(); i != users.end(); i++)
    {
        if(*i == newuser)
            flag = 1;
    }
    if(!flag)
    {
        users.push_back(newuser);
        return 1;
    }
    return 0;

}
void createuser(vector<string> &users,vector<string> &passwords,directory &computer)
{
    string newuser;
    string temp;
    char cstr[32];
    char cstr2[32];
    printw("Enter the name of the new user:\n");
    getstr(cstr);
    newuser = cstr;
    if(!adduser(users,cstr))
    {
        printw("User already exists\n");
        return;
    }
    printw("Enter your password\n");
    getstr(cstr2);
    string newpassword = cstr2;
    string password = encrypt(newpassword,newuser);
    passwords.push_back(password);
    computer.adddirectory(newuser,newuser);
    printw("User created\n");
    return;
}
/*
void savedirectoriesaux(directory &current,fstream &file)
{
    file << current.parent->name << '.' << current.parent->owner << ">>" << current.name << '.' << current.owner << '\n';
    if(!current.directories.empty())
    {
        for (size_t i = 0; i< current.directories.size(); i++)
            savedirectoriesaux(*current.directories[i],file);
        return;
    }
    if(!current.archives.empty())
    {
        for (size_t i = 0; i< current.archives.size(); i++)
            file << current.name << '.' << current.owner << ">!" << current.archives[i]->name << current.archives[i]->type << current.archives[i]->owner << '\n';
    }
    return;
}

void savedirectories(directory computer)
{
    fstream file;
    file.open("resources.dat");
    savedirectoriesaux(computer,file);
    file.close();

}

void loaddirectoriesaux(directory current)
{

}
void loaddirectories(directory computer)
{
    fstream file;
    string line;
    file.open("resources.dat");
    if(file.is_open())
    {
        while(getline(file,line))
        {
            size_t pos = 0;
            pos = line.find(">>");
            if(pos != -1)
            {
                for(size_t i = 0; i<computer.directories)
            }
        }
    }
}

void savekey(Node root,string filename)
{
    {
            std::ofstream outFile(filename, std::ios::binary);
            {
                boost::archive::binary_oarchive output(outFile);
                output << root;
            }
    }
}
Node loadkey(string filename)
{
    {
            std::ifstream inFile(filename);
            boost::archive::binary_iarchive input(inFile);
            Node temp;
            input >> temp;
    }
}*/
enum string_code
{
    nothing,
    man,
    mkdirr,
    rm,
    vim,
    ls,
    cd,
    passwd,
    cp,
    mv,
    exitt,
    date,
    clearr,
    cat,
    chmodd,
    compresss,
    decompresss,
};
string_code hashit(string code)
{
    if (code == "")             return nothing;
    if (code == "man")          return man;
    if (code == "mkdir")        return mkdirr;
    if (code == "rm")           return rm;
    if (code == "vim")          return vim;
    if (code == "ls")           return ls;
    if (code == "cd")           return cd;
    if (code == "passwd")       return passwd;
    if (code == "cp")           return cp;
    if (code == "mv")           return mv;
    if (code == "exit")         return exitt;
    if (code == "date")         return date;
    if (code == "clear")        return clearr;
    if (code == "cat")          return cat;
    if (code == "chmod")        return chmodd;
    if (code == "compress")     return compresss;
    if (code == "decompress")   return decompresss;
}

int kbhit(char key)
{
    int ch,r;

    nodelay(stdscr,TRUE);
    noecho();

    ch = getch();
    if (ch != key)
        r = FALSE;
    else
    {
        r = TRUE;
        ungetch(ch);
    }
    echo();
    nodelay(stdscr,FALSE);
    return r;
}
string readfile(string filename)
{
    ifstream file(filename);
    string file_contents { istreambuf_iterator<char>(file), istreambuf_iterator<char>() };
    return file_contents;
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //File_Explorer w;
    //w.show();
    //a.exec();


    vector<string> users;
    vector<string> passwords;
    vector<string> commands;
    string current_line;
    string current_user;
    loadusers(users,passwords);
    directory computer("sda1","root");
    directory* currentdir = &computer;
    initscr();
    noecho();
    string temp;
    while(current_user.empty())
    {
        char newuser[32];
        printw("Please login\nIf new user type register\n");
        refresh();
        echo();
        getstr(newuser);
        string tempuser(newuser);
        if(tempuser == "register")
        {
            createuser(users,passwords,computer);
            saveusers(users,passwords);
        }
        else
        {
            bool flag = 0;
            size_t i = 0;
            for(i = 0; i<users.size(); i++)
            {
                if(users[i] == tempuser)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag)
            {
                char enteredPassword[32];
                string password;
                printw("Please enter your password\n");
                refresh();
                noecho();
                getstr(enteredPassword);
                password = enteredPassword;
                if (password == encrypt(passwords[i],users[i]))
                {
                    printw("Login successful\n");
                    current_user = users[i];
                    currentdir->adddirectory(users[i],users[i]);
                    currentdir = currentdir->changedir(users[i]);
                    chdir("sda1");
                    int fail = chdir(users[i].c_str());
                    if(fail == -1)
                        mkdir(users[i].c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                    chdir(users[i].c_str());
                }
                else
                    printw("Password does not match\n");
            }
            else
                printw("User not recognized\n");
        }
    }
    noecho();
    printw("%s %s ~$",current_user.c_str(),currentdir->name.c_str());
    while(1)
    {
        char a;
        string b;
        a = getch();
        if(a == 127)
        {
            if(!temp.empty())
                temp.pop_back();
            int y, x;
            getyx(stdscr, y, x);
            move(y, 0);
            clrtoeol();
            printw("%s",temp.c_str());
            refresh();
        }
        if(a != 10 && a != 127)
        {
            temp += a;
            printw("%c",a);
            refresh();
        }

        if(a == 10)
        {
            string first,second,third,fourth;
            char forgetstr[128];
            char forgetstr2[128];
            bool flag;
            size_t pos2,pos3,pos4,pos5;
            size_t pos = temp.find(' ');
            time_t T= time(NULL);
            vector<directory*> forls;
            vector<archive*> forls2;
            Node root;
            struct  tm tm = *localtime(&T);
            int failed;
            fstream file,file2;
            CompressedFile compressedfile;
            if(pos == 0)
                first = temp;
            else
                first = temp.substr(0,pos);
            switch(hashit(first))
            {
                case nothing:
                    printw("Unknown command \n");
                    temp.clear();
                    break;
                case man:
                    pos2 = temp.find(' ',pos);
                    second = temp.substr(pos2);
                    refresh();
                    if (second == "mkdir")
                    {
                        printw("mkdir\nNAME\n\t\t mkdir - make directory\nSYNOPSIS\n\t\t mkdir [FILE]\nDESCRIPTION\n\t\t Create the DIRECTORY, if it does not already exist.");
                        refresh();
                    }
                    if (second == "rm")
                        printw("\nrm\nNAME\n\t\trm - remove files or directories\nSYNPOSIS\n\t\trm [FILE]\nDESCRIPTION\n\t\t rm removes each specified file.  By default, it does not remove directories.");
                    if (second == "vim")
                        printw("\nNo manual entry for vim");
                    if (second == "ls")
                        printw("\nls\nNAME\n\t\tls - list directory contents\nSYNOPSIS\n\t\tls []\nDESCRIPTION\n\t\tList  information  about the FILEs (the current directory by default).");
                    if (second == "cd")
                        printw("\ncd\nNAME\n\t\tcd — change the working directory\nSYNOPSIS\n\t\tcd [DIRECTORY]\nDESCRIPTION\n\t\t The cd utility shall change the working directory of the current shell execution environment (see Section 2.12, Shell Execution  Environment) by  executing  the following steps in sequence.");
                    if (second == "clear")
                        printw("\nclear\nNAME\n\t\tclear - clear the terminal screen\nSYNOPSIS\n\t\t clear\nDESCRIPTION\n\t\tclear  clears  your screen if this is possible, including its scrollback buffer (if the extended “E3” capability is defined).  clear looks in the environment for the terminal type given by the environment variable TERM, and then in the terminfo database to determine how to clear the screen.");
                    if (second == "date")
                        printw("\ndate\nNAME\n\t\tdate - print or set the system date and time\nSYNOPSIS\n\t\tdate\nDESCRIPTION\n\t\tDisplay the current time.");
                    if (second == "compress")
                        printw("\ncompress\nNAME\n\t\t compress - compress a file using Huffman's algorithm\nSYNOPSIS\n\t\tcompress [FILENAME]\nDESCRPITION\n\t\t Will compress the selected file and will return 2 files, the compressed file with the same name but in .cmp format and another file that keeps the key to decompress it");
                    if (second == "decompress")
                        printw("\ndecompress\nNAME\n\t\t decompress - decompress a file using Huffman's algorithm\nSYNOPSIS\n\t\tdecompress [FILENAME]\nDESCRPITION\n\t\t Will decompress the selected, must have the key file on the same directory and with the same name, except for the extension. Will return a .txt file with the content of the file decompressed");
                    if (second == "chmod")
                        printw("\nchmod\nNAME\n\t\t chmod - modify file permissions\nSYNOPSIS\n chmod [OCTAL CODE]\nDESCRIPTION\n\t\t Changes the permissions for the file such as Read, Write and execute. In this version only works for octal mode. 4 is used for read rights, 2 for write, 1 for execute. The sum of the values represent either two or all the permissions");
                    if (second == "exit")
                        printw("\nexit\nNAME\n\t\t exit - exit the console\n SYNOPSIS\n\t\t exit \nDESCRIPTION\n\t\t Exits the console.");
                    if (second == "passwd")
                        printw("\npasswd\nNAME\n\t\tpasswd - change user password\nSYNOPSIS\n\t\tpasswd [USER]\nDESCRIPTION\n\t\t Changes the selected user password, if none user selected goes to change root password which is not supported");
                    printw("\n");
                    temp.clear();
                    break;
                case mkdirr:
                    pos2 = temp.find(' ',pos+1);
                    second = temp.substr(pos, pos2);
                    currentdir->adddirectory(second,current_user);
                    failed = mkdir(second.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                    if(-1 == failed)
                        printw("\nDirectory already exists");
                    temp.clear();
                    printw("\n");
                    refresh();
                    break;
                case rm:
                    pos2 = temp.find(' ',pos+1);
                    second = temp.substr(pos, pos2);
                    failed = remove(second.c_str());
                    if(-1 == failed)
                        printw("\nNo such file or directory");
                    temp.clear();
                    printw("\n");
                    refresh();
                    break;
                case vim:

                    break;
                case ls:
                    for(size_t i = 0;i<currentdir->directories.size(); i++)
                        printw("%s ",currentdir->directories[i]->name.c_str());
                    for(size_t i = 0;i<currentdir->archives.size(); i++)
                        printw("%s ",currentdir->archives[i]->name.c_str());
                    temp.clear();
                    break;
                case cd:
                    pos2 = temp.find(' ',pos+1);
                    second = temp.substr(pos,pos2);
                    printw("%s", second.c_str());
                    if (second == "-")
                    {
                        chdir("..");
                        temp.clear();
                    }
                    else
                    {
                        failed = chdir(second.c_str());
                        if(-1 == failed)
                            printw("\n directory doesn't exist");
                        temp.clear();
                        printw("\n");
                        refresh();
                    }
                    break;
                case clearr:
                    clear();
                    refresh();
                    temp.clear();
                    break;
                case date:
                    printw("\n%02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
                    printw(" %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
                    temp.clear();
                    break;
                case compresss:
                    pos2 = temp.find(' ',pos+1);
                    second = temp.substr(pos, pos2);
                    third = readfile(second);
                    compressedfile = compress(third);
                    pos3 = second.find('.',0);
                    fourth = second.substr(0,pos3);
                    fourth.append(".cmp");
                    file.open(fourth);
                    file<< compressedfile.codedtext;
                    file.close();
                    fourth = second.substr(0,pos3);
                    fourth.append(".key");
                    //savekey(compressedfile.root,fourth);
                    temp.clear();
                    break;
                case decompresss:
                    pos2 = temp.find(' ',pos+1);
                    second = temp.substr(pos, pos2);
                    third = readfile(second);
                    pos3 = second.find('.',0);
                    fourth = second.substr(0,pos3);
                    fourth.append(".key");
                    //root = loadkey(fourth);
                    fourth = second.substr(0,pos3);
                    fourth.append(".txt");
                    file.open(fourth);
                    file<< decode(third,&root);
                    file.close();
                    temp.clear();
                    break;
                case chmodd:
                    pos2 = temp.find(' ',pos+1);
                    second = temp.substr(pos, pos2);
                    third = temp.substr(pos2);
                    if (second == "100")
                        chmod(third.c_str(),S_IXUSR);
                    if (second == "110")
                        chmod(third.c_str(),S_IXUSR | S_IXGRP);
                    if (second == "111")
                        chmod(third.c_str(),S_IXUSR | S_IXGRP | S_IXOTH);
                    if (second == "010")
                        chmod(third.c_str(),S_IXGRP | S_IXOTH);
                    if (second == "001")
                        chmod(third.c_str(),S_IXOTH);
                    if (second == "200")
                        chmod(third.c_str(),S_IWUSR);
                    if (second == "210")
                        chmod(third.c_str(),S_IWUSR|S_IXGRP);
                    if (second == "211")
                        chmod(third.c_str(),S_IWUSR|S_IXGRP|S_IXOTH);
                    if (second == "201")
                        chmod(third.c_str(),S_IWUSR|S_IXOTH);
                    if (second == "220")
                        chmod(third.c_str(),S_IWUSR|S_IWOTH);
                    if (second == "221")
                        chmod(third.c_str(),S_IWUSR|S_IWOTH|S_IXOTH);
                    if (second == "222")
                        chmod(third.c_str(),S_IWUSR|S_IWOTH|S_IWOTH);
                    if (second == "300")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR);
                    if (second == "301")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR|S_IXOTH);
                    if (second == "310")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR|S_IXGRP);
                    if (second == "311")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR|S_IXGRP|S_IXOTH);
                    if (second == "320")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR|S_IWGRP);
                    if (second == "321")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR|S_IWGRP|S_IXOTH);
                    if (second == "322")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR|S_IWGRP|S_IXOTH);
                    if (second == "321")
                        chmod(third.c_str(),S_IWUSR|S_IXUSR|S_IWGRP|S_IXGRP|S_IXOTH);
                    if (second == "777")
                        chmod(third.c_str(),S_IRWXU|S_IRWXG|S_IRWXO);
                    chmod(third.c_str(), S_IRWXU);
                    temp.clear();
                    break;
                case exitt:
                    exit(0);
                    break;
                case passwd:
                    pos2 = temp.find(' ',pos+1);
                    if(pos2 != -1)
                    {
                        second = temp.substr(pos, pos2);
                        for (pos5 = 0; pos5<users.size(); pos5++)
                        {
                            if (second == users[pos5])
                                flag = 1;
                        }
                        if(flag)
                        {
                            printw("Insert %s password",second.c_str());
                            getstr(forgetstr);
                            third = forgetstr;
                            if (third == encrypt(passwords[pos5],second))
                            {
                                printw("Insert %s new password",second.c_str());
                                getstr(forgetstr2);
                                fourth = forgetstr2;
                                passwords[pos5] = encrypt(forgetstr2,second);
                            }
                        }


                    }
                    break;

            }
        }



    }



}
