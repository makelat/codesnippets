//A script to automatically construct directories for xFitter runs to compute
//MC uncertainties.
//
//Compile & run with:
//  g++ -std=gnu++0x -o MC_uncEXE MC_unc.C
//  ./MC_uncEXE
#include "AUX.h"

//AUX function to ensure alphas has lower and upper limit in parameters.yaml
void asLimiter(string dirname, string aslo, string ashi) {

    //Init & open file I/O
    string line, stmp;
    vector<string> vec;
    ifstream in;
    fstream out;
    stringstream sstream;
    sstream << dirname << "/parameters.yaml";
    inStreamOpen(in, sstream.str());
    sstream.str("");  sstream.clear(); //Reinit
    sstream << dirname << "/parameters_asLim.yaml";
    outStreamOpen(out, sstream.str());
    
    while (getline(in,line)) {
        if (line.find("alphas")!=string::npos && 
            line.find(":")!=string::npos      &&
            line.find("[")!=string::npos      && 
            line.find("]")!=string::npos &&
            (line.find("#")==string::npos || 
             line.find("alphas")<line.find("#")))
        {
            line.erase(line.find("alphas"),6);
            line.erase(line.find("["),1);
            line.erase(line.find(":"),1);
            line.erase(line.find("]"),1);
            while (line.find(",")!=string::npos) line.erase(line.find(","),1); 
            sstream.str("");  sstream.clear();
            sstream << line;
            vec.clear();
            while (sstream >> stmp) vec.push_back(stmp);
            while (vec.size()<4) vec.push_back("1.0");
            vec[2] = aslo;  //Lower bd. for alphas
            vec[3] = ashi;  //Upper bd. for alphas
            out << "  alphas: [";
            for (int iv=0; iv!=vec.size(); ++iv) {
                out << " " << vec[iv];
                if (iv < vec.size()-1) out << ",";
            }
            out << " ]" << endl;
        } else out << line << endl;
    }
    in.close();
    out.close();

    //Replace old parameters.yaml w/ new one w/ limits
    sstream.str("");  sstream.clear();
    sstream << "rm " << dirname << "/parameters.yaml";
    system(sstream.str().c_str());
    sstream.str("");  sstream.clear();
    sstream << "mv " << dirname << "/parameters_asLim.yaml"
              << " " << dirname << "/parameters.yaml";
    system(sstream.str().c_str());

} //asLimiter

/* * * * * * * * * * *
 * THE MAIN FUNCTION *
 * * * * * * * * * * */
