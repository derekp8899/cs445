#include <vector>
#include <iostream>
//#include "server.h"
#include "control.h"
//#include "patient.h"
using namespace std;
server::server(int arrMean, int servMean){

  numInQ = 0;
  lArr=(double)1/arrMean;
  lServ = (double)1/servMean;//lamdas used in the exponential dist. functions
  status = 0;
  nextArr = 0;
  nextDep = 999999999;//initialize so that arrive is first event;

}

int server::getStatus(void){

  return status;

}

void server::setStatus(int n){

  status = n;

}
void server::genPatient(double simClock){
  //adds a patient to the queue with the next arrival time
  //  nextArr = control::genArrive(lArr);
  patient Patient;
  Patient.setArrive(nextArr,simClock);
  Patient.setServiceTime(control::genService(lServ));
  queue.push_back(Patient);
  patientArr(numInQ);
  numInQ++;
}

double server::getArr(void){

  return nextArr;

}

double server::patientArr(int i){
  //debugg function to ensure the proper arrival times are set
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

double server::newArrive(){
  double arriveTime = control::genArrive(lArr);
  nextArr = arriveTime;
  return nextArr;

}
