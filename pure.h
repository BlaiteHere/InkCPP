#include "debug.h"
using namespace std;



class Printer
{
    public:
    virtual string print() const = 0;
};



class NamePrinter: public Printer
{
    public:
    string name;
    string print() const { return name; };
};



class BasicItem {
    //FUNCTIONS FOR ITEM(s)
    virtual void use() const = 0;
    virtual void writeDesc() const = 0;
};