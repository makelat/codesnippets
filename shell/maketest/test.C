#include <iostream>
#include "TMath.h"

int getRandomNumber() {
  printf("Rolling the bones... ");
  return 4;	//A fair dice roll (a la XKCD), eh?
}

int main() {
  printf("A random number: %d\n", getRandomNumber());
  printf("FYI, pi is approximately %f\n", TMath::Pi());
  return 1;
}
