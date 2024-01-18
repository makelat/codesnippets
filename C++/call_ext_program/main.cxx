//N.B. you must have auxEXE ready before running this
//
//A program to call an external program, written in an arbitrary language and 
//precompiled externally. This could be done by system("./auxEXE"); but it is
//quite slow so here we demonstrate a few alternative approaches.
//  - fork & execv: otherwise seems to work fine, but program sometimes never
//                  quits until user gives an input newline...
//  - popen: should do the same as fork & execv do under the hoods. Exits fine,
//           but doesn't output to std::out. 
//
//Compile and usage
//  g++ --std=gnu++0x -o aux.exe aux.cxx
//  g++ --std=gnu++0x -o main.exe main.cxx
//  ./main.exe
//The file "output.txt" will be updated each time to contain the output of 
//aux.exe (a simple string, for checking that the output got there) and
//a string stating which method was last used to call it.
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sys/types.h>
#include <unistd.h> 

using namespace std;

//______________________________________________________________________________
void mySystem() {
    cout << "Running aux.exe using system" << endl;	
    system("./aux.exe mySystem"); 
} //mySystem
//______________________________________________________________________________
void myFork() {
    cout << "Running aux.exe using fork" << endl;	
    char *myArgs[4];
    pid_t pid;
    
    myArgs[0] = "aux.exe";
    myArgs[1] = "myFork";
    myArgs[2] = NULL;

    int n=5;
    for (int i=0; i!=n; ++i) {
        
        switch ((pid = fork())) {
            case -1:  //Fork() failed
                cout << "fork has failed" << endl;
                break;
            case 0:  //This is processed by the new program branch
                execv("aux.exe", myArgs);  //The new branch quits after this
                cout << "ERROR: execv() failed" << endl;
                break;
            default:
                /* This is processed by the parent */
                cout << "Using myFork for the " << i << ":th time" << endl;
                break;
        }

    } //Loop i

} //myFork
//______________________________________________________________________________
void myPOpen() {
    cout << "Running aux.exe using popen" << endl;
    FILE *in = popen("./aux.exe myPOpen", "r");
    pclose(in);
} //myPOpen
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                             THE MAIN FUNCTION                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main(int argc, char* argv[]) {
    stringstream sstream;
    if (argc>1) {
        sstream << argv[1];
        cout << "Main read input: " << sstream.str() << endl;
    } else {
        cout << "Using system() by default. Other options:" << endl;
        cout << "  ./main.exe 1    # using fork & execv" << endl;
        cout << "  ./main.exe 2    # using popen" << endl;
    }
    if      (sstream.str()=="1") myFork();    //Forking should be more efficient
    else if (sstream.str()=="2") myPOpen();   //Perhaps a good alternative
    else                         mySystem();  //system() is easy but inefficient
    return 1;
}
