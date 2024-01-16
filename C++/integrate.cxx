//Basic template for numerical integration.
//See numerical_integration for more developed examples.
//  g++ --std=gnu++0x -o integrateEXE integrate.cxx
//  ./integrateEXE
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>

using namespace std;

//Example function to integrate over
double func(double x) {  
    return x;  
}  

//Simple Riemann method integration
double integrate(double (*funcptr)(double),double xlo, double xhi) {  
    double dx = 0.01*(xhi-xlo);
    double ret=0.0;
    for (double x=xlo+0.5*dx; x<xhi; x+=dx) ret += funcptr(x)*dx;
    return ret;
}

int main() {
  double result = integrate(func,0.0,3.0);
  cout << result << endl;  
  return result;  
} 
