//Same as numInt, but illustrate passing several input arguments
//  g++ --std=gnu++0x -o numIntMultiPar.exe numIntMultiPar.cxx
//  ./numIntMultiPar.exe
#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

//A numerical function taking 2 args, evetually called via pointer
double func(vector<double> args) {
    if (args.size()==2) return pow(args[0],args[1]);
    cout << "CHECK: func requires exactly 2 arguments!" << endl;
    return 0;
}

//AUX numerical trapezoid integrator w/ simple importance sampling
//Illustrate integrating over x when y has a fixed value
//Param:  fcnPtr   Pointer to the function to be integrated
//        intOver  Index of the variable to integrate over: (x,y)=(0,1)
//        bdlo     Lower boundary for variable to integrate over
//        bdhi     Upper -||-
//        fixed    Vector of values for the variables kept fixed
double integrator(double (*fcnPtr)(vector<double>),
                  int intOver,
                  double bdlo, double bdhi, 
                  vector<double> fixed)
{    
    double nbins = 100;
    double integral = 0.;    
    double dx=0., x=bdlo;    //Stepper temps
    double upbd = 0.0;
    vector<double> pars;
    for (int i=0; i!=fixed.size(); ++i) {
        if (i==intOver) pars.push_back(x);
        pars.push_back(fixed[i]);
    }
    double lobd = fcnPtr(pars);
    for (double ibin=0; ibin < nbins; ibin += 1.) {
        dx = (pow(ibin+1,4)-pow(ibin,4))/pow(nbins,4)*(bdhi-bdlo);
        x += dx;
        pars[intOver] = x;
        upbd = fcnPtr(pars);
        integral += 0.5*(upbd+lobd)*dx; //Trapezoid
        lobd = upbd;
    }        
    return integral;
}

int main() {

    //Pointer to a numerical function taking 2 args
    double (*fptr)(vector<double>);
    fptr = &func;

    double result;
    double xmin=0.0;
    double xmax=1.0;
    
    cout << "Numerical integral results:" << endl;

    //x^y int over x, y=0
    result = integrator(fptr,0,xmin,xmax,{0.});
    cout << "x^0 func\t" << result << endl;

    //x^y int over x, y=1
    result = integrator(fptr,0,xmin,xmax,{1.});
    cout << "x^1 func\t" << result << endl;

    //x^y int over x, y=2
    result = integrator(fptr,0,xmin,xmax,{2.});
    cout << "x^2 func\t" << result << endl;

    return 1;
}
