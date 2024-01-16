//  g++ --std=gnu++0x -o double2stringEXE double2string.cxx
//  ./double2stringEXE
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

//Turn a double e.g. 1.23 into form "1d23", including ndec decimals
string d2str(double num, unsigned int ndec) {
    stringstream sstream;
    sstream << (int) num;
    if (ndec!=0) {
        sstream << "d";
        double dtmp = (pow(10,ndec)*num);
        int itmp = (int)dtmp % (int)pow(10,ndec);
        sstream << itmp;
    }
    return sstream.str();
}

int main() {
    cout << d2str(1.23,0) << endl;
    cout << d2str(1.23,1) << endl;
    cout << d2str(1.23,2) << endl;
    cout << d2str(1.23,3) << endl;
}
