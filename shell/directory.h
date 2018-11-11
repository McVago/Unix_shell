#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <string>
#include <vector>
#include <archive.h>
using namespace std;
class directory
{
public:
    //Public Functions
    directory(string,string);
    void adddirectory(string,string);
    void addarchive(string,string);

private:
    string name;
    string owner;
    vector<archive> archives;
    vector<directory> directories;
};

#endif // DIRECTORY_H
