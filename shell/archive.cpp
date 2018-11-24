#include "archive.h"
// Remember to verify that archive name has a .something
archive::archive(string n,string o)
{
    string temp;
    size_t pos;
    pos = temp.find(".",0);
    temp = n.substr(0,pos);
    name = temp;
    temp = n.substr(pos,n.length());
    owner = o;
}
