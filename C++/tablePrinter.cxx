//Illustrate proper formatting of printout tables, avoiding whitespace offset
//  g++ --std=gnu++0x -o tablePrinter.exe tablePrinter.cxx
//  ./tablePrinter.exe
#include <iomanip>  //setw
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

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


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                             THE MAIN FUNCTION                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main() {
    stringstream sstream;
    for (int i=0; i!=10; ++i) {
        for (int j=0; j!=10; ++j) {
            sstream.str("");  sstream.clear();
            sstream << i << j;
            //This is the line: it works also for file output via fstream
            cout << setfill(' ') << setw(4) << sstream.str();
        }
        cout << endl;
    }
    return 1;
}
