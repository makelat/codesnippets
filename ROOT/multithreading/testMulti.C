//A ROOT macro to handle multiple TTree runs, ie a walk in the woods
#include "TThread.h"
#include <Riostream.h>

/* The user functions to execute */
void simplePrint1() {
  printf("Stuff works\n");
}
void simplePrint2() {
  printf("It's alive!\n");
}

/* Handles for the threads, needs (void*) return value and param. for ID */
void* handle1(void* in) {
  long n = (long)in;
  simplePrint1();
  return 0;
}
void* handle2(void* in) {
  long n = (long)in;
  simplePrint2();
  return 0;
}

/* The main function */
void testMulti() {

  //Instantiate the new threads
  TThread *t1 = new TThread("t1", handle1, (void*) 1);
  TThread *t2 = new TThread("t2", handle2, (void*) 2);

  //Start running the threads
  t1->Run();
  t2->Run();

  //List existing threads
  TThread::Ps();

  //Gather the threads together after execution
  t1->Join();
  t2->Join();

}

