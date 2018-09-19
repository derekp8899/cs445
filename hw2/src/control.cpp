#include "control.h"
#include <random>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

control::control(int arrMean, int servMean){
  //initialize all object variables
  lastEvent = 0;
  stopCond = 100;
  numServed = 0;
  simClock = 0;
  avgQue = 0;
  avgWait = 0;
  MST = 0;
  numInQue = 0;
  totalArrivals = 0;
  intArrival = 0;
  aMean = arrMean;
  sMean = servMean;//the means for RNG from command line
  nextArrive = 0;
  nextDepart = 9999999999999;//to assure first event is an arrival
  nextType = 0;//event type is 0 for arrive and 1 for depart

  
}
void control::simulate(void){
  //function that controls the simulation
  server *servers[4];
  server triage(aMean,sMean,0,1);//create serverObjects
  server trauma(1,1,1,1);
  server acute(1,1,1,1);
  server prompt(1,1,1,1);
  servers[0] = &triage;
  servers[1] = &trauma;
  servers[2] = &acute;
  servers[3] = &prompt;
  nextArrive = triage.newArrive();//gen first arrival time
  procArr(server[0]);//generate the first patient and generate the next arrive time
  triage.setStatus(1); //move first patient into service
  triage.setNextDep();
  nextDepart = triage.getDep();//update first departure
 
  while ( numServed < stopCond){//loop to continue simulation until the stopping condition is reached

    /*    //this was used for debugging that events, queue , amd sim time were correctly updating
    cout << "event times: Arrive: " << nextArrive << " departue: " << nextDepart << endl;
    cout << "queue size: " << triage.queueLen() << endl;
    cout << "current sim time : " << simClock << endl;
    */

    decide();
    if(nextType==0){
      
      procArr(servers[0]); //if arrive is next event process the arriveal event
      
    }
    else{
      
      procDepart(&triage); // if departure is next event process the departure event

      numServed++;
    }
    


    
  }
  
  numInQue = triage.queueLen();//store the number still left in queue at the end of simulation
  sendReport();//generate the end reports after loop has terminated
 
}
double control::genArrive(double mean){
  //RNG for arrival times
  random_device rd;
  mt19937 gen(rd());
  exponential_distribution<> d(mean);
  return (d(gen));


}

double control::genService(double mean){
  //RNG for service times
  random_device rd;
  mt19937 gen(rd());
  exponential_distribution<> d(mean);
  return (d(gen));


}

void control::decide(void){
  //decide which event type is next
  //Arrival = 0 , Departure = 1
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
  //function no longer needed moved updates to process for each event

}
void control::procArr(server* Server){
  //process a new arrival event

  (*Server).genPatient(simClock+nextArrive);//creates a mew patient and adds it to the queue with the generated arrival time
  simClock += nextArrive;//advamce the clock
  nextDepart -= nextArrive; //update depart event time
  avgQue += ((*Server).queueLen()-1)*(simClock - lastEvent);//update avgQue size counter
  intArrival += (*Server).getArr();//update inter-arrival counter
  nextArrive = (*Server).newArrive();//generate a new arrival time
  if((*Server).getStatus()==0){//if generating a new patient and queue is empty
    (*Server).setStatus(1);//set server to now busy
    (*Server).setNextDep();
    nextDepart = (*Server).getDep();//update next separture time from sentinel value
  }
  totalArrivals++;//increment the number of arrivals processed
  lastEvent = simClock;//store last event time
}
void control::procDepart(server* Server){
  //process a departure event
  simClock += nextDepart;//update sim clock
  avgQue += ((*Server).queueLen()-1)*(simClock - lastEvent);//update avg queue counter
  avgWait += (*Server).patientDep(simClock);//update avg wait counter only needs to update after a new person can move into service
  MST += (*Server).getServiceTime();//update mean service time
  (*Server).departure();//pop a patient from front of the queue
  nextArrive -= nextDepart;//update next arrive event time
  if((*Server).queueLen()>0){//if last person has just departed but ensure that next event is an arrival

    (*Server).setNextDep();
    nextDepart = (*Server).getDep();
 
  }
  else{
    nextDepart = 999999999;
    (*Server).setStatus(0);
  }

  lastEvent = simClock;//store the last event time
}
char * control::sendReport(void){
  //generate the appropriate reports

  char report[100];
  //  strcpy(report,to_string(nextArrive));
  //sprintf(report,"%f",nextArrive);
  avgWait = (avgWait/numServed);
  MST = (MST/numServed);
  intArrival = (intArrival/totalArrivals);
  avgQue = avgQue/simClock;//update the counters by dividing by the appropriate totals
  cout << fixed;
  cout << setprecision(2);
  
  cout << "Mean Inter-Arrival time: " << intArrival << endl;
  cout << "Mean Service time : " << MST << endl;
  cout << "Length of Simulated time : " << simClock << endl;
  cout << "Average Wait Time : " << avgWait <<endl;
  cout << "Average Number of Patients in the queue : " << avgQue << endl;
  cout << "Number in queue after end of simulation : " << numInQue << endl;
  //send reports to the terminal
  return report;

}
double control::findDepart(server *servers){

  for(int i = 1; i < 4; i++){



  }

} 
