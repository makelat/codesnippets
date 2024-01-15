#include <iostream>
#include <vector>
#include "TF1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TRandom3.h"

/* TProfiles calculate a point's vertical axis location as a mean. Here we fit 
 * a Gaussian to each horizontal bin of a 2D histogram, take the locations of
 * the maxima and compare a profile formed in this way to the TProfile. */
void fitGaussToTH2() {
  double lim[2] = {0.0,10.0};
  int nbins[2] = {20,100}; //nbinsx, nbinsy
  double wBin = (lim[1]-lim[0])/((double) nbins[0]);
  TRandom3* dice = new TRandom3();
  TProfile* pr = new TProfile("pr","",nbins[0],lim[0],lim[1]);
  TH2D* data = new TH2D("h2",         ";#font[132]{x};#font[132]{y}",
                        nbins[0],lim[0],lim[1],nbins[1],lim[0],lim[1]);

  //Generate some content for the histograms
  int N=10000;
  double step = (lim[1]-lim[0])/((double) N);
  double temp = lim[0];
  double y = 0;
  for (int i=0; i!=N; ++i) {
    y = temp+dice->Gaus(0,1);
    data->Fill(temp,y);
    pr->Fill(temp,y);
    temp += step;
  }

  TObjArray slices;
  TF1* gaus = new TF1("g","gaus",lim[0],lim[1]);
  TProfile* gausPr = new TProfile("gR","",nbins[0],lim[0],lim[1]);

  data->FitSlicesY(gaus, 1, data->GetEntries(), 0, "QN", &slices);
  //Get the Gaussian fit parameters for all y-bins:
  TH1D* data_0 = (TH1D*) slices[0]; //Const param.s
  TH1D* data_1 = (TH1D*) slices[1]; //Means
  TH1D* data_2 = (TH1D*) slices[2]; //Standard deviations

  for (int i=0; i!=nbins[0]; ++i) {
    gaus->SetParameters(data_0->GetBinContent(i+1),
                        data_1->GetBinContent(i+1),
                        data_2->GetBinContent(i+1));
    gausPr->Fill(lim[0]+i*wBin,gaus->GetMaximumX());
  }

  //Style setup
  data->SetStats(0);
  data->SetMarkerColor(kGray+1);
  data->SetFillColor(kGray+1);
  data->SetLineColor(kWhite);
  data->SetFillStyle(kFDotted3);
  pr->SetLineColor(kAzure);
  gausPr->SetMarkerStyle(kFullCircle);
  gausPr->SetMarkerColor(kGreen+1);

  //Legend
  TLegend* lg = new TLegend(0.55, 0.15, 0.9, 0.30);
  lg->SetBorderSize(0);  lg->SetFillStyle(0);
  lg->AddEntry(gausPr, "#font[132]{Fitted Gaussians' peaks}", "p");
  lg->AddEntry(pr,     "#font[132]{TProfile avgerages}",      "l");
  lg->AddEntry(data,   "#font[132]{Data}",                    "f");

  //Plot
  TCanvas* canv = new TCanvas("","",400,400);
  data->Draw();
  pr->Draw("SAME");
  gausPr->Draw("P HISTO SAME");
  lg->Draw();
  canv->Print("plot_fitGaussToTH2.eps");

  //Free memory
  delete gaus;	delete gausPr;
  delete pr;	delete data;
  delete dice;	delete canv;	delete lg;

}
