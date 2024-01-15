#include "TThread.h"
#include <Riostream.h>

void *handle(void *ptr) {

   long nr = (long) ptr;

   for (int i = 0; i < 10; i++) {

      TThread::Printf("Loop index: %d , thread: %ld", i, nr);
      gSystem->Sleep(1000);
   }
   return 0;
}

void multiThread() {

  printf("Starting Thread 1\n");
  TThread *h1 = new TThread("h1", handle, (void*) 1);
  h1->Run();
  printf("Starting Thread 2\n");
  TThread *h2 = new TThread("h2", handle, (void*) 2);
  h2->Run();
  printf("Starting Thread 3\n");
  TThread *h3 = new TThread("h3", handle, (void*) 3);
  h3->Run();

  //Gather the threads together after execution
  h1->Join();
  TThread::Ps();	//List existing threads
  h2->Join();
  h3->Join();

}

