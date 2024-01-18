//This produces the external program, called in various ways inside main
//  g++ --std=gnu++0x -o aux.exe aux.cxx
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

//AUX functions to open file I/O streams
bool inStreamOpen(ifstream &in, string filename) {
    in.open(filename.c_str());
    if (!in.is_open()) {
        cout << "Can't open " << filename << endl;
        return false;        
    } else return true;
}
bool outStreamOpen(fstream &out, string filename) {
    out.open(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        cout << "Can't open " << filename << endl;
        return false;        
    } else return true;
}

//The main function
int main(int argc, char* argv[]) {
    fstream out;
    outStreamOpen(out,"output.txt");
    out << "こんにちわ！私はauxEXEです。" << endl;
    stringstream sstream;
    if (argc>1) {
        for (int i=1; i<argc; ++i) {
            sstream.str("");  sstream.clear();
            sstream << argv[i];
            out << sstream.str() << " ";
        }
        out << endl;
    }
    out.close();
    return 1;
}
