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
  numDischared = 0;
  avgDelay = 0;
  avgque = 0;
  nextDep = 999999999;//initialize so that arrive is first event;
  for (int i = 0; i < 3;i++)
    serverUtil[i] = 0;
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
  queue.push(Patient);//push a patient into the queue
  if(status < numServers)
    status++;
  if (queue.size() == 1){
    setNextMove();
    setNextDep();
  }
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
    if(numServers > 1 && departList.size() > 0){
      nextDep =departList[0];
      int i = 1;
      while (i < departList.size() && i < status){
	if(nextDep > departList[i])
	  nextDep = departList[i];
	i++;
      }
    }
    else
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

void server::patientDep(double simClock){
  //update the patients departure time and return that patients total wait time in the queue ( arrival until going into service)
  
  queue.front().setDepart(simClock);

}

void server::departure(){
  //remove the patient after service is complete
  avgDelay += queue.front().getWait();
  queue.pop();
  int flag = 0;
  for ( int i = 0; i < departList.size();i++){
    if (departList[i] == nextDep)
      flag = i;
  }
  if(departList.size()> 0){

    departList.erase(departList.begin()+flag);
    
  }
  if(queue.size() < numServers)
    status--;
  numDischared++;
  setNextMove();
  

}
double server::getServiceTime(){
  //return the service time of the patient currently in service
  
  return queue.front().getServiceTime();

}
void server::updateWait(double simClock){
  double waitTime = 0;
  if(queue.front().getDepart() != 0){
    
    waitTime = (simClock - queue.front().getDepart() - queue.front().getServiceTime()); 
    if (waitTime < 0)
      waitTime = 0;//mitigate floating point precision errors 
    queue.front().setWait(waitTime);
  }
  else{
    waitTime = (simClock - queue.front().getArrive() - queue.front().getServiceTime());
    if (waitTime < 0)
      waitTime = 0;//mitigate floating point precision errors 
    queue.front().setWait(waitTime);
  }

}
patient * server::moveOut(){

  patient *temp = &queue.front();
  avgDelay += queue.front().getWait();
  queue.pop();
  
  if (queue.size() < numServers)
    status--;
  setNextMove();
  return temp;

}
void server::moveIn(patient *patient){

  (*patient).setServiceTime(control::genService(lServ));
  if (queue.size() < 1){
    
    nextDep=(*patient).getServiceTime();
  
  }
  if(status < numServers){
    status++;
  }
  departList.push_back((*patient).getServiceTime());
  queue.push(*patient);
  if(numServers > 1)
    setNextDep();
  
}
void server::setNextMove(){

  nextMove = queue.front().getType();

}
int server::getNextMove(){

  return nextMove;

}
void server::updateTotals(double simClock, double lastEvent){
  if (queue.size() > numServers){
    avgque += (queue.size()-numServers)*(simClock - lastEvent);
  }
  for(int i = 0; i < status; i++){

    serverUtil[i] += (simClock - lastEvent);
  }


}
void server::updateDepartureTime(double d,int flag){
  nextDep -= d;
  if (numServers > 1){
    if (flag ==1){

      for(int i = 0; i<(status-1);i++){
	departList[i]-= d;
      }
    }
    else{
      for(int i = 0; i<status;i++){
	departList[i]-= d;
      }
    }
  }
}
void server::report(double simClock){

  avgDelay = avgDelay/numDischared;
  avgque = avgque/simClock;
  for (int i = 0; i < numServers; i++){
    serverUtil[i] = serverUtil[i]/simClock;
  }
  cout << endl;
  cout << "Number of patients discharged: " << numDischared << endl;
  cout << "Average delay for this queue: " << avgDelay << endl;
  cout << "Average queue size: " << avgque << endl;
  cout << "Server utilization(s)" << endl;
  for(int i = 0; i < numServers;i++){
    cout << "Server " << i << " ," << serverUtil[i] << endl;
  }
  cout << endl;
}
