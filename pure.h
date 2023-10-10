#include "debug.h"
using namespace std;



class Printer
{
    public:
    virtual string print() = 0;
};



class NamePrinter: public Printer
{
    public:
    string name;
    string print() { return name; };
};



class BasicItem {
    //FUNCTIONS FOR ITEM(s)
    virtual void use() = 0;
    virtual void writeDesc() = 0;
};