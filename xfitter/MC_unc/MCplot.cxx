//A program combining PDF plots based on results of multiple xFitter runs
//  g++ MCplot.cxx $(root-config --cflags --glibs) -std=gnu++0x  -o MCplotEXE
//  ./MCplotEXE

#include "MCplotAUX.h"

//Parameters    toPlot    "g","U","D","Ubar","Dbar","u_val","d_val",
//                        "sea","u_sea","d_sea","str","chm","bot","ph","strbar"    
//              Nq2v      Index of Q^2 value to plot      
int plotPDF(string toPlot, int Nq2v) {

    // BEGIN USER INPUT ////////////////////////////////////////////////////////
    string centralDir = "../";
    string pathMU = "../modelUnc/";
    string pathPU = "../paramUnc/";
    string plotDir = "./PDF_plots/"; //Save plots here
    // END USER INPUT //////////////////////////////////////////////////////////

    //Init generic vars
    ifstream in;
    string line, Q2str, Q2strLast;

    stringstream sstream;
    if (Nq2v<10) sstream << "0";
    sstream << Nq2v;
    string q2v = sstream.str();

    //First bools: add param unc, add model unc, add scale unc
    //SM fit
    TGraphAsymmErrors g;
    if (!graphSetup(g, false,false,false, centralDir,pathMU,pathPU,
                    q2v,toPlot, kBlue, 3005)) return -1;

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
    bool nonconverged=true;
    vector<string> convergedMC;
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
        
        convergedMC.push_back(seeds[i]);        

    } //Loop seeds

    if (convergedMC.size()==0) {
        cout << "\n\tNo MC fits converged! Exiting.\n" << endl;
        return -1;
    }

    TGraphAsymmErrors g_MC;
    g_MC.SetLineColor(kRed);
    g_MC.SetFillColor(kRed);
    g_MC.SetFillStyle(3004);
    vector<double> PDFtmp, xtmp;
    vector<vector<double>> PDFarr; //<converged PDFs<PDF values per x>>

    double xMC=0, yMC=0;
    for (int i=0; i<convergedMC.size(); ++i) {
        TGraphAsymmErrors g_MCtmp;	
        PDFtmp.clear();
        if (!graphSetup(g_MCtmp, false,false,false, convergedMC[i]+"/","","",
                        q2v,toPlot, kRed, 1000)) return -1;
        for (int j=0; j!=g_MCtmp.GetN(); ++j) {			
            g_MCtmp.GetPoint(j,xMC,yMC);
            //Save currently read PDF values per x
            PDFtmp.push_back(yMC);
            if (i==1) xtmp.push_back(xMC);
        }
        PDFarr.push_back(PDFtmp);
    }

    //Compute mean
    vector<double> PDFmean(PDFarr[0].size(),0.0);
    for (int i=0; i!=PDFarr.size(); ++i) {
        for (int j=0; j!=PDFarr[i].size(); ++j) {
            PDFmean[j] += PDFarr[i][j]/((double) PDFarr.size());
        }
    }
    
    //Compute (Root Mean Square)^2 i.e just don't take sqrt
    //N.B. std.dev^2 = RMS^2 - mean^2
    vector<double> RMS2(PDFmean.size(),0.0);
    for (int i=0; i!=PDFarr.size(); ++i) {
        for (int j=0; j!=PDFarr[i].size(); ++j) {
            RMS2[j] += PDFarr[i][j]*PDFarr[i][j];
        }
    }
    double RMStmp=0.0;
    for (int n=0; n!=PDFmean.size(); ++n) {
        RMS2[n] *= 1.0/((double)PDFarr.size());
        g_MC.SetPoint(n, xtmp[n],PDFmean[n]);
        RMStmp = sqrt(RMS2[n]-PDFmean[n]*PDFmean[n]);
        g_MC.SetPointError(n, 0.0, 0.0, RMStmp, RMStmp);
    }

    vector<TGraphAsymmErrors*> gVec;
    vector<string> lgstr;    //Strings for legend
    gVec.push_back(&g);       lgstr.push_back(" Hessian unc.");
    gVec.push_back(&g_MC);    lgstr.push_back(" MC unc.");
    
    double uplim=10.0;
    if (toPlot=="u_val") {
        if      (q2v=="01") uplim = 1.0;    //Good for 1.9 GeV^2 gluon
        else if (q2v=="02") uplim = 1.0;    //   -||-    4 GeV^2
        else if (q2v=="03") uplim = 0.8;    //   -||-    7 GeV^2
        else if (q2v=="04") uplim = 0.8;    //   -||-   10 GeV^2
        else if (q2v=="05") uplim = 0.7;    //   -||-  100 GeV^2
        else if (q2v=="06") uplim = 0.7;    //   -||-   1k GeV^2
        else if (q2v=="07") uplim = 0.7;    //   -||-  30k GeV^2
    } else if (toPlot=="d_val") {
        if      (q2v=="01") uplim = 0.5;    //Good for 1.9 GeV^2
        else if (q2v=="02") uplim = 0.5;    //   -||-    4 GeV^2
        else if (q2v=="03") uplim = 0.5;    //   -||-    7 GeV^2
        else if (q2v=="04") uplim = 0.5;    //   -||-   10 GeV^2
        else if (q2v=="05") uplim = 0.4;    //   -||-  100 GeV^2
        else if (q2v=="06") uplim = 0.4;    //   -||-   1k GeV^2
        else if (q2v=="07") uplim = 0.4;    //   -||-  30k GeV^2
    } else if (toPlot=="g") {
        if      (q2v=="01") uplim = 4.0;    //Good for 1.9 GeV^2
        else if (q2v=="02") uplim = 8.0;    //   -||-    4 GeV^2
        else if (q2v=="03") uplim = 10.0;   //   -||-    7 GeV^2
        else if (q2v=="04") uplim = 20.0;   //   -||-   10 GeV^2
        else if (q2v=="05") uplim = 15.0;   //   -||-  100 GeV^2
        else if (q2v=="06") uplim = 20.0;   //   -||-   1k GeV^2
        else if (q2v=="07") uplim = 30.0;   //   -||- 30k GeV^2
    } else if (toPlot=="sea") {
        if      (q2v=="01") uplim = 1.6;    //Good for 1.9 GeV^2
        else if (q2v=="02") uplim = 2.5;    //   -||-    4 GeV^2
        else if (q2v=="03") uplim = 3.0;    //   -||-    7 GeV^2
        else if (q2v=="04") uplim = 4.0;   //   -||-   10 GeV^2
        else if (q2v=="05") uplim = 5.0;   //   -||-  100 GeV^2
        else if (q2v=="06") uplim = 6.0;   //   -||-   1k GeV^2
        else if (q2v=="07") uplim = 7.0;   //   -||-  30k GeV^2
    } else if (toPlot=="U" || toPlot=="D") {
        if      (q2v=="01") uplim = 4.0;    //Good for 1.9 GeV^2
        else if (q2v=="02") uplim = 8.0;    //   -||-    4 GeV^2
        else if (q2v=="03") uplim = 10.0;   //   -||-    7 GeV^2
        else if (q2v=="04") uplim = 10.0;   //   -||-   10 GeV^2
        else if (q2v=="05") uplim = 20.0;   //   -||-  100 GeV^2
        else if (q2v=="06") uplim = 25.0;   //   -||-   1k GeV^2
        else if (q2v=="07") uplim = 30.0;   //   -||-  30k GeV^2
    } else if (toPlot=="u_sea" || toPlot=="d_sea" ||
               toPlot=="Ubar"  || toPlot=="Dbar"    )
    {
        if      (q2v=="01") uplim = 0.6;    //Good for 1.9 GeV^2
        else if (q2v=="02") uplim = 0.8;    //   -||-    4 GeV^2
        else if (q2v=="03") uplim = 1.2;    //   -||-    7 GeV^2
        else if (q2v=="04") uplim = 1.5;    //   -||-   10 GeV^2
        else if (q2v=="05") uplim = 2.0;    //   -||-  100 GeV^2
        else if (q2v=="06") uplim = 2.5;    //   -||-   1k GeV^2
        else if (q2v=="07") uplim = 3.0;    //   -||-  30k GeV^2
    } else if (toPlot=="str" || toPlot=="strbar") {
        if      (q2v=="01") uplim = 0.4;    //Good for 1.9 GeV^2
        else if (q2v=="02") uplim = 0.6;    //   -||-    4 GeV^2
        else if (q2v=="03") uplim = 0.8;    //   -||-    7 GeV^2
        else if (q2v=="04") uplim = 1.2;    //   -||-   10 GeV^2
        else if (q2v=="05") uplim = 2.0;    //   -||-  100 GeV^2
        else if (q2v=="06") uplim = 2.5;    //   -||-   1k GeV^2
        else if (q2v=="07") uplim = 3.0;    //   -||-  30k GeV^2
    }

    //Dummy TGraph to plot axes
    TCanvas canv("","",400,400);
    canv.SetRightMargin(0.01);
    canv.SetTopMargin(0.01);
    canv.SetLogx();
    TGraph setup;
    setup.SetPoint(0,0.0015,0);
    setup.SetPoint(1,0.91,uplim);
    setup.SetLineWidth(0);
    setup.SetMarkerColor(kWhite);
    setup.GetXaxis()->SetTitle("#font[12]{x}");
    string yTitle;
    if      (toPlot=="g"    ) yTitle="#font[12]{xg(x)}";
    else if (toPlot=="u_val") yTitle="#font[12]{xu_{v}(x)}";
    else if (toPlot=="d_val") yTitle="#font[12]{xd_{v}(x)}";
    else if (toPlot=="U"    ) yTitle="#font[12]{xD(x)}";
    else if (toPlot=="D"    ) yTitle="#font[12]{xD(x)}";
    else if (toPlot=="chm"  ) yTitle="#font[12]{xc(x)}";
    else if (toPlot=="str"  ) yTitle="#font[12]{xs(x)}";
    else                      yTitle="#font[12]{xf(x)}";
    setup.GetYaxis()->SetTitle(yTitle.c_str());
    setup.GetYaxis()->SetTitleOffset(1);
    setup.GetXaxis()->SetMoreLogLabels();
    setup.GetXaxis()->SetNoExponent();
    setup.Draw("AP");

    //Plot
    for (auto gtmp : gVec) gtmp->Draw("SAME C3");

    //Legend
    double hmin=0.6, hmax=0.97, vmax=0.9;
    double vmin = vmax - 0.1;
    TLegend lg(hmin, vmin, hmax, vmax);
    lg.SetFillStyle(0);  lg.SetBorderSize(0);
    lg.AddEntry(&g,    " Hessian unc.", "f");
    lg.AddEntry(&g_MC, " MC unc.",      "f");
    lg.Draw();

    //Find and write Q^2 value
    if (!inStreamOpen(in, centralDir+"steering.txt")) {
        cout << "Can't check Q2" << endl;
    }
    while (getline(in,line)) {
        if (line.find("Q2VAL =")!=string::npos) {
            sstream.str("");  sstream.clear();
            sstream << line;
            for (int i=0; i!=Nq2v+2; ++i) sstream >> Q2str;
            if (Q2str.find(",")!=string::npos) Q2str.pop_back();
            if (Q2str.size()!=0 && Q2str[Q2str.size()-1]=='.') Q2str.pop_back();
        }
    }
    in.close();
    TLatex lat;
    lat.SetTextFont(132);
    sstream.str("");  sstream.clear();
    sstream << "Q^{2} = " << Q2str << " GeV^{2}";
    lat.DrawLatex(0.06,uplim,sstream.str().c_str());

    //Save plot as .pdf
    sstream.str("");  sstream.clear();
    sstream << plotDir << toPlot << "_q2-" << q2v << ".pdf";
    canv.Print(sstream.str().c_str());

    //Save plot as ROOT file
    string rootname = sstream.str();
    if (rootname.find(".pdf")!=string::npos) {
        rootname.erase(rootname.find(".pdf"));
    }
    rootname += ".root";
    TFile out_file(rootname.c_str(),"RECREATE");
    for (auto g : gVec) g->Write();
    out_file.Close();

    //Form title for ratio plots
    sstream.str("");  sstream.clear();
    sstream << "#font[132]{" << yTitle << "/(" << yTitle << ")}";
    string ratioTitle = sstream.str();

    //Ratio plot
    bool relErr = false;
    sstream.str("");  sstream.clear();
    sstream << plotDir << toPlot << "_q2-" << q2v << "_ratio.pdf";
    graphRatio(gVec, lgstr, sstream.str(),ratioTitle,Q2str,false);

    //Ratio plot w/ relative errors
    relErr = true;
    sstream.str("");  sstream.clear();
    sstream << plotDir << toPlot << "_q2-" << q2v << "_ratio_relErr.pdf";
    graphRatio(gVec, lgstr, sstream.str(),ratioTitle,Q2str,true);


    return 1;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                         THE MAIN FUNCTION                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */    

int main(int argc, char** argv) {

    //Input arg = index of Q^2 to find
    int Nq2v = 1;	//Default
    if (argc > 1) Nq2v = atoi(argv[1]);
    if (Nq2v==0) {
        cout << "ERROR: Q^2 indexing must start from 1" << endl;
        return -1;
    }

    plotPDF("u_val",Nq2v);     
    plotPDF("d_val",Nq2v);     
    plotPDF("g",    Nq2v);     
    plotPDF("sea",  Nq2v);     

    return 1;
}
