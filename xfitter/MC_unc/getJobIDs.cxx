//A basis for C++ programs to modify a text file
//  g++ --std=gnu++0x -o getJobIDsEXE getJobIDs.cxx
//  ./getJobIDsEXE
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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

int main() {

    ifstream in;
    fstream out;
    string line;
    stringstream sstream;
    
    vector<string> seeds, jobIDs;

    //List all directory names (same as seeds)    
    if (!inStreamOpen(in,"seeds.txt")) return -1;
    while (getline(in,line)) seeds.push_back(line);
    in.close();

    //Determine which jobs can be cancelled
    for (string dir : seeds) {

        //No need to remove finished jobs
        sstream.str("");  sstream.clear();
        sstream << dir << "/finished.txt";
        if (inStreamOpen(in,sstream.str())) {in.close(); continue;}

        //Fetch job ID
        sstream.str("");  sstream.clear();
        sstream << dir << "/scan.log";
        if (!inStreamOpen(in,sstream.str())) return -1;
        //The first line contains the job ID surrounded by parentheses and 0s
        getline(in,line);
        if (line.find(")")!=string::npos) line.erase(line.find(")"));
        if (line.find("(")!=string::npos) line.erase(0,line.find("(")+1);
        if (line.find(".")!=string::npos) line.erase(line.find(".")+2);
        jobIDs.push_back(line);
        
        in.close();
    
    }

    cout << "Found " << jobIDs.size() << " unfinished job IDs: " << endl;
    if (!outStreamOpen(out,"eraser.sh")) return -1;
    for (string ID : jobIDs) {
        sstream.str("");  sstream.clear();
        sstream << "condor_rm "<< ID;
        out << sstream.str() << endl;
    }
    out.close();
    cout << "\n\tJob removal commands written to eraser.sh\n" << endl;
    
    return 1;
}
