#include <iostream>
#include <vector>
#include <fstream>

int main() {
  long lim = 5e7;
  std::cout << "Starting "
            << lim
            << " iterations. Prepare for jargon."
            << std::endl;
  std::ofstream out("out.txt");
  for (int i=1; i!=lim; ++i) {
    out << "jargon ";
    if (i%11==0) out << std::endl;
  }
  out << std::endl;
  std::cout << "Exiting." << std::endl;
  out.close();
  std::ofstream out2("finished.txt");
  out2 << "Done." << std::endl;
  out2.close();
  return 1;
}
