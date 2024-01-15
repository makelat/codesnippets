//Opening files for input/output in C++ requires a bunch of lines, which can be condensed into a couple
//of auxiliary functions as illustrated here.
//  g++ --std=gnu++0x -o IOtestEXE IOtest.cxx
//  ./IOtestEXE
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
bool outStreamOpen(fstream &out, string filename, bool app=false) {
    out.open(filename.c_str(), ios::out | (app ? ios::app : ios::trunc));
    if (!out.is_open()) {
        cout << "Can't open " << filename << endl;
        return false;        
    } else return true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                             THE MAIN FUNCTION                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main() {
    fstream out;
    ifstream in;
    
    inStreamOpen(in, "test.log");
    if (in.peek() == fstream::traits_type::eof()) cout << "Empty!" << endl;
    else cout << "The first sentence" << endl;
    in.close();
    
    //Erases file, writes content anew
    outStreamOpen(out, "test.log");
    out << "The second sentence" << endl;
    out.close();

    //Erases file, writes content anew
    outStreamOpen(out, "test.log");
    out << "The third sentence" << endl;
    out.close();
    
    //Appends to the file
    outStreamOpen(out, "test.log",true);
    out << "The fourth sentence" << endl;
    out.close();

    
    return 1;
}
