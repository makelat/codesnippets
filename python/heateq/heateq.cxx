//  g++ heateq.cxx $(root-config --cflags --glibs) --std=c++14 -o heateqEXE
//  ./heateqEXE
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "TCanvas.h"
#include "TH2.h"
#include "TLatex.h"
#include <math.h>

using namespace std;

//FIXME this suffers from similar problems as the python implementation, so it
//is not a python-related problem
int main() {

    //Spatial and temporal grids
    double x0 = 0.;
    double t0 = 0.;
    double xf = 3.*M_PI;
    double tf = 30.;
    int nx = 30;
    int nt = 30;
    double dx = (xf-x0)/nx;
    double dt = (tf-t0)/nt;
    vector<double> t, x;
    for (int it=0; it!=nt; ++it) t.push_back(dt*it);
    for (int ix=0; ix!=nx; ++ix) x.push_back(dx*ix);
    
    //Init function value matrix
    vector< vector<double> > f;
    vector<double> fx;
    for (int ix=0; ix!=nx; ++ix) fx.push_back(0.);
    for (int it=0; it!=nt; ++it) f.push_back(fx);
    
    //Boundary conditions
    for (int i=0; i!=nx; ++i) {
        f[0][i] = sin(x[i]);    //CASE 1: initial heat dissipates
        //f[it][0] = sin(t[it]);    //CASE 2: Other end heated and cooled in waves
    }
    
    //Heat eq. is of the form:
    //    d/dt u[t, x] == d^2/dx^2 u[t, x]
    //Numerically:
    //    (f(t+dt,x) - f(t,x))/dt = (f(t,x+dx) - 2*f(t,x) + f(t,x-dx))/(dx*dx)
    //If t<0 or x<0, f=0.
    //To compute the next moment, use the full formula in the form
    //    f(t+dt,x) = f(t,x) + dt*(f(t,x+dx) - 2*f(t,x) + f(t,x-dx))/(dx*dx)
    int itmax = nt-1;
    for (int it=0; it != itmax; ++it) {        
        for (int ix=1; ix!=nx; ++ix) {  //FIXME doesn't ix go too high?
            f[it+1][ix] =    f[it][ix]
                        +    f[it][ix+1]//*dt/(dx*dx)
                        - 2.*f[it][ix  ]//*dt/(dx*dx)
                        +    f[it][ix-1];//*dt/(dx*dx);
        }
    }        
    
    //Canvas setup
    TCanvas canv("","",800,800);
    canv.SetTopMargin(0.06);
    canv.SetLeftMargin(0.17);
    canv.SetRightMargin(0.15);
    canv.SetBottomMargin(0.17);
    
    //ROOT 2D histogram for plotting
    TH2D h("","",nt, 0, nt, nx, 0, nx);
    h.SetStats(false);
    h.GetXaxis()->SetTitle("t");
    h.GetYaxis()->SetTitle("x");
    h.GetXaxis()->SetLabelSize(0);
    h.GetYaxis()->SetLabelSize(0);
    for (int it=0; it!=nt; ++it) {
        for (int ix=0; ix!=nx; ++ix) {
            //TH2 indexing starts from 1, hence +1
            h.SetBinContent(it+1, ix+1, f[it][ix]);
        }
    }
            
    //Plot
    h.Draw("colz");
    canv.Print("heateq_cxx.pdf");
    
}
