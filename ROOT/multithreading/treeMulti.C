//A ROOT macro to handle multiple TTree runs, ie a walk in the woods
#include "TThread.h"
#include <Riostream.h>
#include <time.h>

/* The user functions to execute */
void func1() {
  TFile *file = TFile::Open("pjets_pythia6_gammajet_30000.root");
  TTree *tree;
  file->GetObject("Pythia6Jets", tree);
  for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
    if (i%1000==0) cout << "Reading event " << i << endl;
    tree->GetEntry(i);	//Retrieve an event
  }
}
void func2() {
  TFile *file = TFile::Open("pjets_pythia6_dijet_30000.root");
  TTree *tree;
  file->GetObject("Pythia6Jets", tree);
  for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
    if (i%1000==0) cout << "Reading event " << i << endl;
    tree->GetEntry(i);	//Retrieve an event
  }
}

/* Handles for the threads, needs (void*) return value and param. for ID */
void* handle1(void* in) {
  func1();
  return 0;
}
void* handle2(void* in) {
  func2();
  return 0;
}

/* The main function */
void treeMulti() {

  clock_t beginningOfTime, endOfTime;	//Tough times

  /* With parallelization */


  //Instantiate the new threads
  TThread *t1 = new TThread("t1", handle1, (void*) 1);
  TThread *t2 = new TThread("t2", handle2, (void*) 2);

  beginningOfTime = clock();	//Start time

  //Start running the threads
  t1->Run();
  t2->Run();
  //List existing threads
  //TThread::Ps();
  //Gather the threads together after execution
  t1->Join();
  t2->Join();

  endOfTime = clock();		//Stop time
  int tPar = endOfTime - beginningOfTime;

  /* Without parallelization */

  beginningOfTime = clock();	//(Re-)start time
  func1();
  func2();
  endOfTime = clock();		//Stop time (again)
  int tSeq = endOfTime - beginningOfTime;

  cout << "Parallelization time: " << tPar << endl;
  cout << "Sequential time: " << tSeq << endl;

}

