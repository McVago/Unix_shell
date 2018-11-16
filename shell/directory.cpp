#include "directory.h"

directory::directory(string n,string o)
{
    name = n;
    owner = o;
}

void directory::adddirectory(string n,string o)
{
    directory* newdirectory = new directory(n,o);
    directories.push_back(newdirectory);
}

void directory::addarchive(string n,string o)
{
    archive* newarchive = new archive(n,o);
    archives.push_back(newarchive);
}
