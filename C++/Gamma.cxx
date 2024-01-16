//Numerical implementation of the Euler Gamma function and its first derivative
//  g++ --std=gnu++0x -o GammaEXE Gamma.cxx
//  ./GammaEXE
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
//#include "TCanvas.h"
//#include "TH2.h"
//#include "TLatex.h"

using namespace std;

double EulerGamma(double z) {
    double infty=1e3;  //Approx infinity, accurate to  6th decimal
    double dt=0.01;
    double ret=0, last=0, next=0;
    for (double t=dt; t<infty; t+=dt) {
        next = dt*pow(t,z-1.)*exp(-t);
        ret += 0.5*(last+next);
        last=next;
    }
    return ret;
}

//First derivative of EulerGamma w.r.t. the argument z
double EulerGammaDer(double z) {
    double infty=1e3;  //Approx infinity, accurate to  6th decimal
    double dt=0.01;
    double ret=0, last=0, next=0;
    for (double t=dt; t<infty; t+=dt) {
        next = dt*pow(t,z-1.)*exp(-t)*log(t);
        ret += 0.5*(last+next);
        last=next;
    }
    return ret;
}

int main(int argc, char* argv[]) {
    for (double z=1.0; z<5.0; z+=0.5) {
        cout << "EulerGamma("    << z << ")=" << EulerGamma(   z) << endl;
        cout << "EulerGammaDer(" << z << ")=" << EulerGammaDer(z) << endl;
    }
    return 1;
}
