#include <vector>
#include <iostream>
//#include "server.h"
#include "control.h"
//#include "patient.h"
using namespace std;
server::server(int arrMean, int servMean){

  lArr=(double)1/arrMean;
  lServ = (double)1/servMean;
  status = 0;
//  genPatient();
  nextArr = 0;
  //  vector <patient>queue;


}

int server::getStatus(void){

  return status;

}

void server::setStatus(int n){

  status = n;

}
void server::genPatient(double simClock){

nextArr = control::genArrive(lArr);
patient Patient;
Patient.setArrive(nextArr,simClock);
queue.push_back(Patient);
 patientArr(0);
}

double server::getArr(void){

return nextArr;

}

double server::patientArr(int i){

  cout << queue[i].getArrive() << endl;


}

