//  g++ --std=gnu++0x -o replaceSubStrEXE replaceSubStr.cxx
//  ./replaceSubStrEXE
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//AUX function to replace all instances of substring "oldsub" by "newsub" in
//the input "instr". Returns a new string.
string replace(string instr, string oldsub, string newsub) {
    string ret = instr;
    if (newsub.find(oldsub)!=string::npos) {
        cout << "WARNING: replace can't handle the following:" <<endl;
        cout << "    instr  = " << instr  << endl;
        cout << "    oldsub = " << oldsub << endl;
        cout << "    newsub = " << newsub << endl;
    } else {
        while (ret.find(oldsub)!=string::npos) {
            string retstart = ret;
            string retend   = ret;
            retstart.erase(retstart.find(oldsub));
            retend.erase(0,retend.find(oldsub)+oldsub.size());
            ret = retstart + newsub + retend;
        }
    }
    return ret;
}

int main(int argc, char* argv[]) {

    string str = "皆様はりんごが大好きです、世界はとても美しい、またね！";
    cout << str << endl;

    string str2 = replace(str,"、","。");
    cout << str2 << endl;

    return 1;
}
