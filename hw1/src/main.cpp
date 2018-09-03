#include <iostream>
#include <string>
#include "control.h"
//#include "server.h"
//#include "patient.h"

using namespace std;
int main(int argc, char* argv[]){

  //  server a(stoi(argv[1]),stoi(argv[2]));
  control controller(stoi(argv[1]),stoi(argv[2]));
  //  a.genPatient();
  //  cout << controller.genArrive(.1666) << endl;
  //  double average = 0;
  //double mean = (double)1/(stoi(argv[1]));
  /*
  cout << mean << endl;
  for(int i = 0; i<1000; i++){

    average += controller.genArrive(mean);


  }
  average = average/1000;

  cout << average <<endl;
  cout << a.getStatus() << endl;
  cout << controller.genArrive(mean) << endl;
  a.setStatus(1);

  cout << a.getStatus() << endl;
  */
  
  //  cout << a.getArr() << endl;
  controller.simulate();
  //  cout << controller.sendReport() << endl;
  return 0;
}

