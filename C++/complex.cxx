//  g++ --std=c++14 -o complexNumbersEXE complexNumbers.cxx
//  ./complexNumbersEXE
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace complex_literals;
 
int main() {
    
    cout << fixed << setprecision(1);  //Print at one decimal accuracy

    //Imaginary
    complex<double> img = 1i;    
    cout << "i         = " << img << endl;
    
    //A few ways to get i^2
    complex<double> z1 = 1i * 1i;
    complex<double> z2 = pow(1i, 2);
    cout << "i*i       = " << z1 << endl;
    cout << "pow(i,2)  = " << z2 << endl;
 
    //Euler's formula
    const double PI = acos(-1);
    complex<double> z3 = exp(1i * PI);
    cout << "exp(i*pi) = " << z3 << endl;

    //Get real and imaginary components
    complex<double> z4    = 1. + 2i;
    cout << "Rea(1+2i) = " << z4.real() << endl;
    cout << "Img(1+2i) = " << z4.imag() << endl;

    //Further complex arithmetic
    cout << "(1+2i) + (1+2i) = " << z4 + z4 << '\n';
    
    //Complex conjugates
    complex<double> z4bar = 1. - 2i;
    cout << "(1+2i)*(1-2i) = " << z4*z4bar << '\n';

}
