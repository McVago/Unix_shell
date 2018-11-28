#ifndef ARCHIVE_H
#define ARCHIVE_H
#include <string>
using namespace std;

class archive
{
public:
    archive(string, string);
    string name;
    string type;
    string owner;
};

#endif // ARCHIVE_H
