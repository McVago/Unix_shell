#include "directory.h"

directory::directory(string n,string o)
{
    name = n;
    owner = o;
    parent = NULL;
}

directory::directory(string n,string o,directory* father)
{
    name = n;
    owner = o;
    parent = father;
}

void directory::adddirectory(string n,string o)
{
    directory* newdirectory = new directory(n,o,this);
    directories.push_back(newdirectory);
}

void directory::addarchive(string n,string o)
{
    archive* newarchive = new archive(n,o);
    archives.push_back(newarchive);
}
void directory::removedirectory(string n)
{
    for(vector<directory*>::iterator i = directories.begin(); i < directories.end(); i++)
    {
        if (n == (*i)->name)
            directories.erase(i);
    }
}
directory* directory::changedir(string name)
{
    for(size_t i = 0; i<directories.size(); i++)
    {
        if (name == directories[i]->name)
        {
            return directories[i];
        }
    }
    return 0;
}
