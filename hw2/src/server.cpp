#include <vector>
#include <iostream>
#include "control.h"

using namespace std;

server::server(int arrMean, int servMean, int servers,double prob[]){//constructor for the server object

  //init all the object variables
  p = prob;
  numServers = servers;
  numInQ = 0;
  lArr=(double)1/arrMean;
  lServ = (double)1/servMean;//lamdas used in the exponential dist. functions
  status = 0;
  nextArr = 0;
  nextDep = 999999999;//initialize so that arrive is first event;
  
  
}

int server::getStatus(void){
  //return the status of the server (0 not busy, 1 is busy)
  return status;

}

void server::setStatus(int n){
  //set the current status
  status = n;

}
void server::genPatient(double simClock){
  //adds a patient to the queue with the next arrival time

  patient Patient;
  Patient.setArrive(simClock);//the patient arrives at current clock time
  Patient.setServiceTime(control::genService(lServ));//generate a service time for the new patient
  Patient.setType(control::genType(p));
  cout << "type of patient is "<< Patient.getType() << endl;
  queue.push(Patient);//push a patient into the queue
  //cout << " front of queue type: " << queue.front().getType() << endl; //for debugging, to ensure arrival time was set correctly

}

double server::getArr(void){
  //return the next arrival time event
  return nextArr;

}

double server::patientArr(int i){
  //debugg function to ensure the proper arrival times are set
  //cout << queue[i].getArrive() << endl;


}

double server::getDep(){
  //return the next departure time event
  return nextDep;

}

int server::queueLen(){
  //return how many patients are currently in the queue
  return queue.size();

}

void server::setNextDep(){
  //set the next departure time 

  if (queue.size() > 0){
  nextDep = queue.front().getServiceTime();
  }
  else{//if the queue is currently empty must use sentinel to ensure next event is an arrival
    nextDep = 999999999;
  }
    
}

double server::newArrive(){
  //generate a new arrival time
  double arriveTime = control::genArrive(lArr);
  nextArr = arriveTime;
  return nextArr;

}

double server::patientDep(double simClock){
  //update the patients departure time and return that patients total wait time in the queue ( arrival until going into service)
  
  queue.front().setDepart(simClock);
  double waitTime = (queue.front().getDepart() - queue.front().getArrive() - queue.front().getServiceTime());
  return waitTime;

}

void server::departure(){
  //remove the patient after service is complete
  
  queue.pop();
  setNextMove();
}
double server::getServiceTime(){
  //return the service time of the patient currently in service
  
  return queue.front().getServiceTime();

}
void server::updateWait(double simClock){

  double waitTime = (simClock - queue.front().getArrive() - queue.front().getServiceTime());
  queue.front().setWait(waitTime);

}
patient * server::moveOut(){

  patient *temp = &queue.front();
  queue.pop();
  setNextMove();
  return temp;

}
void server::moveIn(patient *patient){

  (*patient).setServiceTime(control::genService(lServ));
  queue.push(*patient);

}
void server::setNextMove(){

  nextMove = queue.front().getType();

}
int server::getNextMove(){

  return nextMove;

}