int main() {
    
// BEGIN user input
    int nMC=1000;
    //string central = "../modelUnc/central/";   //Path to central fit
    string central = "../";          //Path to central fit
    bool asLim = true;  //Ensure upper and lower limit on alpha_s given
    string aslo = "0.112";
    string ashi = "0.120";
// END user input
    
    //Init
    string line;
    string parName;    
    stringstream ss;
    fstream out;
    ifstream in;
    vector<int> seeds;
    int seedtmp;
    int nOldSeeds=0;

    if (central[central.size()-1]!='/') central += "/";
    
    //Read in previous random seeds if existing
    if (inStreamOpen(in, "seeds.txt")) {
        while (!in.eof()) {
            in >> seedtmp;
            seeds.push_back(seedtmp);
        }
        seeds.pop_back();   //Above method duplicated last element
        nOldSeeds=seeds.size();
        in.close();
    } else cout << "Writing new seeds" << endl;
    
    //Generate random seeds
    for (int n=0; n!=nMC; ++n) {
        seedtmp = 1 + (rand() % 1000000);
        if (vecFind(seeds,seedtmp)) --n;
        else seeds.push_back(seedtmp);
    }
    
    //Write random seeds to file
    if (!outStreamOpen(out, "seeds.txt")) return -1;
    for (int i=0; i!=seeds.size(); ++i) out << seeds[i] << endl;
    out.close();
    
    if (seeds.size()==0) {
        cout << "ERROR: seeds vector empty" << endl;
        return -1;
    }
        
    //Construct temp directory, a lighter basis for copying all relevant stuff
    system("mkdir tmpdir");
    ss.str("");    ss.clear();
    ss << "cp  " << central << "parameters.yaml tmpdir";
    system(ss.str().c_str());
    ss.str("");    ss.clear();
    ss << "cp  " << central << "constants.yaml tmpdir";
    system(ss.str().c_str());
    ss.str("");    ss.clear();
    ss << "cp  " << central << "steering.txt tmpdir";
    system(ss.str().c_str());
    ss.str("");    ss.clear();
    ss << "cp  " << central << "cond.sh tmpdir";
    system(ss.str().c_str());
    ss.str("");    ss.clear();
    ss << "cp  " << central << "condor.submit tmpdir";
    system(ss.str().c_str());
    //Read last scan step's result pars, to be made new init pars
    map< string, vector<string> > parsout;  //<parname, (value,step,lo_bd,...])>
    ss.str("");
    ss.clear();
    ss << central << "/output/parsout_1";
    if (!inStreamOpen(in, ss.str())) return -1;
    while (!in.eof()) {
        getline(in,line);
        if (!parsoutChopper(line, parsout)) continue;
    }
    in.close();
   
    /* PARAMETERS.YAML
     */
    bool parsFound = false;
    ss.str("");
    ss.clear();
    ss << central << "/parameters.yaml";
    if (!inStreamOpen(in, ss.str())) return -1;
    ss.str("");
    if (!outStreamOpen(out, "./tmpdir/parameters.yaml")) return -1;

    parsFound = false;
    stringstream parCheck;
    while (!in.eof()) {
        line = "";
        getline(in,line);

        //No need to calculate error bands 
        if (line.find("doErrors")!=string::npos) {
            out << "  doErrors : None # Pumplin # Hesse # None" << endl;
            continue;
	    }
        
        //Find pars' start & end in parameters.yaml (modify that list only)
        if (!parsFound) {
            if (line.find("Parameters:")!=string::npos) parsFound=true;
            out << line << endl;
            continue;
        } else if (line.find(":")==string::npos) {out<<endl;  break;}

        //Parameter lines that are not to be touched
        if (line.find("DEPENDENT")!=string::npos ||
            line.find("not used" )!=string::npos   )
        {
            out << line << endl;
            continue;
        } 

        //Retrieve current parameter name
        parCheck.str("");
        parCheck << line;
        parCheck >> parName;
        if (parName.find(":")!=string::npos) {     
            parName.erase(parName.find(":"),1);
        }

        //Make sure parameter values were found
        if (parsout[parName].size()==0) {
            cout << "WARNING: no par values found for " << parName
                 << "\n  -> will not write to new parameters.yaml" << endl;
            continue;
        }
        
        //Write param values
        out << "  " << parName;
        for (int n=5-parName.size(); n>0; --n) out << " ";
        out << ": [ ";
        for (int n=0; n!=parsout[parName].size(); ++n) {
            if (n!=0) out << ", ";
            out << parsout[parName][n];
        }
        out << " ]" << endl;
    }
    //Simply copy the rest of the file and close
    while (!in.eof()) {
        line = "";
        getline(in,line);
        out << line << endl;
    }
    in.close();
    out.close();

    /* CONDOR.SUBMIT
     * request less time than w/ errors
     */
    ss.str("");  ss.clear();    //Reinit
    ss << central << "/condor.submit";
    if (!inStreamOpen(in, ss.str())) return -1;
    if (!outStreamOpen(out, "tmpdir/condor.submit")) return -1;
    while (!in.eof()) {
        line = "";
        getline(in,line);
        if (line.find("+RequestRuntime")!=string::npos) {
            out << "+RequestRuntime     = 30000" << endl;
        } else out << line << endl;
    }
    in.close();
    out.close();
    
    /* PREPARE NEW DIRECTORIES
     */
    for (int j=nOldSeeds; j!=seeds.size(); ++j) {

        //Copy directories            
        ss.str(""); ss.clear(); //Reinit
        ss << "cp -r " << "tmpdir " << seeds[j];
        system(ss.str().c_str());
                
        /*COND.SH
         * Rename the runs
         */
        ss.str(""); ss.clear(); //Reinit
        ss << seeds[j] << "/cond.sh";
        if (!outStreamOpen(out, ss.str())) return -1;
        if (!inStreamOpen(in, "tmpdir/cond.sh")) return -1;
        if (!in.is_open() ) {
            cout << "ERROR: Can't open tmpdir/cond.sh" << endl;
            return -1;
        }
        while (!in.eof()) {
            line = "";
            getline(in,line);
            out << line;
            if (line.find("JOBNAME")!=string::npos &&
                line.find("echo"   )==string::npos   )
            {
                 out << "_MC" << seeds[j] << endl;
            } else out << endl;
        }
        in.close();
        out.close();

        /* STEERING.TXT
         * enable lRand and set MC method seed
         */
        ss.str("");  ss.clear();    //Reinit
        ss << seeds[j] << "/steering.txt";
        if (!outStreamOpen(out, ss.str())) return -1;
        if (!inStreamOpen(in, "tmpdir/steering.txt")) return -1;
        while (!in.eof()) {
            line = "";
            getline(in,line);
            if (line.find("!")==string::npos && 
                (line.find("lRAND ")!=string::npos ||
                 line.find("lRAND=")!=string::npos   ))
            {
                out << "  lRAND   = True" << endl;
            } else if (line.find("!")==string::npos && 
                       line.find("ISeedMC")!=string::npos)
            {
                out << "  ISeedMC = " << seeds[j] << endl;
            } else out << line << endl;
        }
        in.close();
        out.close();
        
    } //loop seeds

    system("rm -rf tmpdir");

    //Ensure alphas has upper and lower bd.
    stringstream sstream;
    if (asLim) {
		for (int i : seeds)  {
            sstream.str("");  sstream.clear();
            sstream << i; 
		    asLimiter(sstream.str(),aslo,ashi);
        }
    }
        
    //Write submit commands
    sstream.str("");  sstream.clear();
    sstream << "submitToHTC" << nOldSeeds <<  ".sh";
    if (!outStreamOpen(out, sstream.str())) return -1;
    for (int j=nOldSeeds; j!=seeds.size(); ++j) {
        if (j==nOldSeeds) out << "cd ";
        else      out << "cd ../"; 
        out << seeds[j] << endl;
        out << "condor_submit condor.submit" << endl;
    }
    
    out << "cd ..";
    out.close();
    cout << "\nSubmit commands written to " << sstream.str() << "\n" << endl;
    
    return 1;
}
