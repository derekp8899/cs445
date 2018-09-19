#include "patient.h"

patient::patient(){//constructor for the patient objects
  //init patient variables
  
  arrive = 0;
  depart= 0;
  serviceTime =0;
  totalWait = 0;


}
void patient::setArrive(double simClock){
  //set the arrival time of the patient
  
  arrive =  simClock;

}

double patient::getArrive(){
  //return arrival time of the patient
  
  return arrive;

}

void patient::setServiceTime(double servtime){
  //set the service time of the patient
  
  serviceTime=servtime;

}

double patient::getServiceTime(){
  //return the service time of the patient
  
  return serviceTime;

}

void patient::setDepart( double simClock){
  //set the depature time of the patient
  
  depart = simClock;

}

double patient::getDepart(){
  //return the departure time of the patient
  
  return depart;

}
double patient::getWait(){

  return totalWait;

}

void patient::setWait(double wait){

  totalWait += wait;

}
