//An example of numerically integrating over a generic function,
//called via a function pointer in the integrator
//  g++ --std=gnu++0x -o numInt.exe numInt.cxx
//  ./numInt.exe
#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

//Example numeric functions, evetually make pointers to these
double func0(double x) {return 137.0;}
double func1(double x) {return x;    }
double func2(double x) {return x*x;  }

//AUX numerical trapezoid integrator w/ simple importance sampling
double integrator(double (*fcnPtr)(double), double xmin, double xmax) {
    
    double nbins = 100;
    double integral = 0.;    
    double dx=0., x=xmin;    //Stepper temps
    double upbd = 0.0;
    double lobd = fcnPtr(xmin);
    for (double ibin=0; ibin < nbins; ibin += 1.) {
        dx = (pow(ibin+1,4)-pow(ibin,4))/pow(nbins,4)*(xmax-xmin);
        x += dx;
        upbd = fcnPtr(x);
        integral += 0.5*(upbd+lobd)*dx; //Trapezoid
        lobd = upbd;
    }        
    return integral;
}

int main() {

    //Pointer to a numerical function
    double (*fptr)(double);
    fptr = &func0;

    double result;
    double xmin=0.0;
    double xmax=1.0;
    
    cout << "Numerical integral results:" << endl;

    result = integrator(fptr,xmin,xmax);
    cout << "func0\t" << result << endl;

    fptr = &func1;
    result = integrator(fptr,xmin,xmax);
    cout << "func1\t" << result << endl;

    fptr = &func2;
    result = integrator(fptr,xmin,xmax);
    cout << "func2\t" << result << endl;
    
    return 1;
}
