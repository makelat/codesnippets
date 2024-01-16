//Illustrate splitting a string of argument values at commas
//  g++ --std=gnu++0x -o stringSplitEXE stringSplit.cxx
//  ./stringSplitEXE
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

vector<int> stringSplit(string str) {
    //Remove string parts outside of the vector/array
    if (str.find("[")!=string::npos) str.erase(0,str.find("[")+1);
    if (str.find("]")!=string::npos) str.erase(str.find("]"));
    stringstream sstream(str);
    vector<string> vs;
    vector<int> vi;
    int itmp;
    while(sstream.good()) {
        string substr;
        getline(sstream, substr, ',');
        vs.push_back(substr);
    }
    for (string s : vs) {
        sstream.str("");  sstream.clear();
        sstream << s;
        sstream >> itmp;
        vi.push_back(itmp);
    }
    return vi;
}

int main() {
    auto vec = stringSplit(" [ 1, 2,  3,137 ]");
    for (auto x : vec) cout << x << endl;
    return 1;
}
