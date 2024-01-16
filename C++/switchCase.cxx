//A simple function to illustrate the use of switch-case structure,
//an efficient alternative for if-else-chains
//  g++ --std=gnu++0x -o switchCase.exe switchCase.cxx
//  ./switchCase.exe
#include <iostream>

using namespace std;

int main() {
  for (int i=0; i!=13; ++i) {
    switch (i) {
      case 0 :
        cout << 0 << endl;
        break;
      case 1 :
      case 2 : cout << "1 or 2" << endl; break;
      case 3 : cout << 3 << endl; break;
      case 4 : cout << 4 << endl; break;
      case 5 : cout << 5 << endl; break;
      case 6 : cout << 6 << endl; break;
      case 7 : cout << 7 << endl; break;
      case 8 : cout << 8 << endl; break;
      case 9 : cout << 9 << endl; break;
      //These can also be nested:
      default : switch (i+1) {
                  case 11 : cout << i << "+1=" << 11 << endl; break;
                  default : cout << "Not 11" << endl; break;
        }
        break;
    }
  }
  return 1;
}

