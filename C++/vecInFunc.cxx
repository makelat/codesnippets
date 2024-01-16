//  g++ --std=gnu++0x -o vecInFuncEXE vecInFunc.cxx
//  ./vecInFuncEXE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//An example function to take in 3 vecs and return 3 new appended vecs
//This is not so general but illustrates handy syntax
vector<vector<int>> func3vec(vector<int> a, vector<int> b, vector<int> c) {
    vector<int> a1=a,b1=b,c1=c;
    for (auto tmp : {&a1,&b1,&c1}) tmp->push_back(42);  //Requires ptrs!
    return {a1,b1,c1};
}

//An example function to take in N vecs and return N new appended vecs
vector<vector<int>> funcNvec(vector<vector<int>> Min) {
    vector<vector<int>> Mret;
    for (auto vtmp : Min) {
        vtmp.push_back(137);
        Mret.push_back(vtmp);
    }
    return Mret;
}

//Clear a vectorful of input vectors
void vecClear(vector< vector<int>* > Min) {
    for (auto vtmp : Min) vtmp->clear();
}

int main() {
    vector<int> a0,b0,c0;

    //Ex1 use generic function
    cout << "Ex1:" << endl;
    vector<vector<int>> M = funcNvec({a0,b0,c0});
    vector<int> a1=M[0],b1=M[1],c1=M[2];
    for (int i=0; i!=a1.size(); ++i) {
        cout << a1[i] << ", " << b1[i] << ", " << c1[i] << endl;
    }

    //Ex2 use less general version
    cout << "Ex2:" << endl;
    vector<vector<int>> M1 = func3vec(a0,b0,c0);
    a1=M1[0];  b1=M1[1];  c1=M1[2];
    for (int i=0; i!=a1.size(); ++i) {
        cout << a1[i] << ", " << b1[i] << ", " << c1[i] << endl;
    }

    //Let's clear the modified vecs
    vecClear({&a1,&b1,&c1});
    cout << "Vector sizes after clear:" << endl;
    cout << a1.size() << ", " << b1.size() << ", " << c1.size() << endl;
    
    return 1;
}
