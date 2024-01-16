//  g++ --std=gnu++0x -o doubleComparisonEXE doubleComparison.cxx
//  ./doubleComparisonEXE
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

bool dAgree(double a, double b, double tol=0.001) {
    return (a*(1.+tol) > b) && (a*(1.-tol) < b); 
}

int main() {
    cout << "1.1==1.1: "
         << dAgree(1.1,1.1)
         << endl;
    cout << "1.1==1.2: " 
         << dAgree(1.1,1.2)
         << endl;
    cout << "1.1==1.2: "
         << dAgree(1.1,1.2,0.1)
         << " (using 10\% tolerance)"
         << endl;
    return 1;
}
