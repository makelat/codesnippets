//A program to combine plots from multiple ROOT files to a single canvas
//  g++ multiplot_MC.cxx $(root-config --cflags --glibs) -std=gnu++0x  -o multiplotEXE
//  ./multiplotEXE

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "../MCplotAUX.h"

using namespace std;

//Return a suitable y-axis upper limit for PDF plot (1) and ratio plot (2)
pair<double,double> uplim(string toPlot, string q2v) {
    if (toPlot=="u_val") {
        if      (q2v=="01") return {0.8, 1.5};    //Good for 1.9 GeV^2
        else if (q2v=="02") return {0.8, 2.0};    //   -||-    4 GeV^2
        else if (q2v=="03") return {0.8, 2.0};    //   -||-    7 GeV^2
        else if (q2v=="04") return {0.8, 2.0};    //   -||-   10 GeV^2
        else if (q2v=="05") return {0.7, 2.0};    //   -||-  100 GeV^2
        else if (q2v=="06") return {0.7, 2.0};    //   -||-   1k GeV^2
        else if (q2v=="07") return {0.7, 1.075};  //   -||-  30k GeV^2
    } else if (toPlot=="d_val") {
        if      (q2v=="01") return {0.5, 1.5};    //Good for 1.9 GeV^2
        else if (q2v=="02") return {0.5, 2.0};    //   -||-    4 GeV^2
        else if (q2v=="03") return {0.5, 2.0};    //   -||-    7 GeV^2
        else if (q2v=="04") return {0.5, 2.0};    //   -||-   10 GeV^2
        else if (q2v=="05") return {0.4, 2.0};    //   -||-  100 GeV^2
        else if (q2v=="06") return {0.4, 2.0};    //   -||-   1k GeV^2
        else if (q2v=="07") return {0.4, 1.23};   //   -||-  30k GeV^2
    } else if (toPlot=="g") {
        if      (q2v=="01") return {4.0 , 1.5};   //Good for 1.9 GeV^2
        else if (q2v=="02") return {10.0 , 2.0};   //   -||-    4 GeV^2
        else if (q2v=="03") return {15.0, 2.0};   //   -||-    7 GeV^2
        else if (q2v=="04") return {20.0, 2.0};   //   -||-   10 GeV^2
        else if (q2v=="05") return {50.0, 2.0};   //   -||-  100 GeV^2
        else if (q2v=="06") return {80.0, 2.0};   //   -||-   1k GeV^2
        else if (q2v=="07") return {110.0,1.11};  //   -||- 30k GeV^2
    } else if (toPlot=="sea") {
        if      (q2v=="01") return {1.6, 1.55};   //Good for 1.9 GeV^2
        else if (q2v=="02") return {2.5, 2.0};    //   -||-    4 GeV^2
        else if (q2v=="03") return {3.0, 2.0};    //   -||-    7 GeV^2
        else if (q2v=="04") return {4.0, 2.0};    //   -||-   10 GeV^2
        else if (q2v=="05") return {8.0, 2.0};    //   -||-  100 GeV^2
        else if (q2v=="06") return {13.0,2.0};    //   -||-   1k GeV^2
        else if (q2v=="07") return {21.0,1.3};    //   -||-  30k GeV^2
    } else if (toPlot=="U" || toPlot=="D") {
        if      (q2v=="01") return {4.0 , 2.0};   //Good for 1.9 GeV^2
        else if (q2v=="02") return {8.0 , 2.0};   //   -||-    4 GeV^2
        else if (q2v=="03") return {10.0, 2.0};   //   -||-    7 GeV^2
        else if (q2v=="04") return {10.0, 2.0};   //   -||-   10 GeV^2
        else if (q2v=="05") return {20.0, 2.0};   //   -||-  100 GeV^2
        else if (q2v=="06") return {25.0, 2.0};   //   -||-   1k GeV^2
        else if (q2v=="07") return {30.0, 2.0};   //   -||-  30k GeV^2
    } else if (toPlot=="u_sea" || toPlot=="d_sea" ||
               toPlot=="Ubar"  || toPlot=="Dbar"    )
    {
        if      (q2v=="01") return {0.6, 2.0};    //Good for 1.9 GeV^2
        else if (q2v=="02") return {0.8, 2.0};    //   -||-    4 GeV^2
        else if (q2v=="03") return {1.2, 2.0};    //   -||-    7 GeV^2
        else if (q2v=="04") return {1.5, 2.0};    //   -||-   10 GeV^2
        else if (q2v=="05") return {2.0, 2.0};    //   -||-  100 GeV^2
        else if (q2v=="06") return {2.5, 2.0};    //   -||-   1k GeV^2
        else if (q2v=="07") return {3.0, 2.0};    //   -||-  30k GeV^2
    } else if (toPlot=="str" || toPlot=="strbar") {
        if      (q2v=="01") return {0.4, 2.0};    //Good for 1.9 GeV^2
        else if (q2v=="02") return {0.6, 2.0};    //   -||-    4 GeV^2
        else if (q2v=="03") return {0.8, 2.0};    //   -||-    7 GeV^2
        else if (q2v=="04") return {1.2, 2.0};    //   -||-   10 GeV^2
        else if (q2v=="05") return {2.0, 2.0};    //   -||-  100 GeV^2
        else if (q2v=="06") return {2.5, 2.0};    //   -||-   1k GeV^2
        else if (q2v=="07") return {3.0, 2.0};    //   -||-  30k GeV^2
    } else {
        cout << "Warning: Urecognized toPlot and q2v in uplim" << endl;
        return {10.0,2.2};
    }
} //uplim

