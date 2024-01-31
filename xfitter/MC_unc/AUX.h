//A colection of AUX functions useful for both compute_MC_unc.C and MC_unc.C

#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

/* AUX function to chop a line in parsout lines of the form:
 *    1   'Adbar'  0.180942    0.011586
 *    6   'Bdbar' -0.094421    0.010254   -1.000000  200.000000
 * into a map< par. name, (value,step, opt. boundaries, ...)>.
 * N.B. the exact #entries may be unknown (boundaries maybe not given)
 * Returns:  true/false    extraction successful/unsuccessful
 */
bool parsoutChopper(string parsoutline, map< string, vector<string> >& pout) {

    if (parsoutline.size()==0) return false;

    //Init
    vector<string> vec;     //Read values first into this
    stringstream sstream;
    sstream << parsoutline;
    string stmp="";
    string parName="";

    //Read the values
    while (sstream) {sstream >> stmp;   vec.push_back(stmp);}
    if (vec.size()%2!=0) vec.pop_back();   //sstream loop adds last elem twice

    //Fetch parameter name and remove "'"s.
    if (vec.size()>1) parName = vec[1]; //vec[0] is an unused parameter index
    else return false;
    while (parName.find("'")!=string::npos) {
        parName.erase(parName.find("'"),parName.find("'")+1);
    }

    //Store the values
    for (int i=2; i!=vec.size(); ++i) pout[parName].push_back(vec[i]);

    return true;
}

bool inStreamOpen(ifstream &in, string filename) {
    in.open(filename.c_str());
    if (!in.is_open()) {
        cout << "Can't open " << filename << endl;
        return false;        
    } else return true;
}

bool outStreamOpen(fstream &out, string filename) {
    out.open(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        cout << "Can't open " << filename << endl;
        return false;        
    } else return true;
}

bool vecFind(vector<int> &v, int x) {
    for (int i=0; i!=v.size(); ++i) if (v[i]==x) return true;
    return false;
}
