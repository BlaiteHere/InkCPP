#include <iostream>
#include <vector>
using namespace std;

struct Blaite{
    int silly;
    float billy;
};


int main() {
    vector<Blaite> spare_parts;
    
    Blaite clone1;
    clone1.billy = 1;
    clone1.silly = 1.0f;
    spare_parts.push_back(clone1);
    clone1.silly = 2;
    clone1.billy = 2.5f;
    cout << spare_parts[0].billy;

    return 0;
}