#include "patient.h"

patient::patient(){
  
  arrive = 0;
  depart= 0;
  serviceTime =0;


}
void patient::setArrive(double simClock){

  arrive =  simClock;


}

double patient::getArrive(){

  return arrive;

}

void patient::setServiceTime(double servtime){

  serviceTime=servtime;


}

double patient::getServiceTime(){

  return serviceTime;

}

void patient::setDepart( double simClock){

  depart = serviceTime + simClock;


}

double patient::getDepart(){

  return depart;

}
