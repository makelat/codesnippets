//An example how to (option 2) and how not to (option 1) loop over a stream.
//  g++ --std=gnu++0x -o whilesstream.exe whilesstream.cxx
//  ./whilesstream.exe
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

int main() {
    stringstream sstream;
    string line = "abc 123";
    string stmp;
    
    //Option 1: this would print the last element twice
    cout << "Option 1:" << endl;
    sstream.str("");  sstream.clear();
    sstream << line;
    while (sstream) {
        sstream >> stmp;
        cout << stmp << endl;
    }
    
    //Option 2: all elements in line printed only once
    cout << "Option 2:" << endl;
    sstream.str("");  sstream.clear();
    sstream << line;
    while (sstream >> stmp) cout << stmp << endl;
    
    return 1;
}
