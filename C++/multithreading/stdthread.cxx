//An example program demonstrating the use of std::thread with arbitrarily sized
//input, given reliably without usual pthread-like (void *) -typecasting abuse.
//
//The motivation of this exercise is to collect all input arg.s in a single
//vector and state the max. #CPUs to use. All inputs are then automatically 
//assigned to threads without further user brainscratching.
//
//Compile and usage:
//  g++ --std=gnu++0x -pthread -o stdthread.EXE stdthread.cxx
//  .stdthreadEXE
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <string>
#include <time.h>
#include <vector>

using namespace std; 

#define NUM_THREADS 2   //Max #threads to use

//A thread will execute this function
//Could only give the vector as input as well, but id can be handy
void threadfunc(int id, vector<string> str) {
  for (auto s : str) cout << "thread " << id << " printing: " << s << endl;
}

int main() {
    
    //Init. "words" contains all input, split later when given to threads
    vector<string> words = {"すみません","ありがとう","漢字","マッドサイエンティスト"};
    vector<string> vtmp;    //Temp. for eventually splitting "words"

    //Init only as many threads as we need
    int ncpu = min((int)NUM_THREADS, (int) words.size());
    thread threads[ncpu];

    //Divide input vector into
    for (int i=0; i!=ncpu; ++i) {
        vtmp.clear();
        for (int j=i; j<words.size(); j+=ncpu) vtmp.push_back(words[j]);
        cout << "Thread " << i << " receives input: " << endl;
        for (string s : vtmp) cout << "    " << s << endl;
        
        //Start threads
        //Args: (func. to exec. in thread], func. input par.s separated by ",")
        threads[i] = thread(threadfunc,i,vtmp);
    }

    //Synchronize threads
    for (int i=0; i!=ncpu; ++i) threads[i].join();
    
    return 1;
}
