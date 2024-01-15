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

void alphasRun_nfl() {
    double MZ     = 91.1876;    //PDG 2016
    double asMZ   = 0.1185;
    double mumin  = 2;
    double mumax  = 510;
    double mu, asmu, Lmu;
    int nloops = 3;
    TGraph g1, g2, g3;
    double nbins = 100.;
    for (double i=0; i<nbins; i+=1.) {
        mu   = mumin + pow(i/nbins,4)*(mumax-mumin);
        g1.SetPoint(i,mu,asEvo(asMZ,MZ,mu,nloops,4.));
        g2.SetPoint(i,mu,asEvo(asMZ,MZ,mu,nloops,5.));
        g3.SetPoint(i,mu,asEvo(asMZ,MZ,mu,nloops,6.));
    }

    TCanvas canv("","",400,400);
    canv.SetRightMargin(0.01);
    canv.SetTopMargin(  0.01);
    canv.SetLeftMargin( 0.12);
    TGraph setup;
    setup.SetMarkerSize(0);
    setup.SetMarkerColor(kWhite);
    setup.SetPoint(0,mumin,0.10);
    setup.SetPoint(1,460,0.22);
    setup.GetXaxis()->SetTitle("#font[12]{#mu}");
    setup.GetYaxis()->SetTitle("#alpha_{s}#font[12]{(#mu)}");
    setup.GetYaxis()->SetTitleOffset(1.5);
    setup.Draw("AP");

    //Draw & setup
    //nfl=4
    g1.SetMarkerSize(0.5);
    g1.SetMarkerColor(kGray+1);
    g1.SetMarkerStyle(kFullSquare);
    g1.Draw("P SAME");
    //nfl=5
    g2.SetMarkerSize(0.5);
    g2.SetMarkerColor(kGreen+2);
    g2.SetMarkerStyle(kOpenCircle);
    g2.Draw("P SAME");
    //nfl=6
    g3.SetMarkerSize(0.3);
    g3.SetMarkerStyle(kFullCircle);
    g3.Draw("P SAME");
    
    TLegend lg(0.7,0.77,0.99,0.9);
    lg.SetBorderSize(0);
    lg.SetFillStyle(0);
    lg.AddEntry(&g3,"#alpha_{s} nfl=6","p");
    lg.AddEntry(&g2,"#alpha_{s} nfl=5","p");
    lg.AddEntry(&g1,"#alpha_{s} nfl=4","p");
    lg.Draw();
    
    TGraph MZline;
    TGraph asMZline;
    MZline.SetPoint(  0,MZ,   0);    MZline.SetPoint(  1, MZ,   1);
    asMZline.SetPoint(0, 0,asMZ);    asMZline.SetPoint(1,162,asMZ);
    MZline.Draw("SAME");
    asMZline.Draw("SAME");
    
    canv.Print("nfl.pdf");
  
}
