//A ROOT macro to illustrate implicit multithreading in TTree reading.
//Abridged from some tutorial found at
//  https://root.cern/doc/v610/imt001__parBranchProcessing_8C_source.html

//N.B. for this example the multithreading doesn't really speed things up.
//May need some complicated, quite specific TTree structure and tasks to shine.

void implicitMulti() {

  //Enable implicit multi-threading globally
  int nthreads = 3;
  ROOT::EnableImplicitMT(nthreads);

  //Open the file and retrieve the TTree
  TFile *file = TFile::Open("pjets_pythia6_gammajet_30000.root");
  TTree *tree;
  file->GetObject("Pythia6Jets", tree);

  //Internally parallelized branch reading, the interface doesn't change
  for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
    if (i%1000==0) cout << "Parallelized reading, event: " << i << endl;
    tree->GetEntry(i);	//Retrieve an event
  }
  cout << "DONE!" << endl;

  //Some handy features for reference, though not interesting ATM
/*
  //Disable parallelization for a specific TTree (handy if many TTrees)
  tree->SetImplicitMT(false);

  //Invoking GetEntry on a tree reads sequentially from now on
  for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
     tree->GetEntry(i);  // sequential read
  }

  //Re-enable parallelization
  tree->SetImplicitMT(true);
*/

  //Disable global implicit multithreading. Everything is sequential after this
  ROOT::DisableImplicitMT();

  //Read the same TTree without parallelization
  for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
    if (i%1000==0) cout << "Non-parallelized reading, event: " << i << endl;
    tree->GetEntry(i);	//Retrieve an event
  }
  cout << "DONE!" << endl;


}