//Parameters:    Plot PDF     "g","U","D","Ubar","Dbar","u_val","d_val","sea",
//                            "u_sea","d_sea","str","chm","bot","ph","strbar"
//               Nq2v         Number of the Q^2 value to plot
int plotCombiner(string toPlot, int Nq2v) {

    stringstream sstream;
    ifstream in;
    string line;
    if (Nq2v<10) sstream << "0";
    sstream << Nq2v;
    string q2v = sstream.str();
    
    //Canvas and division into parts
    TCanvas* canv = new TCanvas("","",600,600);

    //Retrieve graphs
    static int const Npads=2, Ngraphs=2;
    TGraphAsymmErrors* g[Npads][Ngraphs]; //Indexing [PDF/relErr][plot index]
    
    vector<string> fnames;
    sstream.str("");  sstream.clear();
    sstream << toPlot << "_q2-" << q2v << ".root";
    fnames.push_back(sstream.str());
    sstream.str("");  sstream.clear();
    sstream << toPlot << "_q2-" << q2v << "_ratio_relErr.root";
    fnames.push_back(sstream.str());
    vector<string> gnames={";1",";2",";3",";4"};
    for (int m=0; m!=Npads; ++m) {
        TFile *in  = TFile::Open(fnames[m].c_str(),"READ");
        for (int n=0; n!=Ngraphs; ++n) {
            g[m][n] = new TGraphAsymmErrors();
            in->GetObject(gnames[n].c_str(), g[m][n]);
        }
        in->Close();
    }

    string yTitle;
    if      (toPlot=="g"    ) yTitle="#font[62]{x #bullet g (x, Q^{2})}";
    else if (toPlot=="u_val") yTitle="#font[62]{x #bullet u_{v} (x, Q^{2})}";
    else if (toPlot=="d_val") yTitle="#font[62]{x #bullet d_{v} (x, Q^{2})}";
    else if (toPlot=="U"    ) yTitle="#font[62]{x #bullet D (x, Q^{2})}";
    else if (toPlot=="D"    ) yTitle="#font[62]{x #bullet D (x, Q^{2})}";
    else if (toPlot=="chm"  ) yTitle="#font[62]{x #bullet c (x, Q^{2})}";
    else if (toPlot=="str"  ) yTitle="#font[62]{x #bullet s (x, Q^{2})}";
    else if (toPlot=="sea"  ) yTitle="#font[62]{x #bullet #Sigma (x, Q^{2})}";
    else                      yTitle="#font[62]{x #bullet f (x, Q^{2})}";
    
    //Set axis labels etc. for PDF plot
    double setupxlo=0.0001, setupxhi=0.57;
    TGraph* setup  = new TGraph();
    setup->SetPoint(0,setupxlo,0);
    setup->SetPoint(1,setupxhi,uplim(toPlot,q2v).first);
    setup->SetMarkerSize(0);
    setup->SetMarkerColor(kWhite);
    setup->GetYaxis()->SetLabelFont(62);
    setup->GetYaxis()->SetTitle(yTitle.c_str());
    setup->GetYaxis()->SetTitleFont(133);
    setup->GetXaxis()->SetTitleFont(133);
    setup->GetYaxis()->SetTitleOffset(1.1);
    setup->GetYaxis()->SetTitleSize(28);
    setup->GetYaxis()->SetLabelSize(0.054);
    setup->GetXaxis()->SetLabelSize(0.0);

    //Set axis labels etc. for ratio plot
    double yratio = uplim(toPlot,q2v).second;
    TGraph* setupR = new TGraph();
    setupR->SetPoint(0,setupxlo,2.0 - yratio);
    setupR->SetPoint(1,setupxhi,yratio);
    setupR->SetMarkerSize(0);
    setupR->SetMarkerColor(kWhite);
    setupR->GetYaxis()->SetTitle("#font[62]{Fract. uncert.}");
    setupR->GetYaxis()->SetTitleFont(133);
    setupR->GetYaxis()->SetTitleOffset(1.3);
    setupR->GetYaxis()->SetTitleSize(23);
    setupR->GetYaxis()->SetLabelFont(62);
    setupR->GetYaxis()->SetLabelSize(0.11);
    setupR->GetXaxis()->SetTitleSize(20);
    setupR->GetXaxis()->SetTitleOffset(2.5);
    setupR->GetXaxis()->SetTitleFont(133);
    setupR->GetXaxis()->SetTitle("#font[62]{x}");
    setupR->GetYaxis()->SetNdivisions(5);
    setupR->GetXaxis()->SetTitleSize(28);
    setupR->GetXaxis()->SetTickSize(5.0);
    setupR->GetXaxis()->SetLabelFont(62);
    setupR->GetXaxis()->SetLabelSize(0.11);
    setupR->GetXaxis()->SetMoreLogLabels();

    //Style setup
    g[0][1]->SetFillStyle(1000);
    g[1][1]->SetFillStyle(1000);
    g[0][1]->SetFillColor(kAzure+1);
    g[1][1]->SetFillColor(kAzure+1);
    g[0][0]->SetFillColor(kBlack);
    g[1][0]->SetFillColor(kBlack);

    //Lining for Hessian unc
    TGraphAsymmErrors gLining( *(g[0][0]));
    TGraphAsymmErrors gLiningR(*(g[1][0]));
    gLining.SetFillStyle( 1);
    gLiningR.SetFillStyle(1);

    //Legend
    double lgxlo = 0.15;
    TLegend *lg = new TLegend(lgxlo, 0.65, lgxlo+0.35, 0.80);
    lg->SetBorderSize(0);  lg->SetFillStyle(0);
    lg->AddEntry(g[0][0],"#font[62]{Hessian exp unc.}", "f");
    lg->AddEntry(g[0][1],"#font[62]{MC exp unc.}",      "f");
    
    //"","",xlo,ylo,xhi,yhi,bordersize,bordermode
    TPad *pad[2];
    pad[0] = new TPad("","", 0.0, 0.33, 1.0, 1.0,  0,0);
    pad[1] = new TPad("","", 0.0, 0.0,  1.0, 0.33, 0,0); //"","",xlo,ylo,xhi,yhi
    pad[0]->SetLogx();                pad[1]->SetLogx();
    pad[0]->SetLeftMargin(  0.12);    pad[1]->SetLeftMargin(  0.12);
    pad[0]->SetRightMargin( 0.01);    pad[1]->SetRightMargin( 0.01);
    pad[1]->SetTopMargin(   0.00);
    pad[0]->SetBottomMargin(0.001);
    pad[1]->SetBottomMargin(0.3);
    pad[0]->Draw();                    pad[1]->Draw();

    //Draw PDFs
    pad[0]->cd();
    setup->Draw("AP");
    for (int n=Ngraphs-1; n!=-1; --n) g[0][n]->Draw("SAME E3");
    lg->Draw("SAME");
    gLining.Draw("SAME E3");
    canv->Update();

    //Write Q^2 on plot
    TLatex lat;
    lat.SetTextFont(62);
    lat.SetTextSize(0.07);
    sstream.str("");  sstream.clear();
    vector<string> Q2strs={"1.9","4","7","10","100","1000","m_{t}^{2}"};
    if (Nq2v-1<Q2strs.size()) {
        sstream << "#mu_{f}^{2} = " << Q2strs[Nq2v-1];
        if (Q2strs[Nq2v-1].find("m")==string::npos) sstream << " GeV^{2}";
        lat.DrawLatex(0.03,0.99*uplim(toPlot,q2v).first,sstream.str().c_str());
    } else cout << "WARNING: Too large Nq2v, check Q2strs vector!" << endl;
    
    //Write "CMS" atop PDF plot
    lat.SetTextSize(0.055);
    lat.DrawLatex(0.0001,1.15*uplim(toPlot,q2v).first,"CMS");

    //Write utilized data
    lat.SetTextSize(0.052);
    lat.DrawLatex(0.00013,1.*uplim(toPlot,q2v).first,
    "CMS 13 TeV jets & t#bar{t} + HERA DIS");
    lat.SetTextSize(0.055);  //Reset
    
    //Draw ratios
    pad[1]->cd();
    setupR->Draw("AP");
    for (int n=Ngraphs-1; n!=-1; --n) g[1][n]->Draw("SAME E3");
    gLiningR.Draw("SAME E3");
    canv->Update();

    //Fix 0 cut in half -- legend is not axis-value specific
    TLegend lg0(0.0807, 0.921, 0.14777, 1.081);
    lg0.SetBorderSize(0);  lg0.SetFillStyle(0);
    lg0.AddEntry(setup,"#font[62]{0}", ".");    
    lg0.Draw();
    
    //Save plot as PDF
    sstream.str("");  sstream.clear();
    sstream << toPlot << "_q2-" << q2v << "_combined" << ".pdf";
    canv->Print(sstream.str().c_str());

    //Save plot as PDF (w/ "Preliminary" tag)
    pad[0]->cd();
    lat.SetTextSize(0.055);
    lat.DrawLatex(0.00024,1.15*uplim(toPlot,q2v).first,"#font[52]{Preliminary}");
    canv->Update();
    sstream.str("");  sstream.clear();
    sstream << toPlot << "_q2-" << q2v << "_combined_prel" << ".pdf";
    canv->Print(sstream.str().c_str());

    //Free memory and close files
    for (int i=0; i!=Npads; ++i) for (int j=0; j!=Ngraphs; ++j) delete g[i][j];
    for (int i=0; i!=Npads; ++i) delete pad[i];
    delete setup, setupR;
    delete canv;
    
    return 1;

}

//The main function -- produce several combined plots on one go
int main(int argc, char** argv) {

    //Input arg = index of Q^2 to find
    int Nq2v = 1;	//Default
    if (argc > 1) Nq2v = atoi(argv[1]);
    if (Nq2v==0) {
        cout << "ERROR: Q^2 indexing must start from 1" << endl;
        return -1;
    }
    if (!plotCombiner("u_val", Nq2v)) return -1;
    if (!plotCombiner("d_val", Nq2v)) return -1;
    if (!plotCombiner("g",     Nq2v)) return -1;
    if (!plotCombiner("sea",   Nq2v)) return -1;
    
    return 1;
}
