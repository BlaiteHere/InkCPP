using namespace std;


class Printer
{
    public:
    virtual string print() = 0;
};


class NamePrinter: public Printer
{
    string name;
    public:
    string print() { return name; };
};