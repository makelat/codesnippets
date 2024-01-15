#include <iostream>
#include <fstream>

/*Note that the script filename is to be renamed nowRunning.C before running.
  This is done automatically by script.sh */
void nowRunning() {
  ofstream out("out.txt");
  for (int i=0; i!=20; ++i) out << "...and so was Red\n";
  out.close();
}
