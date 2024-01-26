/* A script to compute MC uncertainties from the results of the runs set up by
 * the MC_unc.C code.
 *
 * Compile & run with:
 *   g++ -std=gnu++0x -o computeMC compute_MC_unc.C
 *   ./computeMC
 */
#include "AUX.h"

int main() {
    
    //Init
    string line;
    string parName;    
    stringstream sstream;
    fstream out;
    ifstream in;
    map< string, vector<string> > parsout;  //<parname, [value,step,lo_bd,...]>
    map< string, pair<double,double> > ret; //<parname, <mean, std.dev> >
    double centVal;

    //Read used random seeds = list of directories
    vector<string> seeds;
    if (!inStreamOpen(in, "seeds.txt")) return -1;
    while (getline(in,line)) seeds.push_back(line);
    in.close();
    if (seeds.size()==0) {
        cout << "ERROR: seeds vector empty" << endl;
        return -1;
    }
    
    //Loop seeds, correspond to individual fit directory names
    double N=0;    //Stepper to count successful fits
    bool nonconverged=true;
    for (int i=0; i!=seeds.size(); ++i) {

        //Checks for fit status, only good fits contribute to mean and RMS
        //finished.txt
        sstream.str("");    sstream.clear();
        sstream << seeds[i] << "/finished.txt";
        if (!inStreamOpen(in, sstream.str())) continue;
        in.close();
        //minuit.out.txt
        sstream.str("");    sstream.clear();
        sstream << seeds[i] << "/output/minuit.out.txt";
        if (!inStreamOpen(in, sstream.str())) continue;
        nonconverged = true;
        while (getline(in,line) && nonconverged) {
            if (line.find("CONVERGED")!=string::npos) nonconverged=false;
        }
        in.close();
        if (nonconverged) {
            cout << seeds[i] << " not converged" << endl;
            continue;
        }
        //Status.out
        sstream.str("");    sstream.clear();
        sstream << seeds[i] << "/output/Status.out";
        if (!inStreamOpen(in, sstream.str())) continue;
        getline(in,line);
        in.close();
        if (line.find("OK")==string::npos) continue;
        
       //Read results from parsout 1 files
        parsout.clear();    sstream.str("");    sstream.clear();
        sstream << seeds[i] << "/output/parsout_1";
        if (!inStreamOpen(in, sstream.str())) continue;
        while (!in.eof()) {
            getline(in,line);
            if (!parsoutChopper(line, parsout)) continue;
        }
        in.close();        

        N += 1.0;

        //Init results map on 1st iteration
        if (i==0) {
            for (auto it=parsout.begin(); it!=parsout.end(); ++it) {
                ret[it->first].first  = 0;
                ret[it->first].second = 0;            
            }
        }
        
        //Begin computing mean and root mean square: sum different parsouts
        for (auto it=parsout.begin(); it!=parsout.end(); ++it) {
            centVal = atof(it->second[0].c_str());
            ret[it->first].first  += centVal;
            ret[it->first].second += centVal*centVal;
        }
        
    } //Loop seeds
    
    //Print stats and prevent unlikely division by zero
    if (N<1.0) {
        cout << "ERROR: no runs had readable parsout_1" << endl;
        return -1;
    } else {
        cout << "\n*** MC uncertainties' fit stats ***"     << endl;
        cout << (int) N << "\tSuccessful runs"              << endl;
        cout << seeds.size() - (int) N << "\tFailed runs\n" << endl;
    }

    //Finalize computing mean and root mean square. Write to file.
    //N.B. std.dev^2 = RMS^2 - mean^2
    string resFile = "MC_results.txt";
    if (!outStreamOpen(out, resFile)) return -1;
    for (auto it=ret.begin(); it!=ret.end(); ++it) {
        ret[it->first].first  *= 1.0/N;
        ret[it->first].second *= 1.0/N;
        ret[it->first].second  = sqrt(     ret[it->first].second
                                      -pow(ret[it->first].first,2));
        //Parameter name
        sstream.str("");  sstream.clear();                                      
        sstream << it->first;
        out << sstream.str();
        for (int i=sstream.str().size(); i<8; ++i) out << " ";
        //Central value
        sstream.str("");  sstream.clear();                                      
        sstream << ret[it->first].first;
        for (int i=sstream.str().size(); i<16; ++i) out << " ";
        out << sstream.str();
        //Uncertainty
        sstream.str("");  sstream.clear();                                      
        sstream << ret[it->first].second << endl;
        for (int i=sstream.str().size(); i<16; ++i) out << " ";
        out << sstream.str();
    }
    out.close();
    cout << "Results printed to " << resFile << endl;
    
    return 1;
}
