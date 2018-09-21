#include "control.h"
#include <fstream>
#include <random>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

control::control(int arrMean, int servMean){
  //initialize all object variables
  lastEvent = 0;
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
  sMean = servMean;//the means for RNG from command line
  nextArrive = 0;
  nextDepart = 9999999999999;//to assure first event is an arrival
  nextType = 0;//event type is 0 for arrive and 1 for depart
  for (int i = 0;i<4;i++){p[i]=.25;}//testingpurpose withh be from file in final version
  
}
void control::simulate(void){
  //function that controls the simulation
  //server *servers[4];
  cout << "begin simulation" << endl;
  server **servers = (server**)malloc(sizeof(server*)*4);
  server triage(aMean,sMean,1,p);//create serverObjects
  server trauma(0,1,1,p);
  server acute(0,1,1,p);
  server prompt(0,1,3,p);
  servers[0] = &triage;
  servers[1] = &trauma;
  servers[2] = &acute; 
  servers[3] = &prompt;
  nextArrive = triage.newArrive();//gen first arrival time
  procArr(servers[0]);//generate the first patient and generate the next arrive time
  triage.setStatus(1); //move first patient into service
  departFrom = 0;//default to depart from triage first
  for(int i = 0; i<4;i++){
    (*servers[i]).setNextDep();
    
  }
  
  nextDepart = triage.getDep();//update first departure
 
  while ( stopCond > simClock){//loop to continue simulation until the stopping condition is reached

    /*    //this was used for debugging that events, queue , amd sim time were correctly updating
    cout << "event times: Arrive: " << nextArrive << " departue: " << nextDepart << endl;
    cout << "queue size: " << triage.queueLen() << endl;
    cout << "current sim time : " << simClock << endl;
    */

    decide();
    if(nextType==0){
      
      procArr(servers[0]); //if arrive is next event process the arriveal event
      if(nextDepart > 999999)
	findDepart(servers);

    }
    else{
      
      procDepart(servers); // if departure is next event process the departure event

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
  cout << "comapring evernt time " << nextArrive <<" " << nextDepart <<endl; 
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
void control::procArr(server *Server){
  //process a new arrival event
  cout <<"procing an arrive" << endl;
  (*Server).genPatient(simClock+nextArrive);//creates a mew patient and adds it to the queue with the generated arrival time
  (*Server).setNextMove();//must set queue if case the queue is empty and no move is set in triage

  /*//the outputstats for hw1 different ones required for hw2
  simClock += nextArrive;//advamce the clock
  nextDepart -= nextArrive; //update depart event time
  avgQue += ((*Server).queueLen()-1)*(simClock - lastEvent);//update avgQue size counter
  intArrival += (*Server).getArr();//update inter-arrival counter
  */
  
  nextDepart -= nextArrive;
  nextArrive = (*Server).newArrive();//generate a new arrival time
  if((*Server).getStatus()==0){//if generating a new patient and queue is empty
    (*Server).setStatus(1);//set server to now busy
    (*Server).setNextDep();
    //nextDepart = (*Server).getDep();//update next departure time from sentinel value
  }
  
  totalArrivals++;//increment the number of arrivals processed
  lastEvent = simClock;//store last event time
}
void control::procDepart(server** Servers){
  //process a departure event
  cout << "procing a depart at " << departFrom << endl;
  simClock += nextDepart;//update sim clock

  /*//output stats for hw1 need to be changed for hw2
  avgQue += ((*Servers[departFrom]).queueLen()-1)*(simClock - lastEvent);//update avg queue counter
  avgWait += (*Servers[departFrom]).patientDep(simClock);//update avg wait counter only needs to update after a new person can move into service
  MST += (*Servers[departFrom]).getServiceTime();//update mean service time
  */  

if((*Servers[departFrom]).getNextMove()==0||departFrom!=0){
    (*Servers[departFrom]).departure();//pop a patient from front of the queue
    //  (*Servers[departFrom]).setNextDep();
  }
  else{
    moveServer(Servers,departFrom);
    //(*Servers[departFrom]).setNextDep();
    
  }

  nextArrive -= nextDepart;//update next arrive event time
  (*Servers[departFrom]).setNextDep();
  for( int i =0; i < 4; i ++){

    if ( i != departFrom){

      (*Servers[i]).updateDepartureTime(nextDepart);
      
    }

  }

  findDepart(Servers);

  /*
  if((*Server).queueLen()>0){//if last person has just departed but ensure that next event is an arrival

    (*Server).setNextDep();
    nextDepart = (*Server).getDep();
 
  }
  else{
    nextDepart = 999999999;
    (*Server).setStatus(0);
  }
  *///commented for now to test new departure update

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
double control::findDepart(server **servers){//check all servers for next departure time
  //cout << "finding a new depart " << endl;;
  for(int i = 0; i < 4; i++){
    (*servers[i]).setNextDep();
    if(i == 0 ){
      nextDepart = (*servers[i]).getDep();
      departFrom = i;
    }
    else if(nextDepart > (*servers[i]).getDep()){
      //  cout <<"comparing " << nextDepart << " with " << (*servers[i]).getDep() << endl;
      nextDepart = (*servers[i]).getDep();
      departFrom = i;
    }
    
  }
  //cout << "found at: " << departFrom <<" it is " << nextDepart << endl;
  

} 
void control::moveServer(server **servers, int src){//move a patient from one server to another

  int dest =  (*servers[src]).getNextMove();
  cout << "procing a move at "<< src << " to "<< dest  << endl;
  (*servers[src]).updateWait(simClock);
  (*servers[dest]).moveIn((*servers[src]).moveOut());

}


int control::genType(double p[]){
  //RNG for service times
  random_device rd;
  mt19937 gen(rd());
  discrete_distribution<> d({p[0],p[1],p[2],p[3]});
  return (d(gen));

}
