#include <iostream>
#include <string>
#include "control.h"

using namespace std;

int main(int argc, char* argv[]){
  //just need to generate a controller(with the command line args) and make a call to the simulation 

  control controller(stoi(argv[1]),stoi(argv[2]));

  controller.simulate();
  
  return 0;

}

