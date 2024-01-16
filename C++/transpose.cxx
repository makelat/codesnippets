//Take the transpose of a matrix with elements of arbitrary datatype
//  g++ --std=gnu++0x -o transposeEXE transpose.cxx
//  ./transposeEXE
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

//AUX function to transpose a matrix with any data type
template <typename F>
vector< vector<F> > transpose(vector< vector<F> > M) {
    vector< vector<F> > MT;
    vector<F> tmp;
    for (int i=0; i!=M[0].size(); ++i) {
        tmp.clear();
        for (int j=0; j!=M.size(); ++j) tmp.push_back(M[j][i]);
        MT.push_back(tmp);
    }
    return MT;    
}

//AUX function print a matrix with any data type
template <typename F>
void matrixPrinter(vector< vector<F> > M) {
    for (int i=0; i!=M.size(); ++i) {
        for (int j=0; j!=M[i].size(); ++j) {
            cout << setfill(' ') << setw(3) << M[i][j];
        }
        cout << endl;
    }    
}

int main() {
    //Instantiate example matrix
    vector<int> tmp;
    vector< vector<int> > M;
    int Nrow=3, Ncol=4;
    for (int i=0; i!=Ncol; ++i) {
        tmp.clear();
        for (int j=0; j!=Nrow; ++j) tmp.push_back(i*10+j);
        M.push_back(tmp);
    }

    //Transpose
    vector< vector<int> > MT = transpose(M);
    
    //Print
    cout << "The original matrix:" << endl;
    matrixPrinter(M);
    cout << "Transpose:" << endl;
    matrixPrinter(MT);

    return 1;
}
