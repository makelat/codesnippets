//Illustrate the C++ map object, somewhat similar to dictionaries in Python
//  g++ --std=gnu++0x -o mapEXE map.cxx
//  ./mapEXE
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

int main(int argc, char* argv[]) {
    map<string,int> m;
    m["a"] = 1;
    m["c"] = 3;
    m["b"] = 2;
    //Iterate rigorously. Alternatively, could hand-wavingly use "auto it = m.begin()"
    for(map<string,int>::iterator it = m.begin(); it != m.end(); ++it) {
        string key = it->first;  //Could hand-wavingly use "auto key"
        cout << key << ": "<< m[key] << endl;
    }
    return 1;
}
