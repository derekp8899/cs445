#include "patient.h"

patient::patient(){
  
  arrive = 0;
  depart= 0;
  serviceTime =0;


}
void patient::setArrive(double arrivetime, double simClock){

  arrive = arrivetime + simClock;


}

double patient::getArrive(){

  return arrive;

}
