//An example of a numerical integral with variable differential step size
#include <iostream>
#include <vector>
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"

void growingSteps() {
    TCanvas canv("","",500,500);
    TGraph g;
    double Rmin=1;
    double Rmax=161;
    TF1* f = new TF1("f","-log(x)",Rmin,Rmax);
//    TF1* f = new TF1("f","1/x",Rmin,Rmax);
    double nbins = 100;
    double dR=0., R=Rmin;    //Stepper temps
    for (double ibin=0; ibin < nbins; ibin += 1.) {
        R = Rmin + pow(ibin/nbins,4)*(Rmax-Rmin);
        g.SetPoint(ibin, R, f(R));
    }        
    g.SetMarkerSize(0.4);
    g.SetMarkerStyle(kFullCircle);
    g.Draw("AP");
    
    canv.Print("growingSteps.pdf");
    
    //Integrate f numerically using the grids specified above
    double integral = 0.;
    dR=0.;  R=Rmin;       //Reinit stepper temps
    double upbd = 0.0;
    double lobd = f(Rmin);
    for (double ibin=0; ibin < nbins; ibin += 1.) {
        dR = (pow(ibin+1,4)-pow(ibin,4))/pow(nbins,4)*(Rmax-Rmin);
        R += dR;
        upbd = f(R);
        integral += 0.5*(upbd+lobd)*dR;
        lobd = upbd;
    }        
    cout << "Numerical integral result = " << integral << endl;
}
