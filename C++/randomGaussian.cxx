//Illustrate generating Gaussian random numbers using C++ features
//  g++ $(root-config --cflags --glibs) --std=gnu++0x -o randomGaussian.exe randomGaussian.cxx
//  ./randomGaussian.exe
#include <iostream>
#include <random>
#include <vector>

using namespace std;

//Generate & print univariate Gaussian random numbers
void printRands(int N) {
    //Init generator
    default_random_engine generator;
    normal_distribution<double> distribution(0.0,1.0);
    vector<double> rands;
    for (int n=0; n!=N; ++n) rands.push_back(distribution(generator));
    for (double r : rands) cout << "  " << r << endl;
}

int main() {
    int N=3;  //How many numbers to generate per function call
    cout << "1st printRands call: " << endl;
    printRands(N);
    cout << "2nd printRands call: outcome=same, as gen init w/in func" << endl;
    printRands(N);
    return 1;
}
