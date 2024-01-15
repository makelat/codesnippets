#include <iostream>
#include <vector>
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"

void simpleApprox() {
    double MZ     = 91.1876;    //PDG 2016
    double asMZ   = 0.1185;
    double pi     = 3.141592653589793;
    double nfl    = 5.;
    double bar0   = ( 11. -  2.*nfl/3.)/pow(4.*pi,2);
    double bar1   = (102. - 38.*nfl/3.)/pow(4.*pi,4);
    double mumin  = 2;
    double mumax  = 161;
    double mu, asmu, Lmu;
    TCanvas canv("","",400,400);
    TGraph asNLO, asNNLO;
    double nbins = 100.;
    //N.B. this is a simple expansion for the alphas, not proper evolution from
    //     solving the RGE numerically. The main point here is however to 
    //     illustrate the importance sampling
    for (double i=0; i<nbins; i+=1.) {
        mu   = mumin + pow(i/nbins,4)*(mumax-mumin);
        Lmu  = log(pow(MZ/mu,2));
        asmu = asMZ*(1. + asMZ*4*pi*Lmu*bar0);
        asNLO.SetPoint(i,mu,asmu);
        asmu += asMZ*( pow((asMZ*4*pi),2)*( Lmu*bar1 + pow(Lmu*bar0,2)) );
        asNNLO.SetPoint(i,mu,asmu);
    }
    
    asNNLO.SetMarkerSize(0.4);
    asNNLO.SetMarkerStyle(kFullCircle);
    asNNLO.GetXaxis()->SetTitle("#font[12]{#mu}");
    asNNLO.GetYaxis()->SetTitle("#alpha_{s}#font[12]{(#mu)}");
    asNNLO.Draw("AP");
    
    asNLO.SetMarkerSize(0.4);
    asNLO.SetMarkerStyle(kOpenCircle);
    asNLO.Draw("P SAME");

    TLegend lg(0.6,0.75,0.9,0.87);
    lg.SetBorderSize(0);
    lg.SetFillStyle(0);
    lg.AddEntry(&asNLO, "#alpha_{s}^{NLO}", "p");
    lg.AddEntry(&asNNLO,"#alpha_{s}^{NNLO}","p");
    lg.Draw();
    
    TGraph MZline;
    TGraph asMZline;
    MZline.SetPoint(  0,MZ,   0);    MZline.SetPoint(  1, MZ,   1);
    asMZline.SetPoint(0, 0,asMZ);    asMZline.SetPoint(1,162,asMZ);
    MZline.Draw("SAME");
    asMZline.Draw("SAME");
    
    canv.Print("plot.pdf");
  
}
