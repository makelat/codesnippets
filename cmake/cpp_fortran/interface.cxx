/*

gfortran -c prog.f
g++ -c interface.cxx
mv *.o obj
g++ -o testEXE obj/prog.o obj/interface.o -L/usr/lib/gcc/x86_64-linux-gnu/7 -lgfortran
./testEXE

*/

#include <iostream>
#include <stdio.h>

using namespace std;

extern"C" {
    void fortprog_(int *n, float *f);
}


int main() {

    int n=5;
    float f=5.5;

    fortprog_(&n, &f);
    
    return 1;
}













