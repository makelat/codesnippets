#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include "TAxis.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"

using namespace std;

//AUX functions to open file I/O streams
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

//Aux function to read data
//Pars  fname     Input filename
//      PDFnames  list: "x","g","U","D"... (1st is x, then PDF names)
//      vals      map<par, value, uncertainty>
bool PDFreader(string fname,
                vector<string>& PDFnames,
                map<string,vector<double>>& vals)
{
    //Temps for reading strings and values from files
    string line = "", PDFname="";
    double temp = 0.0;
    stringstream sstream;

    //Open file
    ifstream in;
    if (!inStreamOpen(in,fname)) return false;

    //Read parameter names from 2nd line
    getline(in,line);
    getline(in,line);
    if (PDFnames.size()==0) {   //Only read if not read before
        sstream.str("");  sstream.clear();
        sstream << line;
        while (sstream >> PDFname) PDFnames.push_back(PDFname);
    }

    while (!in.eof()) {
        for (string s : PDFnames) {
            in >> temp;
            if (in.eof()) break;
            vals[s].push_back(temp);
        }        
    }
    in.close();
    return true;
    
}

//______________________________________________________________________________
/* Aux function to check that floats are practically equivalent
 */
bool wInTol(double a, double b) {
    double tol = a*0.0001;
    return (a - tol < b) && (a + tol > b);
}

//______________________________________________________________________________
/* AUX function to read a line in parsout into a 
 * map< "name", pair< value, uncertainty>.
 * The entries in the line are presumed to be of either the forms below:
 *     1   'Adbar'  0.180942    0.011586
 * N.B. we do not care about the boundaries here
 * Returns:  true/false    extraction successful/unsuccessful
 */
void parsoutLineReader(string parsoutline, map< string, pair<double, double> >& pout) {

    //Init
    pair<double, double> valUncPair;     //Read values first into this
    stringstream sstream;
    sstream << parsoutline;
    double val=0, unc=0;
    string parName="";

    //Read the values
    sstream >> val;     //Skip over number, val overwritten later
    sstream >> parName;    //Parameter name
    sstream >> val;
    sstream >> unc;
    
    //Fetch parameter name and remove "'"s.
    while (parName.find("'")!=string::npos) {
        parName.erase(parName.find("'"),parName.find("'")+1);
    }
    
    valUncPair.first= val;
    valUncPair.second = unc;
    pout[parName] = valUncPair;
}
//______________________________________________________________________________
/* A function to read the whole parsout file
 */
bool parsoutReader(string parsoutfile, map< string, pair<double, double> >& pout) {
    string line;
    ifstream in(parsoutfile);
    if (!in.is_open()) {
        cout << "ERROR opening " << parsoutfile << endl;
        return false;        
    }
    while (!in.eof()) {
        getline(in, line);
        parsoutLineReader(line, pout);
    }
    return true;
}
//______________________________________________________________________________
/* Parameters:
 * PDF         Object to store the graph and errors to
 * findPU      Include parameterisation uncertainties? (true/false)
 * findMU      Include model uncertainties? (true/false)
 * findSU      Include scale uncertainties? (true/false)
 * centralDir  Path to central fit directory
 * pathMU      Path to model uncertainties' directories (E.g. "modelUnc_16p/" or "") 
 * pathPU      Path to parameterisation uncertainties' directories
 */
