//  g++ --std=gnu++0x -o pathEXE path.cxx
//  ./pathEXE
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//AUX function to check if dir exists, make it recursively if not
void dirCheck(string dir) {

    //Deal w/ terminating '/' and save working copy of dir string
    if (dir[dir.size()-1]=='/') dir.erase(dir.size()-1);
    string path = dir;
    
    //Store system command state, 0 if successful
    int s=system(("ls "+path).c_str());
    if (s!=0) {
        if (path.find("/")!=string::npos) {  //See if previous dir exists
            reverse(path.begin(),path.end());
            path.erase(0,path.find("/"));
            reverse(path.begin(),path.end());
            if (system(("ls "+path).c_str())!=0) dirCheck(path);  //Recursion
        }    
        s = system(("mkdir "+dir).c_str());    
        if (s==0) cout << "-> made " << dir << endl;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                             THE MAIN FUNCTION                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[]) {

    dirCheck("foo/bar/baz/");  //Can have terminating '/' but not necessary
    
    return 1;
}
