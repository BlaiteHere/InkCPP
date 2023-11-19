#include "debug.h"
using namespace std;



class NamePrinter
{
public:
    string name;

    virtual const string getName() const
    {
        return name;
    }
};



class CharType
{
public:
    char type;

    virtual const char getType() const
    {
        return type;
    }
};



class ThreeLayerDrawable
{
public:
    char layers[3][4];


    ThreeLayerDrawable () {}


    ThreeLayerDrawable (
        const char layerone[4], 
        const char layertwo[4], 
        const char layerthree[4]
    )
    {
        for(int i=0; i<3; i++)
            layers[0][i] = layerone[i];
        layers[0][3] = 0;
        
        for(int i=0; i<3; i++)
            layers[1][i] = layertwo[i];
        layers[1][3] = 0;

        for(int i=0; i<3; i++)
            layers[2][i] = layerthree[i];
        layers[2][3] = 0;
    }


    ThreeLayerDrawable (
        string layerone, 
        string layertwo, 
        string layerthree
    )
    {
        for(int i=0; i<3; i++)
            layers[0][i] = layerone[i];
        layers[0][3] = 0;
        
        for(int i=0; i<3; i++)
            layers[1][i] = layertwo[i];
        layers[1][3] = 0;

        for(int i=0; i<3; i++)
            layers[2][i] = layerthree[i];
        layers[2][3] = 0;
    }


    string print() const 
    {
        string myPrint = "";
        for(int i=0; i<3; i++)
        {
            myPrint += layers[i] + '\n';
        }

        return myPrint;
    }
};