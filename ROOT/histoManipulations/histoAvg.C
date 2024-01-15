#include <iostream>
#include <vector>
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"

//A ROOT macro to demonstrate taking the average of two histograms
void histoAvg() {
  int const nbins=20;
  TH1D* h1   = new TH1D("h1",  "",nbins,1,100);  h1->SetLineColor(  kBlue  +1);
  TH1D* h2   = new TH1D("h2",  "",nbins,1,100);  h2->SetLineColor(  kOrange-3);
  TH1D* hAvg = new TH1D("hAvg","",nbins,1,100);  hAvg->SetLineColor(kSpring+2);
  TH1D* h1cp = new TH1D(*h1);  //To store copy of h1
  TH1D* h2cp = new TH1D(*h2);  // -||- h2
  TRandom3* dice = new TRandom3();
  TCanvas* canv = new TCanvas("c","",400,400);
  double temp;  
  for (int i=0; i!=1000; ++i) {
    h1->Fill(dice->Rndm()*100);
    h2->Fill(dice->Gaus(50,15));
  }
  //Set some errors to the bins to see how they behave
  for (int i=1;i!=nbins+1;++i) {
    h1->SetBinError(i,2);
    h2->SetBinError(i,20);
  }

  /* Find average of h1, h2 */

  h1cp->Add(h1);  h2cp->Add(h2);  //Copy the histos, must be normalized again

  //Find avg. histogram, weighted by #events
  TF1* norm1 = new TF1("norm1","[0]/([0]+[1])",1,100);  //For...
  TF1* norm2 = new TF1("norm2","[1]/([0]+[1])",1,100);  //...weighting
  norm1->SetParameters(h1cp->GetEntries(),h2cp->GetEntries());
  norm2->SetParameters(h1cp->GetEntries(),h2cp->GetEntries());
  h1cp->Multiply(norm1);  h2cp->Multiply(norm2);	//Normalization
  hAvg->Add(h1cp);        hAvg->Add(h2cp);

  //Plot
  h2->Draw();
  h1->Draw("SAME");
  hAvg->Draw("SAME");

  delete dice;	//Free memory
}
