//A demonstration of where passing arguments by reference matters in C++
//  g++ --std=gnu++0x -o matrixAsArgument.exe matrixAsArgument.cxx
//  ./matrixAsArgument.exe
#include <iostream>
#include <vector>

using namespace std;

//Print a matrix. Doesn't matter if reference or not, read only
void printer(vector<vector<int>> matrix) {
  for (int i=0; i!=matrix.size(); ++i) {
    for (int j=0; j!=matrix[i].size(); ++j)  cout << matrix[i][j] << " ";
    cout << endl;
  }
}

//Add +1 to all matrix elements. 
//N.B. here the argument is passed by reference. Otherwise function
//modifies a dummy copy of the argument, returning nothing in this case
//and the "new" matrix would be lost once "adder" exits. With "&",
//the input element is modified, no local copies are made.
void adder(vector<vector<int>>& matrix) {
  for (int i=0; i!=matrix.size(); ++i) {
    for (int j=0; j!=matrix[i].size(); ++j)  matrix[i][j]++;
  }
}

//The main function
int main() {
  vector<vector<int>> M;
  
  //When constructing matrices composed of nested vectors,
  //it must be done line-by-line using an aux vector
  vector<int> auxv;
  for (int i=0; i!=3; ++i) {
    for (int j=0; j!=2; ++j) auxv.push_back(i*j+j);
    M.push_back(auxv);
    auxv.clear();
  }
  
  printer(M);
  adder(M);
  printer(M);
  return 1;
}

