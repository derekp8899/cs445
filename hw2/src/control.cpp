#include "control.h"
#include <fstream>
#include <random>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

control::control(){
  //initialize all object variables
  lastEvent = 0;
  numServed = 0;
  simClock = 0;
  avgQue = 0;
  avgWait = 0;
  MST = 0;
  numInQue = 0;
  totalArrivals = 0;
  intArrival = 0;
  nextArrive = 0;
  nextDepart = 999999999;//to assure first event is an arrival
  nextType = 0;//event type is 0 for arrive and 1 for depart
  
}
void control::simulate(void){
  //function that controls the simulation

  ifstream input ("ed.txt");
  double in[14];
  for (int j = 0 ; j < 14; j++){
    input>>in[j];
  }
  stopCond = in[0];
  p[0]=in[4];p[1]=in[7];p[2]=in[10];p[3]=in[13];
  cout << endl <<"begin simulation" << endl;
  server **servers = (server**)malloc(sizeof(server*)*4);
  server triage(in[2],in[3],in[1],p);//create serverObjects
  server trauma(0,in[6],in[5],p);
  server acute(0,in[9],in[8],p);
  server prompt(0,in[12],in[11],p);//create all the servers
  servers[0] = &triage;
  servers[1] = &trauma;
  servers[2] = &acute; 
  servers[3] = &prompt;//populate the array of servers
  nextArrive = triage.newArrive();//gen first arrival time
  procArr(servers);//generate the first patient and generate the next arrive time
  triage.setStatus(1); //move first patient into service
  departFrom = 0;//default to depart from triage first
  for(int i = 0; i<4;i++){
    (*servers[i]).setNextDep();
    
  }
  
  nextDepart = triage.getDep();//update first departure
 
  while (simClock < stopCond ){//loop to continue simulation until the stopping condition is reached

    //this was used for debugging that events, queue , amd sim time were correctly updating
    //    cout << "event times: Arrive: " << nextArrive << " departue: " << nextDepart << endl;
    //cout << "queue size: " << triage.queueLen() << endl;
    //    cout << "current sim time : " << simClock << endl;
    

    decide();
    if(nextType==0){
      
      procArr(servers); //if arrive is next event process the arriveal event
      if(nextDepart > 9999999)
	findDepart(servers);

    }
    else{
      
      procDepart(servers); // if departure is next event process the departure event

      numServed++;
    }
    


    
  }
  
  numInQue = triage.queueLen();//store the number still left in queue at the end of simulation
  cout<< "Simulation ended at time: " << stopCond << endl;
  for(int j = 0; j < 4; j++){
    cout << "Results for server: " << j << endl;
    (*servers[j]).report(simClock);
  }

 
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
void control::procArr(server **Server){
  //process a new arrival event
  (*Server[0]).genPatient(simClock+nextArrive);//creates a mew patient and adds it to the queue with the generated arrival time
  simClock += nextArrive;
  for(int i = 0; i < 4; i++){
    (*Server[i]).updateTotals(simClock,lastEvent);
  }
  nextDepart -= nextArrive;
  for( int i =1; i < 4; i ++){
   
    (*Server[i]).updateDepartureTime(nextArrive,0); 
  }
  
  nextArrive = (*Server[0]).newArrive();//generate a new arrival time
  if((*Server[0]).getStatus()==0){//if generating a new patient and queue is empty
    (*Server[0]).setNextDep();
  }
  
  totalArrivals++;//increment the number of arrivals processed
  lastEvent = simClock;//store last event time
}
void control::procDepart(server** Servers){
  //process a departure event

  simClock += nextDepart;//update sim clock
  for(int i = 0; i < 4; i++){
    (*Servers[i]).updateTotals(simClock,lastEvent);
  }
  int lastMove = 0;
  if((*Servers[departFrom]).getNextMove()==0||departFrom!=0){

    (*Servers[departFrom]).updateWait(simClock);
    (*Servers[departFrom]).departure();//pop a patient from front of the queue
    (*Servers[departFrom]).setNextDep();
  }
  else{
    
    (*Servers[departFrom]).updateWait(simClock);
    (*Servers[departFrom]).patientDep(simClock);
    lastMove = (*Servers[departFrom]).getNextMove();
    moveServer(Servers,departFrom);
    (*Servers[departFrom]).setNextDep();
   
  }

  nextArrive -= nextDepart;//update next arrive event time
  (*Servers[departFrom]).setNextDep();
  for( int i =0; i < 4; i ++){

    if (i == 3 && (departFrom == 3 || lastMove ==3)){

      (*Servers[i]).updateDepartureTime(nextDepart,1);
      
    }
    else
      (*Servers[i]).updateDepartureTime(nextDepart,0);
  }

  findDepart(Servers);


  lastEvent = simClock;//store the last event time
}
char * control::sendReport(void){
  //generate the appropriate reports

  char report[100];
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

  for(int i = 0; i < 4; i++){
    if ((*servers[i]).getDep() <= 0){
      (*servers[i]).setNextDep();
    }
    if(i == 0 ){
      nextDepart = (*servers[i]).getDep();
      departFrom = i;
    }
    else{

      if(nextDepart > (*servers[i]).getDep()){

	nextDepart = (*servers[i]).getDep();
	departFrom = i;
      }
    }
  }
} 
void control::moveServer(server **servers, int src){//move a patient from one server to another

  int dest =  (*servers[src]).getNextMove();

  (*servers[dest]).moveIn((*servers[src]).moveOut());

}


int control::genType(double p[]){
  //RNG for service times
  random_device rd;
  mt19937 gen(rd());
  discrete_distribution<> d({p[0],p[1],p[2],p[3]});
  return (d(gen));

}
