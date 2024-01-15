#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
    
    string greeting = "こんにちは!";  //Default
    
    //Check for user input string, print that instead
    stringstream sstream;
    if (argc>1) {
        sstream << argv[1];
        greeting = sstream.str();
    }
    
    //Output to "console" here, but redirected into a log file in the main script
    cout << greeting << endl;
    return 1;
}
