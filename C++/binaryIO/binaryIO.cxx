//Illustrate binary file input/output
//  g++ --std=gnu++0x -o binaryIO.exe binaryIO.cxx
//  ./binaryIO.exe
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main() {
  
    std::random_device rd;
    std::mt19937 gen(rd());  //Mersenne twister
    
    //Write
    fstream out;
    out.open("binaryIO_file.bin", ios::out);
    for (int i=0; i!=10; ++i) {
        double rand = generate_canonical<double, 10>(gen);
        if (rand>0.5) out << true;
        else          out << false;
    }
    out.close();
  
    //Read  
    fstream in;
    in.open("binaryIO_file.bin", ios::in);
    char temp;
    long totReadEvts=0;	//Stepper
    vector<bool> bools;
    for(int i=1; in.read(&temp,1); ++i) {
        ++totReadEvts;
        in.seekg(i);
        if (temp=='1') {
            cout << 1 << endl;
            bools.push_back(true);
        } else {
            cout << 0 << endl;
            bools.push_back(false);
        }
    }
  
    cout << "Read " << totReadEvts << " bytes" << endl;
    cout << "Size of bools vector: " << bools.size() << endl;
  
    in.close();
    return 1;
}

