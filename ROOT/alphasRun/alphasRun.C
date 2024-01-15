#include <iostream>
#include <vector>
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"

double asEvo(double asMZ, double MZ, double mu, int nloop, double nfl) {
    double pi       = 3.141592653589793;
    double beta0    =  11. -  2.*nfl/3.;
    double beta1    = 102. - 38.*nfl/3.;
    double beta2    = 325./54.*nfl*nfl - 5033./18.*nfl + 2857./2.;
    double asmu     = asMZ;
    double mutmp    = MZ;
    double sgn      = (mu < MZ ? -1. : 1.);
    int    nbins    = 100;
    double maxStep  = 1.;
    while (fabs(mu-MZ)/((double) nbins) > maxStep) nbins *= 2.;
    double delta = sgn*fabs(mu-MZ)/((double) nbins);
    for (int n=0; n!=nbins; ++n) {
        asmu = asmu*(1.-2*delta/mutmp*( beta0*asmu/(4*pi)
                                       +(nloop>1?beta1*pow(asmu/(4*pi),2):0)
                                       +(nloop>2?beta2*pow(asmu/(4*pi),3):0) ));
        mutmp += delta;
    }
    return asmu;
}

void alphasRun() {
    double MZ     = 91.1876;    //PDG 2016
    double asMZ   = 0.1185;
    double mumin  = 2;
    double mumax  = 161;
    double mu, asmu, Lmu;
    TGraph as1L, as2L, as3L;
    double nbins = 100.;
    for (double i=0; i<nbins; i+=1.) {
        mu   = mumin + pow(i/nbins,4)*(mumax-mumin);
        as1L.SetPoint(i,mu,asEvo(asMZ,MZ,mu,1,5.));
        as2L.SetPoint(i,mu,asEvo(asMZ,MZ,mu,2,5.));
        as3L.SetPoint(i,mu,asEvo(asMZ,MZ,mu,3,5.));
    }

    TCanvas canv("","",400,400);
    canv.SetRightMargin(0.01);
    canv.SetTopMargin(  0.01);
    canv.SetLeftMargin( 0.12);
    TGraph setup;
    setup.SetMarkerSize(0);
    setup.SetMarkerColor(kWhite);
    setup.SetPoint(0,  0,0.11);
    setup.SetPoint(1,145,0.25);
    setup.GetXaxis()->SetTitle("#font[12]{#mu}");
    setup.GetYaxis()->SetTitle("#alpha_{s}#font[12]{(#mu)}");
    setup.GetYaxis()->SetTitleOffset(1.5);
    setup.Draw("AP");

    //Draw & setup
    //1 loop
    as1L.SetMarkerSize(0.5);
    as1L.SetMarkerColor(kGray+1);
    as1L.SetMarkerStyle(kFullSquare);
    as1L.Draw("P SAME");
    //2 loops
    as2L.SetMarkerSize(0.5);
    as2L.SetMarkerColor(kGreen+2);
    as2L.SetMarkerStyle(kOpenCircle);
    as2L.Draw("P SAME");
    //3 loops
    as3L.SetMarkerSize(0.3);
    as3L.SetMarkerStyle(kFullCircle);
    as3L.Draw("P SAME");
    
    TLegend lg(0.7,0.77,0.99,0.9);
    lg.SetBorderSize(0);
    lg.SetFillStyle(0);
    lg.AddEntry(&as3L,"#alpha_{s} 3 loops","p");
    lg.AddEntry(&as2L, "#alpha_{s} 2 loops", "p");
    lg.AddEntry(&as1L, "#alpha_{s} 1 loop ", "p");
    lg.Draw();
    
    TGraph MZline;
    TGraph asMZline;
    MZline.SetPoint(  0,MZ,   0);    MZline.SetPoint(  1, MZ,   1);
    asMZline.SetPoint(0, 0,asMZ);    asMZline.SetPoint(1,162,asMZ);
    MZline.Draw("SAME");
    asMZline.Draw("SAME");
    
    canv.Print("plot.pdf");
  
}
