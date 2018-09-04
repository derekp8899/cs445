#include <vector>
#include <iostream>
//#include "server.h"
#include "control.h"
//#include "patient.h"
using namespace std;
server::server(int arrMean, int servMean){

  numInQ = 0;
  lArr=(double)1/arrMean;
  lServ = (double)1/servMean;
  status = 0;
//  genPatient();
  nextArr = 0;
  nextDep = 999999999;//initialize so that arrive is first event;
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
  Patient.setServiceTime(control::genService(lServ));
  queue.push_back(Patient);
  patientArr(0);
  numInQ++;
}

double server::getArr(void){

  return nextArr;

}

double server::patientArr(int i){

  cout << queue[i].getArrive() << endl;


}

double server::getDep(){

  return nextDep;

}

int server::getQueueSize(){

  return numInQ;

}

void server::setNextDep(){

  nextDep = queue[0].getServiceTime();


}