bool graphSetup(TGraphAsymmErrors& PDF,
                bool findPU, bool findMU, bool findSU,
                string centralDir, string pathMU, string pathPU,
                string q2v, string toPlot, int colour, int style) 
{

    PDF.SetFillStyle(style);
    PDF.SetLineColor(colour);
    PDF.SetFillColor(colour);

    //Init
    ifstream in;
    stringstream sstream;
    vector<string> MUsrc;   //Model uncertainty directories
    vector<string> SUsrc;   //Scale uncertainty directories
    vector<string> PUsrc;   //Parameterisation uncertainty directories
    vector<string> names;   //Parameter names will be stored here
    stringstream errss;
    stringstream evnum;     //Construct Eigenvector number
    string line, stmp;
    double centVal, dtmp, dtmplo, dtmphi;

    //Read central values and errors into maps of the form
    //M = < x or PDFname (*), vector< vals for (*) > >
    map<string,vector<double>> cent; //Central PDFs as a map M
    map<string,vector<double>> maptmp, maptmplo, maptmphi;
    vector<map<string,vector<double>>> p;
    vector<map<string,vector<double>>> m;
    vector<map<string,vector<double>>> MU; //Model unc -- Nth vec. elem
    vector<map<string,vector<double>>> SU; //Scale unc   ...is M for
    vector<map<string,vector<double>>> PU; //Param unc   ...Nth unc.src

    sstream.str("");  sstream.clear();
    sstream << centralDir << "output/pdfs_q2val_" << q2v << ".txt";
    if (!PDFreader(sstream.str(), names, cent)) {
        cout << "ERROR could not fetch central PDF" << endl;
        return false;
    }

    bool exhausted=false;
    for (int i=1; i!=100 && !exhausted; ++i) { //Max 99 points safeguard
        for (int pm=0; pm!=2 && !exhausted; ++pm) {
            errss.str("");  errss.clear();
            evnum.str("");  evnum.clear();
            maptmp.clear();
            evnum << (i<10 ? "0" : "") << i;
            errss << centralDir << "output/pdfs_q2val_s" << evnum.str();
            if (pm==0) errss << "p_" << q2v << ".txt";
            else       errss << "m_" << q2v << ".txt";
            if (!PDFreader(errss.str(), names, maptmp)) {
                exhausted=true;
                continue;
            }
            if (pm==0) p.push_back(maptmp);
            else       m.push_back(maptmp);
        }
    }
    if (!exhausted) {
        cout << "ERROR hit evnum safeguard, raise it in code if needed" << endl;
        return false;
    }

    /*************************** MODEL UNCERTAINTIES *************************/

    if (findMU) {

        //Read which directories are to be used
        sstream.str("");  sstream.clear();
        sstream << pathMU << "used_mu_dirs.txt";
        if (!inStreamOpen(in,sstream.str())) return -1;
        while (getline(in,line)) {
            //Erase comments
            while (line.find("#")!=string::npos) line.erase(line.find("#"));
            sstream.str("");  sstream.clear();  //sstream to ignore whitespace
            sstream << line;
            while (sstream >> stmp && stmp.size()!=0) MUsrc.push_back(stmp);
        }
        in.close();

        for (string MUs : MUsrc) {

            //An envelope will later be computed for these cases
            if (MUs.find("asFixlo")!=string::npos) continue;
            if (MUs.find("asFixhi")!=string::npos) continue;

            //Read PDF
            sstream.clear();   sstream.str("");  //Reinit
            sstream << pathMU << MUs
                    << "/output/pdfs_q2val_" << q2v << ".txt";
            if (!PDFreader(sstream.str(), names, maptmp)) return false;

            //Find envelope for asFix cases
            if (MUs.find("asFix"  )!=string::npos) {

                //Read asFixlo PDFs
                sstream.clear();   sstream.str("");  //Reinit
                sstream << pathMU << MUs << "lo"
                        << "/output/pdfs_q2val_" << q2v << ".txt";
                if (!PDFreader(sstream.str(),names,maptmplo)) return false;
                //Read asFixhi PDFs
                sstream.clear();   sstream.str("");  //Reinit
                sstream << pathMU << MUs << "hi"
                        << "/output/pdfs_q2val_" << q2v << ".txt";
                if (!PDFreader(sstream.str(),names,maptmphi)) return false;

                //Compute envelope of maptmp,maptmphi,maptmplo to maptmp
                for (auto it=cent.begin(); it!=cent.end(); ++it) {
                    if (it->first == "x") continue;
                    for (int n=0; n!=it->second.size(); ++n) {
                        centVal = it->second[n];
                        dtmp    =   maptmp[it->first][n];
                        dtmplo  = maptmplo[it->first][n];
                        dtmphi  = maptmphi[it->first][n];
                        if (fabs(dtmp-centVal) < fabs(dtmplo-centVal)) {
                            maptmp[it->first][n] = dtmplo;
                            dtmp = dtmplo;
                        }
                        if (fabs(dtmp-centVal) < fabs(dtmphi-centVal)) {
                            maptmp[it->first][n] = dtmphi;
                        }
                    } //Loop x
                } //Loop central PDFs
            
            } //Find envelope for asFix cases

            MU.push_back(maptmp);  //Save PDF values for later unc comp.

            //Reinit
            maptmp.clear();  
            maptmplo.clear();
            maptmphi.clear();

        } //Loop MU source dir names

    } //if findMU

    /*************************** SCALE UNCERTAINTIES *************************/

    if (findSU) {

        //Read which dirs are to be used
        sstream.str("");  sstream.clear();
        sstream << pathMU << "used_scale_vars.txt";
        if (!inStreamOpen(in, sstream.str())) return false;
        while (getline(in,line)) {
            //Remove comments
            while (line.find("#")!=string::npos) line.erase(line.find("#"));
            if (line.find(pathMU)!=string::npos) { //Remove "../modelUnc/"
                line.erase(line.find(pathMU),line.find(pathMU)+pathMU.size());
            }
            sstream.str("");  sstream.clear();
            sstream << line;
            while (sstream >> stmp && stmp.size()!=0) {
                stmp = pathMU + stmp;
                if (stmp[stmp.size()-1]!='/') stmp += "/";
                SUsrc.push_back(stmp);
            }
        }
        in.close();

        for (string SUs : SUsrc) {
            sstream.clear();   sstream.str("");
            sstream << SUs << "output/pdfs_q2val_" << q2v << ".txt";
            if (!PDFreader(sstream.str(), names, maptmp)) {
                cout << "ERROR PDFreader can't fetch " << sstream.str() << endl;
                return false;
            }
            SU.push_back(maptmp);
            maptmp.clear();
        }
        
    } //if findSU

    /********************* PARAMETERISATION UNCERTAINTIES ********************/

    if (findPU) {

        //If dirs not given, find which ones exist and use all
        sstream.clear();  sstream.str("");
        sstream << "ls " << pathPU << "used_pu_dirs.txt";
        if (system(sstream.str().c_str())!=0) {  //If ls can't find this
            sstream.clear();  sstream.str("");
            sstream << "ls -d " << pathPU << "*/ > " << pathPU << "used_pu_dirs.txt"; 
            system(sstream.str().c_str());
        }


        //Read which PU dirs are to be used
        sstream.str("");  sstream.clear();
        sstream << pathPU << "used_pu_dirs.txt";
        if (!inStreamOpen(in, sstream.str())) return false;
        while (getline(in,line)) {
            //Remove comments
            while (line.find("#")!=string::npos) line.erase(line.find("#"));
            if (line.find(pathPU)!=string::npos) { //Remove "../paramUnc/"
                line.erase(line.find(pathPU),line.find(pathPU)+pathPU.size());
            }
            sstream.str("");  sstream.clear();
            sstream << line;
            while (sstream >> stmp && stmp.size()!=0) {
                stmp = pathPU + stmp;
                if (stmp[stmp.size()-1]!='/') stmp += "/";
                PUsrc.push_back(stmp);
            }
        }
        in.close();

        for (string PUs : PUsrc) {
            sstream.clear();   sstream.str("");
            sstream << PUs << "output/pdfs_q2val_" << q2v << ".txt";
            if (!PDFreader(sstream.str(), names, maptmp)) {
                cout << "ERROR PDFreader can't fetch " << sstream.str() << endl;
                return false;
            }
            PU.push_back(maptmp);
            maptmp.clear();
        }
        
    }

    /**************************************************************************/

    //PDF graphs
    map<string,TGraphAsymmErrors> PDFs;
    double mtmp=0.0, ptmp=0.0, mtmpsqrt,ptmpsqrt, MUtmp, PUtmp, SUtmp;
    for (string s : names) {
        if (s=="x") continue;		//Would give only f(x)=x

        //Read values to graphs
        for (int ix=0; ix!=cent["x"].size(); ++ix) {
            PDFs[s].SetPoint(ix,cent["x"][ix],cent[s][ix]);
            if (s==toPlot) PDF.SetPoint(ix,cent["x"][ix],cent[s][ix]);
            
            //Param uncert.: add Eigenvec. elem.s in quadrature (asymm.)
            mtmp=0;  ptmp=0;    //Reinit temps
            for (int k=0; k!=m.size(); ++k) {
                mtmp += pow((fabs(cent[s][ix]) - fabs(m[k][s][ix])),2);
                ptmp += pow((fabs(p[k][s][ix]) - fabs(cent[s][ix])),2);
                
                //Check that x values agree
                if (!wInTol(cent["x"][ix], m[k]["x"][ix]) ||
                    !wInTol(cent["x"][ix], p[k]["x"][ix])   )
                {
                    cout<<"ERROR cent & m/p x values disagree:"<<endl;
                    return false;
                }
                
            } //Loop over m (index k)

            /*** Model unc. contributions summed in quadrature ***/

            //N.B. sources with fixed alpha_s are combined into one 
            //     envelope above, the envelope is added into MU as one
            //     source and then summed in quadrature to the others.

            if (findMU) {
                for (int k=0; k!=MU.size(); ++k) {

                    if (!wInTol(cent["x"][ix], MU[k]["x"][ix])) {
                        cout << "ERROR cent & MU x values don't agree"
                             << endl;
                        return false;
                    }
                    MUtmp=pow(fabs(MU[k][s][ix])-fabs(cent[s][ix]),2.0);
                    mtmp += MUtmp;
                    ptmp += MUtmp;
                } //Loop over MU (index k)
            }

            /*** Scale unc. added as max. envelope (sym.) at each x ***/

            if (findSU) {
                SUtmp=0.0;
                for (int k=0; k!=SU.size(); ++k) {
                    if (!wInTol(cent["x"][ix], SU[k]["x"][ix])) {
                        cout << "ERROR paramUnc x don't agree" << endl;
                        return false;
                    }
                    SUtmp=max( fabs( fabs(SU[k][s][ix])
                                    -fabs(cent[s][ix])), SUtmp );
                } //Loop over PU sources (index k)                
                mtmp += SUtmp*SUtmp;
                ptmp += SUtmp*SUtmp;
            }
                        
            /*** Param unc max envelope (sym) added linearly at each x ***/

            mtmpsqrt=sqrt(mtmp);
            ptmpsqrt=sqrt(ptmp);

            if (findPU) {
                PUtmp=0.0;
                for (int k=0; k!=PU.size(); ++k) {
                    if (!wInTol(cent["x"][ix], PU[k]["x"][ix])) {
                        cout << "ERROR paramUnc x don't agree" << endl;
                        return false;
                    }
                    PUtmp=max( fabs( fabs(PU[k][s][ix])
                                    -fabs(cent[s][ix])), PUtmp );
                } //Loop over PU sources (index k)                
                mtmp += PUtmp*PUtmp;  //Redundant, left for reference
                ptmp += PUtmp*PUtmp;  //Redundant, left for reference
                mtmpsqrt += PUtmp;
                ptmpsqrt += PUtmp;
            }
            
            /*** Set computed error band to PDF graph at this x ***/
            
            PDFs[s].SetPointError(ix,0,0,mtmpsqrt,ptmpsqrt);
            if (s==toPlot) PDF.SetPointError(ix,0,0,mtmpsqrt,ptmpsqrt);
            
        } // Loop x & Read values to graphs

    } //Go through names vec.

    return true;
    
} //graphSetup
//______________________________________________________________________________
//Plot each n:th element in gVec divided by the 0:th
//Input:    gVec        vector of graphs, 0th element as the reference
//          lgstr       legend text
//          plotname    name of saved file, including datatype suffix
//          yAxisTitle  Plot vertical axis title
//          Q2str       Q^2 value printed as TLatex on the plot
//          relErr      true=plot like xfitter-draw --relative-errors
bool graphRatio(vector<TGraphAsymmErrors*> gVec, vector<string> lgstr,
                string plotname, string yAxisTitle, string Q2str,
                bool relErr)
{
    //For valence quarks, ensure there are no >0 fluctuations at high x
    bool absVals = plotname.find("_val")!=string::npos ? true : false;
    
    if (gVec.size()==0) return false;

    for (int i=1; i<gVec.size(); ++i) {    
        if (gVec[0]->GetN() != gVec[i]->GetN()) {
            cout << "ERROR in graphRatio: gVec sizes disagree at 0 &" << i
                 << ": "   << gVec[0]->GetN()
                 << " != " << gVec[i]->GetN() << endl;
           	return false;
        }
    }

    //Read Points from gVec
    double xRef, yRef;
    double xCmp, yCmp, yerrlo, yerrhi;    
    for (int n=0; n!=gVec[0]->GetN(); ++n) {
        gVec[0]->GetPoint(n,xRef,yRef);
        yRef = absVals ? fabs(yRef) : yRef;
        for (int i=0; i!=gVec.size(); ++i) {
            gVec[i]->GetPoint(n,xCmp,yCmp);
            yCmp = absVals ? fabs(yCmp) : yCmp;
            yerrlo=gVec[i]->GetErrorYlow(n);
            yerrhi=gVec[i]->GetErrorYhigh(n);
            if (!wInTol(xRef,xCmp)) cout<<"WARNING: xRef=/=xCmp at"<<n<<endl;
            gVec[i]->SetPoint(n,xCmp,relErr ? yRef : yCmp/yRef);
            gVec[i]->SetPointError(n,0,0,yerrlo/yRef,yerrhi/yRef);
        }
    }

    //Canvas and axes setup
    TCanvas canv("","",400,400);
    canv.SetLogx();
    canv.SetTopMargin(0.02);
    canv.SetRightMargin(0.01);
    TGraph setup;
    setup.SetMarkerSize(0.0);
    setup.SetMarkerColor(kWhite);
    double ylo=0.8,yhi=1.2;
    if      (Q2str=="1.9"  ) {ylo = 0.1;  yhi = 1.9;} 
    else if (Q2str=="4.0"  ) {ylo = 0.2;  yhi = 1.8;} 
    else if (Q2str=="7.0"  ) {ylo = 0.3;  yhi = 1.7;} 
    else if (Q2str=="10"   ) {ylo = 0.4;  yhi = 1.6;} 
    else if (Q2str=="100"  ) {ylo = 0.4;  yhi = 1.6;} 
    else if (Q2str=="1000" ) {ylo = 0.5;  yhi = 1.5;} 
    else if (Q2str=="30000") {ylo = 0.6;  yhi = 1.4;} 
    setup.SetPoint(0,0.0,ylo);
    setup.SetPoint(1,0.9,yhi);
    setup.GetXaxis()->SetTitle("#font[12]{x}");
    setup.GetYaxis()->SetTitle(yAxisTitle.c_str());
    setup.GetYaxis()->SetTitleOffset(1.2);
    setup.Draw("AP");

    //Plot
    for (int i=0; i!=gVec.size(); ++i) gVec[i]->Draw("SAME C3");

    //Legend
    double hmin=0.12, hmax=0.5, vmax=0.97;
    double vmin = vmax - lgstr.size()*0.0333;
    TLegend lg(hmin, vmin, hmax, vmax);
    lg.SetFillStyle(0);  lg.SetBorderSize(0);
    if (gVec.size()==lgstr.size()) {
        for (int i=0; i!=gVec.size(); ++i) {
            lg.AddEntry(gVec[i], lgstr[i].c_str(), "f");
        }
        lg.Draw();
    } else cout <<"WARNING: #graphs != #legend texts, omitting" << endl;

    //Write Q^2 value over plot
    TLatex lat;
    stringstream sstream;
    lat.SetTextFont(132);
    sstream.str("");  sstream.clear();
    sstream << "Q^{2} = " << Q2str << " GeV^{2}";
    lat.DrawLatex(0.01,ylo,sstream.str().c_str());

    //Save plot
    canv.Print(plotname.c_str());

    //Save ROOT file
    string rootname = plotname;
    if (rootname.find(".pdf")!=string::npos) {
        rootname.erase(rootname.find(".pdf"));
    }
    rootname += ".root";
    TFile out_file(rootname.c_str(),"RECREATE");
    for (auto g : gVec) g->Write();
    out_file.Close();

    return true;

} //graphRatio
