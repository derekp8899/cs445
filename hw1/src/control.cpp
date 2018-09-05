#include "control.h"
//#include "server.h"
#include <random>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

control::control(int arrMean, int servMean){

  stopCond = 1000;
  numServed = 0;
  simClock = 0;
  avgQue = 0;
  avgWait = 0;
  MST = 0;
  numInQue = 0;
  totalArrivals = 0;
  intArrival = 0;
  aMean = arrMean;
  sMean = servMean;
  nextArrive = 0;
  nextDepart = 9999999999999;//to assure first event is an arrival
  nextType = 0;//event type is 0 for arrive and 1 for depart
  // arriveMean = arrMean;
  // serviceMean = servMean;

  
}
void control::simulate(void){
  server triage(aMean,sMean);//create triage server
 
  nextArrive = triage.newArrive();//gen first arrival time
  procArr(&triage);//generate the first patient and generate the next arrive time
  triage.setStatus(1); //move first patient into service
  triage.setNextDep();
  nextDepart = triage.getDep();//update first departure
  //  nextArrive = triage.newArrive();        

  //this sets up first depart and arrival
  
  
  while ( numServed < stopCond){
    cout << "event times: Arrive: " << nextArrive << " departue: " << nextDepart << endl;
    cout << "queue size: " << triage.queueLen() << endl;
    cout << "current sim time : " << simClock << endl;
    decide();
    if(nextType==0){
      //simClock += nextArrive;
      procArr(&triage); //if arrive is next event process the arriveal event
      //  nextArrive = triage.newArrive();
    }
    else{
      
      procDepart(&triage); // if departure is next event process the departure event

      numServed++;
    }
    


    //update();
  }
  
  numInQue = triage.queueLen();
  sendReport();
 
}
double control::genArrive(double mean){
  random_device rd;
  mt19937 gen(rd());
  exponential_distribution<> d(mean);
  return (d(gen));


}

double control::genService(double mean){
  random_device rd;
  mt19937 gen(rd());
  exponential_distribution<> d(mean);
  return (d(gen));


}

void control::decide(void){//decide which event type is next

  if (nextArrive < nextDepart){
    nextType = 0;
  }
  else if (nextArrive > nextDepart){

    nextType = 1;
    
  }
  else{

    nextType = 0;

  }

}

void control::update(void){

  //do the update maths and clock/event times updates


}
void control::procArr(server* Server){
  //process a new arrival event

  (*Server).genPatient(simClock+nextArrive);//creates a mew patient and adds it to the queue with the generated arrival time
  simClock += nextArrive;//advamce the clock
  nextDepart -= nextArrive; //update depart event time
  intArrival += (*Server).getArr();
  nextArrive = (*Server).newArrive();
  if((*Server).getStatus()==0){
    (*Server).setStatus(1);
    (*Server).setNextDep();
    nextDepart = (*Server).getDep();
  }
  totalArrivals++;
}
void control::procDepart(server* Server){
  //process a departure event
  simClock += nextDepart;
  avgWait += (*Server).patientDep(simClock);
  MST += (*Server).getServiceTime();
  (*Server).departure();
  nextArrive -= nextDepart;//update next arrive event time
  if((*Server).queueLen()>0){

    (*Server).setNextDep();
    nextDepart = (*Server).getDep();
 
  }
  else{
    nextDepart = 999999999;
    (*Server).setStatus(0);
  }


}
char * control::sendReport(void){
  //generate the appropriate reports

  char report[100];
  //  strcpy(report,to_string(nextArrive));
  //sprintf(report,"%f",nextArrive);
  avgWait = (avgWait/numServed);
  MST = (MST/numServed);
  intArrival = (intArrival/totalArrivals);
  
  cout << "Mean Inter-Arrival time: " << intArrival << endl;
  cout << "Mean Service time : " << MST << endl;
  cout << "Length of Simulated time : " << simClock << endl;
  cout << "Average Wait Time : " << avgWait <<endl;
  cout << "Average Number of Patients in the queue : " << avgQue << endl;
  cout << "Number in queue after end of simulation : " << numInQue << endl;

  return report;

}
