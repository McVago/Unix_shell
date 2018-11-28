#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <string>
#include <vector>
#include <archive.h>
using namespace std;
class directory
{
public:
    directory(string,string);
    directory(string, string, directory*);
    void adddirectory(string,string);
    void addarchive(string,string);
    directory* changedir(string);
    directory* parent;
    vector<archive*> archives;
    vector<directory*> directories;
    string name;
    string owner;

    void removedirectory(string n);
};

#endif // DIRECTORY_H
